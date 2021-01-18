/*

MULTIPLE DS18B20 SENSORS CONNECTED VIA ONE WIRE BUS
created by Jesse Davids

Board used: https://www.robotics.org.za/7D3C576A?search=leo%20eth 
Ensure the board is POE-ACTIVE if you will be using the same one.

Sensors used: DS18B20

github page: https://github.com/JesseDavids/multiple-ds18b20-arduino

*/

#include <Arduino.h>
//To send http post in JSON
#include <ArduinoJson.h>
//One wire bus lib
#include <OneWire.h>
//One wire bus lib
#include <DallasTemperature.h>
//lib for MCU ethernet chip (W5500)
#include <Ethernet2.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// ensure your device has a unique device
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF};

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//initialise the server
EthernetServer server(80);

String readString;

//Variable to hold the content of the json payloads
char jsonOutput[512];
//Enter the amount of sensors you will be using
//i used 6 sensors but made space for 10 incase we want to expand functionality
//i have reached a limit of 18 sensors before the memory of the mcu ran out
DeviceAddress One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten ;

void setup()
{  
  Serial.begin(9600);
  sensors.begin();	// Start up the library
  w5500.init(11); // without this line the ethernet chip will not function properly
  Ethernet.begin(mac); // begin ethernet, this is a DHCP connection
  server.begin(); // begin the server
  Serial.println(Ethernet.localIP()); //find your IP, and navigate to it in a web browser
  // set resolution of each sensor
  // feel free to use a better naming convention as me :p
  sensors.setResolution(One, 12);
  sensors.setResolution(Two, 12);
  sensors.setResolution(Three, 12);
  sensors.setResolution(Four, 12);
  sensors.setResolution(Five, 12);
  sensors.setResolution(Six, 12);
  sensors.setResolution(Seven, 12);
  sensors.setResolution(Eight,12);
  sensors.setResolution(Nine, 12);
  sensors.setResolution(Ten, 12); 
}


void loop(){  
  // This maintains the connection with the router, preventing it from timing out.
  Ethernet.maintain();
  EthernetClient client = server.available();
  if(client){
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.print(c);
        if(readString.length()<100){
          readString += c;
        }
        if (c == '\n'){
          // Very important to specify the connection type as json
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Connection-type: application/json"));
          client.println(F("Connection: close"));
          client.println(); 
          
          // create json object and specify the size.           
          const size_t capacity = JSON_OBJECT_SIZE(10) +  239;         
          StaticJsonDocument<capacity> doc;
          JsonObject object = doc.to<JsonObject>();           
          // self explanatory 
          sensors.getAddress(One, 0);
          sensors.getAddress(Two, 1); 
          sensors.getAddress(Three, 2);
          sensors.getAddress(Four, 3);
          sensors.getAddress(Five, 4);
          sensors.getAddress(Six, 5);
          sensors.getAddress(Seven, 6);
          sensors.getAddress(Eight, 7);
          sensors.getAddress(Nine, 8);
          sensors.getAddress(Ten, 9);
          
          // create a string for each sensor to identify their serial number
          String OneX, TwoX, ThreeX, FourX, FiveX, SixX, SevenX, EightX, NineX, TenX  = "";
          // request temp
          sensors.requestTemperatures();

          // loops to identify each sensor, you can label the sensors later
          for (uint8_t i1 = 0; i1 < 8; i1++)       
          OneX += String(One[i1], HEX);
          float val1 = sensors.getTempC(One);
          object[OneX] = roundf(val1*100)/100.0;     
          
          for (uint8_t i2 = 0; i2 < 8; i2++)
          TwoX += String(Two[i2], HEX);
          float val2 = sensors.getTempC(Two);          
          object[TwoX] = roundf(val2*100)/100.0;

          for (uint8_t i3 = 0; i3 < 8; i3++)
          ThreeX += String(Three[i3], HEX);
          float val3 = sensors.getTempC(Three);
          object[ThreeX] = roundf(val3*100)/100.0;

          for (uint8_t i4 = 0; i4 < 8; i4++)
          FourX += String(Four[i4], HEX);
          float val4 = sensors.getTempC(Four);
          object[FourX] = roundf(val4*100)/100.0;

          for (uint8_t i5 = 0; i5 < 8; i5++)
          FiveX += String(Five[i5], HEX);
          float val5 = sensors.getTempC(Five);
          object[FiveX] = roundf(val5*100)/100.0;

          for (uint8_t i6 = 0; i6 < 8; i6++)
          SixX += String(Six[i6], HEX);
          float val6 = sensors.getTempC(Six);
          object[SixX] = roundf(val6*100)/100.0;

          for (uint8_t i7 = 0; i7 < 8; i7++)
          SevenX += String(Seven[i7], HEX);
          float val7 = sensors.getTempC(Seven);
          object[SevenX] = roundf(val7*100)/100.0;

          for (uint8_t i8 = 0; i8 < 8; i8++)
          EightX += String(Eight[i8], HEX);
          float val8 = sensors.getTempC(Eight);
          object[EightX] = roundf(val8*100)/100.0;

          for (uint8_t i9 = 0; i9 < 8; i9++)
          NineX += String(Nine[i9], HEX);
          float val9 = sensors.getTempC(Nine);
          object[NineX] = roundf(val9*100)/100.0;

          for (uint8_t i10 = 0; i10 < 8; i10++)
          TenX += String(Ten[i10], HEX);
          float val10 = sensors.getTempC(Ten);
          object[TenX] = roundf(val10*100)/100.0;             

          // serialize the json output
          serializeJsonPretty(doc, jsonOutput);
          // print to website
          client.println(jsonOutput);
          break; 
        }
      }   
        
    }
  }    
  delay(1);
  client.stop();
  delay(1000);
} 


