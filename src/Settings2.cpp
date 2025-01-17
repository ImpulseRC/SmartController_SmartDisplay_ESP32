//////------------------------------------
////// PREFERENCES functions

#include "main.h"
#include <Settings2.h>
#include "ioprocessing.h"
#define APP_STORAGE "APP_STORAGE"

// Settings2
#define PREF_bleLockForced "bleLockForced"
#define PREF_distanceOdo "distanceOdo"
#define PREF_bMaxCalibUser "bMaxCalibUser"
#define PREF_bMaxCalibRaw "bMaxCalibRaw"
#define PREF_bMinCalibUser "bMinCalibUser"
#define PREF_bMinCalibRaw "bMinCalibRaw"

void Settings2::setSharedData(SharedData *data)
{
  shrd = data;
}

void Settings2::restore()
{
  restoreBleLockForced();
  restoreOdo();
  restoreBatteryCalib();
}

void Settings2::saveBleLockForced()
{
  prefs.begin(APP_STORAGE, false);
  prefs.putInt(PREF_bleLockForced, shrd->isLocked);
  prefs.end();

  Serial.print("save bleLockForced value : ");
  Serial.println(shrd->isLocked);
}

void Settings2::restoreBleLockForced()
{
  prefs.begin(APP_STORAGE, false);
  shrd->isLocked = prefs.getInt(PREF_bleLockForced, 0);
  prefs.end();

  Serial.print("restore bleLockForced value : ");
  Serial.println(shrd->isLocked);
}

void Settings2::saveOdo()
{
  //uint32_t time = micros();
  prefs.begin(APP_STORAGE, false);
  prefs.putUInt(PREF_distanceOdo, shrd->distanceOdo);
  prefs.end();

  //Serial.print("time write : ");
  //Serial.println(micros() - time);

  //Serial.print("save saveOdo value : ");
  //Serial.println(shrd->distanceOdo);
}

void Settings2::restoreOdo()
{
  prefs.begin(APP_STORAGE, false);
  shrd->distanceOdo = prefs.getUInt(PREF_distanceOdo, 0);
  prefs.end();

  shrd->distanceOdoInFlash = shrd->distanceOdo;
  shrd->distanceOdoBoot = shrd->distanceOdo;

  Serial.print("restore restoreOdo value : ");
  Serial.println(shrd->distanceOdo);
}

void Settings2::saveBatteryCalib()
{
  prefs.begin(APP_STORAGE, false);
  prefs.putFloat(PREF_bMaxCalibUser, shrd->batteryMaxVoltageCalibUser);
  prefs.putUInt(PREF_bMaxCalibRaw, shrd->batteryMaxVoltageCalibRaw);
  prefs.putFloat(PREF_bMinCalibUser, shrd->batteryMinVoltageCalibUser);
  prefs.putUInt(PREF_bMinCalibRaw, shrd->batteryMinVoltageCalibRaw);
  prefs.end();

  Serial.println("save BatteryCalib value : ");
  Serial.print("  batteryMaxVoltageCalibUser : ");
  Serial.println(shrd->batteryMaxVoltageCalibUser);
  Serial.print("  batteryMaxVoltageCalibRaw : ");
  Serial.println(shrd->batteryMaxVoltageCalibRaw);
  Serial.print("  batteryMinVoltageCalibUser : ");
  Serial.println(shrd->batteryMinVoltageCalibUser);
  Serial.print("  batteryMinVoltageCalibRaw : ");
  Serial.println(shrd->batteryMinVoltageCalibRaw);
}

void Settings2::restoreBatteryCalib()
{
  prefs.begin(APP_STORAGE, false);
  shrd->batteryMaxVoltageCalibUser = prefs.getFloat(PREF_bMaxCalibUser, 66.20);
  shrd->batteryMaxVoltageCalibRaw = prefs.getUInt(PREF_bMaxCalibRaw, 2970);
  shrd->batteryMinVoltageCalibUser = prefs.getFloat(PREF_bMinCalibUser, 0.0);
  shrd->batteryMinVoltageCalibRaw = prefs.getUInt(PREF_bMinCalibRaw, 0);
  prefs.end();

  Serial.println("restore BatteryCalib value : ");
  Serial.print("  batteryMaxVoltageCalibUser : ");
  Serial.println(shrd->batteryMaxVoltageCalibUser);
  Serial.print("  batteryMaxVoltageCalibRaw : ");
  Serial.println(shrd->batteryMaxVoltageCalibRaw);
  Serial.print("  batteryMinVoltageCalibUser : ");
  Serial.println(shrd->batteryMinVoltageCalibUser);
  Serial.print("  batteryMinVoltageCalibRaw : ");
  Serial.println(shrd->batteryMinVoltageCalibRaw);
}
