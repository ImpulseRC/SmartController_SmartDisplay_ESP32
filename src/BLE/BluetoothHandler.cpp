#include "NimBLEBeacon.h"
#include "NimBLEEddystoneTLM.h"
#include "NimBLEEddystoneURL.h"
#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>

#include "BluetoothHandler.h"
#include "OTA/OTA_wifi.h"
#include "SharedData.h"
#include "debug.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "main.h"
#include "tools/buffer.h"
#include "Settings.h"
#include <WiFi.h>

// See the following for generating UUIDs: https://www.uuidgenerator.net/
#define SERVICE_MAIN_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SERVICE_FIRMWARE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914c"
#define SERVICE_SETTINGS_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914d"

#define MEASUREMENTS_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a0"
#define FIRMWARE_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a3"
#define COMMANDS_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a5"
#define BTLOCK_STATUS_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a6"
#define CALIB_ORDER_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ad"
#define SWITCH_TO_OTA_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ae"
#define LOGS_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26af"
#define FAST_UPDATE_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26b0"
#define DISTANCE_RST_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26b5"
#define ADC_DAC_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26b6"
#define SETTINGS_ACTION_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26fe"
#define SETTINGS_DATA_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26ff"

#define BLE_MTU 23

#define MAX_BEACON_INVISIBLE_COUNT 1

#define BEACON_SCAN_PERIOD_IN_SECONDS 10

NimBLEScan *BluetoothHandler::pBLEScan;
NimBLEServer *BluetoothHandler::pServer;
NimBLESecurity *BluetoothHandler::pSecurity;

// Main services
NimBLECharacteristic *BluetoothHandler::pCharacteristicMeasurements;
NimBLECharacteristic *BluetoothHandler::pCharacteristicBtlockStatus;
NimBLECharacteristic *BluetoothHandler::pCharacteristicCalibOrder;
NimBLECharacteristic *BluetoothHandler::pCharacteristicOtaSwitch;
NimBLECharacteristic *BluetoothHandler::pCharacteristicLogs;
NimBLECharacteristic *BluetoothHandler::pCharacteristicDistanceRst;
NimBLECharacteristic *BluetoothHandler::pCharacteristicCommands;
NimBLECharacteristic *BluetoothHandler::pCharacteristicAdcDac;

// Settings services
NimBLECharacteristic *BluetoothHandler::pCharacteristicSettingsGen;
NimBLECharacteristic *BluetoothHandler::pCharacteristicSettingsAction;

// firmware services
NimBLECharacteristic *BluetoothHandler::pCharacteristicFirmware;

BleStatus BluetoothHandler::deviceStatus;
BleStatus BluetoothHandler::oldDeviceStatus;

Settings *BluetoothHandler::settings;
SharedData *BluetoothHandler::shrd;

uint32_t bleBeaconInvisibleCount1 = 0;
uint32_t bleBeaconInvisibleCount2 = 0;
uint32_t errCounter = 0;

String firmwareString;
bool bleScanActive = false;

BluetoothHandler::BluetoothHandler()
{
}

void BluetoothHandler::init()
{
    class BLEServerCallback : public NimBLEServerCallbacks
    {
        void onConnect(BLEServer *pServer)
        {
            Serial.println("BLH - BLE connecting");

            deviceStatus = BLE_STATUS_CONNECTED_AND_AUTHENTIFYING;

            if (shrd->bleLockForced == 0)
            {
                if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Smartphone_connected)
                {
                    shrd->isLocked = false;
                    Serial.println("BLH -  ==> device connected ==> UNLOCK decision");
                    Serial.println("BLH - -------------------------------------");
                }
                if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Smartphone_connected_or_beacon_visible)
                {
                    shrd->isLocked = false;
                    Serial.println("BLH -  ==> device connected ==> UNLOCK decision");
                    Serial.println("BLH - -------------------------------------");
                }
            }
        };

        void onDisconnect(BLEServer *pServer)
        {
            Serial.println("BLH - BLE disconnected");
            deviceStatus = BLE_STATUS_DISCONNECTED;

            if (shrd->bleLockForced == 0)
            {
                if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Smartphone_connected)
                {
                    shrd->isLocked = true;
                    Serial.println("BLH -  ==> device disconnected ==> LOCK decision");
                    Serial.println("BLH - -------------------------------------");
                }
                if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Smartphone_connected_or_beacon_visible)
                {
                    if ((!shrd->bleBeaconVisible1) && (!shrd->bleBeaconVisible2))
                    {
                        shrd->isLocked = true;
                        Serial.println(" ==> device disconnected / Beacon not visible ==> LOCK decision");
                        Serial.println("-------------------------------------");
                    }
                }
            }
        }
    };

    class BLEAdvertisedDeviceCallback : public BLEAdvertisedDeviceCallbacks
    {
        void onResult(BLEAdvertisedDevice *advertisedDevice)
        {
            Serial.print("BLH - BLE device name: ");
            Serial.println(advertisedDevice->getName().c_str());
            Serial.println("");
        }
    };

    class BLESecurityCallback : public NimBLESecurityCallbacks
    {

        bool onConfirmPIN(uint32_t pin)
        {
            return false;
        }

        uint32_t onPassKeyRequest()
        {
            Serial.print("BLH - onPassKeyRequest : ");
            uint32_t pinCode;
            pinCode = settings->get_Ble_pin_code();
            Serial.println(pinCode);
            return pinCode;
        }

        void onPassKeyNotify(uint32_t pass_key)
        {
            Serial.print("BLH - onPassKeyNotify : ");
            Serial.println(pass_key);
        }

        bool onSecurityRequest()
        {
            Serial.println("BLH - onSecurityRequest");
            return true;
        }

        void onAuthenticationComplete(esp_ble_auth_cmpl_t cmpl)
        {
            if (cmpl.success)
            {
                uint16_t length;
                esp_ble_gap_get_whitelist_size(&length);
                Serial.println("BLH - onAuthenticationComplete cmpl : success");
                deviceStatus = BLE_STATUS_CONNECTED_AND_AUTHENTIFIED;

                // notify commands feedback
                // notify of current modes / values (for value not uptate by LCD)
                notifyCommandsFeedback();
            }
            else
            {
                Serial.print("BLH - onAuthenticationComplete cmpl : hummm ... failed / reason : ");
                Serial.println(cmpl.fail_reason);

                deviceStatus = BLE_STATUS_DISCONNECTED;
            }
        }

        void onAuthenticationComplete(ble_gap_conn_desc *desc)
        {

            if (!desc->sec_state.encrypted)
            {
                Serial.println("BLH - onAuthenticationComplete desc : Encrypt connection failed - disconnecting");
                /** Find the client with the connection handle provided in desc */
                NimBLEDevice::getClientByID(desc->conn_handle)->disconnect();
                deviceStatus = BLE_STATUS_DISCONNECTED;
            }
            else
            {
                Serial.println("BLH - onAuthenticationComplete desc : success");
                deviceStatus = BLE_STATUS_CONNECTED_AND_AUTHENTIFIED;
            }
        }
    };

    class BLECharacteristicCallback : public NimBLECharacteristicCallbacks
    {
        void onWrite(NimBLECharacteristic *pCharacteristic)
        {

            //const char *uuid = pCharacteristic->getUUID().toString().data();
            //Serial.println("onWrite : " + (String)(uuid));

            if (pCharacteristic->getUUID().toString() == CALIB_ORDER_CHARACTERISTIC_UUID)
            {
                std::string rxValue = pCharacteristic->getValue();

                int valueInt;
                memcpy(&valueInt, &rxValue[1], 4);

                //BatMaxVoltage(1),
                if (rxValue[0] == 1)
                {
                    shrd->batteryMaxVoltageCalibUser = valueInt / 10.0;
                    shrd->batteryMaxVoltageCalibRaw = shrd->voltageRawFilterMean;
                    saveBatteryCalib();

                    Serial.print("BLH - batteryMaxVoltageCalibUser : ");
                    Serial.print(shrd->batteryMaxVoltageCalibUser);
                    Serial.print(" / batteryMaxVoltageCalibRaw : ");
                    Serial.println(shrd->batteryMaxVoltageCalibRaw);
                }
                //BatMinVoltage(2),
                else if (rxValue[0] == 2)
                {
                    shrd->batteryMinVoltageCalibUser = valueInt / 10.0;
                    shrd->batteryMinVoltageCalibRaw = shrd->voltageRawFilterMean;
                    saveBatteryCalib();

                    Serial.print("BLH - batteryMinVoltageCalibUser : ");
                    Serial.print(shrd->batteryMinVoltageCalibUser);
                    Serial.print(" / batteryMinVoltageCalibRaw : ");
                    Serial.println(shrd->batteryMinVoltageCalibRaw);
                }
                //CurrentZero(3);
                else if (rxValue[0] == 3)
                {
                    //shrd->currentCalibOrder = valueInt;
                }

                char print_buffer[500];
                sprintf(print_buffer, "type %d / %02x / %02x / %02x / %02x / %02x / value %d", rxValue[0], rxValue[1], rxValue[2], rxValue[3], rxValue[4], rxValue[5], valueInt);
                Serial.print("BLH - Write calib order : ");
                Serial.println(print_buffer);
            }
            else if (pCharacteristic->getUUID().toString() == BTLOCK_STATUS_CHARACTERISTIC_UUID)
            {
                std::string rxValue = pCharacteristic->getValue();
                shrd->bleLockForced = rxValue[3];

                char print_buffer[500];
                sprintf(print_buffer, "%02x", shrd->bleLockForced);
                Serial.print("BLH - Write bleLockForced : ");
                Serial.println(print_buffer);

                shrd->isLocked = shrd->bleLockForced;

                notifyBleLockAndErrors();
                saveBleLockForced();
            }
            else if (pCharacteristic->getUUID().toString() == SWITCH_TO_OTA_CHARACTERISTIC_UUID)
            {
                Serial.println("BLH - Write SWITCH_TO_OTA_CHARACTERISTIC_UUID");

                switchToOta((uint8_t *)pCharacteristic->getValue().data());
            }
            else
                /* if (pCharacteristic->getUUID().toString() == FAST_UPDATE_CHARACTERISTIC_UUID)
            {
                Serial.println("Write FAST_UPDATE_CHARACTERISTIC_UUID");

                std::string rxValue = pCharacteristic->getValue();
                fastUpdate = rxValue[0];

                Serial.print("BLH - Fast update = ");
                Serial.println(fastUpdate);
            }
            else
            */
                if (pCharacteristic->getUUID().toString() == DISTANCE_RST_CHARACTERISTIC_UUID)
            {
                shrd->distanceTrip = 0;
            }
            else if (pCharacteristic->getUUID().toString() == COMMANDS_CHARACTERISTIC_UUID)
            {
                Serial.println("BLH - Write : COMMANDS_CHARACTERISTIC_UUID");
                getCommandsDataPacket((uint8_t *)pCharacteristic->getValue().data());

                notifyCommandsFeedback();
            }
            else if (pCharacteristic->getUUID().toString() == SETTINGS_DATA_CHARACTERISTIC_UUID)
            {
                std::string rxValue = pCharacteristic->getValue();
                /*
                Serial.println("BLH - Write : SETTINGS_DATA_CHARACTERISTIC_UUID");
                uint8_t rxInt[20];
                for (int i = 0; i < rxValue.length(); i++)
                {
                    char print_buffer[5];
                    rxInt[i] = rxValue[i];
                    sprintf(print_buffer, "%02x ", rxValue[i]);
                    Serial.print(print_buffer);
                }

                Serial.println();
                */
                settings->unpack_setting_packet((uint8_t *)pCharacteristic->getValue().data(), rxValue.length());
            }
            else if (pCharacteristic->getUUID().toString() == SETTINGS_ACTION_CHARACTERISTIC_UUID)
            {
                // Serial.println("BLH - Write : SETTINGS_ACTION_CHARACTERISTIC_UUID");
                std::string rxValue = pCharacteristic->getValue();

                if (rxValue[0] == 0)
                {

                    //Serial.println("BLH - request");
                    sendSettingValueDataPacket((uint8_t *)pCharacteristic->getValue().data());
                }
                else if (rxValue[0] == 1)
                {
                    settings->save();
                    Serial.println("BLH - save");
                    
                    // dirty patch
                    convertBrakePressure();

                    startBleScan();
                    Serial.println("BLH - startBleScan");
                }
            }
            else
            {
                const String uuid = pCharacteristic->getUUID().toString().c_str();
                Serial.println("BLH - Write : unknown " + uuid);
            }
        }

        void onRead(NimBLECharacteristic *pCharacteristic)
        {

            const String uuid = pCharacteristic->getUUID().toString().c_str();
            Serial.println("BLH - onRead : " + uuid);

            if (pCharacteristic->getUUID().toString() == FIRMWARE_CHARACTERISTIC_UUID)
            {

                pCharacteristicFirmware->setValue((uint8_t *)firmwareString.c_str(), firmwareString.length());
                Serial.print("BLH - Read firmware : ");
                Serial.println(firmwareString.c_str());
            }
            else if (pCharacteristic->getUUID().toString() == MEASUREMENTS_CHARACTERISTIC_UUID)
            {
                //int nb_bytes =
                setMeasurementsDataPacket();
                /*
                Serial.print("BLH - Read measurement : nb bytes");
                Serial.println(nb_bytes);
                */
            }
            else if (pCharacteristic->getUUID().toString() == COMMANDS_CHARACTERISTIC_UUID)
            {
                int nb_bytes = setCommandsDataPacket();
                Serial.print("BLH - Read commands : nb bytes = ");
                Serial.println(nb_bytes);
            }
            else if (pCharacteristic->getUUID().toString() == BTLOCK_STATUS_CHARACTERISTIC_UUID)
            {

                notifyBleLockAndErrors();

                char print_buffer[500];
                sprintf(print_buffer, "%02x", shrd->isLocked);
                Serial.print("BLH - Read bleLock : ");
                Serial.println(print_buffer);
            }
            else if (pCharacteristic->getUUID().toString() == SETTINGS_DATA_CHARACTERISTIC_UUID)
            {
                Serial.print("BLH - Read SETTINGS_DATA_CHARACTERISTIC_UUID ==> nothing to do");
            }
            else if (pCharacteristic->getUUID().toString() == ADC_DAC_CHARACTERISTIC_UUID)
            {
                Serial.println("BLH - Read : ADC_DAC_CHARACTERISTIC_UUID");

                int nb_bytes = setAdcDacDataPacket(pCharacteristic);
                Serial.print("BLH - Read adcdac : nb bytes = ");
                Serial.println(nb_bytes);
            }
            else
            {
                const String uuid = pCharacteristic->getUUID().toString().c_str();
                Serial.println("BLH - Read : unknown " + uuid);
            }
        }

        void onStatus(BLECharacteristic *pCharacteristic, Status s, uint32_t code)
        {
            //Serial.printf("BLH - onStatus: status = %d / code = %d / errCounter = %d\n", s, code, errCounter);

            if (code == 0xffffffff)
            {
                Serial.printf("BLH - >>>> onStatus: status = %d / code = %d / errCounter = %d\n", s, code, errCounter);
                errCounter++;

                // reset connexion if too many errors
                if (errCounter > 1000)
                {
                    // TODO !!!!!!!!!!!!!
                    //pServer->disconnect(0, 0);
                    //desc->conn_handle
                    //std::list<NimBLEClient> list = NimBLEDevice::getClientList();
                    uint8_t clientId = 0;

                    // TODO : fix this with real client ID
                    NimBLEDevice::getClientByID(clientId)->disconnect();
                    errCounter = 0;
                }
            }
        }
    };

    Serial.println("BLH - init");

    // Set firmware string
    String firmwareVersion = (String)FIRMWARE_VERSION;
    String firmwareType = (String)FIRMWARE_TYPE;
    firmwareType.replace("smartcontroller_", "sc_");
    firmwareType.replace("smartdisplay_", "sd_");
    firmwareString = firmwareType + " " + firmwareVersion;

    // Create the BLE Device
    uint8_t base_mac_addr[6] = {0};
    char bleName[20];
    esp_efuse_mac_get_default(base_mac_addr);
    sprintf(bleName, "Smart-%x",
            base_mac_addr[5]);
    Serial.println("BLH - name : " + (String)bleName);

    NimBLEDevice::init(bleName);

    NimBLEDevice::setMTU(BLE_MTU);
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    /////
    NimBLEDevice::setSecurityAuth(true, true, true);
    NimBLEDevice::setSecurityPasskey(147258);
    NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);
    //NimBLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
    NimBLEDevice::setSecurityCallbacks(new BLESecurityCallback());
    /////

    int mtu = BLEDevice::getMTU();
    Serial.print("BLH - MTU : ");
    Serial.println(mtu);

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new BLEServerCallback());

    // Create the BLE Service
    BLEService *pServiceMain = pServer->createService(BLEUUID(SERVICE_MAIN_UUID), 40);
    BLEService *pServiceFirmware = pServer->createService(BLEUUID(SERVICE_FIRMWARE_UUID), 20);
    BLEService *pServiceSettings = pServer->createService(BLEUUID(SERVICE_SETTINGS_UUID), 20);

    // Create a BLE Characteristic

    //-------------------
    // services main

    pCharacteristicMeasurements = pServiceMain->createCharacteristic(
        MEASUREMENTS_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::READ_AUTHEN);

    pCharacteristicBtlockStatus = pServiceMain->createCharacteristic(
        BTLOCK_STATUS_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN |
            NIMBLE_PROPERTY::READ_AUTHEN);

    pCharacteristicCalibOrder = pServiceMain->createCharacteristic(
        CALIB_ORDER_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    pCharacteristicOtaSwitch = pServiceMain->createCharacteristic(
        SWITCH_TO_OTA_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    pCharacteristicLogs = pServiceMain->createCharacteristic(
        LOGS_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    pCharacteristicDistanceRst = pServiceMain->createCharacteristic(
        DISTANCE_RST_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    pCharacteristicCommands = pServiceMain->createCharacteristic(
        COMMANDS_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::READ |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN |
            NIMBLE_PROPERTY::READ_AUTHEN);

    pCharacteristicAdcDac = pServiceMain->createCharacteristic(
        ADC_DAC_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN |
            NIMBLE_PROPERTY::READ_AUTHEN);

    //-------------------
    // services firmware

    pCharacteristicFirmware = pServiceFirmware->createCharacteristic(
        FIRMWARE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ);

    //-------------------
    // services settings

    pCharacteristicSettingsGen = pServiceSettings->createCharacteristic(
        SETTINGS_DATA_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    pCharacteristicSettingsAction = pServiceSettings->createCharacteristic(
        SETTINGS_ACTION_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY |
            NIMBLE_PROPERTY::WRITE_NR |
            NIMBLE_PROPERTY::WRITE_AUTHEN);

    //////////////
    pCharacteristicMeasurements->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicBtlockStatus->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicCalibOrder->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicOtaSwitch->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicLogs->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicDistanceRst->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicCommands->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicAdcDac->setCallbacks(new BLECharacteristicCallback());

    pCharacteristicSettingsGen->setCallbacks(new BLECharacteristicCallback());
    pCharacteristicSettingsAction->setCallbacks(new BLECharacteristicCallback());

    pCharacteristicFirmware->setCallbacks(new BLECharacteristicCallback());

    // Start the service
    pServiceMain->start();
    pServiceFirmware->start();
    pServiceSettings->start();

    deviceStatus = BLE_STATUS_DISCONNECTED;

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_MAIN_UUID);
    pAdvertising->addServiceUUID(SERVICE_FIRMWARE_UUID);
    pAdvertising->addServiceUUID(SERVICE_SETTINGS_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0); // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");

    // Security
    pSecurity = new BLESecurity();
    Serial.print("BLH - pin code : ");
    uint32_t pinCode = settings->get_Ble_pin_code();
    Serial.println(pinCode);
    pSecurity->setStaticPIN(pinCode);
    pSecurity->setInitEncryptionKey(ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK);
    pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

    // Scan if configuration is ok
    startBleScan();

    Serial.println("BLH - init end");
}

bool BluetoothHandler::isBleScanActive()
{
    return bleScanActive;
}

void BluetoothHandler::startBleScan()
{

    // start scan only if different from dummy mac address
    if ((!bleScanActive) && ((settings->get_Ble_beacon_mac_address1() != "aa:bb:cc:dd:ee:ff") || (settings->get_Ble_beacon_mac_address2() != "aa:bb:cc:dd:ee:ff")))
    {
        bleScanActive = true;

        // Start scanning
        pBLEScan = BLEDevice::getScan(); //create new scan
        pBLEScan->setActiveScan(true);   //active scan uses more power, but get results faster
        pBLEScan->setInterval(100);
        pBLEScan->setWindow(50); // less or equal setInterval value
        pBLEScan->start(BEACON_SCAN_PERIOD_IN_SECONDS, &bleOnScanResults, false);
    }
    else
    {
        bleScanActive = false;
    }
}

void BluetoothHandler::bleOnScanResults(NimBLEScanResults scanResults)
{

#if DEBUG_BLE_DISPLAY_SCAN
    Serial.print("BLH - BLE Scan Device found: ");
    Serial.println(scanResults.getCount());
#endif

    bool newBleBeaconVisible1 = false;
    bool newBleBeaconVisible2 = false;
    int8_t RSSI = -1;
    bool beaconFound1 = false;
    bool beaconFound2 = false;

    // format searched addresses
    String addressBeaconSettings1 = settings->get_Ble_beacon_mac_address1();
    addressBeaconSettings1.toLowerCase();
    addressBeaconSettings1 = addressBeaconSettings1.substring(0, 17);

    String addressBeaconSettings2 = settings->get_Ble_beacon_mac_address2();
    addressBeaconSettings2.toLowerCase();
    addressBeaconSettings2 = addressBeaconSettings2.substring(0, 17);

#if DEBUG_BLE_DISPLAY_SCAN
        Serial.printf("BLH - scan search for %s or %s\n",addressBeaconSettings1.c_str(), addressBeaconSettings2.c_str());
#endif
    for (int i = 0; i < scanResults.getCount(); i++)
    {
        String name = scanResults.getDevice(i).getName().c_str();
        RSSI = scanResults.getDevice(i).getRSSI();
        std::string address = scanResults.getDevice(i).getAddress().toString();
        String addressStr = address.c_str();

#if DEBUG_BLE_DISPLAY_SCAN
        Serial.printf("BLH - scan address : %s  / name : %s / RSSI : %d\n", addressStr.c_str(), name.c_str(), RSSI);
#endif

        if (addressBeaconSettings1.equals(addressStr))
        {
            beaconFound1 = true;
            shrd->beaconRSSI1 = RSSI;

#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon1 found  / RSSI = %d / RSSI required = %d / address = %s", shrd->beaconRSSI2, settings->get_Ble_beacon_range(), addressStr.c_str());
#endif

            if (shrd->beaconRSSI1 > settings->get_Ble_beacon_range())
            {
                bleBeaconInvisibleCount1 = 0;
                newBleBeaconVisible1 = true;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.printf(" ==> range is OK\n");
#endif
            }
            else
            {
#if DEBUG_BLE_DISPLAY_SCAN
                Serial.printf(" ==> range is KO\n");
#endif
            }
        }

        if (addressBeaconSettings2.equals(addressStr))
        {
            beaconFound2 = true;
            shrd->beaconRSSI2 = RSSI;

#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon2 found  / RSSI = %d / RSSI required = %d / address = %s", shrd->beaconRSSI2, settings->get_Ble_beacon_range(), addressStr.c_str());
#endif

            if (shrd->beaconRSSI2 > settings->get_Ble_beacon_range())
            {
                bleBeaconInvisibleCount2 = 0;
                newBleBeaconVisible2 = true;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.printf(" ==> range is OK\n");
#endif
            }
            else
            {
#if DEBUG_BLE_DISPLAY_SCAN
                Serial.printf(" ==> range is KO\n");
#endif
            }
        }
    }

    // reset RSSI
    if (!beaconFound1)
    {
        shrd->beaconRSSI1 = -1;
    }
    if (!beaconFound2)
    {
        shrd->beaconRSSI2 = -1;
    }

    // count beacon invible times
    if (!newBleBeaconVisible1)
    {
        bleBeaconInvisibleCount1++;
        if (bleBeaconInvisibleCount1 >= MAX_BEACON_INVISIBLE_COUNT)
        {
            newBleBeaconVisible1 = false;
#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon1 not found  / bleBeaconInvisibleCount1 = %d / newBleBeaconVisible1 = %d\n", bleBeaconInvisibleCount1, newBleBeaconVisible1);
#endif
        }
        else
        {
            newBleBeaconVisible1 = true;
#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon1 not found  / bleBeaconInvisibleCount1 = %d / newBleBeaconVisible1 = %d ... until lock\n", bleBeaconInvisibleCount1, newBleBeaconVisible1);
#endif
        }
    }

    // count beacon invible times
    if (!newBleBeaconVisible2)
    {
        bleBeaconInvisibleCount2++;
        if (bleBeaconInvisibleCount2 >= MAX_BEACON_INVISIBLE_COUNT)
        {
            newBleBeaconVisible2 = false;
#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon2 not found  / bleBeaconInvisibleCount2 = %d / newBleBeaconVisible2 = %d\n", bleBeaconInvisibleCount2, newBleBeaconVisible2);
#endif
        }
        else
        {
            newBleBeaconVisible2 = true;
#if DEBUG_BLE_DISPLAY_SCAN
            Serial.printf("BLH -  ==> Beacon2 not found  / bleBeaconInvisibleCount2 = %d / newBleBeaconVisible2 = %d ... until lock\n", bleBeaconInvisibleCount2, newBleBeaconVisible2);
#endif
        }
    }

    // store beacon status
    shrd->bleBeaconVisible1 = newBleBeaconVisible1;
    shrd->bleBeaconVisible2 = newBleBeaconVisible2;

#if DEBUG_BLE_DISPLAY_SCAN
    Serial.printf("BLH - bleLockForced = %d / Bluetooth_lock_mode = %d / bleBeaconVisible1 = %d / bleBeaconVisible2 = %d / deviceStatus = %d \n",
                  shrd->bleLockForced, settings->get_Bluetooth_lock_mode(), shrd->bleBeaconVisible1, shrd->bleBeaconVisible2, deviceStatus);
#endif

    if (shrd->bleLockForced <= 0)
    {

        if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Smartphone_connected_or_beacon_visible)
        {
            if ((!shrd->bleBeaconVisible1) && (!shrd->bleBeaconVisible2) && (deviceStatus != BLE_STATUS_DISCONNECTED))
            {
                shrd->isLocked = 1;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.println(" ==> Beacon not visible // smartphone not connected ==> LOCK decision");
                Serial.println("-------------------------------------");
                Serial.println();
#endif
            }
            else if (((shrd->bleBeaconVisible1) || (shrd->bleBeaconVisible2)) && (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED))
            {
                shrd->isLocked = 0;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.println(" ==> Beacon visible // smartphone connected ==> UNLOCK decision");
                Serial.println("-------------------------------------");
                Serial.println();
#endif
            }
            else
            {
                Serial.println(" ==> Beacon visible // smartphone connected ==> .... unchecked condition");
                Serial.println("-------------------------------------");
                Serial.println();
            }
        }
        if (settings->get_Bluetooth_lock_mode() == settings->LIST_Bluetooth_lock_mode_Beacon_visible)
        {
            if ((!shrd->bleBeaconVisible1) && (!shrd->bleBeaconVisible2))
            {
                shrd->isLocked = 1;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.println(" ==> Beacons not visible ==> LOCK decision");
                Serial.println("-------------------------------------");
#endif
            }
            else if ((shrd->bleBeaconVisible1) || (shrd->bleBeaconVisible2))
            {
                shrd->isLocked = 0;

#if DEBUG_BLE_DISPLAY_SCAN
                Serial.println(" ==> At least one beacon visible ==> UNLOCK decision");
                Serial.println("-------------------------------------");
#endif
            }
        }
    }

    notifyBleLockAndErrors();

    // launch new scan
    pBLEScan->start(BEACON_SCAN_PERIOD_IN_SECONDS, &bleOnScanResults, false);

}

uint8_t BluetoothHandler::setMeasurementsDataPacket()
{
    //Serial.println("setMeasurementsDataPacket");

    int32_t ind = 0;

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {

        uint8_t txValue[20];

        int32_t power = ((shrd->currentActual / 1000.0) * (shrd->voltageActual / 1000.0)); // / 1000000;
        power = constrain(power, 0, 65535);

        buffer_append_uint8(txValue, shrd->speedCurrent, &ind);
        buffer_append_uint16_inv(txValue, (shrd->voltageFilterMean / 100.0), &ind);
        buffer_append_int16_inv(txValue, (shrd->currentActual / 100), &ind);
        buffer_append_int16_inv(txValue, power, &ind);
        buffer_append_int16_inv(txValue, (shrd->currentTemperature * 10.0), &ind);
        buffer_append_uint16_inv(txValue, (shrd->currentHumidity * 10.0), &ind);
        buffer_append_uint16_inv(txValue, (shrd->distanceTrip / 100), &ind);
        buffer_append_uint32_inv(txValue, (shrd->distanceOdo), &ind);
        buffer_append_uint8(txValue, (shrd->batteryLevel), &ind);
        buffer_append_uint8(txValue, (shrd->autonomyLeft), &ind);

        pCharacteristicMeasurements->setValue((uint8_t *)&txValue[0], ind);

        //Serial.println("setMeasurementsDataPacket : power " + (String)power);
    }
    return ind;
}

uint8_t BluetoothHandler::setCommandsDataPacket()
{
#if DEBUG_BLE_DISPLAY_COMMANDSFEEDBACK
    Serial.println("setCommandsDataPacket");
#endif

    int32_t ind = 0;

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        uint8_t txValue[20];

        buffer_append_uint8(txValue, shrd->modeOrder, &ind);
        buffer_append_uint8(txValue, shrd->speedLimiter, &ind);
        buffer_append_uint8(txValue, shrd->ecoOrder, &ind);
        buffer_append_uint8(txValue, shrd->accelOrder, &ind);
        buffer_append_uint8(txValue, shrd->auxOrder, &ind);
        buffer_append_uint8(txValue, shrd->brakeSentOrder, &ind);
        buffer_append_uint8(txValue, shrd->brakeSentOrderFromBLE, &ind);
        buffer_append_uint8(txValue, shrd->brakePressedStatus, &ind);
        buffer_append_uint8(txValue, shrd->brakeFordidenHighVoltage, &ind);
        buffer_append_uint8(txValue, shrd->fastUpdate, &ind);

        //#if (MINIMO_SIMULATED_DISPLAY == 0)
        // copy values
        shrd->brakeSentOrderFromBLE = shrd->brakeSentOrder;
        //#endif

        pCharacteristicCommands->setValue((uint8_t *)&txValue[0], ind);

#if DEBUG_BLE_DISPLAY_COMMANDSFEEDBACK
        buffer_display("setCommandsDataPacket : ", txValue, ind);
#endif
    }
    else
    {
        Serial.println("deviceStatus = " + (String)deviceStatus);
    }
    return ind;
}

uint8_t BluetoothHandler::setAdcDacDataPacket(NimBLECharacteristic *pCharacteristic)
{
#if DEBUG_BLE_DISPLAY_ADCDAC
    Serial.println("setAdcDacDataPacket");
#endif

    int32_t ind = 0;

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        uint8_t txValue[20];

        buffer_append_uint16_inv(txValue, shrd->throttleAnalogValue, &ind);
        buffer_append_uint8(txValue, shrd->throttlePercent, &ind);
        buffer_append_uint16_inv(txValue, shrd->brakeAnalogValue, &ind);
        buffer_append_uint8(txValue, shrd->brakePercent, &ind);
        buffer_append_uint16_inv(txValue, shrd->dacOutput, &ind);

        pCharacteristicAdcDac->setValue((uint8_t *)&txValue[0], ind);

#if DEBUG_BLE_DISPLAY_ADCDAC
        buffer_display("setAdcDacDataPacket : ", txValue, ind);
#endif
    }
    else
    {
        Serial.println("deviceStatus = " + (String)deviceStatus);
    }
    return ind;
}

void BluetoothHandler::sendSettingValueDataPacket(uint8_t *rxValue)
{
    int32_t indRcv = 0;
    uint8_t bufferSend[21];
    uint8_t *bufferSendPtr = bufferSend;
    uint8_t packetNumber = 0;

    buffer_get_uint8(rxValue, &indRcv); // skip action
    uint16_t settingId = buffer_get_uint16(rxValue, &indRcv);

    bool hasNextPacketToSend = true;
    while (hasNextPacketToSend)
    {
        int32_t sizeToSend = 0;
        memset(bufferSend, 0, sizeof(bufferSend));
        hasNextPacketToSend = settings->pack_setting_packet(settingId, packetNumber, bufferSendPtr, &sizeToSend);
        pCharacteristicSettingsGen->setValue((uint8_t *)bufferSendPtr, sizeToSend);
        pCharacteristicSettingsGen->notify();
        packetNumber++;
    }

    //Serial.println("BLH - sendSettingValueDataPacket settingId : " + (String)settingId + " / packetNumber" + (String)packetNumber + " / sizeToSend = " + (String)sizeToSend);
}

void BluetoothHandler::switchToOta(uint8_t *rxValue)
{
    int32_t ind = 0;
    shrd->inOtaMode = buffer_get_uint8(rxValue, &ind); // Enable http OTA mode
    shrd->inOtaModeVersion = buffer_get_uint16(rxValue, &ind);
    Serial.println("switchToOta : inOtaMode = " + (String)shrd->inOtaMode + " / inOtaModeVersion = " + (String)shrd->inOtaModeVersion);
}

void BluetoothHandler::getCommandsDataPacket(uint8_t *rxValue)
{
#if DEBUG_BLE_DISPLAY_COMMANDSFEEDBACK
    Serial.println("getCommandsDataPacket");
#endif

    int32_t ind = 0;

    shrd->modeOrder = buffer_get_uint8(rxValue, &ind);
    shrd->speedLimiter = buffer_get_uint8(rxValue, &ind);
    shrd->ecoOrder = buffer_get_uint8(rxValue, &ind);
    shrd->accelOrder = buffer_get_uint8(rxValue, &ind);
    shrd->auxOrder = buffer_get_uint8(rxValue, &ind);
    shrd->brakeSentOrder = buffer_get_uint8(rxValue, &ind);
    shrd->brakeSentOrderFromBLE = buffer_get_uint8(rxValue, &ind);
    buffer_get_uint8(rxValue, &ind); /*shrd->brakePressedStatus*/
    buffer_get_uint8(rxValue, &ind); /*shrd->brakeFordidenHighVoltage*/
    shrd->fastUpdate = buffer_get_uint8(rxValue, &ind);

#if DEBUG_BLE_DISPLAY_COMMANDSFEEDBACK
    Serial.println("getCommandsDataPacket - modeOrder = " + (String)shrd->modeOrder);
    Serial.println("getCommandsDataPacket - speedLimiter = " + (String)shrd->speedLimiter);
    Serial.println("getCommandsDataPacket - ecoOrder = " + (String)shrd->ecoOrder);
    buffer_display("getCommandsDataPacket : ", rxValue, ind);
#endif
}

void BluetoothHandler::notifyCommandsFeedback()
{
#if DEBUG_BLE_DISPLAY_COMMANDSFEEDBACK
    Serial.println("notifyCommandsFeedback");
#endif

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        // notify of new log
        setCommandsDataPacket();
        pCharacteristicCommands->notify();
    }
}

void BluetoothHandler::notifySettingsChanged()
{
#if DEBUG_BLE_DISPLAY_SETTINGSCHANGED
    Serial.println("notifySettingsChanged");
#endif

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        // notify of settings action
        uint8_t txValue[1];
        int ind = 0;
        buffer_append_uint8(txValue, 1, &ind);
        pCharacteristicSettingsAction->setValue((uint8_t *)&txValue[0], ind);

        pCharacteristicSettingsAction->notify();
    }
}

void BluetoothHandler::notifyMeasurements()
{
    // Serial.println("notifyMeasurements");

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        // notify of new log
        setMeasurementsDataPacket();
        pCharacteristicMeasurements->notify();
    }
}

void BluetoothHandler::notifyBleLogs(char *txt)
{

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        char bufferSend[21];

        /*
        memcpy(fullStringBufferWithEnd, txt, strlen(txt));
        fullStringBufferWithEnd[strlen(txt)] = '\0';
*/

        bufferSend[20] = '\0';
        int size = 0;

        // notify of new log
        int nbChunks = ceil((strlen(txt) + 1) / 20.0);
        int lastChunkSize = (strlen(txt) + 1) % 20;

        //Serial.printf("BLH - notifyBleLogs : nbChunks = %d / lastChunkSize = %d\n", nbChunks, lastChunkSize);

        for (int i = 0; i < nbChunks; i++)
        {
            //memset(txt, 0, 20);
            if ((i == nbChunks - 1) && (lastChunkSize > 0))
            {
                size = lastChunkSize;
                // bufferSend[lastChunkSize] = '\0';
            }
            else
            {
                size = 20;
            }

            //Serial.printf("BLH - notifyBleLogs : size = %d / i = %d\n", size, i);

            memcpy(&bufferSend, &txt[i * 20], size);

            //Serial.printf("BLH - notifyBleLogs : chunk = %s\n", bufferSend);

            pCharacteristicLogs->setValue((uint8_t *)bufferSend, size);
            pCharacteristicLogs->notify();
        }
    }
}

void BluetoothHandler::notifyBleLockAndErrors()
{

    //Serial.println("notifyBleLock");

    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        byte value[7];
        value[0] = shrd->isLocked;
        value[1] = shrd->bleBeaconVisible1;
        value[2] = shrd->beaconRSSI1;
        value[3] = shrd->bleBeaconVisible2;
        value[4] = shrd->beaconRSSI2;
        value[5] = shrd->bleLockForced;
        value[6] = shrd->errorBrake | (shrd->errorContrl << 1) | (shrd->errorSerialFromContrl << 2) | (shrd->errorSerialFromDisplay << 3) | (shrd->errorThrottle << 4) | (shrd->errorI2cDAC << 5);
        pCharacteristicBtlockStatus->setValue((uint8_t *)&value, 7);
        pCharacteristicBtlockStatus->notify();

#if DEBUG_DISPLAY_BLE_NOTIFY
        Serial.print("BLH - notifyBleLock : bleLockStatus = ");
        Serial.print(bleLockStatus);
        Serial.print(" / bleBeaconVisible = ");
        Serial.print(bleBeaconVisible);
        Serial.print(" / bleBeaconRSSI = ");
        Serial.print(shrd->beaconRSSI);

        Serial.print(" / bleLockForced = ");
        Serial.print(bleLockForced);
        Serial.println("");
#endif
    }
}

void BluetoothHandler::setBleLock(bool force)
{
    // force locking
    if (force)
    {
        shrd->bleLockForced = 1;
        saveBleLockForced();
    }

    // update lock status
    if (shrd->bleLockForced == 1)
        shrd->isLocked = 1;
}

void BluetoothHandler::processBLE()
{

#ifndef DEBUG_NEW

    // notify changed value
    if (deviceStatus == BLE_STATUS_CONNECTED_AND_AUTHENTIFIED)
    {
        uint16_t period = 250;
        if (shrd->fastUpdate)
            period = 100;

        /*
        Serial.print(millis());
        Serial.print("BLH -  / ");
        Serial.print(shrd->timeLastNotifyBle);
        Serial.print("BLH -  / ");
        Serial.print(period);
        Serial.println(" / ");
        */

        if (millis() > shrd->timeLastNotifyBle + period)
        {

            notifyMeasurements();

            notifyBleLockAndErrors();

            shrd->timeLastNotifyBle = millis();
        }
    }
    // disconnecting
    if ((deviceStatus != oldDeviceStatus) && (deviceStatus == BLE_STATUS_DISCONNECTED))
    {
        delay(500);                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
    }
    oldDeviceStatus = deviceStatus;

#endif
}

void BluetoothHandler::setSharedData(SharedData *data)
{
    shrd = data;
}

void BluetoothHandler::setSettings(Settings *data)
{
    // Init settings
    settings = data;
}

void BluetoothHandler::deinit()
{
    if (deviceStatus != BLE_STATUS_DISABLED)
    {
        // stop advertising
        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
        pAdvertising->stop();

        Serial.println("BLH - stop advertising ... done");
        // stop scanning
        if (pBLEScan != NULL)
            pBLEScan->stop();
        Serial.println("BLH - stop scanning ... done");

        delay(10);

        pServer->stopAdvertising();

        delay(10);

        // stop BLE stack
        NimBLEDevice::stopAdvertising();

        delay(10);

        NimBLEDevice::deinit(true);

        delay(10);

        Serial.println("BLH - deinit ... done");

        deviceStatus = BLE_STATUS_DISABLED;
    }
}
