//we need just 1 CS channel until now
#define CS_CHANNEL0		0			//for TFT
#define CS_CHANNEL1		1			//for NodeMCU ,, not needed

//if CLK_MODE_0 is defined for clock configuration in "main.c"
#ifdef CLK_MODE_0
#define POLARITY		0
#define PHASE			1
#endif

//required delay sets
#define DLYBCT 1 //for a clock = 11 Mhz
#define DLYBS 1 //for a clock = 11 Mhz

//sizes of the info. to be transmitted
#define 8_BITS			0
#define 16_BITS			8


void Spi_chipSelect (uint32_t cs_channel);
void Spi_deactivateAllChipSelects (void);

//enable the SPI, reset, set to master mode, disable mode fault detect&loopback&peripheral select decode,
//enable fixed peripheral mode and set the delay between CS
void Spi_master_init(void);

//set the polarity and phase for the clock.
void Spi_clockConfiguration (uint32_t cs_channel, uint32_t polarity, uint32_t phase, uint8_t baudrate_divider);

//set the transfer size of the information
void Spi_transferSize8Bits (uint32_t cs_channel);
void Spi_transferSize16Bits (uint32_t cs_channel);

//set the delays of the SPI
//void Spi_setDelays (uint32_t ul_value_before_edit, uint32_t dly_bcs, uint32_t cs_channel, uint8_t dly_bs, uint8_t dly_bct);



/** for the main code:
	1- call Spi_master_init();
	2- call pmc_pck_set_prescaler(ID_SPI, PMC_PCK_PRES_CLK_2); //now the spi clock is 10 Mhz
	3- call Spi_clockConfiguration (0, POLARITY, PHASE, ...);
	4- call spi_set_transfer_delay (SPI, 0, DLYBS, DLYBCT);
	5- call Spi_chipSelect(0);
	6- call Spi_transferSize8(16)Bits(0);
	7- call int x = spi_read (SPI);
		or spi_write (SPI, data to be transmitted, if its last transfer enter 1 and if not enter 0); 
		if you want to read just 1 block of data : spi_get(SPI);
		if you want to write just 1 block of data : spi_put (SPI, data to be transmitted);
		
	8- after TFT initialization call : pmc_pck_set_prescaler(ID_SPI, PMC_PCK_PRES_CLK_1); //now the spi clock is 20 Mhz
	9- if you want to deactivate all CS's call : Spi_deactivateAllChipSelects();
**/
		
