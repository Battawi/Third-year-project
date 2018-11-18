/*
 * Riverdi.c
 *
 * Created: 01/11/2018 16:31:52
 *  Author: Abdulrahman
 */ 

#include "Riverdi.h"

uint8_t FT8_init(void){
	ioport_set_pin_level(POWER_PIN,HIGH);
	delay_ms(6);
	ioport_set_pin_level(POWER_PIN,LOW);
	delay_ms(21);
	
		
	
}
