// AzimutMotor 
#include "AzimutMotor.h"

// initialisation des paramètres
//  AzimutMotor::AzimutMotor(int enaPin, int pulsePin, int dirPin, int pas_tours, int reduction, int buteePin, float anglebutee,float angleMax) {
   // AzimutMotor(int enaPin, int pulsePin, int dirPin, int pas_tours, int reduction, int buteePin, float anglebutee,float angleMax);
AzimutMotor::AzimutMotor(uint8_t enablePin, uint8_t pulsePin, uint8_t directionPin, uint8_t endStopSensorPin)
{
  _enablePin = enablePin;
  _pulsePin = pulsePin;
  _directionPin = directionPin;
  _endStopSensorPin = endStopSensorPin;

  pinMode(this->_enablePin, OUTPUT);
  pinMode(this->_pulsePin, OUTPUT);
  pinMode(this->_directionPin, OUTPUT);
  pinMode(this->_endStopSensorPin, INPUT);


  this->_realAngle = MIN_ANGLE;
  this->_realStep = 0;

  _anglebutee = AngButee; // direction en butéee - dépend de la came- 50° est 
  _anglemax = AngMax; 
  _pas_tours = PasParTour;
  _reduction = Reduction;


  //_pasMax = (_anglemax - _anglebutee) * _pas_tours * _reduction / 360.0; // calculé : ( 310-50) * pas * reduction / 360

  this->disableDevice();
   
  
};

void AzimutMotor::enableDevice()
{
  digitalWrite(this->_enablePin, HIGH);
  this->usWait(this->_duration); 
}
void AzimutMotor::disableDevice()
{
  digitalWrite(_enablePin, LOW);
  //this->usWait(this->_duration); 
}

void AzimutMotor::usWait(uint32_t duration) 
{
  // Reset at 2^32 = 4294967296
  if (4294967295-micros() < duration) {
    while (micros() < 1000000) 
    {
      int nop = 1;
    }
  } 
  unsigned long my_micros = micros()+duration;
  while (micros() < my_micros) 
  {
    int nop = 1;
  }

}

void AzimutMotor::setDirection(bool direction)
{
  this->_direction = direction;

  digitalWrite(this->_directionPin, direction);
  this->usWait(this->_duration); 

}


bool AzimutMotor::endStopDetected()
{
  if (digitalRead(this->_endStopSensorPin) == END_STOP_DETECTED) 
  {
    this->disableDevice();
    return true;

  }
}
// privées

uint16_t AzimutMotor::setAngle(uint16_t angle)
{
  uint16_t targetAngle = angle;
  if (angle <= MIN_ANGLE) 
  { 
      targetAngle = MIN_ANGLE;
  }
  else if ( angle >= MAX_ANGLE ) {
      targetAngle = MAX_ANGLE;
  }
  else {
   
  }

  // calcul du nombre de steps du moteur
  int16_t steps_A = int(targetAngle - this->_realAngle) * STEP_PER_TOUR ;
  uint16_t stepTarget = int(float(steps_A) /360.0) * MECHANICAL_GEAR_RATIO;

  this->enableDevice();
  if (stepTarget < 0) 
  {
    this->makeSteps(abs(stepTarget), DIRECTION_WEST);
    this->_realAngle = targetAngle;
    this->_realStep += abs(stepTarget);
  }
  else 
  {
    this->makeSteps(abs(stepTarget), DIRECTION_EST);
    this->_realAngle = targetAngle;
    this->_realStep += abs(stepTarget);
  }
  this->disableDevice();
    /**/
    return stepTarget;
}


void AzimutMotor::makeStep()
{
    digitalWrite(this->_pulsePin, HIGH);
    this->usWait(this->_duration);
    digitalWrite(this->_pulsePin, LOW);
    this->usWait(this->_duration);
}

int AzimutMotor::makeSteps(uint32_t steps, bool direction) 
{
  uint32_t stepDone=0;
  // Set the spinning direction clockwise:

  this->enableDevice();
  this->usWait(this->_duration); 

  this->setDirection(direction);
  this->usWait(this->_duration); 
  
   for (int i = 0; i < steps; i++) {

   /* if(this->endStopDetected() == true) 
    {
      break;
    }*/
    this->makeStep();
    stepDone += 1;
   
  }
   this->disableDevice();
   return stepDone;
}



int AzimutMotor::returnToEst()
{

  uint8_t endStopValue = digitalRead(this->_endStopSensorPin);

  if (endStopValue == END_STOP_NO_DETECTED) 
  {
    
    this->setDirection(DIRECTION_EST);
    this->enableDevice();

    while (digitalRead(this->_endStopSensorPin) != END_STOP_DETECTED) 
    {
      this->makeStep();
    }
    
    this->setDirection(DIRECTION_WEST);

    while (digitalRead(this->_endStopSensorPin) == END_STOP_DETECTED) 
    {
      this->makeStep();
    }

    this->disableDevice();
  }
  else 
  {
    this->setDirection(DIRECTION_WEST);
    this->enableDevice();

    while (digitalRead(this->_endStopSensorPin) == END_STOP_DETECTED) 
    {
      this->makeStep();
    }
    this->disableDevice();

  }//End else

  this->disableDevice();
  this->_realAngle = MIN_ANGLE;
  //_pascourant = 0;

  return 0;
};



int AzimutMotor::returnToWest()
{

    uint8_t endStopValue = digitalRead(this->_endStopSensorPin);

  if (endStopValue == END_STOP_NO_DETECTED) 
  {
    
    this->setDirection(DIRECTION_WEST);
    this->enableDevice();

    while (digitalRead(this->_endStopSensorPin) != END_STOP_DETECTED) 
    {
      this->makeStep();
    }
    
    this->setDirection(DIRECTION_EST);

    while (digitalRead(this->_endStopSensorPin) == END_STOP_DETECTED) 
    {
      this->makeStep();
    }

    this->disableDevice();
  }
  else 
  {
    this->setDirection(DIRECTION_EST);
    this->enableDevice();

    while (digitalRead(this->_endStopSensorPin) == END_STOP_DETECTED) 
    {
      this->makeStep();
    }
    this->disableDevice();

  }//End else

  this->disableDevice();
  this->_realAngle = MIN_ANGLE;
  this->_realStep = 0;

  return 0;
};



