// cette librairie définit toutes les pins utilisées

#ifndef ConnexionPins_h
#define ConnexionPins_h

// pour le GPS
long GPS_Speed=9600;
uint8_t myGPS_RX=2;  // broche RX pour l'arduino
uint8_t myGPS_TX=3;  // broche TX pour l'arduino

//eventuellement pour avoir des traces dans le gps
//#define DEBUG_GPS

// pour le vérin d'élévation pint en H
uint8_t elevEnable=5;   // broche Enable - output Active High
uint8_t elevIN_A=6;     // broche IN_A - output Active High
uint8_t elevIN_B=7;     // broche IN_B - output Active High

uint8_t  elevPotar=A0;  // mesure du potentiomètre Input Analog 



//pour le TB6600 d'azimuth
//controle du tb6600
uint8_t tb66DirPin = 8;  // Broche Dir   - output Active High
uint8_t tb66PulsePin = 9; // Broche Pulse  - output Active High
uint8_t tb66EnaPin = 10; // broche Enable -  - output Active High

uint8_t tb66ButeePin=11;  // Broche Capteur fin de course Retour - Active High

// oled - Par defaut c'est reconnu par la librairie Wire, donc on s'assure que les pattes ne sont pas utilisées

uint8_t oled_SCL=A5; 
uint8_t oled_SDA=A4; 






#endif