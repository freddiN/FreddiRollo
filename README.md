# FreddiRollo

Control your blinds with a little motor via an ESP8266 (I use a Wemos D1).

Upon startup the Wemos connects to your wifi and starts a webserver at port 80.
YOu can either connect to it and use the buttons to move the blinds, or simply GET the parameter "direction" (left, right) and "count" (amount of steps) to the server.

For example:  
http://IP/?direction=left&count=256  
http://IP/?direction=right&count=7150

You need to test yourself how many steps you need to fully move your blinds up and down, I needed 7150.

# BOM
- Wemos D1 or any other ESP8266
- ULN2003 motor driver
- 28BYJ-48 stepper motor 12V
- LM2596 12V to 5V step down module
- 12V power supply
- a few 3D printed parts
- cables andsoldering iron

# electrical wiring

TODO:
- 12V from the power supply to step down input
- 12V rom the power supply to stepper
- configure step down module to putput 5V
- 5V step down module output to Wemos ground and 5V
- Wemos D5,D6,D7,D8 to stepper IN1,IN2,IN3,IN4 SWAPCABLES!!!!!

# 3D printed parts / STLs
Since I reuse the window brackets from the original blinds, I needed to print some adapters:

- motor case (houses the stepper motor and fits on the original window clamp)
- motor connector (connects the motor with the blind)
- rotator connector (fits on the second window clamp and connects to the blind on the opposite side)
- box bottom (houses the wemos, step down module and the driver)
- box top 

You can find the STLs on Thingiverse here: (TODO)

# assemblement
(TODO: pictures)

# Arduino setup
libraries needed:
- ESP8266WebServer
- ESP8266WiFi

settings to upload to the Wemos D1: (TODO)

# codechanges
You need to do the following codechanges before flashing to your Wemos:

- configure your wifi details in lines 4-6
- configure the used digital ports in lines 8-11
- play around with the rotationSpeed in line 13
