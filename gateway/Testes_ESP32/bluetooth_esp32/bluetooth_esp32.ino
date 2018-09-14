#include "BluetoothSerial.h"
//
//#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
//#endif

BluetoothSerial SerialBT;
int led = 2;
char leu;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("Pronto para parear");
  pinMode(led, OUTPUT);  
  digitalWrite(led, LOW);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    leu = SerialBT.read();
    Serial.write(leu);
    if (leu == 'H') digitalWrite(led, HIGH);
    else if (leu == 'L') digitalWrite(led, LOW);
  }
  delay(20);
}
