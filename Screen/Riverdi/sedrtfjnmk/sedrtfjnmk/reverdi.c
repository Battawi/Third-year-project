/*
 * reverdi.c
 *
 * Created: 7/13/2019 3:25:07 PM
 *  Author: 123
 */ 

#include <sam.h>
#include "Riverdi.h"
//#include "spi.h"
volatile uint32_t cmdOffset=0;

uint8_t Riverdi_read_8(uint32_t address){
	uint8_t Data8 = 0;
	spi_write((uint8_t)(address >> 16) | MEM_READ);	/* send Memory Write plus high address byte */
	spi_write((uint8_t)(address >> 8));	/* send middle address byte */
	spi_write((uint8_t)(address));	/* send low address byte */
	spi_write(0x00);	/* send dummy byte */
	Data8=spi_read();	/* read data byte */
	return Data8;
}

void Riverdi_write_16(uint32_t address,uint16_t data){
	spi_write((uint8_t)(address >> 16) | 0x80);
	spi_write((uint8_t)(address >> 8) | 0x80); //lesa htt3del
	spi_write((uint8_t)(address));
	spi_write(data);
	spi_write((uint8_t)(data>> 8) | 0x80);

}
//---------------------------------------------------
void Riverdi_write_32(uint32_t address,uint32_t data){
	spi_write((uint8_t)(address >> 16) | 0x80); //lesa htt3del
	spi_write((uint8_t)(address >> 8) | 0x80);
	spi_write((uint8_t)(address));
	spi_write((uint8_t) (data));
	spi_write((uint8_t)(data>> 8) | 0x80);
	spi_write((uint8_t)(data>> 16) | 0x80);
	spi_write((uint8_t)(data>> 24) | 0x80);

}
//-----------------------------------------------------
void Riverdi_write_8(uint32_t address,uint8_t data){
	spi_write((uint8_t)(address >> 16) | 0x80); //lesa htt3del
	spi_write((uint8_t)(address >> 8) | 0x80); //lesa htt3del
	spi_write((uint8_t)(address));
	spi_write(data);//8-bit
}

void Riverdi_init(void){
	REG_PIOC_PER |= POWER_PIN; //pio enable PA11
	REG_PIOC_OER |= POWER_PIN;
	REG_PIOC_SODR |=POWER_PIN;
	//ioport_set_pin_level(POWER_PIN,HIGH);
	delay_ms(6);
	REG_PIOC_CODR |=POWER_PIN;
	//ioport_set_pin_level(POWER_PIN,LOW);
	delay_ms(21);
	Riverdi_host_command(FT8_CLKINT);
	Riverdi_host_command(FT8_ACTIVE); //send host command "ACTIVE" to FT81X
	
	/* Configure display registers - demonstration for WQVGA resolution */
	Riverdi_write_16(REG_HSIZE,   FT8_HSIZE);	/* active display width */
	Riverdi_write_16(REG_HCYCLE,  FT8_HCYCLE);	/* total number of clocks per line, incl front/back porch */
	Riverdi_write_16(REG_HOFFSET, FT8_HOFFSET);	/* start of active line */
	Riverdi_write_16(REG_HSYNC0,  FT8_HSYNC0);	/* start of horizontal sync pulse */
	Riverdi_write_16(REG_HSYNC1,  FT8_HSYNC1);	/* end of horizontal sync pulse */
	Riverdi_write_16(REG_VSIZE,   FT8_VSIZE);	/* active display height */
	Riverdi_write_16(REG_VCYCLE,  FT8_VCYCLE);	/* total number of lines per screen, incl pre/post */
	Riverdi_write_16(REG_VOFFSET, FT8_VOFFSET);	/* start of active screen */
	Riverdi_write_16(REG_VSYNC0,  FT8_VSYNC0);	/* start of vertical sync pulse */
	Riverdi_write_16(REG_VSYNC1,  FT8_VSYNC1);	/* end of vertical sync pulse */
	Riverdi_write_8(REG_SWIZZLE,  FT8_SWIZZLE);	/* FT8xx output to LCD - pin order */
	Riverdi_write_8(REG_PCLK_POL, FT8_PCLKPOL);	/* LCD data is clocked in on this PCLK edge */
	Riverdi_write_8(REG_CSPREAD,	FT8_CSPREAD); // check value
	/*Initialize interrupts*/
	Riverdi_write_8(REG_INT_EN,GLOBAL_INTERRUPT_ENABLE);
	Riverdi_write_8(REG_INT_MASK,TOUCH_DETECTED_MASK);
	
	/* write first display list */
	Riverdi_write_32(FT8_RAM_DL+0,CLEAR_COLOR_RGB(0,0,0));
	Riverdi_write_32(FT8_RAM_DL+4,CLEAR(1,1,1));
	Riverdi_write_32(FT8_RAM_DL+8,DISPLAY());
	Riverdi_write_8(REG_DLSWAP,FT8_DLSWAP_FRAME);//display list swap
	Riverdi_write_8(REG_GPIO_DIR,0x80 | Riverdi_read_8(REG_GPIO_DIR));
	Riverdi_write_8(REG_GPIO,0x080 | Riverdi_read_8(REG_GPIO));//enable display bit
	Riverdi_write_8(REG_PCLK,5);//after this display is visible on the LCD
	/* touch init */
	/*
	Riverdi_write_32(REG_TOUCH_TRANSFORM_A, )//missing data 
	Riverdi_write_32(REG_TOUCH_TRANSFORM_B, )
	Riverdi_write_32(REG_TOUCH_TRANSFORM_C, )
	Riverdi_write_32(REG_TOUCH_TRANSFORM_D, )
	Riverdi_write_32(REG_TOUCH_TRANSFORM_E, )
	Riverdi_write_32(REG_TOUCH_TRANSFORM_F, )*/
	//Riverdi_write_32(REG_TOUCH_CONFIG,0x8381 ) if touch is not accurate , disable low power mode (bit 11 ) 
	
//Riverdi_write_16(REG_TOUCH_RZTHRESH,1200L ) to change touch sensitivity 
//Riverdi_write_8(REG_TOUCH_OVERSAMPLE , ) to change oversampling factor ( power consumption)
//Riverdi_write_8(REG_TOUCH_SETTLE , ) settling time for the screen ( default 18L)
//Riverdi_Write _16(REG_TOUCH_CHARGE, ) default 6*6000
//Riverdi_write_8(REG_TOUCH_MODE, ) sampling mode, default set to continuous (00)	
		
	
}
void Riverdi_test_logo(void){
	Riverdi_cmd(CMD_LOGO);
	delay_ms(3000);

}
void Riverdi_cmd(uint32_t command)
{
	uint32_t ftAddress;
	//chip select low
	ftAddress = FT8_RAM_CMD + cmdOffset;
	spi_write((uint8_t)(ftAddress >> 16) | 0x80); /* send Memory Write plus high address byte */
	spi_write((uint8_t)(ftAddress >> 8));	/* send middle address byte */
	spi_write((uint8_t)(ftAddress));		/* send low address byte */
	spi_write((uint8_t)(command));		/* send data low byte */
	spi_write((uint8_t)(command >> 8));
	spi_write((uint8_t)(command >> 16));
	spi_write((uint8_t)(command >> 24));		/* Send data high byte */
	Riverdi_inc_cmdoffset(4);			/* update the command-ram pointer */
	//chip select high
}

void Riverdi_inc_cmdoffset(uint16_t increment)
{
	cmdOffset += increment;
	cmdOffset &= 0x0fff;
}

void Riverdi_host_command(uint8_t command){
	spi_write(command); //8-bit
	spi_write(0x00);//8-bit
	spi_write(0X00);//8-bit
}
