#ifndef _prefs_storage_h
#define _prefs_storage_h

#include "SharedData.h"
#include "BLE/BluetoothHandler.h"
#include <Preferences.h>


class Settings2
{
public:

    void init();
    
    void setSharedData(SharedData *);
    
    void restore();

    void displaySettings1();

    void saveBleLockForced();
    void saveOdo();
    void saveBatteryCalib();

private:
    SharedData *shrd;
    Preferences prefs;

    void restoreMode();
    void restoreBleLockForced();
    void restoreOdo();
    void restoreBatteryCalib();

};

#endif