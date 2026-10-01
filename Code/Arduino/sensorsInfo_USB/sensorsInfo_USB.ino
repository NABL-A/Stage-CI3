// Broches de contrôle du multiplexeur (S0 à S3)
const int S3 = 19;
const int S2 = 20;
const int S1 = 21;
const int S0 = 22;

// Broche de sortie du multiplexeur
const int MUX_OUT = 5;

const int NB_CAPTEURS = 16;

// Seuil de bruit
const int SEUIL = 100;

int lectures[NB_CAPTEURS];

// Sélectionne le canal du mux (0 à 15)
void selectCanal(int canal) {
  digitalWrite(S0, (canal >> 0) & 1);
  digitalWrite(S1, (canal >> 1) & 1);
  digitalWrite(S2, (canal >> 2) & 1);
  digitalWrite(S3, (canal >> 3) & 1);
}

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
}

void loop() {
  for (int i = 0; i < NB_CAPTEURS; i++) {
    selectCanal(i);
    delayMicroseconds(10); 

    int valeur = analogRead(MUX_OUT);
    lectures[i] = (valeur <= SEUIL) ? 0 : valeur;
  }

  for (int i = 0; i < NB_CAPTEURS; i++) {
    Serial.print(lectures[i]); 
    if (i < NB_CAPTEURS - 1) Serial.print("\t");
  }
  Serial.println();

  delay(50);
}