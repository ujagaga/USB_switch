# USB_switch

Device using ESP8266 WiFi module and 4 relays to switch USB connection between two computers.
This allows having a USB HUB with a keyboard and mouse connected to two computers, while choosing the host via python script.
The USB connector is designed to first remove communications pins and then the power pins when disconnecting.
When connecting, the power pins should be first to connect, then the communication pins.
I use 4 relays each with two switches, two of which are used for power and communication on one USB cable and the other two on the other USB cable.
The switching is done by sending a command via UDB broadcast at specific port. This way we do not need to worry about the IP address of the device.
The WiFi credentials are hard-codded, so please edit the code to your preferences.
There is also an optional toggle button.

## How To Start

1. Open ESP8266_USB_sw folder in Arduino IDE.
2. Rename "config.h.example" to "config.h" and adjust your WiFi credentials.
3. Program an ESP8266 based module.
4. Build the circuit according to "Schematic.png".
5. Plugin the two USB cables to two computers.
6. Copy "switch.py" to both computers.
7. To switch USB ports, run:

    python3 switch.py

For more info on the script, run

    python3 switch.py h


