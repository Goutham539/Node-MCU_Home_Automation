#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
const char* ssid = "Googlep";
const char* password = "lkjhgfdsa";
int WET= 5; // Wet Indicator at Digital PIN D1
int DRY= 16;  // Dry Indicator at Digital PIN D0
int MEDIUM= 4;  // Dry Indicator at Digital PIN D2
int MOTOR= 2;  // Dry Indicator at Digital PIN D4
int sense_Pin=A0; // Soil Sensor input at Analog PIN A0
int value= 0;
WiFiClient client;
unsigned long myChannelNumber = 767741;
const char * myWriteAPIKey = "FUDDM1BBMWGU0TTF";
void setup() {
  Serial.begin(9600);
   pinMode(WET, OUTPUT);
   pinMode(DRY, OUTPUT);
   pinMode(MEDIUM, OUTPUT);
   pinMode(MOTOR, OUTPUT);
   WiFi.begin(ssid, password);
   // Connect to WiFi network
   ThingSpeak.begin(client);
   delay(2000);
}
void loop() {
   Serial.print("DAMP LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
  ThingSpeak.writeField(myChannelNumber, 1,value, myWriteAPIKey);
   delay(100);
if(value >= 90)
   {
      digitalWrite(WET, LOW);
      digitalWrite(DRY, HIGH);
      digitalWrite(MEDIUM, LOW);
      digitalWrite(MOTOR, HIGH);
   }
   else if(value >=40 && value < 70)
   {
      digitalWrite(WET, LOW);
      digitalWrite(DRY, LOW);
      digitalWrite(MEDIUM, HIGH);
      digitalWrite(MOTOR, LOW);
    }
   else
   {
      digitalWrite(DRY,LOW);
      digitalWrite(WET,HIGH);
      digitalWrite(MEDIUM, LOW);
      digitalWrite(MOTOR, LOW);
   }
   delay(1000);
   }