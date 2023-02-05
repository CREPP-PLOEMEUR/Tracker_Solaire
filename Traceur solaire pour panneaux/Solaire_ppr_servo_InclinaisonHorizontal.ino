#include  <Servo.h>     //Inclusion de la bibliothèque Servo
  Servo monServoI;  // Création d'un objet Servo inclinaison
  Servo monServoH;  // Création d'un objet Servo suivi horizontal

#define ServoPinH  3 // servo moteur horizontal
#define ServoPinI  7 // servo moteur inclinaison
  
  int pos = 0;    //Angle du servomoteur
  int MaxPosI = 80;  // angle d'inclinaison maximum 
                     //100: les pièces en bois se touchent
  int MaxPosH = 180;  // angle de poursuite horizontal du soleil
                     //100: les pièces en bois se touchent
  
  void setup() {
    monServoI.attach(ServoPinI);  // servo moteur inclinaison
    monServoH.attach(ServoPinH);  // servo moteur suivi horizontal
  }
    
  void loop() {

    // servomoteur d'inclinaison
    // angle maximum de 80°
    for (pos = 0; pos <= MaxPosI; pos += 1) { // 180 Parcours la plage angulaire [0-180] degré par degré
      monServoI.write(pos);              //Actualise la position 
      delay(15);                       //Attend 15 ms avant l'actualisation
    }//Fin for
  
    for (pos = MaxPosI; pos >= 0; pos -= 1) {     //Parcours la plage angulaire [0-180] degré par degré
      monServoI.write(pos);              //Actualise la position 
      delay(15);                       //Attend 15 ms avant l'actualisation
    }//Fin for

  //***************

    // servomoteur de suivi horizontal 
    // angle maximum de 180°
    for (pos = 0; pos <= MaxPosH; pos += 1) { // 180 Parcours la plage angulaire [0-180] degré par degré
      monServoH.write(pos);              //Actualise la position 
      delay(15);                       //Attend 15 ms avant l'actualisation
    }//Fin for
  
    for (pos = MaxPosH; pos >= 0; pos -= 1) {     //Parcours la plage angulaire [0-180] degré par degré
      monServoH.write(pos);              //Actualise la position 
      delay(15);                       //Attend 15 ms avant l'actualisation
    }//Fin for  
  }//Fin loop
