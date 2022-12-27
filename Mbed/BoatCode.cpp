#include "mbed.h"

PwmOut Vel(PTB0);
PwmOut Servo(PTB1);

DigitalOut Led11(LED1);
DigitalOut Led21(LED2);
DigitalOut Led31(LED3);
DigitalOut M1 (PTE20);
DigitalOut M2 (PTE21);
DigitalOut Dir (PTC7);

Serial bt(PTE0,PTE1);
Serial pc(USBTX,USBRX);


int main() {
        Dir=0;
        M1=0;
        M2=1;
    bt.baud(38400);
    pc.baud(9600);
    pc.printf("Listo");
    Vel.period(0.020);
    Servo.period_ms(20);
    while(1) {
        if (bt.readable()){
            pc.putc(bt.getc());
        }
        if (pc.readable()){
            pc.printf("\n");
            bt.putc(pc.getc());
        }
        
        //Switch pod velocidad
        switch(bt.getc()){
            case 'a':
                Servo.pulsewidth_us(500);    
            break;
            case 'b':
                Servo.pulsewidth_us(900);
            break;
            case 'c':
                Servo.pulsewidth_us(1400);
            break;
            case 'd':
                Servo.pulsewidth_us(1900);
            break;
            case 'e':
                Servo.pulsewidth_us(2500);
            break;
            case 'v':
                Led11=1;
                Led21=0;
                Led31=0;
                Vel.write(0);
            break;
            case 'w':
                Led11=0;
                Led21=1;
                Led31=0;
                Vel.write(0.25);
            break;
            case 'x':
                Led11=0;
                Led21=0;
                Led31=1;
                Vel.write(0.5);
            break;
            case 'y':
                Led11=1;
                Led21=1;
                Led31=0;
                Vel.write(0.75);
            break;
            case 'z':
                Led11=1;
                Led21=0;
                Led31=1;
                Vel.write(1);
            break;
            case 'l':
                M1=!M1;
                M2=!M2;
            break;   
        }                        
    }
}