//we need just 1 CS channel until now
#define CS_CHANNEL0		0

//if CLK_MODE_0 is defined for clock configuration in "main.c"
#ifdef CLK_MODE_0
#define POLARITY		0
#define PHASE			1
#endif

//sizes of the info. to be transmitted
#define 8_BITS			0
#define 16_BITS			8




//enable the SPI, reset, set to master mode, disable mode fault detect&loopback&peripheral select decode,
//enable fixed peripheral mode and set the delay between CS
void Spi_master_init(void);

//set the polarity and phase for the clock.
void Spi_clockConfiguration (uint32_t cs_channel, uint32_t polarity, uint32_t phase, uint8_t baudrate_divider);

//set the transfer size of the information
void Spi_transferSize8Bits (uint32_t cs_channel);
void Spi_transferSize16Bits (uint32_t cs_channel);

//set the delays of the SPI
void Spi_setDelays (uint32_t ul_value_before_edit, uint32_t dly_bcs, uint32_t cs_channel, uint8_t dly_bs, uint8_t dly_bct);


void Spi_master_init() {
	//enable clock (PMC)
	spi_enable_clock(SPI);
	//reset SPI SW (will set it in slave mode)
	spi_reset(SPI);
	//set to master mode
	spi_set_master_mode(SPI);
	//disable mode fault detect& loopback
	spi_disable_mode_fault_detect(SPI);
	spi_disable_loopback(SPI);
															// this API will be used each time the spi reads or writes
															/**spi_set_peripheral_chip_select_value(SPI,
																spi_get_pcs(DEFAULT_CHIP_ID));**/
	//enable fixed peripheral mode and disable the peripheral select decoder.												
	spi_set_fixed_peripheral_select(SPI);
	spi_disable_peripheral_select_decode(SPI);
}

void Spi_transferSize8Bits (uint32_t cs_channel){
	spi_set_bits_per_transfer(SPI, cs_channel, 8_BITS);
}

void Spi_transferSize16Bits (uint32_t cs_channel){
	spi_set_bits_per_transfer(SPI, cs_channel, 16_BITS);
}


void Spi_clockConfiguration (uint32_t cs_channel, uint32_t polarity, uint32_t phase, uint8_t baudrate_divider ) {
	int8_t success;
	
	spi_set_clock_polarity(SPI, cs_channel, polarity);
	spi_set_clock_phase(SPI, cs_channel, phase);
	success = spi_set_baudrate_div(SPI, cs_channel, baudrate_divider);
	if (success == -1) {
		#error "baudrate error in clock configuration"
	}
	else {}
}

void Spi_setDelays (uint32_t ul_value_before_edit, uint32_t dly_bcs, uint32_t cs_channel, uint8_t dly_bs, uint8_t dly_bct){
	
	//set delay between CS's
	//since we are dealing with just 1 CS, then we can initiate it only once .. change this if other CS's added 
	spi_set_delay_between_chip_select(SPI, dly_bcs);

	//set SPCK delay and the delay between transfers
	spi_set_transfer_delay(SPI, cs_channel, dly_bs, dly_bct);
}




//kda fadel elly f el spi.h
