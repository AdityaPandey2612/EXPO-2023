#include <LiquidCrystal.h>
#include <IRremote.h>
// If you use a different pin for your wiring, make sure it is a PWM pin (~)
// and replace 6 with the pin you used.
#define CONTRAST_PIN 6


// MAKE SURE THESE PINS MATCH YOUR WIRING!!!
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 IRrecv irrecv(8);
 decode_results results;




void setup() {


// initialize lcd screen and cursor
  lcd.begin(16, 2);
lcd.setCursor(0,1);
  lcd.print("FAN: OFF");
  lcd.setCursor(1,1);
  lcd.print("VOLUME: OFF");
  // set contrast
  analogWrite(CONTRAST_PIN, 70);


// remote setup
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}


void loop() {
// read in a value
  if(irrecv.decode(&results)){
    // based on value, communicate with other subsystems to generate
    // appropriate response


// change info on LCD screen accordingly
 lcd.setCursor(0,1);
 lcd.print("FAN: 1"); // numbers denote fan speed


lcd.setCursor(1,1);
lcd.print("VOLUME: 52");


    // resume reading for next command
    irrecv.resume()
  }
