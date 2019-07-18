/*
 * sedrtfjnmk.c
 *
 * Created: 7/13/2019 5:03:25 PM
 * Author : 123
 */ 


#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
	SystemInit();
	clock_init();
	timerInit();
	SPI_init();
	Riverdi_init();
    /* Replace with your application code */
    while (1) 
    {
		Riverdi_test_logo();
    }
}
