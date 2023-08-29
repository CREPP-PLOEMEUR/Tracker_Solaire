/* V2-221118
 Traceur solaire 4 capteurs de lumière.
 
 Le programme:
 - lit les 4 capteurs de lumière,
 - Les interpretes pour décider vers où s'orienter,
 - et fait tourner les 2 servos moteurs pour s'aligner vers la lumière.

 Créé le 1 Sep 2022, par Xavier Lesot, basé sur : https://www.instructables.com/DIY-Miniature-Solar-Tracker/
 Modifié le 4 Nov 2022, par Xavier Lesot : Ajout des commentaires.
 Modifié le 18 Nov 2022, par Xavier Lesot : Améliorations après 1ers retours d'expériences.
*/

// --------------------------------------------
// Câblage des broches
// Connecte la broche physique avec sa référence dans le programme.
// --------------------------------------------
// Entrées
int brocheHG = A0;
int brocheHD = A1;
int brocheBG = A2;
int brocheBD = A3;
int brocheJoyX = A4;
int brocheJoyY = A5;

// Sorties
//* ****** PPR: test OLED: on désactive 
//*  les 2 servomoteurs en débranchant
//*  10 --> 8,  11--> 9
int brocheServoRotation = 8;     // 10 opérationnel
int brocheServoInclinaison = 9;  // 11 opérationnel
int brocheLed = 13;

// --------------------------------------------
// Créer des Variables
// Définit des cases dans la mémoire RAM pour y stocker des valeurs. 
// int = 16 bits = -32,768 to 32,767
// --------------------------------------------
int HG; // stockera la valeur du capteur Haut Gauche
int HD; // stockera la valeur du capteur Droite
int BG; // stockera la valeur du capteur Bas Gauche
int BD; // stockera la valeur du capteur Bas droite
int JoyX; // Option contrôle par joystick
int JoyY;

// Réglages paramétrable:
int frequenceActualisation = 25; // Réglage de la vitesse
int consigneRotation = 90; // Position initiale (au démarrage) 90° = millieu.
int consigneInclinaison = 10; // Position initiale (au démarrage) 90° = millieu.
bool modeJoystick = false; // false: Mode capteur, true: mode joystick (optionnel).

// limites logiciels
// Butées logiciels pour empêcher le mecanisme d'aller là ou il coince.
// Ces réglages doivent être adjustés lorsque c'est mécaniquement impossible d'atteindre toute la plage de rotation du servomoteur.
int LimiteRotationMax = 180;
int LimiteRotationMin = 0;
int LimiteInclinaisonMax = 180;  // 100 ppr valeur origine
int LimiteInclinaisonMin = 10;

// --------------------------------------------
// Servo
// --------------------------------------------
// créer un objet servo pour contrôler un servo.
// douze objets servo peuvent être créés sur la plupart des cartes.
#include <Servo.h> // La biblotèque d'instructions qui s'occupe de fabriquer le signal electrique pour piloter le servo.
Servo servoRotation; // crée un objet servo pour contrôler un servo.
Servo servoInclinaison; // crée un objet servo pour contrôler un servo

// ----------ppr début ------------------------
// écran OLED
// --------------------------------------------
//
#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
// ----------ppr fin   ------------------------
//


// ============================================
// Setup
// ============================================
void setup() { // mettez votre code d'installation ici, à exécuter une fois.

  // Servo
  servoRotation.attach(brocheServoRotation); // attache le servomoteur à l'objet servoRotation par la broche 10.
  servoInclinaison.attach(brocheServoInclinaison); // attache le servomoteur à l'objet servoInclinaison par la broche 11.

  // broche à configurer en sortie
  pinMode(brocheLed, OUTPUT); // dit à l'arduino que la broche est utilisée en sortie (car aussi possible de l'utiliser en entrée).

  // Liaison Série
  // Démarre la communication sur la liaison série à la vitesse 9600 bauds 
  // (bauds: bit per second: bps. Représente le nombre de bits (0 ou 1) transmis en une seconde.)
  // (9600 bauds: +-1ko/s. Durée d'un bit: 1.042 ms.)
  Serial.begin(115200); // Démarre la liaison série
  Serial.println("Hello World !"); // « Hello world » sont les mots traditionnellement écrits par un programme informatique simple dont le but est de faire la démonstration rapide de son exécution sans erreur.

  // ----------ppr début ------------------------
  // écran OLED démarrage
  // --------------------------------------------
  //
  myOLED.begin();
  myOLED.setFont(SmallFont);
  // ----------ppr fin   ------------------------
  //
  
}

// ============================================
// Loop
// ============================================
void loop() { //mettez votre code principal ici, à exécuter à plusieurs reprises.
  
  // --------------------------------------------
  // Lecture des entrées analogiques.
  // --------------------------------------------
  // Lectures des valeurs des photoresistances
  HG = analogRead(brocheHG); // lit l'entrée A0 et stock le résultat dans HG
  HD = analogRead(brocheHD);
  BG = analogRead(brocheBG);
  BD = analogRead(brocheBD);

  if (modeJoystick){ // si mode Joystick alors:
    JoyX = analogRead(A4); // lit aussi les joysticks
    JoyY = analogRead(A5);
  }

  // A propos des photorésistances:
  // https://fr.wikipedia.org/wiki/Photor%C3%A9sistance
  // Exposé à la lumière affiche grands chiffres car représente beaucoup d'électricitée à pouvoir la traverser.
  // Caché de la lumière affiche petits chiffres car représente peu d'électricitée à pouvoir la traverser.

  // Affichage des résultats sur le moniteur série:
  // (L'arduino envoi sur la liaison série, l'ordinateur reçoit et affiche sur le moniteur série).
  Serial.println(); // Commence sur une nouvelle ligne. (println: "Print Line New" fait Retour chariot et saut à la ligne)

  Serial.print("HG: "); // envoi un texte qui décrit ce qui va suivre
  Serial.print(HG); // envoi la valeur du capteur HautGauche
  Serial.print(", "); // envoi virgule et espace pour la mise en forme pour que ce soit mieux lisible dans le moniteur serie 

  Serial.print("HD: ");
  Serial.print(HD);
  Serial.print(", ");

  Serial.print("BG: ");
  Serial.print(BG);
  Serial.print(", ");

  Serial.print("BD: ");
  Serial.print(BD);
  Serial.print(", ");

  if (modeJoystick){
    Serial.print("JoyX: "); Serial.print(JoyX); Serial.print(", ");
    Serial.print("JoyY: "); Serial.print(JoyY); Serial.print(", ");
  }
  // --------------------------------------------
  // Interprétation des capteurs:
  // Selon la provenance de la lumière,
  // change la consigne à l'axe du servomoteur d' 1° dans un sens ou dans l'autre.
  // --------------------------------------------
  Serial.print("| "); // mise en forme

  // Rotation
  if (HG > HD) { // Si +plus de lumière à Gauche
    consigneRotation -= 1; // incrémente 1° de rotation dans le sens horaire pour aller vers elle.
    Serial.print("R- "); // Affiche le résultat de l'interprétation: "Rotation -1°"
  }
  if (BG > BD) { // Si +plus de lumière à Gauche
    consigneRotation -= 1; // incrémente 1° de rotation horaire
    Serial.print("R- "); 
  }
  if (HG < HD) { // Si +plus de lumière à Droite
    consigneRotation += 1; // incrémente 1° de rotation anti-horaire
    Serial.print("R+ ");
  }
  if (BG < BD) { // Si +plus de lumière à Droite
    consigneRotation += 1; // incrémente 1° de rotation anti-horaire
    Serial.print("R+ ");
  } 

  // inclinaison 
  if (HG > BG){ // Si +plus de lumière en Haut
    consigneInclinaison += 1; // incrémente incline 1° vers le Haut
    Serial.print(" Ih+:");
    Serial.print(HG-BG);
  }
  if (HD > BD){ // Si +plus de lumière en Haut
    consigneInclinaison += 1; // incrémente incline 1° vers le Haut
    Serial.print(" Ih+:");
    Serial.print(HD-BD);
  }
  if (HG < BG){ // Si +plus de lumière en Bas
    consigneInclinaison -= 1; // incrémente incline 1° vers le Bas
    Serial.print(" Ib-:");
    Serial.print(BG-HG);
  }
  if (HD < BD){  // Si +plus de lumière en Bas
    consigneInclinaison -= 1; // incrémente incline 1° vers le Bas
    Serial.print(" Ib-:");
    Serial.print(BD-HD);
  }
  Serial.print("| "); // mise en forme
  // --------------------------------------------
  // interprétation des capteurs terminé
  // --------------------------------------------

  // --------------------------------------------
  // Fin de course logiciel.
  // Limite les consignes minimums et maximums
  // la limite max des servomoteur c'est 0...180°
  // (modification des réglages des limites tout en haut du programme.)
  // -------------------------------------------- 
  
  // Rotation Minimum
  if (consigneRotation < LimiteRotationMin) { // Si (Consigne plusPetiteQue minimum) alors
    consigneRotation = LimiteRotationMin; // réhausse la consigne à la limite.
  }
  // Rotation Maximum
  if (consigneRotation > LimiteRotationMax) {// Si (Consigne plusGrandeQue maximum) alors
    consigneRotation = LimiteRotationMax; // redescend la consigne à la limite.
  }
  // Inclinaison Minimum
  if (consigneInclinaison < LimiteInclinaisonMin){
    consigneInclinaison = LimiteInclinaisonMin;
  }
  // Inclinaison Maximum
  if (consigneInclinaison > LimiteInclinaisonMax){
    consigneInclinaison = LimiteInclinaisonMax;
  }

  // --------------------------------------------
    // Joystick
    // Si bouton mode joystick alors branche les joysticks directement sur les consignes aux moteurs et ignore les résultats précents.
    // --------------------------------------------
 
  if (modeJoystick){
    consigneRotation = map(JoyX, 0, 1023, 0, 180);
    consigneInclinaison = map(JoyY, 0, 1023, 0, 180);
  }
  
  // --------------------------------------------
    // Ecriture de la consigne vers les moteurs 
    // --------------------------------------------
  // Affichage les consignes sur le moniteur série
  Serial.print("Rotation: ");
    Serial.print(consigneRotation);
  Serial.print(", ");
  Serial.print("Inclinaison: ");
  Serial.print(consigneInclinaison);
  Serial.print(", ");


  // ----------ppr début ------------------------
  // écran OLED affichage
  // --------------------------------------------
  //myOLED.drawLine(0,0,127,63); 
  // Draw a line from the upper left 
  // to the lower right corner

    myOLED.drawLine(0,20,127,20);  // ligne horizontale 
    myOLED.drawLine(65,0,65,40);   // ligne verticale
    myOLED.setFont(MediumNumbers);
      
    myOLED.printNumI(HG, LEFT, 0);
    myOLED.printNumI(HD, RIGHT, 0);
    myOLED.printNumI(BG, LEFT, 20);
    myOLED.printNumI(BD, RIGHT, 20);
     
    myOLED.setFont(BigNumbers);
    myOLED.printNumI(consigneInclinaison, LEFT, 40);
    myOLED.printNumI(consigneRotation, RIGHT, 40);
    myOLED.update();
  // ----------ppr fin --------------------------
  //
  
  servoRotation.write(consigneRotation); // envoi la consigne vers le moteur
  servoInclinaison.write(consigneInclinaison); // envoi la consigne vers le moteur


  // fait clignoter la led à chaque actualisation
  if (digitalRead(brocheLed) == LOW){
    digitalWrite(brocheLed, HIGH);
  }else{
    digitalWrite(brocheLed, LOW);
  }

  // --------------------------------------------
  // Fréquence d'actualisation.
  // C'est le temps avant de relire la boucle,
  // C'est donc le Temps avant de refaire tourner d'1° les moteurs,
  // C'est donc la vitesse du traceur solaire.
    // --------------------------------------------
  delay(frequenceActualisation); // en millisecondes
} // Fin.
