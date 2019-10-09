#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi Settings
const char* ssid = "XHNV-THUVIEN"; // your wireless network name (SSID)
const char* password = "xhnvthuvien@2017"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = 874362; //
const char* readAPIKey = "TS3CTM2ZOBVE3S6U";
const char* writeAPIKey = "48569AIKYQZTE1KK"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 30 * 1000; // post data every x seconds
unsigned int dataFieldOne = 1;
unsigned int dataFieldTwo = 2;
unsigned int aField = 8;

// Global variables
float aConst = 0;

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;

void setup() {
  Serial.begin(115200);
  connectWiFi();

//  aConst = readTSData(channelID, dataFieldOne);  
}

float readValue = 100;

void loop() {
    
  float sec = millis() - lastUpdateTime;
  if(sec >= postingInterval){
    
//    float readValue = 100;
    
    lastUpdateTime = millis();
    
    write2TSData(channelID, dataFieldOne, readValue, dataFieldTwo, millis());
    Serial.println("Value= " + String(readValue +=random(-5,20)) + "& sec= " + millis() + "\n");
  }
}

void connectWiFi(){
  Serial.print("Connecting");
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
  }
  Serial.println("\r\nWiFi connected!");  
  ThingSpeak.begin( client );
};

float readTSData( long TSChannel,unsigned int TSField ){
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println("Data read from ThingSpeak: " + String(data, 9));
  //return data;
  
}

// Write a single field.
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}

// Write multiple fields simultaneously.
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
