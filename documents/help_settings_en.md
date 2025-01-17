
# Settings manual

## Escooter characteristics
### Wheel size
Valid configuration : SmartController / SmartDisplay<br>
Default value : 10.0 (inches)<br>
<br>
Usage : Wheel size (in inches) is used to adjust the speed and distance when riding.<br>
                
### Number of poles pairs
Valid configuration : SmartController / SmartDisplay<br>
Default value : 15<br>
<br>
Usage : Motors number of poles are used to compute speed/distance. Check you manual to set the correct value. If the manual specify '30 poles', set 15.<br>
                
### Battery nominal voltage
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - 36V (42V full / 10S) (value = 0)<br>
    - 48V (54,6V full / 13S) (value = 1)<br>
    - 52V (58,8V full / 14S) (value = 2)<br>
    - 60V (67,2V full / 16S) (value = 3)<br>
    - 72V (84V full / 20S) (value = 4)<br>
    - 86V (100,8V full / 24S) (value = 5)<br>
Default value : 2<br>
<br>
Usage : Battery voltage is used to compute the autonomy left and charge indicator. Check your manuel or charger (it indicate full charge voltage) to set the correct setting.<br>
                
### Battery maximum distance
Valid configuration : SmartController / SmartDisplay<br>
Default value : 40 (kilometers)<br>
<br>
Usage : Used to compute autonomy. Set your regular max distance with one full charge.
Autonomy is computed following the LG MJ1 discharge curve.<br>
                

## General
### Speed limiter at startup
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Enable speed limit after power on. It set a power limit on most escooters (Dualtron/Speedway/Zero �) or real speed limit on VESC.
For Dualtron/Speedway/Zero, you need to find the right setting if you want to limit it to the legal speed limit.
Once enabled, it will limit the displayed speed to 25 km/h.<br>
                
### Speed limiter max speed
Valid configuration : SmartController / SmartDisplay<br>
Default value : 37<br>
<br>
Usage : Power limit is expressed in percent (same power setting as in your manual). For VESC, the speed limit is set to 25 Km/h.<br>
                
### Bluetooth lock mode
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - None (value = 0)<br>
    - Smartphone connected (value = 1)<br>
    - Smartphone connected or beacon visible (value = 2)<br>
    - Beacon visible (value = 3)<br>
Default value : 0<br>
<br>
Usage : Lock the scooter if bluetooth device check is not successful :
- None : no bluetooth peripheral check, no lock mecanism.
- Smartphone connected : your smartphone needs to be connected to the SmartElec device in Bluetooth to unlock the scooter.
- Smartphone connected or beacon visible : your smartphone needs to be connected OR a BLE (Bluetooth Low Energy) must be in range beacon of the SmartElec device in Bluetooth to unlock the scooter.
- Beacon visible : BLE beacon must be in range of the SmartElec device in Bluetooth to unlock the scooter.
<b>Those modes are used as anti-theft protection</b>. If an thief try to still you escooter, as soon as the escooter is out of range of your bluetooth device, it will cut power of the escooter.<br>
                
### PIN code
Valid configuration : SmartController / SmartDisplay<br>
Default value : 147258<br>
<br>
Usage : Bluetooth PIN code is used when you want to connect a smartphone to your SmartElec device. <b>Change it to protect your SmartElec device from any anybody connection.</b><br>
                
### Beacon Mac Address 1
Valid configuration : SmartController / SmartDisplay<br>
Default value : aa:bb:cc:dd:ee:ff<br>
<br>
Usage : To search a beacon you must specify the beacon mac address. 
Search on your smartphone store for a 'BLE Scanner', it will scan all Bluetooth devices and the MAC address (an unique identifier) for the beacon, then enter this MAC address in this setting.<br>
You can use any Bluetooth Low Energy device as beacon (any BLE band/bracelet for example) or use a BLE beacon (10$ on aliexpress).
Important : you cannot search for most smartphone because they are protected against search scan.<br>
                
### Beacon Mac Address 2
Valid configuration : SmartController / SmartDisplay<br>
Default value : aa:bb:cc:dd:ee:ff<br>
<br>
Usage : Same as 'Beacon Mac Address 1' but for a second device. If one is found in range, the escooter is unlocked.<br>
                
### Smartphone or Beacon Mac range
Valid configuration : SmartController / SmartDisplay<br>
Default value : -80 (dB)<br>
<br>
Usage : Minimal reception power of the beacon to unlock the escooter. This is in dB, it means a -100dB value will be a longer distance than -50dB.<br>
                
### Original display speed adjustment (in percent)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0 (percent)<br>
<br>
Usage : Use this value to correct the speed on the escooter display.
You can increase or decrease the speed.
Set at -50%, it will display 25km/h when riding at 50km/h.<br>
                
### Temperature warning
Valid configuration : SmartController / SmartDisplay<br>
Default value : 70 (celcuis)<br>
<br>
Usage : Trig an error indicator on the display or the smartphone application if this temperature threshold is reached. If you place the temperature sensor inside the deck, it will warn you if the controller or the battery are too hot.<br>
                
### Humidity warning
Valid configuration : SmartController / SmartDisplay<br>
Default value : 80 (RH)<br>
<br>
Usage : Trig an error indicator on the display or the smartphone application if this humidy threshold is reached. If you place the humidity sensor inside the deck, it will warn you if the water is entered inside the deck.<br>
                
### Automatic power off
Valid configuration : SmartDisplay<br>
Possible values : <br>
    - None (value = 0)<br>
    - 2 min (value = 1)<br>
    - 3 min (value = 2)<br>
    - 4 min (value = 3)<br>
    - 5 min (value = 4)<br>
    - 10 min (value = 5)<br>
    - 15 min (value = 6)<br>
    - 20 min (value = 7)<br>
    - 30 min (value = 8)<br>
    - 60 min (value = 9)<br>
Default value : 0<br>
<br>
Usage : Automatically shutdown the escooter after this period when escooter is not moving.<br>
                

## Smartphone display
### Speed adjustment (in percent)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Use this value to correct the speed on the smartphone display.
You can increase or decrease the speed.<br>
                
### Aux relay name
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - AUX (value = 0)<br>
    - DUAL (value = 1)<br>
    - LIGHT (value = 2)<br>
    - HORN (value = 3)<br>
    - RELAY (value = 4)<br>
Default value : 0<br>
<br>
Usage : Change the name of the auxilary relay on the display and smartphone for the integrated relay action. Exemple : if you connect a light, you can display "light" on the dashboard instead of "aux".<br>
                
### Display GPS speed instead of escooter speed
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Display GPS speed instead of escooter speed on the smartphone display.<br>
                

## SmartDisplay
### Default mode at startup
Valid configuration : SmartDisplay<br>
Default value : 3<br>
<br>
Usage : Default speed mode after escooter power up.<br>
                
### Default eco mode at startup
Valid configuration : SmartDisplay<br>
Possible values : <br>
    - Max (value = 0)<br>
    - Medium (value = 1)<br>
    - None (value = 2)<br>
Default value : 2<br>
<br>
Usage : Default eco mode after escooter power up.<br>
                
### Default acceleration
Valid configuration : SmartDisplay<br>
Possible values : <br>
    - Maximum (value = 0)<br>
    - Very fast (value = 1)<br>
    - Fast (value = 2)<br>
    - Medium (value = 3)<br>
    - Slow (value = 4)<br>
    - Very slow (value = 5)<br>
Default value : 0<br>
<br>
Usage : Default acceleration mode after escooter power up.<br>
                
### Default electric brake at startup
Valid configuration : SmartDisplay<br>
Default value : 3<br>
<br>
Usage : Default electric brake power mode after escooter power up.<br>
                
### PAS enabled
Valid configuration : SmartDisplay<br>
Default value : 0<br>
<br>
Usage : The 'pedal assitance switch' will force you to push the escooter to start the engine. 
If you don't push the scooter, the throttle is not effective. The motor will engage as soon as 1km/h is reached.<br>
                
### ABS enabled
Valid configuration : SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Enable the anti-lock electric braking system (not advised, not well implemented on most escooters),<br>
                
### Display brightness
Valid configuration : SmartDisplay<br>
Default value : 100<br>
<br>
Usage : Set the SmartDisplay screen brightness.<br>
                
### Display splash screen
Valid configuration : SmartDisplay<br>
Default value : 1<br>
<br>
Usage : Enable the splash screen at escotter startup<br>
                
### Rotate screen
Valid configuration : SmartDisplay<br>
Possible values : <br>
    - Normal (value = 0)<br>
    - Inverted (value = 1)<br>
Default value : 0<br>
<br>
Usage : Rotate screen if you mount the display in un unorthodox way.<br>
                

## Electric brake
### Progressive mode
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Enable the electric brake progressive mode.<br>
                
### Smart brake type
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - Controller (value = 0)<br>
    - Smart - Digital brake lever (value = 1)<br>
    - Smart - Analog brake lever (value = 2)<br>
    - Smart - Digital brake + throttle (exp) (value = 3)<br>
Default value : 0<br>
<br>
Usage : If you enable the electric progressive mode, the braking feedback must arrive to the SmartElec device. <b>There is mulitple possibilities to wire the brake on the SmartElec and you MUST select the brake type according to your wiring</b> :
- Controller : no specific wiring required, the brake feedback will come from the controller. This is slower and will add a delay of 200/300ms between the brake pressure and the electric brake activation. The brake force will be determined by the brake lever pressure time. Longer you press, stronger the electric brake will become.
- Smart - Digital brake lever : a standard on/off brake lever is wired directly to the SmartElec device. This wiring has a faster reaction. The brake force will be determined by the brake lever pressure time. Longer you press, stronger the electric brake will become.
- Smart - Analog brake lever : an analog brake lever (xiaomi type or any hall sensor brake lever) is wired to directly to the SmartElec device. This wiring is the best. The brake force will be determined by the brake lever pressure force.
- Smart - Digital brake + throttle (experimental) : a standard on/off brake lever is wired directly to the SmartElec device and the throttle pressure set the brake force. You will need time to use this mode when riding.<br>
                
### Input min voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 650 (millivolts)<br>
<br>
Usage : Throttle input signal voltage when the throttle is released.
Note : if the motor is spinning when the throttle is not pressed, try to decrease this value.<br>
                
### Input max voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 3950 (millivolts)<br>
<br>
Usage : Throttle input signal voltage when the throttle is fully pressed
Note : if the motor is not reaching max speed when the throttle is pressed, try to increase this value.<br>
                
### Min power value
Valid configuration : SmartController / SmartDisplay<br>
Default value : 1<br>
<br>
Usage : Define the minimum electric brake force when you start pressing the brake lever.
Note : don't forget to calibrate the brake lever pressure for a better feeling.<br>
                
### Max power value
Valid configuration : SmartController / SmartDisplay<br>
Default value : 5<br>
<br>
Usage : Define the maximum electric brake force when you pressing the brake lever.
Note : don't forget to calibrate the brake lever pressure for a better feeling.<br>
                
### Time between mode shift
Valid configuration : SmartController / SmartDisplay<br>
Default value : 500 (milliseconds)<br>
<br>
Usage : When using a digital brake lever (on/off switch on the lever), this period will determine when the brake force is increased to the next lever (from min to max) as long as you keep the brake active.
Exemple : brake min = 1 / brake max = 3 / brake switch period = 500ms. When you start pressing the brake, it will set a electric brake force at 1. If you keep the brake pressed, 500ms later, it will set a electric brake force at 2, and 500ms later to 3. It will remain at 3 (max) until you release the brake lever.<br>
                
### Disabled on high battery voltage
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Prevent power surge when braking if the battery is full or almost full. 
Electric brake generate current/voltage when used. If you use the electric brake when the battery is battery is full, the battery cannot take the energy and the controller will try to dissipate the energy... and can heat/blow.
This option disable the electric brake until the baterry reach a threshold.<br>
                
### Disabled percent limit
Valid configuration : SmartController / SmartDisplay<br>
Default value : 100 (percent)<br>
<br>
Usage : Battery load percent threshold to reach to enable electric brake.<br>
                

## Throttle
### Throttle regeneration
Valid configuration : SmartController / SmartDisplay<br>
Default value : 0<br>
<br>
Usage : Enable throttle signal regeneration.
This option allow you to modify the acceleration curve to make it more/less dynamic with different acceleration curves.
<b>To enable this feature, you must wire the trottle jumpers according to the WIRING documentation.</b><br>
                
### Input min voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 650 (millivolts)<br>
<br>
Usage : Throttle input signal voltage when the throttle is released.
Note : if the motor is spinning when the throttle is not pressed, try to decrease this value.<br>
                
### Input max voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 3950 (millivolts)<br>
<br>
Usage : Throttle input signal voltage when the throttle is fully pressed
Note : if the motor is not reaching max speed when the throttle is pressed, try to increase this value.<br>
                
### Output min voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 800 (millivolts)<br>
<br>
Usage : Throttle ouput signal voltage when the throttle is released.
Note : if the motor is spinning when the throttle is not pressed, try to decrease this value.<br>
                
### Output max voltage (in millivolts)
Valid configuration : SmartController / SmartDisplay<br>
Default value : 3350 (millivolts)<br>
<br>
Usage : Throttle output signal voltage when the throttle is fully pressed
Note : if the motor is not reaching max speed when the throttle is pressed, try to increase this value.<br>
                
### Output curve
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - Linear (value = 0)<br>
    - Exponential 1 (value = 1)<br>
    - Exponential 2 (value = 2)<br>
    - Exponential 3 (value = 3)<br>
    - Exponential 4 (value = 4)<br>
    - Custom 6 points (value = 5)<br>
Default value : 2<br>
<br>
Usage : This option modify the throttle response and acceleration curve.
There is 3 main modes :
- linear : same as original, except you can put  an offset to increase the dead zone (with min input voltage)
- exponential : those curves follow exponential functions, the acceleration becomes more violent as you reach the end the trigger pressure. Exponential 1 is soft but more violent than linear, Exponential 4 is very violent.
- custom 6 points : 2 points are fixed (0% trigger pressure = 0% output / 100% trigger pressure = 100% output), with the next option, you can the set the output percent for 20, 40, 60 and 80% pressure on the trigger. It will interpolate the values between those pressure percentage to determine the ouput throttle percentage.<br>
                
### Custom output curve points
Valid configuration : SmartController / SmartDisplay<br>
Default value : 20,40,60,80<br>
<br>
Usage : String of 4 values separated by commas.
It will determine the output level for the 4 points (see custom curve option above) of 20, 40, 60, 80% pressure.
Example with : 7, 15, 45, 75
![](throttle_custom_curve.png)<br>
                

## Escooter buttons
### Button 1 short press action
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - None (value = 0)<br>
    - Speed limit ON/OFF (value = 1)<br>
    - Aux ON/OFF (value = 2)<br>
    - Mode switch 1/2/3 (value = 3)<br>
    - Mode switch 2/3 (value = 4)<br>
    - Eco switch NONE/MED/MAX (value = 5)<br>
    - Eco switch NONE/MED (value = 6)<br>
Default value : 0<br>
<br>
Usage : Set the button 1 short press action (for external buttons wired to the SmartElec) :
- None : no action
- Speed limitation ON/OFF : enable/disable the speed limiter
- Aux ON/OFF : enable/disable the auxiliary relay output
- Mode switch 1/2/3 : switch between speed modes
- Mode switch 2/3 : switch between speed modes
- Eco switch NONE/MED/MAX : switch between eco modes
- Eco switch NONE/MED : switch between eco modes
- Anti-theft manual lock ON : lock the escooter (motor power is locked, nobody can steal & ride with this mode)
- Nitro boost continuous : switch speed mode to 3 while the button is pressed, then go back to original speed mode<br>
                
### Button 1 long press action
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - None (value = 0)<br>
    - Speed limitation ON/OFF (value = 1)<br>
    - Aux ON/OFF (value = 2)<br>
    - Mode switch 1/2/3 (value = 3)<br>
    - Mode switch 2/3 (value = 4)<br>
    - Eco switch NONE/MED/MAX (value = 5)<br>
    - Eco switch NONE/MED (value = 6)<br>
    - Anti-theft manual lock ON (value = 7)<br>
    - Nitro boost continuous (value = 8)<br>
Default value : 0<br>
<br>
Usage : Set the button 1 long press action (for external buttons wired to the SmartElec) :
- None : no action
- Speed limitation ON/OFF : enable/disable the speed limiter
- Aux ON/OFF : enable/disable the auxiliary relay output
- Mode switch 1/2/3 : switch between speed modes
- Mode switch 2/3 : switch between speed modes
- Eco switch NONE/MED/MAX : switch between eco modes
- Eco switch NONE/MED : switch between eco modes
- Anti-theft manual lock ON : lock the escooter (motor power is locked, nobody can steal & ride with this mode)
- Nitro boost continuous : switch speed mode to 3 while the button is pressed, then go back to original speed mode<br>
                
### Button 2 short press action
Valid configuration : SmartController / SmartDisplay<br>
Possible values : <br>
    - None (value = 0)<br>
    - Speed limitation ON/OFF (value = 1)<br>
    - Aux ON/OFF (value = 2)<br>
    - Mode switch 1/2/3 (value = 3)<br>
    - Mode switch 2/3 (value = 4)<br>
    - Eco switch NONE/MED/MAX (value = 5)<br>
    - Eco switch NONE/MED (value = 6)<br>
Default value : 0<br>
<br>
Usage : Set the button 2 short press action (for external buttons wired to the SmartElec) :
- None : no action
- Speed limitation ON/OFF : enable/disable the speed limiter
- Aux ON/OFF : enable/disable the auxiliary relay output
- Mode switch 1/2/3 : switch between speed modes
- Mode switch 2/3 : switch between speed modes
- Eco switch NONE/MED/MAX : switch between eco modes
- Eco switch NONE/MED : switch between eco modes
- Anti-theft manual lock ON : lock the escooter (motor power is locked, nobody can steal & ride with this mode)
- Nitro boost continuous : switch speed mode to 3 while the button is pressed, then go back to original speed mode
Note : button 2 long press action allow you to enter the settings menu.<br>
                
### Button long press duration
Valid configuration : SmartController / SmartDisplay<br>
Default value : 3 (seconds)<br>
<br>
Usage : If you press the button for this period, the SmartElec will launch the "long press" action.<br>
                

## OTA update
### Wifi network name (SSID)
Valid configuration : SmartController / SmartDisplay<br>
Default value : <br>
<br>
Usage : Wifi network SSID/name used for software updates.<br>
                
### Wifi password
Valid configuration : SmartController / SmartDisplay<br>
Default value : <br>
<br>
Usage : Wifi network password used for software updates.<br>
                

