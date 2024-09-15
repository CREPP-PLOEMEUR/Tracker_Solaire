// cette librairie définit toutes les pins utilisées

#ifndef CONNECTION_PIN_h
#define CONNECTION_PIN_h

// pour le GPS
long GPS_Speed=9600;
uint8_t myGPS_RX=1;  // broche RX pour l'arduino
uint8_t myGPS_TX=0;  // broche TX pour l'arduino

//eventuellement pour avoir des traces dans le gps
//#define DEBUG_GP


// pour le vérin d'élévation pint en H
uint8_t elevEnable=5;   // broche Enable - output Active High
uint8_t elevIN_A=4;     // broche IN_A - output Active High
uint8_t elevIN_B=5;     // broche IN_B - output Active High

uint8_t  elevPotar=A0;  // mesure du potentiomètre Input Analog 
uint8_t userPot = A1;


//pour le TB6600 d'azimuth
//controle du tb6600
uint8_t tb66DirPin = 9;  // Broche Dir   - output Active High
uint8_t tb66PulsePin = 10; // Broche Pulse  - output Active High
uint8_t tb66EnaPin = 8; // broche Enable -  - output Active High

uint8_t tb66ButeePin=A2;  // Broche Capteur fin de course Retour - Active High

// oled - Par defaut c'est reconnu par la librairie Wire, donc on s'assure que les pattes ne sont pas utilisées

uint8_t oled_SCL=A5; 
uint8_t oled_SDA=A4; 






#endif