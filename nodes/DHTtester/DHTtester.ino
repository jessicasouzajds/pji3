#include "DHT.h"
#define DHTPIN A2
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void sendData(int data){
  Serial.println(data, HEX);
  Serial1.write(data);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println("------------------------------------------------");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  Serial.println("Eniando dados de hum e temp...");
  sendData((int) h);
  sendData((int) t);
}
