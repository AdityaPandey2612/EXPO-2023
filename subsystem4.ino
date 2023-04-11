//---NOTE ON ASSUMPTION----\\
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - Below mentioned pin numbers ae assumed to be the connection
//---NOTE END----\\
#include "DHT.h"
#include <SoftwareSerial.h>


#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11


// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
int speedpin = 5;//speedpin pin motor
int dir1 = 4;//direction pin motor
int dir2 = 3;//direction pin motor
int mSpeed = 250;//motor speed
float humidity;
float tempc;
float tempf;
const int recv = 11;//recieve pin for bluetooth
const int transmit = 10;//transmit pin for bluetooth
int st = 500;


// Initialize DHT sensor.
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);//object for dht sensor
SoftwareSerial bt(recv,transmit);//object for bluetooth


void setup() {
 Serial.begin(9600);
 Serial.println(F("DHTxx test!"));
 pinMode(speedpin,OUTPUT);
 pinMode(dir1,OUTPUT);
 pinMode(dir2,OUTPUT);
 pinMode(recv,INPUT);
 pinMode(transmit,OUTPUT);
 bt.begin();
 dht.begin();
}


void loop() {
 // Wait a few seconds between measurements.
 tempf = dht.readTemperature(true);
 digitalWrite(dir1,HIGH);
 digitalWrite(dir2,LOW);
 mSpeed = tempf+210;
 if (mSpeed >= 250){
   mSpeed = 250;
 }
 analogWrite(speedpin,mSpeed);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 humidity = dht.readHumidity();
 // Read temperature as Celsius (the default)
 tempc = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 // Check if any reads failed and exit early (to try again).
 if (isnan(humidity) || isnan(tempc) || isnan(tempf)) {
   Serial.println(F("Failed to read from DHT sensor!"));
   return;
 }


 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(tempf, humidity);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(tempc, humidity, false);


 Serial.print(F("Humidity: "));
 Serial.print(humidity);
 Serial.print(F("%  Temperature: "));
 Serial.print(tempc);
 Serial.print(F("°C "));
 Serial.print(tempf);
 Serial.print(F("°F  Heat index: "));
 Serial.print(hic);
 Serial.print(F("°C "));
 Serial.print(hif);
 Serial.println(F("°F"));
}
