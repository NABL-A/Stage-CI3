#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID   "12345678-1234-1234-1234-123456789012"
#define CHAR_READ_UUID "12345678-1234-1234-1234-000000000001"

const int pinCapteur1 = 2;  // GPIO2
const int pinCapteur2 = 3;  // GPIO3

int lectureCapteur1;
int lectureCapteur2;

BLECharacteristic *charRead;
bool deviceConnected = false;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Téléphone connecté !");
  }
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Déconnecté, redémarrage advertising...");
    pServer->startAdvertising();
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32-C6-Capteurs");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  charRead = pService->createCharacteristic(
    CHAR_READ_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  charRead->addDescriptor(new BLE2902());
  charRead->setValue("En attente...");

  pService->start();
  BLEDevice::getAdvertising()->addServiceUUID(SERVICE_UUID);
  BLEDevice::getAdvertising()->start();

  Serial.println("BLE prêt !");
}

void loop() {
  lectureCapteur1 = analogRead(pinCapteur1);
  lectureCapteur2 = analogRead(pinCapteur2);

  if (lectureCapteur1 <= 30) lectureCapteur1 = 0;
  if (lectureCapteur2 <= 30) lectureCapteur2 = 0;

  Serial.print(lectureCapteur1);
  Serial.print(",");
  Serial.println(lectureCapteur2);

  if (deviceConnected) {
    String val = String(lectureCapteur1) + "," + String(lectureCapteur2);
    charRead->setValue(val.c_str());
    charRead->notify();
  }

  delay(50);
}