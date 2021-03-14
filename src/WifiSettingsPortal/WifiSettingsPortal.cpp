#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <AutoConnect.h>
#include "Settings.h"

using WebServerClass = WebServer;

Settings *WifiSettingsPortal_settings;

#define USERNAME "admin" // For HTTP authentication
#define PASSWORD "admin" // For HTTP authentication

/*
ACStyle(ACE_Style1, "input[type='text']{width: 100px!important;}");
ACStyle(ACE_Style2, "input[type='number']{width: 50px!important;}");
ACStyle(ACE_Style3, "input[type='password']{width: 100px!important;}");
*/

ACStyle(ACE_Style1, "");
ACStyle(ACE_Style2, "input[type='button']{background-color:#303F9F; border-color:#303F9F}");
ACStyle(ACE_Style3, "select{width:44%}");
ACStyle(ACE_Style4, ".noorder{width:100%}.noorder label{display:inline-block;width:40%;cursor:pointer;padding:5px}.noorder .noorder input[type='text']{width:40%} .noorder input[type='password']{width:40%} .noorder input[type='text']{width:40%}");

//ACElement(ACE_Js1, "<script type=\"text/javascript\">window.onload=function(){var t=document.querySelectorAll(\"input[type='text']\");for(i=0;i<t.length;i++){var e=t[i].getAttribute(\"placeholder\");e&&t[i].setAttribute(\"class\",e)}};</script>");
ACElement(ACE_Js1, "");

#include "WifiSettingsPortalSpecs.h"

// Declare AutoConnectElements for the page as /mqtt_save
ACText(ACE_Save_header, "<h4>Settings has been saved.</h4>", "text-align:center;padding:10px;");
ACSubmit(ACE_Save_confirm, "Ok", "/elements");

// Declare the custom Web page as /mqtt_save and contains the AutoConnectElements
AutoConnectAux saveAux("/save", "SmartElec Setting", false, {ACE_Style1, ACE_Style2, ACE_Style3, ACE_Style4, ACE_Save_header, ACE_Save_confirm});

WebServerClass server;
AutoConnect portal(server);
AutoConnectConfig config;

/*
void saveConfig(AutoConnectAux &aux)
{
  String val1 = (elementsAux["ACE_Wheel_size"].as<AutoConnectInput>()).value;
  Serial.println("val1 = " + (String) val1);

}
*/

void WifiSettingsPortal_setup()
{

  // Responder of root page handled directly from WebServer class.
  server.on("/_ac", []() {
    server.sendHeader("Location", "/elements", true);
    server.send(302, "text/plain", "");
    //server.client().stop();
  });

  // Load a custom web page described in JSON as PAGE_ELEMENT and
  // register a handler. This handler will be invoked from
  // AutoConnectSubmit named the Load defined on the same page.
  elementsAux.on([](AutoConnectAux &aux, PageArgument &arg) {
    Serial.println("portal where = " + (String)portal.where());
    if ((portal.where() == "/elements") || (portal.where() == ""))
    {
      Serial.println("load begin");

      loadConfig(aux);

      //#include "portal_settings_load.h"

      /*
      aux.setElementValue("uniqueid", "checked");
      aux.setElementValue("channelid", "15");
      aux.setElementValue("select", "1");
      */
    }
    Serial.println("load end");
    return String();
  });

  saveAux.on([](AutoConnectAux &aux, PageArgument &arg) {
    Serial.println("save begin");

    saveConfig(aux);

    // You can validate input values ​​before saving with
    // AutoConnectInput::isValid function.
    // Verification is using performed regular expression set in the
    // pattern attribute in advance.
    /*
    
*/
    //#include "portal_settings_save.h"
    /*
    String val1 = (elementsAux["channelid"].as<AutoConnectInput>()).value;
    Serial.println("val1 = " + val1);
    
    bool val2 = elementsAux["Throttle_regeneration"].as<AutoConnectCheckbox>().checked;
    Serial.println("val2 = " + (String)val2);

    int val3 = elementsAux["radio"].as<AutoConnectSelect>().selected;
    Serial.println("val3 = " + (String)val3);

    String val4 = elementsAux["radio"].as<AutoConnectSelect>().value();
    Serial.println("val4 = " + (String)val4);
*/
    return String();
  });

  // In the setup(),
  // Join the custom Web pages and performs begin
  portal.join({elementsAux, saveAux});

  config.auth = AC_AUTH_NONE;
  config.authScope = AC_AUTHSCOPE_AUX;
  config.psk = "12345678";

  // bool      autoRise;           /**< Automatic starting the captive portal */
  // bool      autoReset;          /**< Reset ESP8266 module automatically when WLAN disconnected. */
  // bool      autoReconnect;      /**< Automatic reconnect with past SSID */
  // bool      immediateStart;     /**< Skips WiFi.begin(), start portal immediately */
  // bool      retainPortal;       /**< Even if the captive portal times out, it maintains the portal state. */
  // bool      preserveAPMode;     /**< Keep existing AP WiFi mode if captive portal won't be started. */
  // unsigned long beginTimeout;   /**< Timeout value for WiFi.begin */
  // unsigned long portalTimeout;  /**< Timeout value for stay in the captive portal */
  // uint8_t   reconnectInterval;  /**< Auto-reconnect attempt interval uint */

  config.autoRise = true;

  // fix wifi name ... same as BLE
  uint8_t base_mac_addr[6] = {0};
  char bleName[20];
  esp_efuse_mac_get_default(base_mac_addr);
  sprintf(bleName, "Smart-%x",
          base_mac_addr[5]);
  config.apid = bleName;

  //config.immediateStart = true;
  //config.autoReconnect = true;
  config.retainPortal = true;
  config.preserveAPMode = true;
  config.homeUri = "/elements";
  //config.menuItems = AC_MENUITEM_RESET | AC_MENUITEM_UPDATE;

  //config.ota;
  config.title = "SmartElec";

  portal.config(config);
  portal.begin();

  Serial.println("wifi portal open !");
}

void WifiSettingsPortal_loop()
{
  portal.handleClient();
}

void WifiSettingsPortal_close()
{
  portal.end();
  server.close();
  Serial.println("Wifi portal closed");
}

void WifiSettingsPortal_setSettings(Settings *set) {
  WifiSettingsPortal_settings = set;
}