const int ledPins[] = { 8, 9, 10, 11 };  // Tableau des numéros de broches
int potentiometerPin = A1;
int potentiometerValue = 0;
int bouttonPin = 2;
int etatPresent;
int ledState = HIGH;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    // Initialisation des DEL en sortie
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(bouttonPin, INPUT_PULLUP);
}

void loop() {
  potentiometerValue = analogRead(potentiometerPin);
  int potentiometerValuePourcent = map(potentiometerValue, 0, 1023, 0, 100);
  int longueurBarre = map(potentiometerValue, 0, 1023, 0, 20);
  int etatPresent = digitalRead(bouttonPin);
  if (potentiometerValue < 256) {
    cas1();
  } else if (potentiometerValue < 512) {
    cas2();
  } else if (potentiometerValue < 768) {
    cas3();
  } else {
    cas4();
  }
  static int etatPrecedent = LOW;              // État initial cohérent avec INPUT_PULLUP
  static int etat = HIGH;                      // État stable du bouton
  const int delai = 50;                        // Délai anti-rebond en ms
  static unsigned long dernierChangement = 0;  // Dernier changement d'état

  if (etatPresent != etatPrecedent) {  // Si l'état change
    dernierChangement = millis();      // Mise à jour du temps
  }

  if ((millis() - dernierChangement) > delai && etatPresent != etat) {
    etat = etatPresent;  // Mise à jour de l’état stable
    affichageBarre();    // Affichage
  }

  etatPrecedent = etatPresent;  // Mise à jour pour la prochaine itération
}




void affichageBarre() {
  potentiometerValue = analogRead(potentiometerPin);
  int potentiometerValuePourcent = map(potentiometerValue, 0, 1023, 0, 100);
  int longueurBarre = map(potentiometerValue, 0, 1023, 0, 20);
  Serial.print(potentiometerValuePourcent);
  Serial.print("% [");
  for (int i = 0; i < longueurBarre; i++) {
    Serial.print("@");
  }
  for (int i = longueurBarre; i < 20; i++) {
    Serial.print(".");
  }
  Serial.println("]");
}


void cas1() {
  digitalWrite(ledPins[0], ledState);
  digitalWrite(ledPins[1], !ledState);
  digitalWrite(ledPins[2], !ledState);
  digitalWrite(ledPins[3], !ledState);
}
void cas2() {
  digitalWrite(ledPins[0], ledState);
  digitalWrite(ledPins[1], ledState);
  digitalWrite(ledPins[2], !ledState);
  digitalWrite(ledPins[3], !ledState);
}
void cas3() {
  digitalWrite(ledPins[0], ledState);
  digitalWrite(ledPins[1], ledState);
  digitalWrite(ledPins[2], ledState);
  digitalWrite(ledPins[3], !ledState);
}
void cas4() {
  digitalWrite(ledPins[0], ledState);
  digitalWrite(ledPins[1], ledState);
  digitalWrite(ledPins[2], ledState);
  digitalWrite(ledPins[3], ledState);
}
