//Using Servo Library
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<Servo.h>
#include<string.h>

const byte address[6] = "00001";//Address for transmission
Servo roll;
Servo pitch;

RF24 radio(7,8);//CE PIN and CSN PIN respectively

void setup() {
  Serial.begin(9600);//baud rate
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);//100m range
  radio.startListening();
  roll.attach(6);//Attaching wires to D6 on Arduino
  pitch.attach(9);//Attaching wires to D9 on Arduino
}

void loop() {
  
  if(radio.available())//Connected
  {
    double test[2];//Array to be received
    radio.read(&test, sizeof(test));//Receiving Array
    //Printing on Graphs Uncomment it
    /*Serial.print(test[0]);
    Serial.print("\t");
    Serial.print(test[1]);
    Serial.print("\t\n");*/
    double roll_transmission=2.08*test[1]+1500;  // linear mapping to generate a pulse width 1ms to 2ms
    double pitch_transmission=-2.08*test[0]+1500;// linear mapping to generate a pulse width 1ms to 2ms
    //Setting transmission range from 1250 to 1750
    if(roll_transmission < 1250)
      roll_transmission = 1250;
    if(roll_transmission > 1750)
      roll_transmission = 1750;
    if(pitch_transmission < 1250)
      pitch_transmission = 1250;
    if(pitch_transmission > 1750)
      pitch_transmission = 1750;
    //Setting values on KK2.1
    roll.writeMicroseconds(roll_transmission);
    pitch.writeMicroseconds(pitch_transmission);
  }
}
