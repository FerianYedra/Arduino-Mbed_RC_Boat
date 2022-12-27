# Arduino to Mbed RC Boat

<details><summary>English Instructions</summary>
<p>

## Introduction
This repo contains the documented code used for a remote controlled boat using the Arduino and Mbed platforms, utilizing bluetooth as the medium for wireless communication.

This was used for a class project, however, while doing so our team found few and often confusing documentation and explanations on the details of the components used for the boat. Hopefully this helps someone else understand and implement this to their own projects.

## Boat Specifications
For this project the boat was designed to do the following things:
- Use a Mbed microcontroller (FRDM-KL25Z) to control the boat components.
- Use a servo (SG90) to control the rudder of the boat.
- Control the boat velocity and direction using a H-Bridge module (L-298N).
- Communicate wirelessly with the controller using a bluetooth module (HC-05).

## Controller Specifications
For this project the controller was designed to do the following things:
- Use an Arduino microcontroller (Arduino UNO) to control and read the controller components.
- Use two potentiometers to control velocity and direction of the boat.
- Use two push-buttons to control propeller rotation direction and controller timer.
- Use an LCD display module to show speed and direction information as well as the timer.
- Communicate wirelessly with the boat using a bluetooth module (HC-05).

## Configuring the Bluetooth Modules
Connecting both HC-05 modules was one of the most challenging parts of the project, this originates from the many resources that present confusing and even conflicting information about how to connect the bluetooth modules.

### Bluetooth Modules

First thing you need to know is the difference between the HC-05 and the HC-06 modules, primarily that the latter is only able to serve as slave, meaning it won't be able to establish the connection.

To know if you are using the HC-05 module (assuming it's not marked) you can check the amount of pins it has, as more often than not the HC-05 has 6 pins and a small button, while the HC-06 has only 4 and no button.

### AT Command Mode

Another important aspect to notice is the AT command mode of the HC-05, it is in this mode that the module can be configured. Weather the module is in its normal mode or in its AT mode can be known if when connected to Vin and Gnd it behaves in one of the following ways:
- Fast blinking of the LED: Normal mode.
- Slow blinking of the LED: AT Mode.
- Double blinking of the LED: Connected to another device. 

To access this mode there are two ways that can work depending on how new or old is the model of the bluetooth module:
- Older module: The circuit plate tends to be thicker, around 2mm, and only has one red LED on the lower left side.
- New module: The circuit plate tends to be more slim, around 1mm, and has two LED's, the lower red one and a upper blue one.

To enter AT mode on older modules you can simply press and hold the button (while it is disconnected) and then give power to the module. For new models you have to connect the `Enable` pin to 3V before giving power to the module.

### Communicate with the module
To configure the bluetooth module we found it to be much easier to use the following method:

Use a computer and a Arduino microcontroller, use the Arduino 5V and Gnd pins to give power to the module, connect bluetooth TX pin to Arduino pin 10 and bluetooth RX pin to Arduino pin 11.

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

Repeat the process with the other module in a different computer.

### AT Commands
There are many AT commands you can send to the module to configure it, a comprehensive list of these commands is linked in the external resources section, here we list in order the ones required to establish the connection between the modules:
- `AT+NAME=[PARAM]`         //Gives a name to the module.
- `AT+ROLE?`                //Returns the role it has taken (0 - Slave, 1 - Master, 2 - Slave-loop).
- `AT+ROLE=[PARAM]`         //Assigns a role to the module (0/1/2).
- `AT+ADDR?`                //Returns the address to connect to (Must be asked to the salve).
- `AT+UART=[PARAM]`         //Assigns the UART values (Reccommend `AT+UART=38400,0,0` as it's the baud rate used in the code).
- `AT+BIND=[ADDRESS]`       //Tells the master which address to connect once in is powered (Must be told to the master).
- `AT+LINK=[ADDRESS]`       //Asks to connect to the address.
- `AT+STATE?`               //Returns the current state of the module (Master should be: Ready/Connected/Paired. Slave should be: Pairable/Paired/Connected).

Once both modules indicate they are connected/paired you can once again disconnect them from power and connect them again in normal mode (Just connect Vin and Gnd),
wait for the both modules to start double blinking simultaneously that way you will know they are connected. Using the same code as before you should be able to send a string like "Hello" through one command line and watch it display on the other computer's command line.

### Important notes
- The FRDM-KL25Z can be used to power the bluetooth module however you can not power anything else using the 5V pin or else the modules will disconnect.
- The HC-05 modules will begin to disconnect at around 2 to 3 meters. 

## External Resources
- [HC-05 AT Command List](https://www.teachmemicro.com/hc-05-bluetooth-command-list/)
- [Boat Schematics](https://www.instructables.com/RC-Boat-2/)

</p>
</details>

<details><summary>Instrucciones en español</summary>
<p>

## Introducción
Este repositorio contiene el código documentado utilizado para un barco controlado a distancia que utiliza las plataformas Arduino y Mbed, utilizando bluetooth como medio para la comunicación inalámbrica.

Esto se utilizó para un proyecto de clase, sin embargo, mientras lo hacía, nuestro equipo encontró poca documentación y explicaciones, a menudo confusas, sobre los detalles de los componentes utilizados para el barco. Esperemos que esto ayude a alguien más a entender e implementar esto en sus propios proyectos.

## Especificaciones del bote
Para este proyecto, el barco fue diseñado para hacer lo siguiente:
- Utilice un microcontrolador Mbed (FRDM-KL25Z) para controlar los componentes del barco.
- Utilice un servo (SG90) para controlar el timón del barco.
- Controlar la velocidad y dirección del barco mediante un módulo de Puente-H (L-298N).
- Comunicarse de forma inalámbrica con el controlador mediante un módulo bluetooth (HC-05).

## Especificaciones del control
Para este proyecto, el controlador fue diseñado para hacer lo siguiente:
- Utilice un microcontrolador Arduino (Arduino UNO) para controlar y leer los componentes del controlador.
- Utilice dos potenciómetros para controlar la velocidad y la dirección del barco.
- Use dos botones para controlar la dirección de rotación de la hélice y el temporizador del controlador.
- Use un módulo de pantalla LCD para mostrar información de velocidad y dirección, así como el temporizador.
- Comunicarse de forma inalámbrica con el barco mediante un módulo bluetooth (HC-05).

## Configuración de los módulos de bluetooth
Conectar ambos módulos HC-05 fue una de las partes más desafiantes del proyecto, esto se origina en los muchos recursos que presentan información confusa e incluso contradictoria sobre cómo conectar los módulos bluetooth.

### Módulos Bluetooth

Lo primero que debe saber es la diferencia entre los módulos HC-05 y HC-06, principalmente que este último solo puede servir como esclavo, lo que significa que no podrá establecer la conexión.

Para saber si está utilizando el módulo HC-05 (suponiendo que no esté marcado), puede verificar la cantidad de pines que tiene, ya que la mayoría de las veces el HC-05 tiene 6 pines y un botón pequeño, mientras que el HC-06 tiene solo 4 y sin botón.

### Modo de comando AT

Otro aspecto importante a notar es el modo de comando AT del HC-05, es en este modo que se puede configurar el módulo. Se puede saber si el módulo está en su modo normal o en su modo AT si cuando está conectado a Vin y Gnd se comporta de una de las siguientes maneras:
- Parpadeo rápido del LED: Modo normal.
- Parpadeo lento del LED: Modo AT.
- Doble parpadeo del LED: Conectado a otro dispositivo.

Para acceder a este modo hay dos formas que pueden funcionar dependiendo de lo nuevo o antiguo que sea el modelo del módulo bluetooth:
- Módulo antiguo: La placa del circuito tiende a ser más gruesa, alrededor de 2 mm, y solo tiene un LED rojo en el lado inferior izquierdo.
- Nuevo módulo: La placa del circuito tiende a ser más delgada, alrededor de 1 mm, y tiene dos LED, el rojo inferior y el azul superior.

Para ingresar al modo AT en módulos más antiguos, simplemente presione y mantenga presionado el botón (mientras está desconectado) y luego encienda el módulo. Para los modelos nuevos, debe conectar el pin `Enable` a 3V antes de dar energía al módulo.

### Comunicarse con el módulo
Para configurar el módulo bluetooth nos resultó mucho más sencillo utilizar el siguiente método:

Use una computadora y un microcontrolador Arduino, use los pines Arduino 5V y Gnd para alimentar el módulo, conecte el pin bluetooth TX al pin 10 de Arduino y el pin bluetooth RX al pin 11 de Arduino.

Sube el siguiente código al Arduino:
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

Asegúrese de iniciar el módulo bluetooth en modo AT, use Arduino IDE para abrir un monitor en serie y seleccione `Both NL & CR` y 9600 baudios.

Si escribe 'AT' y lo envía en la línea de comando, debe responder con 'OK'.

Repita el proceso con el otro módulo en una computadora diferente.

### Comandos AT
Hay muchos comandos AT que puede enviar al módulo para configurarlo, una lista completa de estos comandos está vinculada en la sección de recursos externos, aquí enumeramos en orden los necesarios para establecer la conexión entre los módulos:
- `AT+NAME=[PARAM]`         //Da un nombre al módulo.
- `¿AT+ROLE?`               //Devuelve el rol que ha tomado (0 - Slave, 1 - Master, 2 - Slave-loop).
- `AT+ROLE=[PARAM]`         //Asigna un rol al módulo (0/1/2).
- `¿AT+ADDR?`               //Devuelve la dirección a la que conectarse (Se debe preguntar al esclavo).
- `AT+UART=[PARAM]`         //Asigna los valores UART (se recomienda `AT+UART=38400,0,0`).
- `AT+BIND=[DIRECCIÓN]`     //Le dice al maestro qué dirección conectarse una vez que está encendido (Debe informarse al maestro).
- `AT+LINK=[DIRECCIÓN]`     //Pide conectarse a la dirección.
- `AT+STATE?`               //Devuelve el estado actual del módulo (El maestro debe estar: Ready/Connected/Paired. El esclavo debe ser: Pairable/Paired/Connected).

Una vez que ambos módulos indiquen que están conectados/emparejados, puede volver a desconectarlos de la alimentación y volver a conectarlos en modo normal (solo conecte Vin y Gnd),
espere a que ambos módulos comiencen a parpadear dos veces simultáneamente de esa manera sabrá que están conectados. Usando el mismo código que antes, debería poder enviar una cadena como "Hola" a través de una línea de comando y ver cómo se muestra en la línea de comando de la otra computadora.

### Notas importantes
- El FRDM-KL25Z se puede usar para alimentar el módulo bluetooth, sin embargo, no puede alimentar nada más con el pin de 5V o, de lo contrario, los módulos se desconectarán.
- Los módulos HC-05 comenzarán a desconectarse alrededor de los 2 a 3 metros.

## Recursos externos
- [Lista de comandos AT del HC-05](https://www.teachmemicro.com/hc-05-bluetooth-command-list/)
- [Esquemas del barco](https://www.instructables.com/RC-Boat-2/)

</p>
</details>
