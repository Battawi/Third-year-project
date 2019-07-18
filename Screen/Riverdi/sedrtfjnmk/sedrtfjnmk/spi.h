/*
 * SPIIII.c
 *
 * Created: 7/13/2019 2:27:27 PM
 *  Author: 123
 */ 

#ifndef spi_h 
#define spi_h

#include "sam.h"
/*
void clock_init(){
    REG_CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTEN;
    while (!(REG_PMC_SR & PMC_SR_MOSCXTS));
    REG_CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;
    REG_PMC_MCKR |= PMC_MCKR_CSS_MAIN_CLK;
    while (!(REG_PMC_SR & PMC_SR_MCKRDY));
    REG_PMC_MCKR |= PMC_MCKR_PRES_CLK_1;
    while (!(REG_PMC_SR & PMC_SR_MCKRDY));
}
*/
void SPI_setMode(uint8_t mode){	
    /*
    Mode		CPOL	NCPHA
    Mode0		0		1
    Mode1		0		0
    Mode2		1		1
    Mode3		1		0
    */
    if (mode == 0){
        REG_SPI_CSR &= ~SPI_CSR_CPOL;
        REG_SPI_CSR |= SPI_CSR_NCPHA;
    }
    else if (mode == 1){
        REG_SPI_CSR &= ~SPI_CSR_CPOL;
        REG_SPI_CSR &= ~SPI_CSR_NCPHA;
    }
    else if (mode == 2){
        REG_SPI_CSR |= SPI_CSR_CPOL;
        REG_SPI_CSR |= SPI_CSR_NCPHA;
    }
    else if (mode == 3){
        REG_SPI_CSR |= SPI_CSR_CPOL;
        REG_SPI_CSR &= ~SPI_CSR_NCPHA;
    }
}

void SPI_selectPeripheral(uint8_t peripheral){
    //chose peripheral
    //this only works if SPI_MR.PS = 0
    //if SPI_MR.PS = 1 then peripheral selection is done in SPI_THR.PCS
    if (peripheral == 0){
        //choose NPCS0
        REG_SPI_MR |= SPI_MR_PCS(0b1110);
    }
    else if (peripheral ==1){
        //choose NPCS1
        REG_SPI_MR |= SPI_MR_PCS(0b1101);
    }
    else if (peripheral ==2){
        //choose NPCS2
        REG_SPI_MR |= SPI_MR_PCS(0b1011);
    }
    else if (peripheral ==3){
        //choose NPCS3
        REG_SPI_MR |= SPI_MR_PCS(0b0111);
    }
}

void SPI_deselect_span(){
    //wait for transmit register to be empty
    while (!(REG_SPI_SR & SPI_SR_TDRE));
    //send data to transmit register
    REG_SPI_TDR |= SPI_TDR_LASTXFER;
    //wait for received data to be ready to be read
    while (!(REG_SPI_SR & SPI_SR_RDRF));
}

void SPI_init(){
    //enable peripheral clock
    REG_PMC_PCER0 |= PMC_PCER0_PID21;
    //set spi master mode
    REG_SPI_MR |= SPI_MR_MSTR;
    //set fixed peripheral select(peripheral chosen in SP_MR.PCS instead of SPI_THR.PCS)
    REG_SPI_MR &= ~SPI_MR_PS;
    //set polarity and clock phase
    //SPI_setMode(3);
	SPI_setMode(0);//////
	SPI_selectPeripheral(0);////////
    //set clock generator (1 = peripheral clock rate), otherwise a divisor
    //SCBR = fperipheral clock / SPCK Bit Rate
    REG_SPI_CSR |= SPI_CSR_SCBR(64);
    //chip select remains low after transfer
    REG_SPI_CSR |= SPI_CSR_CSNAAT;
    //give peripheral control of pins (Chip select pins are optional)
    REG_PIOA_PDR |= PIO_PDR_P11; //NPCS0
    //REG_PIOA_PDR |= PIO_PDR_P31; //NPCS1
    REG_PIOA_PDR |= PIO_PDR_P12; //MISO
    REG_PIOA_PDR |= PIO_PDR_P13; //MOSI
    REG_PIOA_PDR |= PIO_PDR_P14; //MOSI
    //enable SPI
    REG_SPI_CR |= SPI_CR_SPIEN;
}

//flir slave select is pa11
    void slaveselect(){
    REG_PIOA_CODR |= PIO_CODR_P11; //set PA11 low	///////
}

void slavedeselect(){
    //wait for transmit register to be empty
    while (!(REG_SPI_SR & SPI_SR_TDRE));
    //send data to transmit register
    REG_SPI_TDR|= SPI_TDR_LASTXFER;
    //wait for received data to be ready to be read
    while (!(REG_SPI_SR & SPI_SR_RDRF));
    REG_PIOA_SODR |= PIO_SODR_P11; //set PA11 high///////
}

//flir reset is pa30
void flirReset_assert(){
    //clear pa30 to reset pin
    //check hold time and make delay
    REG_PIOA_CODR |= PIO_CODR_P30;
}
void flirReset_deassert(){
    //reset pin high to prevent reset
    REG_PIOA_SODR |= PIO_SODR_P30;
}

uint8_t SPI_byteExchange(uint8_t data){
    //wait for transmit register to be empty
    while (!(REG_SPI_SR & SPI_SR_TDRE));
    //send data to transmit register
    REG_SPI_TDR |= data;
    //wait for received data to be ready to be read
    while (!(REG_SPI_SR & SPI_SR_RDRF));////
    //read received data
    return REG_SPI_RDR;
}
//write spi only
void spi_write(uint8_t data){
	//wait for transmit register to be empty
	while (!(REG_SPI_SR & SPI_SR_TDRE));
	//send data to transmit register
	REG_SPI_TDR |= data;
	
}

//read spi only
uint8_t spi_read(){
	//wait for received data to be ready to be read
	while (!(REG_SPI_SR & SPI_SR_RDRF));////
	//read received data
	return REG_SPI_RDR;
}
void spi_write16(uint16_t data){
spi_write8(data);
spi_write8(data>>8);
}



volatile uint32_t counter = 0;
void delay_ms(uint32_t delayInMs){

	REG_TC0_RC0 = 10000; //1 second / 10mhz = 1ms
	//enable tc clock
	REG_TC0_CCR0 |= TC_CCR_CLKEN;
	//start timer
	REG_TC0_CCR0 |= TC_CCR_SWTRG;

	while (counter <= delayInMs){
		
	}
}
#endif