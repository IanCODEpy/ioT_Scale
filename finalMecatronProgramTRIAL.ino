#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include "HX711.h"

// Set these to run example.
#define FIREBASE_HOST "exemple.firebaseio.com" //put your fisehost code | bote seu codigo de firebase "exemplo.firebase.com"
#define FIREBASE_AUTH "123asd" //put your firebase authentication key | bote sua chave de autenticação 
#define WIFI_SSID "wifi name" //put your wifi name | bote o nome seu wifi
#define WIFI_PASSWORD "password123" //put word wifi password | bote sua senha do seu wifi

HX711 scale;



float weight; 
float calibration_factor = 419640;
float percent;

void setup() {
  Serial.begin(9600);
  pinMode(D3,OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("emergency",0);
  Firebase.setFloat("Weight",0);
  Firebase.setFloat("percent",0);
  Serial.begin(9600);
  scale.begin(D6,D7);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

int value = 0;
void loop(){

value = Firebase.getInt("emergency");


if(value == 1){
  
  Serial.println("emergency stop");
  //REMEMBER TO PUT FUCKING OUTPUTS LOW HERE!!!!
  
  }

else{
  
scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  weight = scale.get_units(5); 
  Serial.print("Kilogram:");
  Serial.print( weight); 
  Serial.print(" Kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
  
percent = (weight/1)*100;
Firebase.setFloat("percent",percent);
Firebase.setFloat("Weight",weight);

if(weight > 1){
  digitalWrite(D3,HIGH);
  }
else{
  
  digitalWrite(D3,LOW);
  }}
  }

