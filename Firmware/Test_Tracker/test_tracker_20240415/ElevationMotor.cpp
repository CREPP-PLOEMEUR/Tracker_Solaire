#include "Arduino.h"
#include <math.h>
// ElevationMotor
// controle l'élévation du panneau en ajustant la longueur du vérin entre 37 et 57cm
// la longueur du vérin est mesurée via un potentiometre electronique entre 0 (36cm) 10V (58cm)
// l'elevation est obtenue par le theoreme d'AL Kashi 

#include "ElevationMotor.h"


// init des paramètres

ElevationMotor::ElevationMotor(uint8_t enaPin, uint8_t inAPin, uint8_t inBPin, uint8_t anaVerinPin) {
  _enaPin =  enaPin;
  _inAPin =  inAPin;
   _inBPin = inBPin;
   _anaVerinPin = anaVerinPin;

   pinMode(_enaPin, OUTPUT);
   pinMode(_inAPin, OUTPUT);
   pinMode(_inBPin, OUTPUT);
   pinMode(_anaVerinPin, INPUT);

  // lecture de la longeur du vérin et calcul de l'angle d'élévation
   _elevationCourante = elevationCourante();

}

float ElevationMotor::getLongVerin() {
  uint16_t valeurLue = analogRead(_anaVerinPin);
  float tension = valeurLue * (4.4 / 1023.0);
  float longeur = PistonMin + (tension / tensionMax) * (PistonMax - PistonMin);
   #ifdef DEBUG_ELEV 
  Serial.print("valeur brute : ");
  Serial.print(valeurLue);
  Serial.print(" : ");
  Serial.print(tension,4);
  Serial.print(" en cm  ");
  Serial.println(longeur,4);
  #endif

  if (tension==0) {
     // _isValid = false ;
    Serial.println("***** Problème rencontré, vérifier le cable du potentiometre ! *****");
  }
 return longeur;


}

float ElevationMotor::elevationCourante() {
  float long_test = getLongVerin();
  float angle_tst =  Angle_Al_Kashi(long_test);
  float elev = 90.0 - angle_tst + angleAB0;
  #ifdef DEBUG_ELEV
  Serial.print("Elevation actuelle :");
  Serial.println(elev,4);
  #endif

  return elev;
  }

// on avance le vérin, l'élévation va diminuer
void ElevationMotor::avanceMoteur() {
  // on ne bouge plus si le potentiometre est débranché
  if (_isValid == true) {
  // duree min >= 200ms 
 
   // Configuration du pont en "marche avant", pour le moteur connecté au pont A. Selon sa table de vérité, il faut que :
  digitalWrite(_inAPin, HIGH);                 // L'entrée inA doit être au niveau haut
  digitalWrite(_inBPin, LOW);                  // L'entrée inB doit être au niveau bas

  digitalWrite(_enaPin, HIGH);       // Active l'alimentation du moteur 1
  }

}

// on recule le verin, l'élévation va augmenter
void ElevationMotor::reculeMoteur() {
    // on ne bouge plus si le potentiometre est débranché
  if (_isValid == true) {

   // Configuration du pont en "marche avant", pour le moteur connecté au pont A. Selon sa table de vérité, il faut que :
  digitalWrite(_inAPin, LOW);                  // L'entrée inA doit être au niveau bas
  digitalWrite(_inBPin, HIGH);                 // L'entrée inB doit être au niveau haut

  digitalWrite(_enaPin, HIGH);       // Active l'alimentation du moteur 1
  }
}

//arret du moteur
void ElevationMotor::arretMoteur() {
// Configuration du pont en "marche avant", pour le moteur connecté au pont A. Selon sa table de vérité, il faut que :
  digitalWrite(_inAPin, LOW);                  // L'entrée inA doit être au niveau bas
  digitalWrite(_inBPin, LOW);                 // L'entrée inB doit être au niveau haut

  digitalWrite(_enaPin, LOW);        // Désactive l'alimentation du moteur 1

  }


// les 2 formules du profeqqeur Al Kashi
// 
// BC^2 = AB^2 + AC^2 - 2*AB*AC*cos(alpha)
// donc
// cos(alpha) = (AB^2 + AC^2 - BC^2) / (2*AB*AC)
// alpha (rad) = arccos((AB^2 + AC^2 - BC^2) / (2*AB*AC))
// alpha (deg) = alpha (rad) * 180/3.14153*

// formule d'AL Kashi : donne l'angle en A connaissant la longueur opposée
float ElevationMotor::Angle_Al_Kashi(float longBC) {
 
    float acc = (AB*AB + AC*AC - longBC*longBC) / (2*AB*AC);
    float alpha_rad = acos( acc);
  

    #ifdef DEBUG_ELEV
    Serial.print("Angle_Al_Kashi :\t ");
    Serial.print(longBC,8);
    Serial.print(" ... ");
    Serial.print(acc,4);
    Serial.print(" °°° ");
    Serial.println(alpha_rad,4);
    #endif


    return (alpha_rad * 180.0 / PI);

    }

  // formule inverse : donne la longueur opposée en fonction de l'angle en A
  float ElevationMotor::Long_Al_Kashi(float angle) {
    // la formule 2: cos(alpha) = (AB^2 + AC^2 - BC^2) / (2*AB*AC) - alpha en radian
    // BC^2 = AB^2 + AC^2 - 2*AB*AC*cos(alpha)
    // donc prendre la racine
    float alpha_rad = angle * PI / 180.0;
    float bc2 = sqrt(AB*AB + AC*AC - 2*AB*AC*cos(alpha_rad));
  
    #ifdef DEBUG_ELEV
    Serial.print("Long_Al_Kashi alpha rad :\t ");
    Serial.print(alpha_rad,8);
    Serial.print(" cos alpha_rad :");
    Serial.print(cos(alpha_rad),8);
    Serial.print(" ***** ");
    Serial.println(bc2,8);
    #endif

    return bc2;
    }

// avance ou recule le vérin pour se mettre à l'élévation demandée
float ElevationMotor::setAngle(float elevDemandee) {
    // on ne bouge plus si le potentiometre est débranché

  // position actuelle
  float elev_courante = elevationCourante();
  #ifdef DEBUG_ELEV
  Serial.print("setAngle, demandée : ");
  Serial.print(elevDemandee);
  #endif
 

if (elevDemandee < elev_courante and elevDemandee > elevationMin) {
    #ifdef DEBUG_ELEV
  Serial.print("Avance, demandée : ");
  Serial.print(elevDemandee);
  Serial.print(", Actuelle : ");
  Serial.println(elev_courante);

    #endif
  // il faut baisser l'elevation donc avancer le verin
  avanceMoteur();
  while ( elev_courante > elevDemandee ) {
    elev_courante = elevationCourante();
    delay(50);
    }
  arretMoteur();
  }
else if (elevDemandee > elev_courante and elevDemandee < elevationMax) {

    #ifdef DEBUG_ELEV
    Serial.print("recul, demandée : ");
    Serial.print(elevDemandee);
    Serial.print(", Actuelle : ");
    Serial.println(elev_courante);

    #endif
  // il faut augmenter  l'elevation donc reculer le verin
  reculeMoteur();
  while ( elev_courante < elevDemandee ) {
    elev_courante = elevationCourante();
    delay(50);
    }
  arretMoteur();
  }
  
  Serial.print(", obtenue : ");
  Serial.println(elev_courante);
  return elev_courante;
}
