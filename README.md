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

It's around 5€ per window blind plus one pwoer supply. I got most of the parts from AliExpress.

# electrical wiring

![wiring](https://user-images.githubusercontent.com/14030572/112663888-9f40f500-8e59-11eb-9b0c-0f3eda713c63.jpg)

- 12V from the power supply to power converter input
- 12V from the power supply to stepper driver
- IMPORTANT: configure power converter to putput 5V!
- power converter output (5V) to Wemos D1
- Wemos D5,D6,D7,D8 to stepper IN1,IN3,IN2,IN4

Important: The two middle stepper cables need to be crossed: D5,D6,D7,D8 connect to IN1,**IN3,IN2**,IN4. Either that or you need change the code to reflect that.
This has to do with the way the electromagents within the stepper motor operate ... unfortunately I found this very intransparent and is different from library to library ... but since I dont use any stepper library: Cross the middle cables!

# original parts

I resued the clamps and rotator connector
![original_parts](https://user-images.githubusercontent.com/14030572/112665220-1c209e80-8e5b-11eb-8f0e-ae68ebc8df6d.jpg)


# 3D printed parts / STLs
Since I reuse the window brackets from the original blinds, I needed to print some adapters.

You can find the STLs on Thingiverse here: https://www.thingiverse.com/thing:4806384

## motor case 
houses the stepper motor and fits on the original window clamp
![motor_case](https://user-images.githubusercontent.com/14030572/112664833-b03e3600-8e5a-11eb-85c6-72a9b8cbdd0e.jpg)

## motor connector
connects the motor with the blind
![motor_connector](https://user-images.githubusercontent.com/14030572/112664869-be8c5200-8e5a-11eb-9199-b0edb66e4972.jpg)

## rotator connector
fits on the second window clamp and connects to the blind on the opposite side
![blinds_rotator](https://user-images.githubusercontent.com/14030572/112665079-f5fafe80-8e5a-11eb-87b8-c28c05921414.jpg)

## box
houses the wemos, step down module and the driver
![box](https://user-images.githubusercontent.com/14030572/112665117-001cfd00-8e5b-11eb-938c-d02f5a8438c7.jpg)


# assemblement

![window_clamps](https://user-images.githubusercontent.com/14030572/112665411-512cf100-8e5b-11eb-82b8-1fe0fc88ffff.jpg)
![blinds_motor](https://user-images.githubusercontent.com/14030572/112665433-58ec9580-8e5b-11eb-8b18-0ab959c9f620.jpg)
![blinds_rotator](https://user-images.githubusercontent.com/14030572/112665440-5ab65900-8e5b-11eb-9ebc-35fa29206e85.jpg)
![fully_assembled](https://user-images.githubusercontent.com/14030572/112665483-673ab180-8e5b-11eb-816e-00fd59eb9da1.jpg)


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
