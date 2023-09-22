#include "Arduino.h"
#include "RGB.h"


RGB::RGB(int pin_red, int pin_green, int pin_blue) 
{

		pin_redIN = pin_red;
		pin_greenIN = pin_green;
		pin_blueIN = pin_blue;

		pinMode(pin_redIN, OUTPUT);
		pinMode(pin_greenIN, OUTPUT);
		pinMode(pin_blueIN, OUTPUT);
}
void RGB::on(int color) 
{

switch(color) {

	case 0: analogWrite(pin_redIN,255);
			analogWrite(pin_greenIN,0);
			analogWrite(pin_blueIN,0);
			break;

	case 1: analogWrite(pin_redIN,0);
			analogWrite(pin_greenIN,255);
			analogWrite(pin_blueIN,0);
			break;


	case 2:	analogWrite(pin_redIN,0);
			analogWrite(pin_greenIN,0);
			analogWrite(pin_blueIN,255);
			break;

	case 3: analogWrite(pin_redIN,0);
			analogWrite(pin_greenIN,255);
			analogWrite(pin_blueIN,0255);
			break;
	case 4: analogWrite(pin_redIN,255);
			analogWrite(pin_greenIN,165);
			analogWrite(pin_blueIN,0);
			break;

	case 5: analogWrite(pin_redIN,255);
			analogWrite(pin_greenIN,255);
			analogWrite(pin_blueIN,255);
			break;

	case 6: analogWrite(pin_redIN,75);
			analogWrite(pin_greenIN,0);
			analogWrite(pin_blueIN,130);
			break;

	case 7: analogWrite(pin_redIN,64);
			analogWrite(pin_greenIN,224);
			analogWrite(pin_blueIN,208);
			break;

	case 8: analogWrite(pin_redIN,255);
			analogWrite(pin_greenIN,255);
			analogWrite(pin_blueIN,0);
			break;

	case 9: analogWrite(pin_redIN,255);
			analogWrite(pin_greenIN,0);
			analogWrite(pin_blueIN,255);
			break;

	case 10: analogWrite(pin_redIN,255);
			 analogWrite(pin_greenIN,192);
			 analogWrite(pin_blueIN,203);
			 break;
			 		
	}			
}

void RGB::blink(int color, unsigned long delai_high, unsigned long delai_low,unsigned long nombre) 
{

switch(color) {

	case 0: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 1: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 2: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 3: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;
	case 4: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 5: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 6: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 7: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;
	case 8: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;
			
	case 9: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;

	case 10: for(int i=0;i<nombre;i++) {
			on(color);
			delay(delai_high);
			off();
			delay(delai_low);
			}//End for
			break;
	}
}//End


void RGB::off() 
{

	analogWrite(pin_redIN,0);
	analogWrite(pin_greenIN,0);
	analogWrite(pin_blueIN,0);
}

void RGB::randomRGB(unsigned long delai, int frequence) 
{

	unsigned long temps = millis();
	unsigned long delai_for = 1000/frequence;

	while(millis()-temps>delai) {

			byte val_red = random(0,255);
			byte val_green = random(0,255);
			byte val_blue = random(0,255);
			analogWrite(pin_redIN,64);
			analogWrite(pin_greenIN,224);
			analogWrite(pin_blueIN,208);
			delay(delai_for);
	}//end while

}








