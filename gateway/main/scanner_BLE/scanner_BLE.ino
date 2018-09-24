#define SCAN_TIME  5 // seconds

// comment the follow line to disable serial message
#define SERIAL_PRINT

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks{
    void onResult(BLEAdvertisedDevice advertisedDevice){
    #ifdef SERIAL_PRINT
//      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      Serial.printf("-------------------------------\n");
      Serial.printf("Advertised Device: %s\n", advertisedDevice.getName().c_str());
      Serial.printf("Address: %s\n", advertisedDevice.getAddress().toString().c_str());
      Serial.printf("RSSI: %d\n", advertisedDevice.getRSSI());
//      Serial.printf("TxPower: %d\n", d.getTXPower());
    #endif
    }
};

void setup(){

  #ifdef SERIAL_PRINT
    Serial.begin(115200);
    Serial.println("ESP32 BLE Scanner");
  #endif
  
  #ifdef SERIAL_PRINT
    Serial.printf("Start BLE scan for %d seconds...\n", SCAN_TIME);
  #endif
}
void loop(){
  BLEDevice::init("");
  
  BLEScan *pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(0x50);
  pBLEScan->setWindow(0x30);
  
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME); //start scan
  
  #ifdef SERIAL_PRINT
    Serial.println("Scan done!");
  #endif
}
