#include <DHT.h>

// Définir les broches
#define DHTPIN 16       // Broche de données du DHT22
#define DHTTYPE DHT22  // Type de capteur DHT22

#define RELAY1 26      // Broche du relais 1
#define RELAY2 29      // Broche du relais 2
#define RELAY3 14      // Broche du relais 3
#define in1 13  // pin driver
#define in2 23      // pin driver
#define ena 27     // variation de vitesse moteur 1 
#define in3 28  // pin driver
#define in4 30      // pin driver
#define enb 31      // variation de vitesse moteur 2

// Initialiser le capteur DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialiser la communication série
  Serial.begin(115200);

  // Initialiser le capteur DHT22
  dht.begin();

  // Configurer les broches des relais en sortie
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
 pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
   pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  // Désactiver les relais au démarrage (état HIGH pour les relais actifs bas)
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(ena, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enb, LOW);

  Serial.println("Système initialisé.");
}

void loop() {
  // Lire la température et l'humidité
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Vérifier si la lecture a échoué
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT22 !");
    return;
  }

  // Afficher les données sur le moniteur série
  Serial.print("Humidité : ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Température : ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Contrôler le moteur en fonction de la température
  if (temperature > 25) {
    digitalWrite(RELAY1, 1);  // Activer le relais 1 (moteur ON)
    Serial.println("lampe allumer ");
    //sens directe moteur a 
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,150);
    Serial.println("Moteur ACTIVER (température > 25°C)");

    
  } else {
    digitalWrite(RELAY1, 0); // Désactiver le relais 1 (moteur OFF)
    Serial.println("Moteur désactivé (température <= 25°C)");
    //sens inverse moteur b
    digitalWrite(in3,0);
    digitalWrite(in4,1);
    analogWrite(enb,150);
  }
  

  // Exemple d'utilisation des autres relais
  digitalWrite(RELAY2, LOW);   // Activer le relais 2
  delay(1000);                // Attendre 1 seconde
  digitalWrite(RELAY2, HIGH); // Désactiver le relais 2

  digitalWrite(RELAY3, LOW);   // Activer le relais 3
  delay(1000);                // Attendre 1 seconde
  digitalWrite(RELAY3, HIGH); // Désactiver le relais 3

  // Attendre 2 secondes avant la prochaine lecture
  delay(2000);
}
