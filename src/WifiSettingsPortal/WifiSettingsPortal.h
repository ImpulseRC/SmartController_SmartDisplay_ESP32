
#ifndef _WifiSettingsPortal_h
#define _WifiSettingsPortal_h

void WifiSettingsPortal_setup();
void WifiSettingsPortal_loop();
void WifiSettingsPortal_close();
void WifiSettingsPortal_begin();
void WifiSettingsPortal_setSettings(Settings *);
void WifiSettingsPortal_setSharedData(SharedData *set);
void WifiSettingsPortal_setBluetoothHandler(BluetoothHandler *set);
void WifiSettingsPortal_sendValues();

#endif