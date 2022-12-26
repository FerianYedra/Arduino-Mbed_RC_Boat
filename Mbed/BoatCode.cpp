#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>


LiquidCrystal lcd(12,9,8,5,4,3,2);  

SoftwareSerial miBT(10,11); //Conectar TX al pin 10 y RX al pin 11
const int pin=6, pin2=7;
int value=0,value2=0;
const float SensorPodVelocidad = A5;
const float SensorPodDireccion = A4;
float Pod_vel;
float Pod_dir;
char c = ' ';
String vel;
String dir;
String tempo;
volatile long int Time = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Listo");
  miBT.begin(38400);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  delay(5000);
  lcd.setCursor(0,1);
  lcd.print("Dir:");
  lcd.setCursor(0,0);
  lcd.print("Vel:       Time:");
  pinMode(pin,INPUT);
  pinMode(pin2, INPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Temporizador);

}

void loop(){
  value = digitalRead(pin);
  value2 = digitalRead(pin2);
  if(miBT.available()){
    c = miBT.read();
    Serial.write(c);
  }

  if(Serial.available()){
    c = Serial.read();
    miBT.write(c);
    
  }
  Pod_vel=analogRead(SensorPodVelocidad);
    //Configuración pantalla LCD---------------------------------------------------------------
    vel = String((Pod_dir * 100) / 750, 0);
    lcd.setCursor(5,0);
    lcd.print(vel + "%");
    lcd.print("  ");

    dir = String((Pod_vel * 180) /750, 0);
    lcd.setCursor(5, 1);
    lcd.print(dir);
    lcd.print("  ");

    tempo = String(Time, 0);
    Serial.println(Time);
    lcd.setCursor(11, 1);
    lcd.print(Time);
    lcd.print("  ");


//Pod de velocidad
    //Pod_vel=analogRead(SensorPodVelocidad);
    //Serial.write("%d",Pod_vel);
    //Velocidad 1
    if(Pod_vel<=205)
      miBT.write("a"); 
    //Velocidad 2
    if(Pod_vel>205 && Pod_vel<=410)
      miBT.write("b");
    //Velocidad 3  
    if(Pod_vel>410 && Pod_vel<=615)
      miBT.write("c");
    //Velocidad 4  
    if(Pod_vel>615 && Pod_vel<=750)
      miBT.write("d");
    //Velocidad 5  
    if(Pod_vel>800)
      miBT.write("e");   

 //Pod de Direccionamiento
    Pod_dir=analogRead(SensorPodDireccion);
    //Direccion 1
    if(Pod_dir<=205)
      miBT.write("v");
    //Direccion 2
    if(Pod_dir>205 && Pod_dir<=410)
      miBT.write("w");
    //Direccion 3  
    if(Pod_dir>410 && Pod_dir<=615)
      miBT.write("x");
    //Direccion 4  
    if(Pod_dir>615 && Pod_dir<=750)
      miBT.write("y");
    //Direccion 5  
    if(Pod_dir>750)
      miBT.write("z");
      
    //Boton Cambio de direccion
    if (value==HIGH)
      miBT.write("l");
      //Serial.println("low");
    if (value2 == HIGH)
    {
      Time = 0; 
      Serial.println("high");
    }
      
}

int Temporizador(void){
  Time++;
  if(Time > 1000){
    Time = 0;
  }

  return Time;
}
