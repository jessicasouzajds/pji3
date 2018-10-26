  
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "rede-jessica";
const char* password =  "jessicarede";
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
   JsonObject& JSONencoder = JSONbuffer.createObject(); 

   //long rssi = WiFi.RSSI();     
   //Serial.print("RSSI: ");
   //Serial.println(rssi); 

   /*{
      "gateway_id":1,
      "sensor_id":1,
      "dado_sensor":"32",
      "rssi":30
    }*/

    JSONencoder["gateway_id"] = 1;
    JSONencoder["sensor_id"] = 1;
    JSONencoder["dado_sensor"] = "20";
    JSONencoder["rssi"] = 70;
 
    char JSONmessageBuffer[1000];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://localhost:5000/save_data");              //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/json");         //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();             //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Free resources
 
 }else{
    Serial.println("Error in WiFi connection");   
 }
 
  delay(1000);  //Send a request every 10 seconds
}





//outros exemplos?
//https://techtutorialsx.com/2017/04/29/esp32-sending-json-messages-over-mqtt/
