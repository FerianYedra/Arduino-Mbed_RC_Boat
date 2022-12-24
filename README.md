# Arduino to Mbed RC Boat (Work in progress)

<details><summary>English Instructions</summary>
<p>

## Introduction
This repo contains the documented code used for a remote controlled boat using the Arduino and Mbed platforms, utilizing bluetooth as the medium for wireless communication.

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
Connecting both HC-05 modules was one of the most challenging parts of the project, this originates form the many resources that present confusing and even conflicting information about how to connect the bluetooth modules.

### Bluetooth Modules

First thing you need to know is the difference between the HC-05 and the HC-06 modules, primarily that the latter is only able to serve as slave, meaning it wownt be able to establish the connection.

To know if you are using the HC-05 module (assuming its not marked) you can check the amount of pins it has, as more often than not the HC-05 has 6 pins and a small button, while the HC-06 has only 4 and no button.

### AT Command Mode

Another important aspect to notice is the AT command mode of the HC-05, it is in this mode that the module can be configured. Weather the module is in its normal mode or in its AT mode can be known if when connected to Vin and Grnd it behaves in one of the following ways:
- Fast blinking of the LED: Normal mode.
- Slow blinnking of the LED: AT Mode.
- Double blinking of the LED: Connected to another device. 
To access this mode there are to ways that can work depending on how new or old is the model of the bluetooth module.
- Older module: The circuit plate tends to be more thick, arround 2mm, and only has one red LED on the lower left side.
- New module: The circuit plate tends to be more slim, arround 1mm, and has two LED's the lower red onde and a upper blue one.

### Communicate with the module
To configure the bluetooth module we found it to be much easier to use the following method:

Use a computer and a Arduino microcontroller, use the Arduino 5V and Grnd pins to give power to the module, connect bluetooth TX pin to Arduino pin 10 and bluetooth RX pin to Arduino pin 11.

Upload the code below to the Arduino:

```arduino
#include <SoftwareSerial.h>

SoftwareSerial miBT(10,11); //Connect bluetooth TX pin to Arduino pin 10 and bluetooth RX pin to Arduino pin 11.
char c = ' ';

void setup(){
  Serial.begin(9600);
  Serial.println("Ready");
  miBT.begin(38400);
}

void loop(){
  if(miBT.available()){
    c = miBT.read();
    Serial.write(c);
  }

  if(Serial.available()){
    c = Serial.read();
    miBT.write(c);
  }
}
```

Make sure to start the bluetooth module in AT mode, use the Arduino IDE to open a serial monitor, and select `Both NL & CR` and 9600 bauds.
If you write `AT` and send it in the command line you should be answered with `OK`.

### AT Commands

## External Recources
- [HC-05 AT Command List](https://www.teachmemicro.com/hc-05-bluetooth-command-list/)
- [Boat Schematics](https://www.instructables.com/RC-Boat-2/)

</p>
</details>

<details><summary>Instrucciones en español</summary>
<p>

## Introducción

## Especificaciones del bote

## Especificaciones del control

## Configuración de los módulos de bluetooth

## Recursos externos

</p>
</details>
