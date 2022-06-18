#include <PCM.h>
#include "music.h"
#include <PCD8544.h>
PCD8544 lcd;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 10
#define LED_COUNT 9


int Motor = 9;                              //Eingänge
int Modusschalter = 8;
int Wippe = 2;
int As6 = 12;
int As7 = 13;

int MerkerModus = 0;                        //Merker
int Modus = 0;
int StatusvariableModus = 0;
int StatusvariableWippe = 0;
int Geschwindigkeit = 255;
int MerkerDurchlauf = 0;

int Merker1 = 0;                            //Spielermerker
int Merker2 = 0;
int Merker3 = 0;
int Merker4 = 0;
int Merker5 = 0;
int Merker6 = 0;
int Merker7 = 0;
int Merker8 = 0;

int zufall;




int Players[8] = {3, 3, 3, 3, 3, 3, 3, 3};    //Spielercoins
int Playersm[8] = {1, 1, 1, 1, 1, 1, 1, 1};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(Motor, OUTPUT);
  pinMode(Modusschalter, INPUT);
  pinMode(Wippe, INPUT);
  pinMode(As6, INPUT);
  pinMode(As7, INPUT);

  lcd.begin(84, 48);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  colorWipe(strip.Color(255, 0, 0), 5, 0, 0);
  colorWipe(strip.Color(0, 255, 0), 5, 1, 1);
  colorWipe(strip.Color(0, 0, 255), 5, 2, 2);
  colorWipe(strip.Color(255, 255, 0), 5, 3, 3);
  colorWipe(strip.Color(255, 0, 255), 5, 4, 4);
  colorWipe(strip.Color(255, 255, 255), 5, 5, 5);
  colorWipe(strip.Color(0, 255, 255), 5, 6, 6);
  colorWipe(strip.Color(255, 30, 166), 5, 7, 7);
  colorWipe(strip.Color(255, 0, 0), 5, 8, 8);

}
void loop()
{
  int WP1 = digitalRead(A0);
  int WP2 = digitalRead(A1);
  int WP3 = digitalRead(A2);
  int WP4 = digitalRead(A3);
  int WP5 = digitalRead(A4);
  int WP6 = digitalRead(A5);
  int WP7 = digitalRead(As6);
  int WP8 = digitalRead(As7);


  if (MerkerDurchlauf == 1000) {
    MerkerDurchlauf = 0;
    Geschwindigkeit = random(150, 300);
    if (Geschwindigkeit > 255) {
      Geschwindigkeit = 0;
    }
  }
  if (Geschwindigkeit == 0 && MerkerDurchlauf == 1) {
    MerkerDurchlauf = 600;
  }






  for (int i = 0; i < 9; i++) {                               //RBG färben
    if ((Players[i] == 0) && (Playersm[i] == 1)) {
      colorWipe(strip.Color(0, 0, 0), 100, i, i);
      Playersm[i] = 0;
      strip.show();
    }
  }

  if ((digitalRead(Modusschalter) == 1) && (StatusvariableModus == 0)) {   //Modus Button Betätigung
    MerkerModus ++;
    StatusvariableModus = 1;
    if (MerkerModus > 2) {
      MerkerModus = 0;
    }
    delay(5);
  }
  if ((digitalRead(Modusschalter) == 0) && (StatusvariableModus == 1)) {
    StatusvariableModus = 0;
    delay(5);
  }


  if ((digitalRead(Wippe) == 1) && (StatusvariableWippe == 0)) {   //Wippe Button Betätigung
    startPlayback(sprung , sizeof(sprung));
    StatusvariableWippe = 1;
    delay(5);
  }
  if ((digitalRead(Wippe) == 0) && (StatusvariableWippe == 1)) {
    StatusvariableWippe = 0;
    delay(5);
  }


  if ((Merker1 == 1) && (WP1 == 1) && (Players[0] > 0)) {     //Coins Spieler 1
    Merker1 = 0;
    Players[0]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP1 == 0) && (Merker1 == 0)) {
    Merker1 = 1;
    delay(100);
  }

  if ((Merker2 == 1) && (WP2 == 1) && (Players[1] > 0)) {     //Coins Spieler 2
    Merker2 = 0;
    Players[1]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP2 == 0) && (Merker2 == 0)) {
    Merker2 = 1;
    delay(100);
  }

  if ((Merker3 == 1) && (WP3 == 1) && (Players[2] > 0)) {     //Coins Spieler 3
    Merker3 = 0;
    Players[2]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP3 == 0) && (Merker3 == 0)) {
    Merker3 = 1;
    delay(100);
  }

  if ((Merker4 == 1) && (WP4 == 1) && (Players[3] > 0)) {     //Coins Spieler 4
    Merker4 = 0;
    Players[3]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP4 == 0) && (Merker4 == 0)) {
    Merker4 = 1;
    delay(100);
  }

  if ((Merker5 == 1) && (WP5 == 1) && (Players[4] > 0)) {     //Coins Spieler 5
    Merker5 = 0;
    Players[4]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP5 == 0) && (Merker5 == 0)) {
    Merker5 = 1;
    delay(100);
  }

  if ((Merker6 == 1) && (WP6 == 1) && (Players[5] > 0)) {     //Coins Spieler 6
    Merker6 = 0;
    Players[5]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP6 == 0) && (Merker6 == 0)) {
    Merker6 = 1;
    delay(100);
  }

  if ((Merker7 == 1) && (WP7 == 1) && (Players[6] > 0)) {     //Coins Spieler 7
    Merker7 = 0;
    Players[6]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP7 == 0) && (Merker7 == 0)) {
    Merker7 = 1;
    delay(100);
  }

  if ((Merker8 == 1) && (WP8 == 1) && (Players[7] > 0)) {     //Coins Spieler 8
    Merker8 = 0;
    Players[7]--;
    startPlayback(over, sizeof(over));
    delay(100);
  }
  if ((WP8 == 0) && (Merker8 == 0)) {
    Merker8 = 1;
    delay(100);
  }



  //coinser(WP1, 0, Merker1);                                   //Coins auswerten
  //coinser(WP2, 1, Merker2);
  //coinser(WP3, 2, Merker3);
  //coinser(WP4, 3, Merker4);
  //coinser(WP5, 4, Merker5);
  //coinser(WP6, 5, Merker6);
  //coinser(WP7, 6, Merker7);
  //coinser(WP8, 7, Merker8);


  switch (MerkerModus) {                                            //Modi einstellen
    case 0:
      if (Modus == 0) {

        lcd.setCursor(0, 0);
        lcd.print("Looping Louis    Extreme!");
        lcd.setCursor(0, 1);
        lcd.print("");
        lcd.setCursor(0, 3);
        lcd.print("   Modus: 1");
        lcd.setCursor(0, 5);
        lcd.print("Geschw.: 150");
        Modus = 1;
        MerkerDurchlauf = 0;
        analogWrite(Motor, 150);
      }
      break;


    case 1:
      if (Modus == 1) {
        analogWrite(Motor, 255);
        lcd.setCursor(0, 3);
        lcd.print("   Modus: 2");
        lcd.setCursor(0, 5);
        lcd.print("Geschw.: 255");
        Geschwindigkeit = 255;
        Modus = 2;
      }
      break;


    case 2:
      if (MerkerDurchlauf == 0) {
        lcd.setCursor(0, 3);
        lcd.print("   Modus: 3");
        lcd.setCursor(0, 5);
        lcd.print("              ");
        lcd.setCursor(0, 5);
        lcd.print("Geschw.: ");
        lcd.print(Geschwindigkeit);
        Modus = 0;
        analogWrite(Motor, Geschwindigkeit);
      }
      MerkerDurchlauf++;
      break;

    default:
      MerkerModus = 0;
  }

  delay(5);                                                           //Seriel Print
  Serial.println(MerkerDurchlauf);
}


void colorWipe(uint32_t color, int wait, int i, int ende) {         //Color Methode
  for (; i <= ende; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}


//void coinser(int Eingang, int Player, int Merker) {                 //Coins Methode
//
//  if ((Merker == 1) && (Eingang == 1) && (Players[Player] > 0)) {
//    Merker = 0;
//    Players[Player]--;
//      startPlayback(over, sizeof(over));
//    delay(5);
//  }
//  if ((Eingang == 0) && (Merker == 0)) {
//    Merker = 1;
//    delay(5);
//  }
//}
