# [ SmartController & SmartDisplay ]
⚠️ **Warning : this is work in progress. I decline all responsability about using informations from this project** ⚠️

To contribute and help this project :

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/pools/c/8ut4175ux4) 

![Logo](/img/smart.png)

## What is SmartController ?
It's a combo of electronic and smartphone application. It extend all features from original Minimotors EYE LCD and Minimotors controller, but it can also interface VESC, SmartESC adnd Kelly controllers.
The electronic board will interract with most of the e-scooter electronic when you plug it.
You simply place the little box inside the deck and connect it to the controller (and other electric parts if you want more features)

### Requirements
- An e-scooter with any supported controllers (single or dual)
- An power supply between 12V and 100V... (possible with external DC-DC providing 12V or 5V if you have 24S or more)
- If you want to use progressive brake feature, you must ensure no more than 60V pass in the brake handle (issue noted only for Kaabo)
- The electronics (ESP32 Dev KitC V4 + SmartController shield + JST SM/PH connectors)
- Some electronic skills

### What can be done ?
I suggest you to have a look at all planed/added features in the image below.
There is almost no limit in custom features.
The controller power cannot exceed the nominal power, but with a shunt, you can increase the acceleration and still have a current control loop to limit the current by software (and avoid burning the controller).

Most settings will be configurable by the smartphone, and additionnal hardware buttons will allow you to control specific features.

Some examples : 
- It can lock the escooter with bluetooth proximity (with a beacon, the smartphone or any bluetooth device). When locked, the power is so reduced that nobody can ride it is you aren't close enouth. You can also manually lock the scooter with the Smartphone.

- You find the acceleration trigger to agressive at low speed ? you can change the acceleration curve for smooth trigger at low speed, and still have the beast once you push the trigger harder

- You want a mode for some weather conditions like 'rainy' with less torque ? no problem. Use fast settings access on the application dashboard or configuration hardware buttons.

- You feel the electric brake too strong at full power ? The progressive electric braking adjust the brake power with digital, or better, analog brake lever pressure sensor in real time.

- You can to limit speed to legal limits at startup ? Simply enable the option, and the speed limit can be removed with a brake pressure at startup or the smartphone.

- You want to control all settings for the Smartphone ? Use the Android native application or you can connect any device to the SmartElec in Wifi

- You want to know if there is not issue inside you escooter deck ? Temperature and humidity sensors will tell you is water entered inside the deck or if the ESC/battery is overheating.


**>>> [Check all detailed features here](/documents/FEATURES.md) <<<**

## Board assembly (v1.3.2)
![Ass1](/img/20210109_134700.jpg)

![Ass2](/img/20210109_134706.jpg)

![Ass3](/img/20210109_134713.jpg)

## Wrapping & Size
Current PCB size : 6cm x 3cm x 2cm

![Idea](/img/20210109_160006.jpg)

## Electronic
### Compatibility
The software is designed for [ESP32 Dev Kit v4](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html) microcontroller.

### Schematics
[PCB schematic v1.4.2](https://oshwlab.com/Koxx3/smartlcd-v1-4_copy)

[old - PCB schematic v1.3.2](https://oshwlab.com/Koxx3/smartlcd-v1-3_copy_copy)

![PCB from easyEDA](/img/pcb_typon.png)

![PCB from easyEDA](/img/smartControllerPcb.PNG)

### Protype parts list
[Google sheet](https://docs.google.com/spreadsheets/d/11n0oXzwr5ERSipWXZO53-mBwc6KPEdF8Q-aYTcDPNbk/edit?usp=sharing)

### Inspiration to understand controller electronic
[China BLDC motor controller 36v 250W](http://avdweb.nl/Article_files/Solarbike/Motor-controller/China-BLDC-motor-controller-36V-250W.pdf)

## Applications
### Android 
[SmartElec Application - Google play](https://play.google.com/store/apps/details?id=org.koxx.smartcntrl)

### iPhone
I have no skills in iPhone apps. If anyone wants to develop, let me know 😉

## TODO

- [✅] Serial Minimotors
    - [✅] Read/write serial link LCD_TO_CNTRL
    - [✅] Read/write serial link CNTRL_TO_LCD
    - [✅] Decode speed/mode/brake/regulator from serial link
    - [✅] Frame error detection
    - [N PROGRESS 🔄] Error codes processing
        - [✅] Controller under voltage error
        - [✅] Throttle voltage
        - [✅] Brake voltage
        - [ ] Controller other error
       
- [✅] VESC
    - [✅] Read serial link
    - [✅] Decode datas : speed, voltage, current
    - [✅] Set speed 1/2/3 modes
    - [✅] Electric brake max power setting
    - [✅] PAS
    - [✅] Lock (anti-theft or manual)
    - [✅] Speed computing
    - [✅] Temperature feedback
    - [✅] Brake power smartphone feedback
    - [✅] Speed limiter
    - [✅] Power processing / display
    - [✅] Brake forbiden on high voltage
    - [✅] Electric analog brake processing
    - [✅] Electric digital brake processing
    - [ ] Dual VESC
      - [ ] Change speed limits
      - [ ] Get infos
    - [ ] Error codes processing
      - [ ] Temperature alarm
      - [ ] Other errors

- [✅] Zero/Apollo
    - [✅] Read serial link
    - [✅] Decode datas : speed, mode, power, pas ...
    - [✅] Set speed 1/2/3 modes
    - [✅] Speed computing
    - [✅] Speed limiter
    - [✅] Lock (anti-theft or manual)
    - [✅] PAS
    - [✅] Set accel mode
    - [✅] Electric brake max power setting
    - [✅] Brake power smartphone feedback
    - [✅] Brake forbiden on high voltage
    - [✅] Electric analog brake processing
    - [✅] Electric digital brake processing
    - [ ] Error codes processing

- [✅] Kelly
    - [✅] Read serial link
    - [✅] Decode datas : speed, voltage, controller temperature
    - [ ] Error codes processing
 
- [IN PROGRESS 🔄] [SmartESC v1](https://github.com/Koxx3/SmartESC_STM32)
    - [✅] Read serial link
    - [✅] Decode datas : speed, voltage, controller temperature
    - [ ] Error codes processing
 
- [ ] Serial Zero / Appolo / Weped

- [✅] Bluetooth 
    - [✅] Communication with Android
    - [✅] Dashboard
    - [✅] Anti-theth with smartphone
    - [✅] Anti-theth with beacon (scan & rssi detection)
    - [✅] Lock beacon or device settings
    - [✅] SmartController connection security (PIN code)
    - [✅] SmartController connection with multi devices (BT device choice)
    - [✅] Settings
    - [✅] Flash firmware

- [✅] Wifi
    - [✅] Settings
    - [✅] Flash firmware
    - [ ] Dashboard

- [✅] Other inputs/outputs ↔️
    - [✅] Read current with WCS1700
    - [✅] Read battery voltage
    - [✅] Read tempertature/humidity with DHT11/DHT22
    - [✅] Read break handle position on serial
    - [✅] Read break handle position on standard brake handle
    - [✅] Read break handle position on analog brake handle
    - [✅] Read buttons
    - [✅] Send break handle position to controller
    - [✅] Send LED status
    - [✅] Send optocopler order
    - [✅] Internal temperature sensor
    - [✅] Throttle signal regeneration
    - [IN PROGRESS 🔄] External expansion boards

- [✅] Power 🔋
    - [✅] Convert 12V to 5V
    - [✅] Convert 80V to 5V
    - [✅] Convert 100V to 5V

- [ ] Features ⚙️
    - [✅] Save settings in non volatile memory
    - [✅] Progressive electric braking (software detection)
    - [✅] Progressive electric braking (hardware analog detection)
    - [✅] OTA update
    - [✅] Current measure auto calibration (at startup)
    - [✅] Current measure manual calibration
    - [✅] Speed limiter at startup
    - [✅] Configurable speed limit
    - [✅] Remote physical button
        - [✅] Speed limiter ON/OFF
        - [✅] Lock ON      
        - [✅] Nitro Boost continuous
        - [✅] Nitro Boost ON/OFF
        - [✅] Aux ON/OFF       
        - [✅] Switch modes 1/2/3 or 2/3   
        - [✅] Settings access
    - [✅] Disable electric brake with full battery
    - [✅] Manual calibration for analog brake
    - [✅] Manual calibration for voltage
    - [✅] Use brake switch as startup for speed limiter
    - [✅] LCD Speed adjustment
    - [✅] Exponential acceleration curve
    - [✅] PAS switch
    - [✅] Custom acceleration curves (linear/expo/custom)
    - [✅] Automatic power off
    - [IN PROGRESS 🔄] Automatic ECO mode on low battery 
    - [ ] Dynamic BLE debug infos

- [✅] Android application 📱
    - [✅] Display : 
        - [✅] Speed
        - [✅] Mode
        - [✅] Voltage
        - [✅] Current
        - [✅] Power
        - [✅] Brake mode (PA)
        - [✅] Max speed
        - [✅] Max power
        - [✅] Max current
        - [✅] Temperature
        - [✅] Humidity
        - [✅] Time
        - [✅] Moving time
        - [✅] Odometer / distance
        - [✅] Trip distance
        - [✅] Average speed
        - [✅] Autonomy
        - [✅] Brake forbiden
        - [✅] Errors
    - [✅] Auto-launch app with NFC tag
    - [✅] Parameters custom settings
    - [✅] Data logging
    - [✅] History graphics
    - [ ] Wizzard for escooter model choice
    - [ ] Wizzard for calibrations
    - [ ] UI configuration (hide items)
   
- [ ] iPhone application 🍏
    - [ ] A kind developper to do this part ? 😇


## Produce your own board
- [Here](/documents/MAKE_IT.md)

## Wiring
- [Here](/documents/WIRING.md)

## Run it !
- [Here](/documents/RUN.md)

## Settings description
- [Here](/documents/help_settings_en.md)

## Ressources 🔗
- [Serial links data decoding - Excel XLSX](/documents/MINIMO.xlsx)

## Donate to support
- [If you want to support me, click here !](https://www.paypal.com/pools/c/8ut4175ux4)

## License
[The code is under GNU GPL v3 license](/LICENSE)
All code usage must be redistributed in public.
