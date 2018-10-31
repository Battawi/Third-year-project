/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "Pin_Declaration.h"

#define FT8_PDN ***   //POWER UP PIN IN LCD 

void LCD_initialization(void)
{
	
	ioport_disable_pin(FT8_PDN) //  0 --> PDN pin
	
}
int main (void)
{
	ioport_init() // initialization of ioport
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();


	board_init();

	/* Insert application code here, after the board has been initialized. */
}
