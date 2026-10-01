const int valeurCapteur1 = A0 ;
const int valeurCapteur2 = A5 ;
int lectureCapteur1 ;
int lectureCapteur2 ;

void setup() {
  Serial.begin(9600);
}

void loop() {
  lectureCapteur1 = analogRead(valeurCapteur1);
  lectureCapteur2 = analogRead(valeurCapteur2);

  if (lectureCapteur1 <= 30) {
    lectureCapteur1 = 0;
  };

   if (lectureCapteur2 <= 30) {
    lectureCapteur2 = 0;
  };

  Serial.print(lectureCapteur1);
  Serial.print(",");
  Serial.println(lectureCapteur2);
  delay(50);
}


#include <WiFi.h>

const char* ssid     = "";
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connexion au Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Connecté");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal (RSSI) : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi OK");
  } else {
    Serial.println("Wi-Fi Perdu");
  }
  delay(5000);
}