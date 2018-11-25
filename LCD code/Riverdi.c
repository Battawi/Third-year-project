/*
 * Riverdi.c
 *
 * Created: 01/11/2018 16:31:52
 *  Author: Abdulrahman
 * Edited : 24/11/2018 by Gamal
 *  Added widget commands addresses and functions---
 *  Added command transaction functions
 */ 

#include "Riverdi.h"

#define SPI_ID            ID_SPI
#define SPI_MASTER_BASE     SPI
#define SPI_MISO_GPIO  (PIO_PA12_IDX)
#define SPI_MISO_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_MOSI_GPIO  (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_SPCK_GPIO  (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS0_GPIO            (PIO_PA11_IDX)
#define SPI_NPCS1_GPIO            (PIO_PA31_IDX)
#define SPI_NPCS1_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_CHIP_SEL 0    //Use SPI Chip Select 0 (SPI_NPCS0_GPIO) for CS
#define SPI_CHIP_PCS spi_get_pcs(SPI_CHIP_SEL)

void Riverdi_init(void){
	ioport_set_pin_level(POWER_PIN,HIGH);
	delay_ms(6);
	ioport_set_pin_level(POWER_PIN,LOW);
	delay_ms(21);
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
	
	/* write first display list */
	Riverdi_write_32(RAM_DL+0,CLEAR_COLOR_RGB(0,0,0));
	Riverdi_write_32(RAM_DL+4,CLEAR(1,1,1));
	Riverdi_write_32(RAM_DL+8,DISPLAY());
	Riverdi_write_8(REG_DLSWAP,FT8_DLSWAP_FRAME);//display list swap
	Riverdi_write_8(REG_GPIO_DIR,0x80 | Riverdi_read_8(REG_GPIO_DIR));
	Riverdi_write_8(REG_GPIO,0x080 | Riverdi_read_8(REG_GPIO));//enable display bit
	Riverdi_write_8(REG_PCLK,5);//after this display is visible on the LCD
	
	
	
	
		
	
}

void Riverdi_write_16(uint32_t address,uint16_t data){
	spi_write(SPI,(uint16_t)(address >> 16) | MEM_WRITE,SPI_CHIP_PCS,0); //lesa htt3del
	spi_write(SPI,(uint16_t)(address),SPI_CHIP_PCS,0);
	spi_write(SPI,data,SPI_CHIP_PCS,1);
}
//---------------------------------------------------
void Riverdi_write_32(uint32_t address,uint32_t data){
	spi_write(SPI,(uint16_t)(address >> 16) | MExM_WRITE,SPI_CHIP_PCS,0); //lesa htt3del
	spi_write(SPI,(uint16_t)(address),SPI_CHIP_PCS,0);
	spi_write(SPI,(uint16_t) (data),SPI_CHIP_PCS,0);
	spi_write(SPI,(uint16_t)(data>> 16) | MEM_WRITE,SPI_CHIP_PCS,1);
	

}
//-----------------------------------------------------
void Riverdi_write_8(uint32_t address,uint8_t data){
	spi_write(SPI,(uint16_t)(address >> 16) | MEM_WRITE,0,0); //lesa htt3del
	spi_write(SPI,(uint16_t)(address),SPI_CHIP_PCS,0);
	spi_write(SPI,data,SPI_CHIP_PCS,1);//8-bit
}
//-----------------------------------------------------




void Riverdi_host_command(uint8_t command){
	spi_write(SPI,command,SPI_CHIP_PCS,0); //8-bit
	spi_write(SPI,0x00,SPI_CHIP_PCS,0);//8-bit
	spi_write(SPI,0X00,SPI_CHIP_PCS,0);//8-bit
}


uint8_t Riverdi_read_8(uint32_t address){
	uint8_t Data8 = 0;
	spi_write(SPI,(uint8_t)(address >> 16) | MEM_READ,0,0);	/* send Memory Write plus high address byte */
	spi_write(SPI,(uint8_t)(address >> 8),0,0);	/* send middle address byte */
	spi_write(SPI,(uint8_t)(address),0,0);	/* send low address byte */
	spi_write(SPI,0x00,0,0);	/* send dummy byte */
	Data8 = spi_read(SPI,Data8,0);	/* read data byte */
}


uint16_t Riverdi_read_16(uint32_t address){ //fix arguments of functions
	uint16_t Data16 = 0;
	spi_write(SPI,(uint8_t)(address >> 16) | MEM_READ,0,0);	/* send Memory Write plus high address byte */
	spi_write(SPI,(uint8_t)(address >> 8),0,0);	/* send middle address byte */
	spi_write(SPI,(uint8_t)(address),0,0);	/* send low address byte */
	spi_write(SPI,0x00,0,0);	/* send dummy byte */
	Data16 = spi_read(SPI,0x00,0);	/* read low byte */
	Data16 = spi_read(SPI,((0x00) << 8) | Data16,0);	/* read high byte */
	return Data16 ;
}

uint32_t Riverdi_read_32(uint32_t ftAddress)
{
	uint32_t ftData32= 0;	
	spi_write(SPI,(uint8_t)(ftAddress >> 16) | MEM_READ,0,0);	/* send Memory Write plus high address byte */
	spi_write(SPI,(uint8_t)(ftAddress >> 8),0,0);	/* send middle address byte */
	spi_write(SPI,(uint8_t)(ftAddress),0,0);	/* send low address byte */
	spi_write(SPI,0x00,0,0);	/* send dummy byte */
	ftData32 = spi_read(SPI,(uint32_t)(0x00),0);		/* read low byte */
	ftData32 = spi_read(SPI,(uint32_t)(0x00) << 8,0) | ftData32;
	ftData32 = spi_read(SPI,(uint32_t)(0x00) << 16,0) | ftData32;
	ftData32 = spi_read(SPI,(uint32_t)(0x00) << 24,0) | ftData32; /* read high byte */
	return ftData32;	/* return long read */
}
uint8_t Riverdi_busy(void)
{
	uint16_t cmdBufferRead;

	cmdBufferRead = R_read_16(REG_CMD_READ);	/* read the graphics processor read pointer */

	if(cmdBufferRead == 0xFFF)
	{
		FT8_memWrite8(REG_CPURESET, 1);		/* hold co-processor engine in the reset condition */
		FT8_memWrite16(REG_CMD_READ, 0);	/* set REG_CMD_READ to 0 */
		FT8_memWrite16(REG_CMD_WRITE, 0);	/* set REG_CMD_WRITE to 0 */
		cmdOffset = 0;						/* reset cmdOffset */
		FT8_memWrite8(REG_CPURESET, 0);		/* set REG_CMD_WRITE to 0 to restart the co-processor engine*/
	}

	if(cmdOffset != cmdBufferRead)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Riverdi_write_string(const char *text)
{
	uint8_t textindex = 0;
	uint8_t padding = 0;

	while(text[textindex] != 0)
	{
		spi_write(SPI,text[textindex]);
		textindex++;
	}

	padding = textindex % 4;  /* 0, 1, 2 oder 3 */
	padding = 4-padding; /* 4, 3, 2, 1 */

	while(padding > 0)
	{
		spi_write(SPI,0);
		padding--;
		textindex++;
	}

	Riverdi_inc_cmdoffset(textindex);
}
void Riverdi_cmd_text(int16_t x0, int16_t y0, int16_t font, uint16_t options, const char* text)
{
	Riverdi_start_cmd(CMD_TEXT);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(font));
	spi_write(SPI,(uint8_t)(font >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	Riverdi_inc_cmdoffset(8);
	Riverdi_write_string(text);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_button(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text)
{
	Riverdi_start_cmd(CMD_BUTTON);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(w0));
	spi_write(SPI,(uint8_t)(w0 >> 8));

	spi_write(SPI,(uint8_t)(h0));
	spi_write(SPI,(uint8_t)(h0 >> 8));

	spi_write(SPI,(uint8_t)(font));
	spi_write(SPI,(uint8_t)(font >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	Riverdi_inc_cmdoffset(12);
	Riverdi_write_string(text);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


/* draw a clock */
void Riverdi_cmd_clock(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t hours, uint16_t minutes, uint16_t seconds, uint16_t millisecs)
{
	Riverdi_start_cmd(CMD_CLOCK);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(r0));
	spi_write(SPI,(uint8_t)(r0 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(hours));
	spi_write(SPI,(uint8_t)(hours >> 8));

	spi_write(SPI,(uint8_t)(minutes));
	spi_write(SPI,(uint8_t)(minutes >> 8));

	spi_write(SPI,(uint8_t)(seconds));
	spi_write(SPI,(uint8_t)(seconds >> 8));

	spi_write(SPI,(uint8_t)(millisecs));
	spi_write(SPI,(uint8_t)(millisecs >> 8));

	Riverdi_inc_cmdoffset(16);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_bgcolor(uint32_t color)
{
	Riverdi_start_cmd(CMD_BGCOLOR);

	spi_write(SPI,(uint8_t)(color));
	spi_write(SPI,(uint8_t)(color >> 8));
	spi_write(SPI,(uint8_t)(color >> 16));
	spi_write(SPI,0x00);

	Riverdi_inc_cmdoffset(4);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_fgcolor(uint32_t color)
{
	Riverdi_start_cmd(CMD_FGCOLOR);

	spi_write(SPI,(uint8_t)(color));
	spi_write(SPI,(uint8_t)(color >> 8));
	spi_write(SPI,(uint8_t)(color >> 16));
	spi_write(SPI,0x00);

	Riverdi_inc_cmdoffset(4);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_gradcolor(uint32_t color)
{
	Riverdi_start_cmd(CMD_GRADCOLOR);

	spi_write(SPI,(uint8_t)(color));
	spi_write(SPI,(uint8_t)(color >> 8));
	spi_write(SPI,(uint8_t)(color >> 16));
	spi_write(SPI,0x00);

	Riverdi_inc_cmdoffset(4);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_gauge(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range)
{
	Riverdi_start_cmd(CMD_GAUGE);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(r0));
	spi_write(SPI,(uint8_t)(r0 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(major));
	spi_write(SPI,(uint8_t)(major >> 8));

	spi_write(SPI,(uint8_t)(minor));
	spi_write(SPI,(uint8_t)(minor >> 8));

	spi_write(SPI,(uint8_t)(val));
	spi_write(SPI,(uint8_t)(val >> 8));

	spi_write(SPI,(uint8_t)(range));
	spi_write(SPI,(uint8_t)(range >> 8));

	Riverdi_inc_cmdoffset(16);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1)
{
	Riverdi_start_cmd(CMD_GRADIENT);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(rgb0));
	spi_write(SPI,(uint8_t)(rgb0 >> 8));
	spi_write(SPI,(uint8_t)(rgb0 >> 16));
	spi_write(SPI,0x00);

	spi_write(SPI,(uint8_t)(x1));
	spi_write(SPI,(uint8_t)(x1 >> 8));

	spi_write(SPI,(uint8_t)(y1));
	spi_write(SPI,(uint8_t)(y1 >> 8));

	spi_write(SPI,(uint8_t)(rgb1));
	spi_write(SPI,(uint8_t)(rgb1 >> 8));
	spi_write(SPI,(uint8_t)(rgb1 >> 16));
	spi_write(SPI,0x00);

	Riverdi_inc_cmdoffset(16);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_keys(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text)
{
	Riverdi_start_cmd(CMD_KEYS);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(w0));
	spi_write(SPI,(uint8_t)(w0 >> 8));

	spi_write(SPI,(uint8_t)(h0));
	spi_write(SPI,(uint8_t)(h0 >> 8));

	spi_write(SPI,(uint8_t)(font));
	spi_write(SPI,(uint8_t)(font >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	Riverdi_inc_cmdoffset(12);
	Riverdi_write_string(text);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_progress(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t range)
{
	Riverdi_start_cmd(CMD_PROGRESS);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(w0));
	spi_write(SPI,(uint8_t)(w0 >> 8));

	spi_write(SPI,(uint8_t)(h0));
	spi_write(SPI,(uint8_t)(h0 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(val));
	spi_write(SPI,(uint8_t)(val >> 8));

	spi_write(SPI,(uint8_t)(range));
	spi_write(SPI,(uint8_t)(range >> 8));

	spi_write(SPI,0x00);	/* dummy byte for 4-byte alignment */
	spi_write(SPI,0x00); /* dummy byte for 4-byte alignment */

	Riverdi_inc_cmdoffset(16);	/* update the command-ram pointer */

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_scrollbar(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t size, uint16_t range)
{
	Riverdi_start_cmd(CMD_SCROLLBAR);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(w0));
	spi_write(SPI,(uint8_t)(w0 >> 8));

	spi_write(SPI,(uint8_t)(h0));
	spi_write(SPI,(uint8_t)(h0 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(val));
	spi_write(SPI,(uint8_t)(val >> 8));

	spi_write(SPI,(uint8_t)(size));
	spi_write(SPI,(uint8_t)(size >> 8));

	spi_write(SPI,(uint8_t)(range));
	spi_write(SPI,(uint8_t)(range >> 8));

	Riverdi_inc_cmdoffset(16);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_slider(int16_t x1, int16_t y1, int16_t w1, int16_t h1, uint16_t options, uint16_t val, uint16_t range)
{
	Riverdi_start_cmd(CMD_SLIDER);

	spi_write(SPI,(uint8_t)(x1));
	spi_write(SPI,(uint8_t)(x1 >> 8));

	spi_write(SPI,(uint8_t)(y1));
	spi_write(SPI,(uint8_t)(y1 >> 8));

	spi_write(SPI,(uint8_t)(w1));
	spi_write(SPI,(uint8_t)(w1 >> 8));

	spi_write(SPI,(uint8_t)(h1));
	spi_write(SPI,(uint8_t)(h1 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(val));
	spi_write(SPI,(uint8_t)(val >> 8));

	spi_write(SPI,(uint8_t)(range));
	spi_write(SPI,(uint8_t)(range >> 8));

	spi_write(SPI,0x00); /* dummy byte for 4-byte alignment */
	spi_write(SPI,0x00); /* dummy byte for 4-byte alignment */

	Riverdi_inc_cmdoffset(16);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_dial(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t val)
{
	Riverdi_start_cmd(CMD_DIAL);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(r0));
	spi_write(SPI,(uint8_t)(r0 >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(val));
	spi_write(SPI,(uint8_t)(val >> 8));

	spi_write(SPI,0);
	spi_write(SPI,0);

	Riverdi_inc_cmdoffset(12);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}


void Riverdi_cmd_toggle(int16_t x0, int16_t y0, int16_t w0, int16_t font, uint16_t options, uint16_t state, const char* text)
{
	Riverdi_start_cmd(CMD_TOGGLE);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(w0));
	spi_write(SPI,(uint8_t)(w0 >> 8));

	spi_write(SPI,(uint8_t)(font));
	spi_write(SPI,(uint8_t)(font >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(state));
	spi_write(SPI,(uint8_t)(state >> 8));

	Riverdi_inc_cmdoffset(12);
	Riverdi_write_string(text);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}

void Riverdi_cmd_setbase(uint32_t base)
{
	Riverdi_start_cmd(CMD_SETBASE);

	spi_write(SPI,(uint8_t)(base));		/* send data low byte */
	spi_write(SPI,(uint8_t)(base >> 8));
	spi_write(SPI,(uint8_t)(base >> 16));
	spi_write(SPI,(uint8_t)(base >> 24));	/* send data high byte */

	Riverdi_inc_cmdoffset(4);	/* update the command-ram pointer */

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}

void Riverdi_cmd_setbitmap(uint32_t addr, uint16_t fmt, uint16_t width, uint16_t height)
{
	Riverdi_start_cmd(CMD_SETBITMAP);

	spi_write(SPI,(uint8_t)(addr));
	spi_write(SPI,(uint8_t)(addr >> 8));
	spi_write(SPI,(uint8_t)(addr >> 16));
	spi_write(SPI,(uint8_t)(addr >> 24));
	
	spi_write(SPI,(uint8_t)(fmt));
	spi_write(SPI,(uint8_t)(fmt>> 8));

	spi_write(SPI,(uint8_t)(width));
	spi_write(SPI,(uint8_t)(width >> 8));

	spi_write(SPI,(uint8_t)(height));
	spi_write(SPI,(uint8_t)(height >> 8));

	spi_write(SPI,0);
	spi_write(SPI,0);
	
	Riverdi_inc_cmdoffset(12);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}



void Riverdi_cmd_number(int16_t x0, int16_t y0, int16_t font, uint16_t options, int32_t number)
{
	Riverdi_start_cmd(CMD_NUMBER);

	spi_write(SPI,(uint8_t)(x0));
	spi_write(SPI,(uint8_t)(x0 >> 8));

	spi_write(SPI,(uint8_t)(y0));
	spi_write(SPI,(uint8_t)(y0 >> 8));

	spi_write(SPI,(uint8_t)(font));
	spi_write(SPI,(uint8_t)(font >> 8));

	spi_write(SPI,(uint8_t)(options));
	spi_write(SPI,(uint8_t)(options >> 8));

	spi_write(SPI,(uint8_t)(number));
	spi_write(SPI,(uint8_t)(number >> 8));
	spi_write(SPI,(uint8_t)(number >> 16));
	spi_write(SPI,(uint8_t)(number >> 24));

	Riverdi_inc_cmdoffset(12);

	if(cmd_burst == 0)
	{
		Riverdi_cs_clear();
	}
}

void Riverdi_start_cmd(uint32_t command)
	{
		uint32_t ftAddress;
		
		ftAddress = FT8_RAM_CMD + cmdOffset;
		spi_write(SPI,(uint8_t)(ftAddress >> 16) | MEM_WRITE); /* send Memory Write plus high address byte */
		spi_write(SPI,(uint8_t)(ftAddress >> 8));	/* send middle address byte */
		spi_write(SPI,(uint8_t)(ftAddress));		/* send low address byte */
		spi_write(SPI,(uint8_t)(command));		/* send data low byte */
		spi_write(SPI,(uint8_t)(command >> 8));
		spi_write(SPI,(uint8_t)(command >> 16));
		spi_write(SPI,(uint8_t)(command >> 24));		/* Send data high byte */
		Riverdi_inc_cmdoffset(4);			/* update the command-ram pointer */
	}

void Riverdi_inc_cmdoffset(uint16_t increment)
{
	cmdOffset += increment;
	cmdOffset &= 0x0fff;
}
