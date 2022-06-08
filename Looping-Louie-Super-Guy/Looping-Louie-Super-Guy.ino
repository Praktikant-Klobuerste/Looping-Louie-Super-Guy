#include <PCM.h>
#include "music.h"

int Motor = 3;
int LED1 = 10;
int LED2 = 7;
int LED3 = 12;
int btn1 = 8;
int jump = 6;
int coin = 9;
int track = 0;
int merk = 0;
int Statusvariable1 = 0;
int Statusvariable2 = 0;
int Statusvariable3 = 0;
int zufall;
int poti;
int potim;


void setup()
{
  Serial.begin(9600);
  pinMode(Motor, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(jump, INPUT);
  pinMode(coin, INPUT);

  
  
  
}
void loop()
{

    poti = analogRead(A0);
    poti = map(poti, 0, 1023, 0, 255); 
  
    if((digitalRead(btn1)==1) && (Statusvariable1==0))
    {
    track ++;
    Statusvariable1 = 1;
    
    if(track > 3)
    {
    track = 0;
    }
      
    delay(5); 
    }
    if((digitalRead(btn1)==0) && (Statusvariable1==1))
    {
    Statusvariable1 = 0;
    delay(5);
    }

    if((digitalRead(jump)==1) && (Statusvariable2==0))
    {
    startPlayback(sprung, sizeof(sprung));
    Statusvariable2 = 1;
    delay(5); 
    }
  if((digitalRead(jump)==0) && (Statusvariable2==1))
    {
    Statusvariable2 = 0;
    delay(5);
    }
    
  if((digitalRead(coin)==1) && (Statusvariable3==0))
    {
    startPlayback(over, sizeof(over));
    Statusvariable3 = 1;
    delay(5); 
    }
  if((digitalRead(coin)==0) && (Statusvariable3==1))
    {
    Statusvariable3 = 0;
    delay(5);
    }
  
 
  if(track == 0){
    analogWrite(Motor, 0);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  
  else if(track == 1){
    analogWrite(Motor, poti);
    digitalWrite(LED1, HIGH);
    
  }
    
  else if(track == 2){
    analogWrite(Motor, 150);
    digitalWrite(LED2, HIGH);  
  }
  
  else if(track == 3){
    analogWrite(Motor, 255);
    digitalWrite(LED3, HIGH);
  }
  Serial.println(poti);
  delay(5);
}
