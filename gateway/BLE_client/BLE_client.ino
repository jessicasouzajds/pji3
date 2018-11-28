#include "BLEDevice.h"
//#include "BLEScan.h"

// Serviço remoto que se deseja conectar
static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
// Característica associada ao serviço que estamos interessados
static BLEUUID    charUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static BLEAddress *pServerAddress; 
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
//static boolean notify = false;

struct Desc{
    BLEClient*  pClient  = BLEDevice::createClient();
}aux;

static void notifyCallback( BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("Notificação recebida de: ");
    Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print("Tamanho da mensagem: ");
    Serial.println(length);
    Serial.print("Dados: ");
    unsigned int dado[length];
    for (int i = 0; i < length; i++){
      dado[i] = pData[i];
    }
    Serial.print("Umidade: ");
    Serial.print(dado[0]);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(dado[1]);
    Serial.println(" *C ");

    Serial.println("VAI DESCONECTAR AGORA");
    aux.pClient->disconnect();
}

bool connectToServer(BLEAddress pAddress) {
    Serial.print("Conectando com: ");
    Serial.println(pAddress.toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();

    // Conecta com dispositivo BLE
    pClient->connect(pAddress);

    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Falha ao encontrar o service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      return false;
    }
    Serial.println("Serviço encontrado!");

    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Falha ao encontrar o charUUID: ");
      Serial.println(charUUID.toString().c_str());
      return false;
    }
    Serial.println("Característica encontrada!");
    // callback para cada notificação enviada pelo dispositivo
    aux.pClient = pClient;
    doConnect = false;
    pRemoteCharacteristic->registerForNotify(notifyCallback); 
//    while(notify == false) delay(3000);  
//    notify = false;
//    pClient->disconnect();

//    desconectar(pClient);
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("Dispositivo BLE encontrado: ");
    Serial.println(advertisedDevice.toString().c_str());

    // Verifica se o dispositivo encontrado possui ServiceUUID valido
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)){
      Serial.print("Dispositivo válido!"); 
      advertisedDevice.getScan()->stop();

      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;
    }
    else Serial.println("ServiceUUID inválido!!! Ignorando dispositivo.");
  }
//
};

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando cliente BLE...");
}

void loop() {
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  //setando funcao de callback que sera chamada quando um novo dispositivo for encontrado
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  //Inicia scan BLE por 30 segundos
  pBLEScan->start(30);
  
  if (doConnect == true) {
    if (!connectToServer(*pServerAddress)) {
      Serial.println("Falha na conexão");
    }
    doConnect = false;
  }
  delay(1000);
}
