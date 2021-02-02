//////------------------------------------
////// Manage bluetooth

#include "Arduino.h"

#ifndef _BluetoothHandler_h
#define _BluetoothHandler_h

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "Settings.h"
#include "SharedData.h"
#include "EEPROM_storage.h"

typedef enum
{
    BLE_STATUS_DISABLED,
    BLE_STATUS_DISCONNECTED,
    BLE_STATUS_CONNECTED_AND_AUTHENTIFYING,
    BLE_STATUS_CONNECTED_AND_AUTHENTIFIED,
} BleStatus;

class BluetoothHandler
{
public:
    BluetoothHandler();
    static void setSettings(Settings *);
    static void setSharedData(SharedData *);
    static void deinit();
    static void bleOnScanResults(BLEScanResults);
    static void notifyBleLock();
    static void notifyBleLogs(char *);
    static void setBleLock(bool);
    static void processBLE();
    static void notifyMeasurements();
    static void notifyCommandsFeedback();
    static uint8_t setMeasurementsDataPacket();
    static uint8_t setCommandsDataPacket();
    static void getGeneralOrderDataPacket(uint8_t*);
    
    /*
    static void notifyModeOrder(uint8_t);
    static void notifySpeedLimiterStatus(uint8_t);
    static void notifyBreakeSentOrder(uint8_t, uint8_t, uint8_t);
    static void notifyEcoOrder(uint8_t);
    static void notifyAccelOrder(uint8_t);
    static void notifyAuxOrder(uint8_t);
    */

    static BLEScan *pBLEScan;
    static BLEServer *pServer;
    static BLESecurity *pSecurity;
    static BLECharacteristic *pCharacteristicMeasurements;
    static BLECharacteristic *pCharacteristicBtlockStatus;
    static BLECharacteristic *pCharacteristicCalibOrder;
    static BLECharacteristic *pCharacteristicOtaSwitch;
    static BLECharacteristic *pCharacteristicLogs;
    static BLECharacteristic *pCharacteristicSpeedPid;
    static BLECharacteristic *pCharacteristicDistanceRst;
    static BLECharacteristic *pCharacteristicKeepAlive;
    static BLECharacteristic *pCharacteristicCommands;
    //static BLECharacteristic *pCharacteristicSpeedLimiter;
    //static BLECharacteristic *pCharacteristicEco;
    //static BLECharacteristic *pCharacteristicAccel;
    //static BLECharacteristic *pCharacteristicFastUpdate;
    //static BLECharacteristic *pCharacteristicAux;
    //static BLECharacteristic *pCharacteristicMode;
    //static BLECharacteristic *pCharacteristicBrakeSentOrder;

    static BLECharacteristic *pCharacteristicSettings1;
    static BLECharacteristic *pCharacteristicSettings2;
    static BLECharacteristic *pCharacteristicSettings3;
    static BLECharacteristic *pCharacteristicSettings4;
    static BLECharacteristic *pCharacteristicSettings5;

    static BLECharacteristic *pCharacteristicFirmware;

    static int8_t bleLockStatus;
    static int8_t bleBeaconVisible;
    static int8_t bleBeaconRSSI;
    static int8_t bleLockForced;
    static int8_t fastUpdate;

    static BleStatus deviceStatus;
    static BleStatus oldDeviceStatus;

    static SharedData *shrd;
    static Settings *settings;
};

#endif