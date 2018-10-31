/*GPIO*/
ioport_init();
// initialize ioport
ioport_set_pin_dir(number of pin,direction);
/*
direction either IOPORT_DIR_OUTPUT
or IOPORT_DIR_INPUT
*/
ioport_set_pin_level(pin number,level);
/* 
level is HIGH or LOW, true or false. 
*/

ioport_set_pin_mode(pin number, mode);

/*
mode is IOPORT_MODE_PULLUP or pull down
other modes are defined in ioport_pio.h 
*/

ioport_get_pin_level(pin number)

/*
returns 1 if pin is high 0 if pin is false
*/
//Rest of functions in PIO.h
//PORT name
/*
#define IOPORT_PIOA     0
#define IOPORT_PIOB     1
#define IOPORT_PIOC     2
#define IOPORT_PIOD     3
#define IOPORT_PIOE     4
#define IOPORT_PIOF     5
*/


/*USART*/
usart_write_line(pointer to usart, pointer to string)
//Pointer to usart: USART0 or USART1
//