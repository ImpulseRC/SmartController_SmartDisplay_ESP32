//////------------------------------------
////// OTA Services

#include "Arduino.h"

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ArduinoJson.h"

#include "OTA/esp32fota.h"
#include <WiFiClientSecure.h>
#include "Controllers/ControllerType.h"

#define OTA_HOSTNAME "SmartElec_OTA"

char *github_root_ca = (char *)"-----BEGIN CERTIFICATE-----\n"
                               "MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBsMQswCQYDVQQG\n"
                               "EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSsw\n"
                               "KQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5jZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAw\n"
                               "MFoXDTMxMTExMDAwMDAwMFowbDELMAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZ\n"
                               "MBcGA1UECxMQd3d3LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFu\n"
                               "Y2UgRVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm+9S75S0t\n"
                               "Mqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTWPNt0OKRKzE0lgvdKpVMS\n"
                               "OO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEMxChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3\n"
                               "MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFBIk5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQ\n"
                               "NAQTXKFx01p8VdteZOE3hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUe\n"
                               "h10aUAsgEsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQFMAMB\n"
                               "Af8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaAFLE+w2kD+L9HAdSY\n"
                               "JhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3NecnzyIZgYIVyHbIUf4KmeqvxgydkAQ\n"
                               "V8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6zeM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFp\n"
                               "myPInngiK3BD41VHMWEZ71jFhS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkK\n"
                               "mNEVX58Svnw2Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"
                               "vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep+OkuE6N36B9K\n"
                               "-----END CERTIFICATE-----\n";

// defined in PlatformIO envs
// #define FIRMWARE_VERSION 1
// #define FIRMWARE_TYPE "smartcontroller_smartdisplay_minimo"

static boolean OTA_ide_init = false;

WiFiClientSecure clientForOta;
secureEsp32FOTA secureEsp32FOTA((String)FIRMWARE_TYPE, FIRMWARE_VERSION);

void OTA_server_run(char *ssid, char *password, uint16_t version)
{
  Serial.println("------------- OTA Server -------------");

  //delay(100);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);

  //delay(100);

#if SCAN_WIFI
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
#endif

  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  byte retries = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
    retries++;
    if ((retries % 5) == 4)
      WiFi.begin(ssid, password); //solves AUTH_FAIL bug on some routers
  }
  Serial.println("");
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());

  secureEsp32FOTA._host = "raw.githubusercontent.com";
  secureEsp32FOTA._descriptionOfFirmwareURL = "/Koxx3/SmartController_SmartDisplay_ESP32/master/ota_updates/" + (String)FIRMWARE_TYPE + "/firmware_v" + version + ".json";
  secureEsp32FOTA._certificate = github_root_ca;
  secureEsp32FOTA.clientForOta = clientForOta;

  bool shouldExecuteFirmwareUpdate = secureEsp32FOTA.execHTTPSCheck();
  //if (shouldExecuteFirmwareUpdate)
  //{
  Serial.println("Firmware update to version : " + (String)version);
  secureEsp32FOTA.executeOTA();
  //}
  //else
  //{
  //  Serial.println("No firmware update available...");
  // }
  ESP.restart();
}

// STD OTA
void OTA_ide_setup(char *wifi_ssid, char *wifi_pwd)
{
  OTA_ide_init = true;

  Serial.println("wifi_ssid : " + (String)wifi_ssid);
  Serial.println("wifi_pwd : " + (String)wifi_pwd);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pwd);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE); // required to set hostname properly
  WiFi.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setHostname(OTA_HOSTNAME);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
    ESP.restart();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());
}

void OTA_ide_loop(char *wifi_ssid, char *wifi_pwd)
{
  if (!OTA_ide_init)
  {
    Serial.println("------------- OTA IDE -------------");
    OTA_ide_setup(wifi_ssid, wifi_pwd);
  }
  else
  {
    ArduinoOTA.handle();
  }
}
