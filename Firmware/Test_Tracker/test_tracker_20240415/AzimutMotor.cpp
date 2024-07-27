// AzimutMotor 
#include "AzimutMotor.h"

// initialisation des paramètres
//  AzimutMotor::AzimutMotor(int enaPin, int pulsePin, int dirPin, int pas_tours, int reduction, int buteePin, float anglebutee,float angleMax) {
   // AzimutMotor(int enaPin, int pulsePin, int dirPin, int pas_tours, int reduction, int buteePin, float anglebutee,float angleMax);
AzimutMotor::AzimutMotor(uint8_t enaPin, uint8_t pulsePin, uint8_t dirPin, uint8_t buteePin){
  _enaPin = enaPin;
  _pulsePin = pulsePin;
  _dirPin = dirPin;
  _buteePin = buteePin;

  pinMode(_enaPin, OUTPUT);
  pinMode(_pulsePin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
  pinMode(_buteePin, INPUT);

  // valeurs dans le .h
  _anglebutee = AngButee; // direction en butéee - dépend de la came- 50° est 
  _anglemax = AngMax; 
  _pas_tours = PasParTour;
  _reduction = Reduction;


  _pascourant = 0; // pas mémorisisé du pas, pas=0 -> butéé
  _anglecourant = _anglebutee; // angle mémorisé par rapport au 50° est
  _pasMax = (_anglemax - _anglebutee) * _pas_tours * _reduction / 360.0; // calculé : ( 310-50) * pas * reduction / 360



   digitalWrite(_enaPin, HIGH); // desactive le TB6600 - économies d'énergie 
  
  
};

  // attente utilisant micros()  qui reset toutes les 2^32 microsecondes
  // remplace delaymicrosecondes(int durée)
void AzimutMotor::usWait(uint32_t duree) {
  // micros reinitialise à 2^32 -  4294967296, donc 2*32-1  doit être la date de fin
  // 
  if (4294967295-micros() < duree) {
    while (micros() < 1000000) {
      // on attend le passage par 0
    int nop=1;
    }
  } 
  unsigned long my_micros = micros()+duree;
  while (micros() < my_micros) {
    int nop=1;
  }

}

// privées
// a tester avec des boutons ou un potentiometre
int AzimutMotor::versOuest(int nombre) {
  int pasfaits=0;
  // Set the spinning direction clockwise: 
  digitalWrite(_dirPin, HIGH);
  usWait(_duration); // delai entre le changement de dir et le train de pulse

  digitalWrite(_enaPin, LOW);
  usWait(_duration); // delai entre le changement de dir et le train de pulse

   for (int i = 0; i < nombre; i++) {
    // on sort si on atteint la butee
    if (digitalRead(_buteePin) == LOW) break;
    // These four lines result in 1 step:
    
    digitalWrite(_pulsePin, HIGH);
    usWait(_duration);
    digitalWrite(_pulsePin, LOW);
    usWait(_duration);
    pasfaits += 1;
   
  }
   digitalWrite(_enaPin, HIGH);
   return(pasfaits);
}

int AzimutMotor::versEst(int nombre) {
  int pasfaits=0;
  
  // Set the spinning direction counter clockwise:
  digitalWrite(_dirPin, LOW);
  usWait(_duration); // delai entre le changement de dir et le train de pulse

  digitalWrite(_enaPin, LOW);
  usWait(_duration); // delai entre le changement de dir et le train de pulse

   for (int i = 0; i < nombre; i++) {
      // on sort si on atteint la butee
    if (digitalRead(_buteePin) == LOW) break;
    // These four lines result in 1 step:
    digitalWrite(_pulsePin, HIGH);
    usWait(_duration);
    digitalWrite(_pulsePin, LOW);
    usWait(_duration);
    pasfaits += 1;
    

  }
 digitalWrite(_enaPin, HIGH);
 return(pasfaits);
}

// positionne le nouvel azimut en absolu - sens horaire - limites 50 à 310°, donne l'angle atteint    
float AzimutMotor::setAngle(float angle){
  int pasAFaire=0;
  int ret=0;
  float angleAFaire=_anglecourant;

  Serial.print("Pas max"); 
  Serial.println(_pasMax);

  Serial.print(" Angle courant ") ;
  Serial.print(_anglecourant,2);

  Serial.print("      angle demandés ") ;
  Serial.print(angle,2);
  Serial.print(" \t");

  // bornage des angles
  
  if (angle <= _anglebutee) { 
      angleAFaire = _anglebutee;
      }
  else if ( angle >= _anglemax ) {
      angleAFaire = _anglemax;
  }
  else {
    angleAFaire = angle;
  }
  Serial.print(" angle possible avant butées \t") ;
  Serial.println(angleAFaire);

  // calcul du nombre de steps du moteur
  pasAFaire = (angleAFaire - _anglecourant) * _pas_tours * _reduction / 360;
  Serial.print(" à faire ");
  Serial.println(pasAFaire);

  // on est dans les limites donc a priori le retour importe peu
  // ça peut prendre un peu de temps - on n'est pas multitache
  ret=tournePas(pasAFaire);
  // nouvelle valeur courante
  _anglecourant = angleAFaire;
  return angleAFaire;

};

// tourne de x steps par rapport à la position courante en positif (W) ou negatif (E), 
// s'arrête si le compteur atteint les butées 0 (50°) ou _pasMax (310°)
int AzimutMotor::tournePas(int step){
  int nbsteps=0;
  Serial.print(" tournePas \t") ;
  Serial.print(" pas demandés ") ;
  Serial.print(step);
  Serial.print(" \t");

  /* * /
  if (futurstep <=0) {
    // pas plus loin que la butée
    versEst(_pascourant);
    _pascourant = 0;
    _anglecourant = _anglebutee;
    }

  else if (futurstep >= _pasMax) {
    // pas plus loin que l'angle max
    futurstep = _pasMax - _pascourant;
    versOuest(futurstep);
    _anglecourant = _anglemax;
    _pascourant = _pasMax;
    }
  else if ( step < 0) {
    versEst( 0 - step);
    _pascourant += step;
    _anglecourant +=  360 * step / (_pas_tours * _reduction);
    }

  else {
      versOuest( step);
    _pascourant += step;
    _anglecourant +=  360 * step / (_pas_tours * _reduction);
    }
    /**/
    if ( step < 0) {
    nbsteps=versEst(0 - step);
    _pascourant -= nbsteps;
    _anglecourant -=  360 * nbsteps / (_pas_tours * _reduction);
    }

  else {
    nbsteps=versOuest( step);
    _pascourant += nbsteps;
    _anglecourant +=  360 * nbsteps / (_pas_tours * _reduction);
    }
    /**/
    
    Serial.println(_anglecourant,2);
  return 0;
};

// donne le pas courant
int AzimutMotor::getPas(){
  Serial.print(" getPas :") ;
  Serial.println(_pascourant);
  return _pascourant;
};

// donne l'angle courant
float AzimutMotor::getAngle(){
    Serial.print(" getAngle :") ;
    Serial.println(_anglecourant);
  return _anglecourant; 
};

// retourne en butée à l'est
int AzimutMotor::retourEst(){
  int butee = digitalRead(_buteePin);
  Serial.print(" retourEst : \t") ;

  // Butée = LOW => contact 
  if (butee == HIGH) {
    // pas en contact
    Serial.print(" OK pour retour vers l'est donc : \t") ;
    Serial.flush();
    // on est du bon coté
    // activer la direction est
    digitalWrite(_dirPin, LOW);
    usWait(_duration); // delai entre le changement de dir et le train de pulse

    digitalWrite(_enaPin, LOW);
    usWait(_duration); 
    while (digitalRead(_buteePin) != LOW) {
      // un step a la fois)
      digitalWrite(_pulsePin, HIGH);
      usWait(_duration);
      digitalWrite(_pulsePin, LOW);
      usWait(_duration);
    }
    // on ressort de la
    while (digitalRead(_buteePin) == LOW) {
      digitalWrite(_dirPin, HIGH);
      usWait(_duration);

      digitalWrite(_pulsePin, HIGH);
      usWait(_duration);
      digitalWrite(_pulsePin, LOW);
      usWait(_duration);
    }
    // et on désactive
    digitalWrite(_enaPin, HIGH);
  }
  else {
    // butée = LOW
    // on est au contact ou sur la butée, on avance vers louest un peu
    Serial.print(" trop loin -  l'ouest donc : \t") ;
    Serial.flush();

    // on est passé trop au nord
    // on va tourner vers l'ouest jusque"a ce que ca remonte
    digitalWrite(_dirPin, HIGH);
    usWait(_duration); // delai entre le changement de dir et le train de pulse

    digitalWrite(_enaPin, LOW);
    usWait(_duration); 
    while (digitalRead(_buteePin) != HIGH) {
      // un step a la fois)
      digitalWrite(_pulsePin, HIGH);
      usWait(_duration);
      digitalWrite(_pulsePin, LOW);
      usWait(_duration);
      
      }
    // et on désactive
    digitalWrite(_enaPin, HIGH);
  }
  _anglecourant = _anglebutee;
  _pascourant = 0;
  Serial.println(" en butée ") ;
  Serial.flush();
  return 0;
};



