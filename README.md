# FreddiRollo

Control your blinds with a little direct driven motor via an ESP8266 without any stepper library.

Upon startup the Wemos connects to your wifi and starts a webserver at port 80.
You can either connect to the webserver and use simple html buttons to move the blinds, or GET the parameters "direction" (left, right) and "count" (amount of steps) to the server.

Example:  
http://IP/?direction=left&count=256  
http://IP/?direction=right&count=7150

You need to test yourself how many steps are needed to fully move your blinds up and down, I needed 7150.

# features
- simple http interface other devices can connect to easily
- no wifi manager or AP setup
- no stepper library
- direct drive without the need of gears
- simple html page interface without jQuery or anything external

# BOM
- Wemos D1 or any other ESP8266 (~1,60€)
- ULN2003 motor driver (~0,50€)
- 28BYJ-48 stepper motor 12V (~1,50€)
- LM2596 12V-to-5V step down module (0,80€)
- 12V power supply (~6€)
- a few 3D printed parts
- cables and soldering iron

It's around 5€ per window blind plus one pwoer supply.

# electrical wiring

TODO:
- 12V from the power supply to step down input
- 12V rom the power supply to stepper
- configure step down module to putput 5V
- step down module output (5V) to Wemos ground and 5V
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
- ESP8266WebServer (to open up a webserver)
- ESP8266WiFi (to connect to your local wifi via SSID and password)

Note the absence of any stepper library here, since I couldnt find a working one. The low level solution of manually outputting the digital pins in a 8 step fashion worked and easily creates enough torque to move the blind.

Settings to upload to the Wemos D1: (TODO)

# codechanges
You need to do the following codechanges before flashing to your Wemos:

- configure your wifi details in lines 4-6
- configure the used digital ports in lines 8-11
- play around with the rotationSpeed in line 13
