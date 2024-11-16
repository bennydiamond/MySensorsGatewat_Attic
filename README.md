# MySensorsGateway_Attic
MySensors Ethernet Gateway with a couple sensors locally attached.
This is going in my attic for the following reasons:

- Offer a central point around my property for MySensors Gateway purposes
- Monitor Temperature and humidity in the attic
- Monitor access trap door going to the attic to help with an automation on Home Assistant to control lights in the attic.

# Hardware
Uses an Arduino UNO R3

Ethernet Shield V1 W5100

SHT21 Temperature + Humidity sensor

Reed switch normally open

Couple of LEDs


# Libraries
[MySensors](https://github.com/mysensors/MySensors) to set up the device as an Ethernet gateway as well as expose sensors.

[Ethernet](https://github.com/arduino-libraries/Ethernet) because obviously.

[tinySHT2X](https://github.com/RobTillaart/tinySHT2x) because it's lean and does what it needs and nothing more.


# Quirks
This project is very much tailored to my needs.
MySensors library on platformio includes a `MyConfig.h` file that kinda needs to be modified and thus must be moved out of the library files managed by PlatformIO.
So I copied it to a locally managed directory and moved out the `MyConfig.h` file to modify it.
