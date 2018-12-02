/**
 * A BLE client example that is rich in capabilities.
 */

#include "BLEDevice.h"
#define BACKOFF_TIME 15000

// Serviço remoto que se deseja conectar
static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
// Característica associada ao serviço que estamos interessados
static BLEUUID    charUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;

struct Disp_BLE{
    BLEClient*  pClient  = BLEDevice::createClient();
    BLEAddress *pServerAddress;
    BLEAdvertisedDevice advertisedDevice;
    boolean leu = false;
}aux;

static long int last_time = 0, current_time= 0;
static String last_mac = "", current_mac = "";

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("Notificação recebida de: ");
    Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());
    
    Serial.print("Umidade: ");
    Serial.print(pData[0]);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(pData[1]);
    Serial.println(" *C ");
    aux.leu = true;
    aux.pClient->disconnect();
//    delay(2000);
}

// VERIFICA ULTIMA CONEXAO DO BEACON
bool verifica_conexao(){
    current_mac = aux.pServerAddress->toString().c_str();
    
    if((current_mac.equals(last_mac))){
      current_time = millis();
      long int tempo = current_time - last_time;
      if (tempo < BACKOFF_TIME){ // se houve um novo anuncio do mesmo beacon em menos de 10 segundos
        Serial.print("MUITO CEDO, IGNORANDO: ");
        Serial.println(aux.advertisedDevice.getName().c_str());
        Serial.print("Tempo em espera: ");
        Serial.print(tempo/1000);
        Serial.println(" segundos");
        return false;
      }else{  // se ja se passaram os 10 segundos
        last_time = current_time;
        Serial.print("Dispositivo conectado: ");
        Serial.println(aux.advertisedDevice.getName().c_str());
        return true;
      }
    }else{ // se o dispositivo que se conectou não é o mesmo que o anterior
        Serial.print("Dispositivo conectado: ");
        Serial.println(aux.advertisedDevice.getName().c_str());
        last_mac = current_mac;
        last_time = current_time;
        return true;
     }
}

bool connectToServer(BLEAddress pAddress) {
    if (verifica_conexao()){
        BLEClient*  pClient  = BLEDevice::createClient();
        aux.pClient = pClient;
        pClient->connect(pAddress);
    
        // Obtain a reference to the service we are after in the remote BLE server.
        BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
        if (pRemoteService == nullptr) {
          Serial.print("Falha ao encontrar UUID de servico: ");
          Serial.println(serviceUUID.toString().c_str());
          return false;
        }
        
        // Obtain a reference to the characteristic in the service of the remote BLE server.
        pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
        if (pRemoteCharacteristic == nullptr) {
          Serial.print("Falha ao encotrar UUID da caracteristica: ");
          Serial.println(charUUID.toString().c_str());
          return false;
        }
      
        pRemoteCharacteristic->registerForNotify(notifyCallback);
    }else return false;
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("Dispositivo BLE Encontrado: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {

      advertisedDevice.getScan()->stop();

      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      aux.pServerAddress = pServerAddress;
      aux.advertisedDevice = advertisedDevice;
      doConnect = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {
  Serial.begin(115200);
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
} // End of setup.


// This is the Arduino main loop function.
void loop() {
  Serial.println("REINICIOU");
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    connectToServer(*pServerAddress);
    doConnect = false;
  }
 
  // inicia um novo scan
  // aqui deve verificar se uma nova informacao foi recebida (USAR AUX.LEU)
  // e a conexao BLE é fehcada, aqui que tera que ser chamada uma
  // funcao para mandar infos via Wi-Fi
  
    delay(3000);
    
    aux.leu = false;
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->start(30);

}
