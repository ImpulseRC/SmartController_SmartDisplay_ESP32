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
- DC-DC module for 5V power

Check the project here : https://oshwlab.com/Koxx3/smartlcd-v1-3_copy

## After ordering the board PCB

Order the missing components !

Don't forget to order connectors :
- JST SM (2/3/6 pins)
- JST PH 2.0 (2/3/6 pins)

You can also add the external sensors :
- WCS1700 : current sensor
- DHT22 : temperature and humity sensor

## Minimal soldering

![Jumper for direct throlle](/img/pcb_typon_mini1.png)

![Capacitor](/img/pcb_typon_mini2.png)

![JST-SM cables - display](/img/pcb_typon_mini4.png)

Wiring (left to right) :
1 - black - 
2 - red - 
3 - orange or blue - throttle signal
4 - white - GND
5 - yellow - battery feedback
6 - green - battery power

![JST-SM cables - controller](/img/pcb_typon_mini5.png)


Wiring (left to right) :
1 - black - 
2 - red - 
3 - orange or blue - throttle signal
4 - white - GND
5 - yellow - battery feedback
6 - green - battery power

... and finish with ESP32

![ESP32](/img/pcb_typon_mini3.png)


## Wrap it
You need a wrap for 10.5cm / diameter 33mm
[Link](https://fr.aliexpress.com/item/4000787511699.html)

## Once you receive the board and the components 

Assemble it, and upload the application :D

[Next steps ...](RUN.md)

