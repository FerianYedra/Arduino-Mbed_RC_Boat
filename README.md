# Arduino to Mbed RC Boat (Work in progress)
## Introduction
This repo contains de documented code used for a remote controlled boat using the Arduino and Mbed platforms, utilizing bluetooth as the medium for wireless communication.

This was used for a class project, however, while doing so our team found few and often confusing documentation and explenations on the details of the comenents used for the boat. Hopefully this helps someone else understand and implement this to their own projects.

## Boat Specifications
For this project the boat was designed to do the following things:
- Use a Mbed microcontroller (FRDM-KL25Z) to control de boat components.
- Use a servo (SG90) to control the rudder of the boat.
- Control the boat velocity and direction using a H-Bridge module (L-298N).
- Communicate wirelessly with the controller using a bluetooth module (HC-05).

## Controller Specifications
For this project the controller was designed to do the following things:
- Use a Arduino microcontroller (Arduino UNO) to control and read the controller components.
- Use two potenciometers to control velocity and direction of the boat.
- Use two push-buttons to control propeller rotation direction and controller timer.
- Use an LCD display module to show speed and direction information as well as the timer.
- Communicate wirelessley with the boat using a bluetooth module (HC-05).

## Configuring the Bluetooth Modules
Configuring the Bluetooth Modules
Connecting both HC-05 modules was one of the most challenging parts of the project, this originates form the many resources that present confusing and even conflicting information about how to connect the bluetooth modules.

First thing you need to know is the difference between the HC-05 and the HC-06 modules, primarily that the latter is only able to serve as slave, meaning it wownt be able to establish the connection.

To know if you are using the HC-05 module (assuming its not marked) you can check the amount of pins it has, as more often than not the HC-05 has 6 pins and a small button, while the HC-06 has only 4 and no button.

(To be continued...)

## External Recources
- [HC-05 AT Command List](https://www.teachmemicro.com/hc-05-bluetooth-command-list/)

