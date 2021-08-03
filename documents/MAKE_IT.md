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

# Ports usage and jumpers

<img width="200%" height="200%" src="../img/PCB_SC v1.4.2_2021-08-03-2.svg">

:warning: Square in the connector mark the pin number 1. :warning:

## Ports

### [LC] For original controller display cable

Minimotors/Zero/Vsett wiring :
- 1 - serial / ESP to LCD
- 2 - serial / LCD to ESP
- 3 - throttle signal
- 4 - GND
- 5 - battery feedback
- 6 - battery power

VESC wiring : not connected

### [CT] For controller cable

Minimotors/Zero/Vsett wiring :
- 1 - serial / controller to ESP
- 2 - serial / ESP to controller
- 3 - throttle signal
- 4 - GND
- 5 - battery feedback
- 6 - battery power

VESC wiring :
- 1 - RX ESP / TX VESC
- 2 - TX ESP / RX VESC
- 3 - throttle
- 4 - GND
- 5 - not connected
- 6 - not connected

### [BKO] Brake output

Wiring :
- no pin order (relay)
- max voltage/current : depends of Solid state relay you placed

## [REL] Relay output

Wiring :
- no pin order (relay)
- max voltage/current : depends of Solid state relay you placed

### [BKI] Brake input

Analog brake wiring :
- 1 - signal
- 2 - GND
- 3 - 5V

Digital brake wiring :
- 1 - brake switch
- 2 - not connected
- 3 - brake switch

### [WCS] WCS1700 current sensor

Wiring:
- 1 - signal
- 2 - GND
- 3 - 5V

### [LCD] LCD display

Wiring :
- 1 - GND
- 2 - 3.3V
- 3 - SPI CLK
- 4 - SPI MOSI
- 5 - SPI RESET
- 6 - SPI DC
- 7 - Backlight control 3.3V
- 8 - Backlight control 5V

### [THR] Throttle signals

Wiring :
- 1 - signal
- 2 - GND
- 3 - 5V

### [BTN] Buttons & LEDs

Wiring :
- 1 - button 1
- 2 - button 2
- 3 - buttons LEDs
- 4 - button power
- 5 - GND

### [OW] Expansion board connector

Reserved for PRO version.

## Jumpers and other selections

### [JTH] Throttle signal
If you want to use the throttle curve modification of the Smart, solder 1&2 and 3&4 on the SMD jumper (don't bridge 2&3)
If you don't want to modify the throttle signal, solder 2&3 on the SMD jumper.

:warning: The throttle signal modification by the Smart boards is dangerous because if the software crash, the escooter motor can continue to accelerate even if the throttle is released. Multiple protections have been added, but the risk still exists. Use it at your own risks ! :warning:

### [JPWR] Power switch & source
For SmartDisplay, you have a power latch. It allows to power the board and the escooter from the power button (see "Buttons" connector).
If you want to use the latch, close 1&2 on the SMD jumper.
If your controller needs a power feedback, solder 1&2&3.
For SmartController, you don't need to sodler anything.

### [X] VESC UART in 3.3V
- remove R20, R10, R3
- solder X jumper

# Finish with ESP32

- leave right pin on the right unconnected (unused)
- USB port on the left side

# Wrap it
You need a wrap for 10.5cm / diameter 33mm
[Link](https://fr.aliexpress.com/item/4000787511699.html)

# Once you assembled the board and the components 

Upload the applications :D

[Next steps ...](RUN.md)
