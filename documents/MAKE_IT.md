# How to make the your own ?

All electronic designs and software are open source. So, you can easily make your own board if you have some electronic skills.

## Produce the board with [JLCPBC](https://jlcpcb.com/)

The first step is : produce your board.
JLCPCB has interesting capacities : [PCB assembly](https://jlcpcb.com/smt-assembly).
They print your PCB and solder components on it.

It cost arround 40/50€ to produce the board.

The issue : they don't have all components.

You'll have to order the missing components on aliexpress or any electronic store and solder it yourself.

The major non included components are :
- SMD relays
- connectors
- Power supply capacitor
- Solid State Relay (DIP4 package)

Check the electronic project link on the [main github page](https://github.com/Koxx3/SmartController_SmartDisplay_ESP32#Schematics)

# After ordering the board PCB

Order the missing components !

Don't forget to order connectors :
- JST SM (2/3/6 pins)
- JST PH 2.0 (2/3/6 pins)

You can also add the external  :
- WCS1700 : current sensor
- Expansion boards (PRO version only)

# Port usage

![PCB](/img/PCB_SC v1.6.2_2021-08-03-2.svg)
![Alt text](/img/PCB_SC v1.6.2_2021-08-03-2.svg)
<img src="../img/PCB_SC v1.6.2_2021-08-03-2.svg">

/!\ Square in the connector mark the pin number 1.

## [LC] For original controller display cable

Minimotors/Zero/Vsett wiring (left to right) :
- 1 - serial / ESP to LCD
- 2 - serial / LCD to ESP
- 3 - throttle signal
- 4 - GND
- 5 - battery feedback
- 6 - battery power

VESC wiring : not connected

## [CT] For controller cable

Minimotors wiring (left to right) :
- 1 - black - serial / controller to ESP
- 2 - red - serial / ESP to controller
- 3 - orange or blue - throttle signal
- 4 - white - GND
- 5 - yellow - battery feedback
- 6 - green - battery power

VESC wiring (left to right) :
- 1 - yellow - RX ESP / TX VESC
- 2 - white - TX ESP / RX VESC
- 3 - red - throttle
- 4 - black - GND
- 5 - not connected
- 6 - not connected

## [BKO] Brake output

Wiring :
- no pin order (relay)
- max voltage/current : depends of Solid state relay you placed

## [REL] Relay output

Wiring :
- no pin order (relay)
- max voltage/current : depends of Solid state relay you placed

## [BKI] Brake input

Analog brake wiring (right to left):
- 1 - 5V
- 2 - GND
- 3 - signal

Digital brake wiring (right to left):
- 1 - brake witch
- 2 - not connected
- 3 - brake witch

## [OWB] Expansion board connector

Wiring (right to left):
- 1 - 5V
- 2 - GND
- 3 - signal


## [WCS] WCS1700 current sensor

Wiring (right to left):
- 1 - 5V
- 2 - GND
- 3 - signal

## [LCD] LCD display

Wiring :
- 1 - GND
- 2 - 3.3V
- 3 - SPI CLK
- 4 - SPI MOSI
- 5 - SPI RESET
- 6 - SPI DC
- 7 - Backlight control 3.3V
- 8 - Backlight control 5V

## [THR] Throttle signals

Wiring :


## [BTN] Buttons & LEDs

Wiring :
- 1 - GND - black
- 2 - button power - green
- 3 - buttons LEDs - white
- 4 - button 2 - brown
- 5 - button 1 - yellow

# Finish with ESP32

- leave right pin on the right unconnected (unused)
- USB port on the left side

# Wrap it
You need a wrap for 10.5cm / diameter 33mm
[Link](https://fr.aliexpress.com/item/4000787511699.html)

# Once you assembled the board and the components 

Upload the applications :D

[Next steps ...](RUN.md)
