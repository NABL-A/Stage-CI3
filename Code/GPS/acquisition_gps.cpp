#include <HardwareSerial.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TinyGPSPlus.h>

#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_COORDS_UUID    "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_STATUS_UUID    "6E400004-B5A3-F393-E0A9-E50E24DCCA9E"

HardwareSerial icarusSerial(0);
BLECharacteristic *pCharCoords;
BLECharacteristic *pCharStatus;
TinyGPSPlus gps;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
        Serial.println("Client BLE connecté");
    }
    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
        Serial.println("Client BLE déconnecté");
        pServer->startAdvertising();
    }
};

void setup() {
    Serial.begin(115200);
    icarusSerial.begin(115200, SERIAL_8N1, 17, 16);

    BLEDevice::init("Semelle_GPS");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), 20);

    pCharCoords = pService->createCharacteristic(
        CHAR_COORDS_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    pCharCoords->addDescriptor(new BLE2902());

    pCharStatus = pService->createCharacteristic(
        CHAR_STATUS_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    pCharStatus->addDescriptor(new BLE2902());

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    Serial.println("BLE démarré");
}

void loop() {
    while (icarusSerial.available()) {
        String line = icarusSerial.readStringUntil('\n');
        Serial.println(line);

        for (int i = 0; i < line.length(); i++) {
            gps.encode(line[i]);
        }

        if (deviceConnected && line.length() > 0) {
            if (line.startsWith("Tracking:") || line.startsWith("SEARCHING:") || line.startsWith("FIX:")) {
                pCharStatus->setValue(line.c_str());
                pCharStatus->notify();
            }
            delay(10);
        }
    }

    if (deviceConnected && gps.location.isUpdated() && gps.location.isValid()) {
        char coords[64];
        snprintf(coords, sizeof(coords), "Lat: %.6f Lon: %.6f Alt: %.1fm",
            gps.location.lat(),
            gps.location.lng(),
            gps.altitude.meters());
        pCharCoords->setValue(coords);
        pCharCoords->notify();
        Serial.println(coords);
    }
}