
//////------------------------------------
//////------------------------------------
//////------------------------------------
////// GENERATED FILE - DO NOT EDIT MANUALLY
//////------------------------------------
//////------------------------------------
//////------------------------------------

////// Manage settings exchanged in BLE and stored in EEPOM

#include "Arduino.h"
#include <Preferences.h>

#ifndef _Settings_h
#define _Settings_h

class Settings
{
private : 
    Preferences prefs;

public:

    Settings();

    void restore();
    void save();

    void unpack_setting_packet(uint8_t* packet, uint8_t length);
    bool pack_setting_packet(uint16_t settingId, uint16_t packetNumber, uint8_t* packet, int32_t* length);


    
            
    /*-------------------------------------------------------*/

    #define SETTINGS_WHEEL_SIZE_ID 1
    #define SETTINGS_WHEEL_SIZE_ID_STR "1"
    #define SETTINGS_WHEEL_SIZE_NAME "Wheel_size"

    float Wheel_size;

    void set_Wheel_size (float value);
    float get_Wheel_size();
    void display_Wheel_size();
    void save_Wheel_size(float value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_NUMBER_OF_POLES_PAIRS_ID 2
    #define SETTINGS_NUMBER_OF_POLES_PAIRS_ID_STR "2"
    #define SETTINGS_NUMBER_OF_POLES_PAIRS_NAME "Number_of_poles_pairs"

    uint8_t Number_of_poles_pairs;

    void set_Number_of_poles_pairs (uint8_t value);
    uint8_t get_Number_of_poles_pairs();
    void display_Number_of_poles_pairs();
    void save_Number_of_poles_pairs(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BATTERY_MINIMUM_VOLTAGE_ID 3
    #define SETTINGS_BATTERY_MINIMUM_VOLTAGE_ID_STR "3"
    #define SETTINGS_BATTERY_MINIMUM_VOLTAGE_NAME "Battery_minimum_voltage"

    float Battery_minimum_voltage;

    void set_Battery_minimum_voltage (float value);
    float get_Battery_minimum_voltage();
    void display_Battery_minimum_voltage();
    void save_Battery_minimum_voltage(float value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BATTERY_MAXIMUM_VOLTAGE_ID 4
    #define SETTINGS_BATTERY_MAXIMUM_VOLTAGE_ID_STR "4"
    #define SETTINGS_BATTERY_MAXIMUM_VOLTAGE_NAME "Battery_maximum_voltage"

    float Battery_maximum_voltage;

    void set_Battery_maximum_voltage (float value);
    float get_Battery_maximum_voltage();
    void display_Battery_maximum_voltage();
    void save_Battery_maximum_voltage(float value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BATTERY_MAXIMUM_DISTANCE_ID 5
    #define SETTINGS_BATTERY_MAXIMUM_DISTANCE_ID_STR "5"
    #define SETTINGS_BATTERY_MAXIMUM_DISTANCE_NAME "Battery_maximum_distance"

    uint8_t Battery_maximum_distance;

    void set_Battery_maximum_distance (uint8_t value);
    uint8_t get_Battery_maximum_distance();
    void display_Battery_maximum_distance();
    void save_Battery_maximum_distance(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_SMARTDISPLAY_SPEED_ADJUSTMENT_ID 13
    #define SETTINGS_SMARTDISPLAY_SPEED_ADJUSTMENT_ID_STR "13"
    #define SETTINGS_SMARTDISPLAY_SPEED_ADJUSTMENT_NAME "Smartdisplay_speed_adjustment"

    int8_t Smartdisplay_speed_adjustment;

    void set_Smartdisplay_speed_adjustment (int8_t value);
    int8_t get_Smartdisplay_speed_adjustment();
    void display_Smartdisplay_speed_adjustment();
    void save_Smartdisplay_speed_adjustment(int8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DISPLAY_GPS_SPEED_INSTEAD_OF_ESCOOTER_SPEED_ID 14
    #define SETTINGS_DISPLAY_GPS_SPEED_INSTEAD_OF_ESCOOTER_SPEED_ID_STR "14"
    #define SETTINGS_DISPLAY_GPS_SPEED_INSTEAD_OF_ESCOOTER_SPEED_NAME "Display_gps_speed_instead_of_escooter_speed"

    uint8_t Display_gps_speed_instead_of_escooter_speed;

    void set_Display_gps_speed_instead_of_escooter_speed (uint8_t value);
    uint8_t get_Display_gps_speed_instead_of_escooter_speed();
    void display_Display_gps_speed_instead_of_escooter_speed();
    void save_Display_gps_speed_instead_of_escooter_speed(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_AUX_RELAY_NAME_ID 15
    #define SETTINGS_AUX_RELAY_NAME_ID_STR "15"
    #define SETTINGS_AUX_RELAY_NAME_NAME "Aux_relay_name"

    uint8_t Aux_relay_name;
    typedef enum LIST_Aux_relay_name {
        LIST_Aux_relay_name_Aux,
        LIST_Aux_relay_name_Dual,
        LIST_Aux_relay_name_Lights,
        LIST_Aux_relay_name_Horn,
        LIST_Aux_relay_name_Relay, 
    } tAux_relay_name;

    void set_Aux_relay_name (uint8_t value);
    uint8_t get_Aux_relay_name();
    void display_Aux_relay_name();
    void save_Aux_relay_name(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DEFAULT_MODE_AT_STARTUP_ID 16
    #define SETTINGS_DEFAULT_MODE_AT_STARTUP_ID_STR "16"
    #define SETTINGS_DEFAULT_MODE_AT_STARTUP_NAME "Default_mode_at_startup"

    uint8_t Default_mode_at_startup;

    void set_Default_mode_at_startup (uint8_t value);
    uint8_t get_Default_mode_at_startup();
    void display_Default_mode_at_startup();
    void save_Default_mode_at_startup(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DEFAULT_ECO_MODE_AT_STARTUP_ID 17
    #define SETTINGS_DEFAULT_ECO_MODE_AT_STARTUP_ID_STR "17"
    #define SETTINGS_DEFAULT_ECO_MODE_AT_STARTUP_NAME "Default_eco_mode_at_startup"

    uint8_t Default_eco_mode_at_startup;
    typedef enum LIST_Default_eco_mode_at_startup {
        LIST_Default_eco_mode_at_startup_Max,
        LIST_Default_eco_mode_at_startup_Medium,
        LIST_Default_eco_mode_at_startup_None, 
    } tDefault_eco_mode_at_startup;

    void set_Default_eco_mode_at_startup (uint8_t value);
    uint8_t get_Default_eco_mode_at_startup();
    void display_Default_eco_mode_at_startup();
    void save_Default_eco_mode_at_startup(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DEFAULT_ACCELERATION_ID 18
    #define SETTINGS_DEFAULT_ACCELERATION_ID_STR "18"
    #define SETTINGS_DEFAULT_ACCELERATION_NAME "Default_acceleration"

    uint8_t Default_acceleration;
    typedef enum LIST_Default_acceleration {
        LIST_Default_acceleration_Very_slow,
        LIST_Default_acceleration_Slow,
        LIST_Default_acceleration_Medium,
        LIST_Default_acceleration_Fast,
        LIST_Default_acceleration_Very_fast,
        LIST_Default_acceleration_Maximum, 
    } tDefault_acceleration;

    void set_Default_acceleration (uint8_t value);
    uint8_t get_Default_acceleration();
    void display_Default_acceleration();
    void save_Default_acceleration(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DEFAULT_ELECTRIC_BRAKE_AT_STARTUP_ID 19
    #define SETTINGS_DEFAULT_ELECTRIC_BRAKE_AT_STARTUP_ID_STR "19"
    #define SETTINGS_DEFAULT_ELECTRIC_BRAKE_AT_STARTUP_NAME "Default_electric_brake_at_startup"

    uint8_t Default_electric_brake_at_startup;

    void set_Default_electric_brake_at_startup (uint8_t value);
    uint8_t get_Default_electric_brake_at_startup();
    void display_Default_electric_brake_at_startup();
    void save_Default_electric_brake_at_startup(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_PAS_ENABLED_ID 20
    #define SETTINGS_PAS_ENABLED_ID_STR "20"
    #define SETTINGS_PAS_ENABLED_NAME "Pas_enabled"

    uint8_t Pas_enabled;

    void set_Pas_enabled (uint8_t value);
    uint8_t get_Pas_enabled();
    void display_Pas_enabled();
    void save_Pas_enabled(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_ABS_ENABLED_ID 21
    #define SETTINGS_ABS_ENABLED_ID_STR "21"
    #define SETTINGS_ABS_ENABLED_NAME "Abs_enabled"

    uint8_t Abs_enabled;

    void set_Abs_enabled (uint8_t value);
    uint8_t get_Abs_enabled();
    void display_Abs_enabled();
    void save_Abs_enabled(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_DISPLAY_BRIGHTNESS_ID 22
    #define SETTINGS_DISPLAY_BRIGHTNESS_ID_STR "22"
    #define SETTINGS_DISPLAY_BRIGHTNESS_NAME "Display_brightness"

    uint8_t Display_brightness;

    void set_Display_brightness (uint8_t value);
    uint8_t get_Display_brightness();
    void display_Display_brightness();
    void save_Display_brightness(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_TEMPERATURE_WARNING_ID 23
    #define SETTINGS_TEMPERATURE_WARNING_ID_STR "23"
    #define SETTINGS_TEMPERATURE_WARNING_NAME "Temperature_warning"

    uint8_t Temperature_warning;

    void set_Temperature_warning (uint8_t value);
    uint8_t get_Temperature_warning();
    void display_Temperature_warning();
    void save_Temperature_warning(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_HUMIDITY_WARNING_ID 24
    #define SETTINGS_HUMIDITY_WARNING_ID_STR "24"
    #define SETTINGS_HUMIDITY_WARNING_NAME "Humidity_warning"

    uint8_t Humidity_warning;

    void set_Humidity_warning (uint8_t value);
    uint8_t get_Humidity_warning();
    void display_Humidity_warning();
    void save_Humidity_warning(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_SPEED_LIMITER_AT_STARTUP_ID 6
    #define SETTINGS_SPEED_LIMITER_AT_STARTUP_ID_STR "6"
    #define SETTINGS_SPEED_LIMITER_AT_STARTUP_NAME "Speed_limiter_at_startup"

    uint8_t Speed_limiter_at_startup;

    void set_Speed_limiter_at_startup (uint8_t value);
    uint8_t get_Speed_limiter_at_startup();
    void display_Speed_limiter_at_startup();
    void save_Speed_limiter_at_startup(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_SPEED_LIMITER_MAX_SPEED_ID 7
    #define SETTINGS_SPEED_LIMITER_MAX_SPEED_ID_STR "7"
    #define SETTINGS_SPEED_LIMITER_MAX_SPEED_NAME "Speed_limiter_max_speed"

    uint8_t Speed_limiter_max_speed;

    void set_Speed_limiter_max_speed (uint8_t value);
    uint8_t get_Speed_limiter_max_speed();
    void display_Speed_limiter_max_speed();
    void save_Speed_limiter_max_speed(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BLUETOOTH_LOCK_MODE_ID 8
    #define SETTINGS_BLUETOOTH_LOCK_MODE_ID_STR "8"
    #define SETTINGS_BLUETOOTH_LOCK_MODE_NAME "Bluetooth_lock_mode"

    uint8_t Bluetooth_lock_mode;
    typedef enum LIST_Bluetooth_lock_mode {
        LIST_Bluetooth_lock_mode_None,
        LIST_Bluetooth_lock_mode_Smartphone_connected,
        LIST_Bluetooth_lock_mode_Smartphone_connected_or_beacon_visible,
        LIST_Bluetooth_lock_mode_Beacon_visible, 
    } tBluetooth_lock_mode;

    void set_Bluetooth_lock_mode (uint8_t value);
    uint8_t get_Bluetooth_lock_mode();
    void display_Bluetooth_lock_mode();
    void save_Bluetooth_lock_mode(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BLE_PIN_CODE_ID 9
    #define SETTINGS_BLE_PIN_CODE_ID_STR "9"
    #define SETTINGS_BLE_PIN_CODE_NAME "Ble_pin_code"

    uint32_t Ble_pin_code;

    void set_Ble_pin_code (uint32_t value);
    uint32_t get_Ble_pin_code();
    void display_Ble_pin_code();
    void save_Ble_pin_code(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BLE_BEACON_MAC_ADDRESS_ID 10
    #define SETTINGS_BLE_BEACON_MAC_ADDRESS_ID_STR "10"
    #define SETTINGS_BLE_BEACON_MAC_ADDRESS_NAME "Ble_beacon_mac_address"

    String Ble_beacon_mac_address;

    void set_Ble_beacon_mac_address (String value);
    String get_Ble_beacon_mac_address();
    void display_Ble_beacon_mac_address();
    void save_Ble_beacon_mac_address(String value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BLE_BEACON_RANGE_ID 11
    #define SETTINGS_BLE_BEACON_RANGE_ID_STR "11"
    #define SETTINGS_BLE_BEACON_RANGE_NAME "Ble_beacon_range"

    int8_t Ble_beacon_range;

    void set_Ble_beacon_range (int8_t value);
    int8_t get_Ble_beacon_range();
    void display_Ble_beacon_range();
    void save_Ble_beacon_range(int8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_ORIGINAL_DISPLAY_SPEED_ADJUSTMENT_ID 12
    #define SETTINGS_ORIGINAL_DISPLAY_SPEED_ADJUSTMENT_ID_STR "12"
    #define SETTINGS_ORIGINAL_DISPLAY_SPEED_ADJUSTMENT_NAME "Original_display_speed_adjustment"

    int8_t Original_display_speed_adjustment;

    void set_Original_display_speed_adjustment (int8_t value);
    int8_t get_Original_display_speed_adjustment();
    void display_Original_display_speed_adjustment();
    void save_Original_display_speed_adjustment(int8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_PROGRESSIVE_MODE_ID 25
    #define SETTINGS_EBRAKE_PROGRESSIVE_MODE_ID_STR "25"
    #define SETTINGS_EBRAKE_PROGRESSIVE_MODE_NAME "Ebrake_progressive_mode"

    uint8_t Ebrake_progressive_mode;

    void set_Ebrake_progressive_mode (uint8_t value);
    uint8_t get_Ebrake_progressive_mode();
    void display_Ebrake_progressive_mode();
    void save_Ebrake_progressive_mode(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_SMART_BRAKE_TYPE_ID 26
    #define SETTINGS_EBRAKE_SMART_BRAKE_TYPE_ID_STR "26"
    #define SETTINGS_EBRAKE_SMART_BRAKE_TYPE_NAME "Ebrake_smart_brake_type"

    uint8_t Ebrake_smart_brake_type;
    typedef enum LIST_Ebrake_smart_brake_type {
        LIST_Ebrake_smart_brake_type_Controller,
        LIST_Ebrake_smart_brake_type_Smart__digital_brake_lever,
        LIST_Ebrake_smart_brake_type_Smart__analog_brake_lever,
        LIST_Ebrake_smart_brake_type_Smart__digital_brake__throttle_exp, 
    } tEbrake_smart_brake_type;

    void set_Ebrake_smart_brake_type (uint8_t value);
    uint8_t get_Ebrake_smart_brake_type();
    void display_Ebrake_smart_brake_type();
    void save_Ebrake_smart_brake_type(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_MIN_POWER_VALUE_ID 27
    #define SETTINGS_EBRAKE_MIN_POWER_VALUE_ID_STR "27"
    #define SETTINGS_EBRAKE_MIN_POWER_VALUE_NAME "Ebrake_min_power_value"

    uint8_t Ebrake_min_power_value;

    void set_Ebrake_min_power_value (uint8_t value);
    uint8_t get_Ebrake_min_power_value();
    void display_Ebrake_min_power_value();
    void save_Ebrake_min_power_value(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_MAX_POWER_VALUE_ID 28
    #define SETTINGS_EBRAKE_MAX_POWER_VALUE_ID_STR "28"
    #define SETTINGS_EBRAKE_MAX_POWER_VALUE_NAME "Ebrake_max_power_value"

    uint8_t Ebrake_max_power_value;

    void set_Ebrake_max_power_value (uint8_t value);
    uint8_t get_Ebrake_max_power_value();
    void display_Ebrake_max_power_value();
    void save_Ebrake_max_power_value(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_TIME_BETWEEN_MODE_SHIFT_ID 29
    #define SETTINGS_EBRAKE_TIME_BETWEEN_MODE_SHIFT_ID_STR "29"
    #define SETTINGS_EBRAKE_TIME_BETWEEN_MODE_SHIFT_NAME "Ebrake_time_between_mode_shift"

    uint32_t Ebrake_time_between_mode_shift;

    void set_Ebrake_time_between_mode_shift (uint32_t value);
    uint32_t get_Ebrake_time_between_mode_shift();
    void display_Ebrake_time_between_mode_shift();
    void save_Ebrake_time_between_mode_shift(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_DISABLED_ON_HIGH_BATTERY_VOLTAGE_ID 30
    #define SETTINGS_EBRAKE_DISABLED_ON_HIGH_BATTERY_VOLTAGE_ID_STR "30"
    #define SETTINGS_EBRAKE_DISABLED_ON_HIGH_BATTERY_VOLTAGE_NAME "Ebrake_disabled_on_high_battery_voltage"

    uint8_t Ebrake_disabled_on_high_battery_voltage;

    void set_Ebrake_disabled_on_high_battery_voltage (uint8_t value);
    uint8_t get_Ebrake_disabled_on_high_battery_voltage();
    void display_Ebrake_disabled_on_high_battery_voltage();
    void save_Ebrake_disabled_on_high_battery_voltage(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_EBRAKE_DISABLED_PERCENT_LIMIT_ID 31
    #define SETTINGS_EBRAKE_DISABLED_PERCENT_LIMIT_ID_STR "31"
    #define SETTINGS_EBRAKE_DISABLED_PERCENT_LIMIT_NAME "Ebrake_disabled_percent_limit"

    uint8_t Ebrake_disabled_percent_limit;

    void set_Ebrake_disabled_percent_limit (uint8_t value);
    uint8_t get_Ebrake_disabled_percent_limit();
    void display_Ebrake_disabled_percent_limit();
    void save_Ebrake_disabled_percent_limit(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_REGENERATION_ID 32
    #define SETTINGS_THROTTLE_REGENERATION_ID_STR "32"
    #define SETTINGS_THROTTLE_REGENERATION_NAME "Throttle_regeneration"

    uint32_t Throttle_regeneration;

    void set_Throttle_regeneration (uint32_t value);
    uint32_t get_Throttle_regeneration();
    void display_Throttle_regeneration();
    void save_Throttle_regeneration(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_INPUT_MIN_VOLTAGE_ID 33
    #define SETTINGS_THROTTLE_INPUT_MIN_VOLTAGE_ID_STR "33"
    #define SETTINGS_THROTTLE_INPUT_MIN_VOLTAGE_NAME "Throttle_input_min_voltage"

    uint32_t Throttle_input_min_voltage;

    void set_Throttle_input_min_voltage (uint32_t value);
    uint32_t get_Throttle_input_min_voltage();
    void display_Throttle_input_min_voltage();
    void save_Throttle_input_min_voltage(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_INPUT_MAX_VOLTAGE_ID 34
    #define SETTINGS_THROTTLE_INPUT_MAX_VOLTAGE_ID_STR "34"
    #define SETTINGS_THROTTLE_INPUT_MAX_VOLTAGE_NAME "Throttle_input_max_voltage"

    uint32_t Throttle_input_max_voltage;

    void set_Throttle_input_max_voltage (uint32_t value);
    uint32_t get_Throttle_input_max_voltage();
    void display_Throttle_input_max_voltage();
    void save_Throttle_input_max_voltage(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_OUTPUT_MIN_VOLTAGE_ID 35
    #define SETTINGS_THROTTLE_OUTPUT_MIN_VOLTAGE_ID_STR "35"
    #define SETTINGS_THROTTLE_OUTPUT_MIN_VOLTAGE_NAME "Throttle_output_min_voltage"

    uint32_t Throttle_output_min_voltage;

    void set_Throttle_output_min_voltage (uint32_t value);
    uint32_t get_Throttle_output_min_voltage();
    void display_Throttle_output_min_voltage();
    void save_Throttle_output_min_voltage(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_OUTPUT_MAX_VOLTAGE_ID 36
    #define SETTINGS_THROTTLE_OUTPUT_MAX_VOLTAGE_ID_STR "36"
    #define SETTINGS_THROTTLE_OUTPUT_MAX_VOLTAGE_NAME "Throttle_output_max_voltage"

    uint32_t Throttle_output_max_voltage;

    void set_Throttle_output_max_voltage (uint32_t value);
    uint32_t get_Throttle_output_max_voltage();
    void display_Throttle_output_max_voltage();
    void save_Throttle_output_max_voltage(uint32_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_THROTTLE_OUTPUT_CURVE_ID 37
    #define SETTINGS_THROTTLE_OUTPUT_CURVE_ID_STR "37"
    #define SETTINGS_THROTTLE_OUTPUT_CURVE_NAME "Throttle_output_curve"

    uint8_t Throttle_output_curve;
    typedef enum LIST_Throttle_output_curve {
        LIST_Throttle_output_curve_Linear,
        LIST_Throttle_output_curve_Exponential_1,
        LIST_Throttle_output_curve_Exponential_2,
        LIST_Throttle_output_curve_Exponential_3,
        LIST_Throttle_output_curve_Exponential_4, 
    } tThrottle_output_curve;

    void set_Throttle_output_curve (uint8_t value);
    uint8_t get_Throttle_output_curve();
    void display_Throttle_output_curve();
    void save_Throttle_output_curve(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BUTTON_1_SHORT_PRESS_ACTION_ID 38
    #define SETTINGS_BUTTON_1_SHORT_PRESS_ACTION_ID_STR "38"
    #define SETTINGS_BUTTON_1_SHORT_PRESS_ACTION_NAME "Button_1_short_press_action"

    uint8_t Button_1_short_press_action;
    typedef enum LIST_Button_1_short_press_action {
        LIST_Button_1_short_press_action_None,
        LIST_Button_1_short_press_action_Speed_limitation_on_off,
        LIST_Button_1_short_press_action_Aux_on_off,
        LIST_Button_1_short_press_action_Mode_switch_1_2_3,
        LIST_Button_1_short_press_action_Mode_switch_2_3,
        LIST_Button_1_short_press_action_Eco_switch_none_med_max,
        LIST_Button_1_short_press_action_Eco_switch_none_med, 
    } tButton_1_short_press_action;

    void set_Button_1_short_press_action (uint8_t value);
    uint8_t get_Button_1_short_press_action();
    void display_Button_1_short_press_action();
    void save_Button_1_short_press_action(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BUTTON_1_LONG_PRESS_ACTION_ID 39
    #define SETTINGS_BUTTON_1_LONG_PRESS_ACTION_ID_STR "39"
    #define SETTINGS_BUTTON_1_LONG_PRESS_ACTION_NAME "Button_1_long_press_action"

    uint8_t Button_1_long_press_action;
    typedef enum LIST_Button_1_long_press_action {
        LIST_Button_1_long_press_action_None,
        LIST_Button_1_long_press_action_Speed_limitation_on_off,
        LIST_Button_1_long_press_action_Aux_on_off,
        LIST_Button_1_long_press_action_Mode_switch_1_2_3,
        LIST_Button_1_long_press_action_Mode_switch_2_3,
        LIST_Button_1_long_press_action_Eco_switch_none_med_max,
        LIST_Button_1_long_press_action_Eco_switch_none_med,
        LIST_Button_1_long_press_action_Antitheft_manual_lock_on,
        LIST_Button_1_long_press_action_Nitro_boost_continuous, 
    } tButton_1_long_press_action;

    void set_Button_1_long_press_action (uint8_t value);
    uint8_t get_Button_1_long_press_action();
    void display_Button_1_long_press_action();
    void save_Button_1_long_press_action(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BUTTON_2_SHORT_PRESS_ACTION_ID 40
    #define SETTINGS_BUTTON_2_SHORT_PRESS_ACTION_ID_STR "40"
    #define SETTINGS_BUTTON_2_SHORT_PRESS_ACTION_NAME "Button_2_short_press_action"

    uint8_t Button_2_short_press_action;
    typedef enum LIST_Button_2_short_press_action {
        LIST_Button_2_short_press_action_None,
        LIST_Button_2_short_press_action_Speed_limitation_on_off,
        LIST_Button_2_short_press_action_Aux_on_off,
        LIST_Button_2_short_press_action_Mode_switch_1_2_3,
        LIST_Button_2_short_press_action_Mode_switch_2_3,
        LIST_Button_2_short_press_action_Eco_switch_none_med_max,
        LIST_Button_2_short_press_action_Eco_switch_none_med, 
    } tButton_2_short_press_action;

    void set_Button_2_short_press_action (uint8_t value);
    uint8_t get_Button_2_short_press_action();
    void display_Button_2_short_press_action();
    void save_Button_2_short_press_action(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_BUTTON_LONG_PRESS_DURATION_ID 41
    #define SETTINGS_BUTTON_LONG_PRESS_DURATION_ID_STR "41"
    #define SETTINGS_BUTTON_LONG_PRESS_DURATION_NAME "Button_long_press_duration"

    uint8_t Button_long_press_duration;

    void set_Button_long_press_duration (uint8_t value);
    uint8_t get_Button_long_press_duration();
    void display_Button_long_press_duration();
    void save_Button_long_press_duration(uint8_t value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_WIFI_SSID_ID 42
    #define SETTINGS_WIFI_SSID_ID_STR "42"
    #define SETTINGS_WIFI_SSID_NAME "Wifi_ssid"

    String Wifi_ssid;

    void set_Wifi_ssid (String value);
    String get_Wifi_ssid();
    void display_Wifi_ssid();
    void save_Wifi_ssid(String value);
            
    /*-------------------------------------------------------*/

    #define SETTINGS_WIFI_PASSWORD_ID 43
    #define SETTINGS_WIFI_PASSWORD_ID_STR "43"
    #define SETTINGS_WIFI_PASSWORD_NAME "Wifi_password"

    String Wifi_password;

    void set_Wifi_password (String value);
    String get_Wifi_password();
    void display_Wifi_password();
    void save_Wifi_password(String value);

};

#endif