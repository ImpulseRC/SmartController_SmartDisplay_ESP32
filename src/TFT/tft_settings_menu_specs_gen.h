
//////------------------------------------
//////------------------------------------
//////------------------------------------
////// GENERATED FILE - DO NOT EDIT MANUALLY
//////------------------------------------
//////------------------------------------
//////------------------------------------

////// Manage settings exchanged in BLE and stored in EEPOM

/*

float Wheel_size = 8.5;
int Motor_number_of_magents_pairs=15;
float Battery_minimum_voltage =42.0;
float Battery_maximum_voltage=59.0;
int Battery_distance=40;
int thottleRegen=0;

TOGGLE(thottleRegen,setThottleRegen,"  Throttle signal regeneration: ",doNothing,noEvent,noStyle //
  ,VALUE("On",1,doNothing,noEvent) //
  ,VALUE("Off",0,doNothing,noEvent) //
);

MENU(escooterCharac,"  E-scooter characteristics",doNothing,noEvent,noStyle //
  ,altFIELD(decPlaces<1>::menuField, Wheel_size, "  Wheel size (inches)","",8.5,13.0,0.5,0.1,doNothing,anyEvent,wrapStyle) //
  ,FIELD(Motor_number_of_magents_pairs,"  Motor number of magents pairs","",5,20,1,0,doNothing,noEvent,wrapStyle) //
  ,altFIELD(decPlaces<1>::menuField, Battery_minimum_voltage,"  Battery minimum voltage (volts)","",30, 100,1,0.1,doNothing,noEvent,wrapStyle) //
  ,altFIELD(decPlaces<1>::menuField, Battery_maximum_voltage,"  Battery maximum voltage (volts)","",30, 100,1,0.1,doNothing,noEvent,wrapStyle) //
  ,FIELD(Battery_distance,"  Battery distance (km)","",30, 100,5,1,doNothing,noEvent,wrapStyle) //
  ,SUBMENU(setThottleRegen) //
  ,EXIT("< Back")
);

MENU(escooterSettings,"  E-scooter settings",doNothing,noEvent,noStyle //
  ,altFIELD(decPlaces<1>::menuField, dummy, "  Dummy","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
  ,EXIT("< Back") //
);

MENU(escooterAccessories,"  E-scooter accessories",doNothing,noEvent,noStyle //
  ,altFIELD(decPlaces<1>::menuField, dummy, "  Dummy","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
  ,EXIT("< Back") //
);

MENU(electricBrake,"  Electric brake",doNothing,noEvent,noStyle //
  ,altFIELD(decPlaces<1>::menuField, dummy, "  Dummy","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
  ,EXIT("< Back") //
);

MENU(electricThrottle,"  Electric throttle",doNothing,noEvent,noStyle // 
  ,altFIELD(decPlaces<1>::menuField, dummy, "  Dummy","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
  ,EXIT("< Back") //
);

MENU(displaySettings,"  Display",doNothing,noEvent,noStyle //
  ,altFIELD(decPlaces<1>::menuField, dummy, "  Dummy","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
  ,EXIT("< Back") //
);


*/
    float wheel_size;
    uint8_t number_of_poles_pairs;
    float battery_minimum_voltage;
    float battery_maximum_voltage;
    uint8_t battery_maximum_distance;
    uint8_t default_mode_at_startup;
    uint8_t default_eco_mode_at_startup;
    uint8_t default_acceleration;
    uint8_t default_electric_brake_at_startup;
    uint8_t pas_enabled;
    uint8_t abs_enabled;
    uint8_t display_brightness;
    uint8_t temperature_warning;
    uint8_t humidity_warning;
    uint8_t speed_limiter_at_startup;
    uint8_t speed_limiter_max_speed_in_percent_of_max_speed;
    uint8_t electric_brake_progressive_mode;
    uint8_t type;
    uint8_t min_value;
    uint8_t max_value;
    uint8_t time_between_mode_shift;
    uint8_t disabled_on_high_battery_voltage;
    uint8_t disabled_percent_limit;
    uint8_t throttle_regeneration;
    uint32_t input_min_voltage_in_millivolts;
    uint32_t input_max_voltage_in_millivolts;
    uint32_t output_min_voltage_in_millivolts;
    uint32_t output_max_voltage_in_millivolts;
    uint8_t output_curve;
    uint8_t button_1_short_press_action;
    uint8_t button_1_long_press_action;
    uint8_t button_2_short_press_action;
    uint8_t button_long_press_duration;

MENU(SUBMENU_Escooter_characteristics,"  Escooter characteristics",doNothing,noEvent,noStyle //
    ,altFIELD(decPlaces<1>::menuField, wheel_size, "  Wheel size","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
    ,FIELD(number_of_poles_pairs,"  Number of poles pairs","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,altFIELD(decPlaces<1>::menuField, battery_minimum_voltage, "  Battery minimum voltage","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
    ,altFIELD(decPlaces<1>::menuField, battery_maximum_voltage, "  Battery maximum voltage","",0,10.0,0.5,0.01,doNothing,anyEvent,wrapStyle) //
    ,FIELD(battery_maximum_distance,"  Battery maximum distance","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
    
MENU(SUBMENU_SmartDisplay,"  SmartDisplay",doNothing,noEvent,noStyle //
    ,FIELD(default_mode_at_startup,"  Default mode at startup","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(default_eco_mode_at_startup,"  Default eco mode at startup","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(default_acceleration,"  Default acceleration","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(default_electric_brake_at_startup,"  Default electric brake at startup","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(pas_enabled,"  PAS enabled","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(abs_enabled,"  Abs enabled","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(display_brightness,"  Display brightness","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(temperature_warning,"  Temperature warning","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(humidity_warning,"  Humidity warning","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
MENU(SUBMENU_General,"  General",doNothing,noEvent,noStyle //
    ,FIELD(speed_limiter_at_startup,"  Speed limiter at startup","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(speed_limiter_max_speed_in_percent_of_max_speed,"  Speed limiter max speed (in percent of max speed)","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
MENU(SUBMENU_Electric_brake,"  Electric brake",doNothing,noEvent,noStyle //
    ,FIELD(electric_brake_progressive_mode,"  Electric brake progressive mode","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(type,"  Type","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(min_value,"  Min value","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(max_value,"  Max value","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(time_between_mode_shift,"  Time between mode shift","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(disabled_on_high_battery_voltage,"  Disabled on high battery voltage","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(disabled_percent_limit,"  Disabled percent limit","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
MENU(SUBMENU_Throttle,"  Throttle",doNothing,noEvent,noStyle //
    ,FIELD(throttle_regeneration,"  Throttle regeneration","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(input_min_voltage_in_millivolts,"  Input min voltage (in millivolts)","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(input_max_voltage_in_millivolts,"  Input max voltage (in millivolts)","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(output_min_voltage_in_millivolts,"  Output min voltage (in millivolts)","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(output_max_voltage_in_millivolts,"  Output max voltage (in millivolts)","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(output_curve,"  Output curve","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
MENU(SUBMENU_Escooter_buttons,"  Escooter buttons",doNothing,noEvent,noStyle //
    ,FIELD(button_1_short_press_action,"  Button 1 short press action","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(button_1_long_press_action,"  Button 1 long press action","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(button_2_short_press_action,"  Button 2 short press action","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,FIELD(button_long_press_duration,"  Button long press duration","",5,20,1,0,doNothing,noEvent,wrapStyle) //
    ,EXIT("< Back")
);
    
    

MENU(mainMenu,"  Main menu",doNothing,noEvent,wrapStyle //
    ,SUBMENU(SUBMENU_MANUAL_moreInfos) //
    ,SUBMENU(SUBMENU_Escooter_characteristics) //
    ,SUBMENU(SUBMENU_SmartDisplay) //
    ,SUBMENU(SUBMENU_General) //
    ,SUBMENU(SUBMENU_Electric_brake) //
    ,SUBMENU(SUBMENU_Throttle) //
    ,SUBMENU(SUBMENU_Escooter_buttons) //
    ,SUBMENU(SUBMENU_MANUAL_bluetooth) //
    ,SUBMENU(SUBMENU_MANUAL_firmware) //
    ,OP("< Discard & exit", discard_exit,enterEvent) //
    ,OP("< Save & exit", save_exit,enterEvent) //
);
