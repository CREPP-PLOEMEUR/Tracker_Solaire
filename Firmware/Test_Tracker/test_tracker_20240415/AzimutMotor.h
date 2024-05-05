// AzimutMotor 

#ifndef AzimutMotor_h
#define AzimutMotor_h

#include <Arduino.h>


const int deg10 = 512; // 5000 pas pour 90° donc 511 pour 10°
const int duration = 800; // en microsecondes - min 2.5

// controle retour au 50
// const int buteePin = 16; // D0

// Parametres de rotation
const int PasParTour = 200; // pas defaut 1.8 deg au moteur mais depend de step 200, 400, 800, 1600, 3200 sur TB6600
const int Reduction = 92; // rapport worm gear 1:92
const float EstMax = 70.0; // cap max NE du matin
const float OuestMax = 290.0; // cap max NW du soir

const float Ang2pas = PasParTour * Reduction / 360; // 18400 pas pour 360




class AzimutMotor {

private:
    int privatea;

    uint8_t _buteePin; // pin butee fin de course est
    uint8_t _enaPin;  // pin enable du TB6600
    uint8_t _pulsePin; // pin pulse du TB6600
    uint8_t _dirPin; // pin direction du TB6600
    int _pas_tours; // 200 par defaut - parametrage du TB6600
    int _reduction; // rapport boite de vitesse 92 ici
    float _anglebutee; // direction en butéee - dépend de la came- 50° est 
    float _anglemax;

    int _pascourant; // pas mémorisisé du pas, pas=0 -> butéé
    float  _anglecourant; // angle mémorisé par rapport au 50° est
    float _pasMax; // calculé : ( 310-50) * pas * reduction / 360

    const int _duration = 1200; // en microsecondes - min 2.5

    int compteursteps = 0;
    int nbsteps = 512;
    float angStep=10.0;
    float AngButee = 80.0;
    float AngMax = 290.0;
    int retint = 0;
    float retfloat;


 



public:

 

    // init
    // AzimutMotor(int enaPin, int pulsePin, int dirPin, int pas_tours, int reduction, int buteePin, float anglebutee,float angleMax);
    AzimutMotor(uint8_t enaPin, uint8_t pulsePin, uint8_t dirPin, uint8_t buteePin);
    // positionne le nouvel azimut en absolu - sens horaire - limites 50 à 310°, donne l'angle atteint
    float setAngle(float angle); 

    // attente utilisant micros()  qui reset toutes les 2^32 microsecondes
    void usWait(uint32_t duree) ;

    // tourne de x steps par rapport à la position courante en positif (W) ou negatif (E), 
    // s'arrête si le compteur atteint les butées 0 (50°) ou _pasMax (310°)
    int tournePas(int step); 

    // donne le pas courant
    int getPas(); 

    // donne l'angle courant
    float getAngle(); 

    // retourne en butée à l'est
    int retourEst(); 

       // avance ou recule d'un certain nombre de pas
    int versOuest(int nombre);
    int versEst(int nombre) ;

};

#endif
