#include <Arduino.h>

#ifndef AzimutMotor_h
#define AzimutMotor_h



#define END_STOP_DETECTED 0
#define END_STOP_NO_DETECTED 1


#define DIRECTION_EST 0
#define DIRECTION_WEST 1

#define DELAY_US_BETWEEN_STEP 1200


#define MIN_ANGLE 50
#define MAX_ANGLE 290.0



#define MECHANICAL_GEAR_RATIO 92
#define STEP_PER_TOUR 200 //Any microstep

const int deg10 = 512; // 5000 pas pour 90° donc 511 pour 10°
const int duration = DELAY_US_BETWEEN_STEP; // en microsecondes - min 2.5

// controle retour au 50
// const int buteePin = 16; // D0

// Parametres de rotation
const int PasParTour = 200; // pas defaut 1.8 deg au moteur mais depend de step 200, 400, 800, 1600, 3200 sur TB6600
const int Reduction = 92; // rapport worm gear 1:92


const float Ang2pas = PasParTour * Reduction / 360; // 18400 pas pour 360




class AzimutMotor 
{

private:

    uint8_t _endStopSensorPin; //End Stop sensor Pin

    uint8_t _enablePin;  // pin enable of TB6600
    uint8_t _pulsePin; // pin pulse of TB6600
    uint8_t _directionPin; // pin direction of TB6600

    bool _direction = false;
    uint16_t _realAngle = 0;
    int _realStep = 0;


    int _pas_tours; // 200 par defaut - parametrage du TB6600
    int _reduction; // rapport boite de vitesse 92 ici
    float _anglebutee; // direction en butéee - dépend de la came- 50° est 
    float _anglemax;

    int _pascourant; // pas mémorisisé du pas, pas=0 -> butéé
    float  _anglecourant; // angle mémorisé par rapport au 50° est
    float _pasMax; // calculé : ( 310-50) * pas * reduction / 360

    const int _duration = DELAY_US_BETWEEN_STEP; // en microsecondes - min 2.5

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

    void enableDevice(void);
    void disableDevice(void);

    bool endStopDetected(void);

    void usWait(uint32_t duration) ;


    int makeSteps(uint32_t steps, bool direction);
    uint16_t setAngle(uint16_t angle);

    

    // positionne le nouvel azimut en absolu - sens horaire - limites 50 à 310°, donne l'angle atteint
    //float setAngle(float angle); 
    // tourne de x steps par rapport à la position courante en positif (W) ou negatif (E), 
    // s'arrête si le compteur atteint les butées 0 (50°) ou _pasMax (310°)
   //int tournePas(int step); 


    // attente utilisant micros()  qui reset toutes les 2^32 microsecondes
    // donne le pas courant
    //int getPas(); 

    // donne l'angle courant
    float getAngle(); 

    int returnToEst();
    int returnToWest();
    void setDirection(bool direction);



    private:
      
      void makeStep();

};

#endif
