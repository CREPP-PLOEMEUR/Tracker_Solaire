// ElevationMotor
// controle l'élévation du panneau en ajustant la longueur du vérin entre 37 et 57cm
// la longueur du vérin est mesurée via un potentiometre electronique entre 0 (36cm) 10V (58cm)
// l'elevation est obtenue par le theoreme d'AL Kashi 
// cette classe utilise le circuit L298N
// attention le L298 est limité à 2A max par pont

#ifndef ElevationMotor_h
#define ElevationMotor_h

#include <Arduino.h>
#include <math.h>

class ElevationMotor{

private:

  // formule d'AL Kashi : donne l'angle en A connaissant la longueur opposée
  float Angle_Al_Kashi(float longBC);

  // formule inverse : donne la longueur opposée en fonction de l'angle en A
  float Long_Al_Kashi(float angle);


    uint8_t _enaPin; 
    uint8_t _inAPin;
    uint8_t _inBPin;
    uint8_t _anaVerinPin;

   /* si on passe sur du controle par MOSFET , il faut gérer les 4 commandes de transistor pontA, B, haut, bas
   int _ha1Pin, _ha2Pin, _hb1Pin, _hb2Pin;
   */

 // Mémorisation de la longueur du verin
  float _BC = 49.5; // longueur du vérin - entre 39.5 et 55.5
  float _elevationCourante;

  // valeur de construction mecanique de la fixation du panneau
const float AC = 56.0;  // longueur panneau entre fixation avant et point de poussee 
const float AB = 17.0;  // longueur base entre fixation avant et fixation moteur
const float angleAB0 = 7.0; // le point A et 1.6ncm au dessus du B et a 17cm horizontal

// valeur de limitation du potentiometre - un pont diviseur 27K/10K limite la tension mesurée
const float LMax=55.6; // longueur max du piston - pour environ 10° d'élévation
const float Lmin=39.5; // longueur min du piston - pour environ 75° d'élevation
const float tensionMax = 2.66; // coefficient tension -> Longeur

// valeurs physique du potentiometre
const float PistonMin = 37.5; // potentiometre au minimum 0.0 V
const float PistonMax = 57.5; // potentiometre au maximum 2.66V

const float elevationMin = 19.0;
const float elevationMax = 72.0;

bool  _isValid = true;  // si la mesure du verin indique 0 c'est qu'il y a un problème



public:

  // init indiquer les pins affectée pour le pont et la lecture du potentiomètre
  ElevationMotor(uint8_t enaPin, uint8_t inAPin, uint8_t inBPin, uint8_t anaVerinPin );

  /* pour commmande via MOSFET
  ElevationMotor(int ha1Pin, int ha2Pin, int hb1Pin, int hb2Pin, int anaVerinPin );
  */

 

  // donne la longuer du vérin
  float getLongVerin();

  // donne 

  //avance le moteur - le vérin s'allonge - pendant une certaine durée
  // la longueur dépend de la puissance fournie au moteur PWM entre 50 et 100%*
  // pour l'instant pleine puissance
  void avanceMoteur();

  // idem pour reduire le vérin
  void reculeMoteur();

  // arret du moteur
  void arretMoteur();

  // positionne le verin pour l'élévation (avance ou recule le moteur en conséquence)
  float setAngle(float elev);

  // elevation Courante par mesure de la longueur du verin et calcul al kashi
  float elevationCourante();

};

#endif  //ElevationMotor_h