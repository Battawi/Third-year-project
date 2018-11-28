#include "spi_integration.h"


void Spi_master_init(void) {
	//enable clock (PMC)
	spi_enable_clock(SPI);
	//enable SPI
	spi_enable(SPI);
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

//activate the required chip select
//API takes the CS value (0, 1, 2) and returns void
void Spi_chipSelect (uint32_t cs_channel){
	
	spi_set_peripheral_chip_select_value(SPI, spi_get_pcs(cs_channel));
	spi_configure_cs_behavior(SPI, cs_channel, SPI_CS_RISE_NO_TX);
}


void Spi_deactivateAllChipSelects (void){
	SPI->SPI_MR &= (~SPI_MR_PCS_Msk);
	SPI->SPI_MR |= (0xF << 16);	
}

//set transfer size to 8 bits
//API takes the CS value (0,1,2) and returns void
void Spi_transferSize8Bits (uint32_t cs_channel){
	spi_set_bits_per_transfer(SPI, cs_channel, 8_BITS);
}

//set transfer size to 16 bits
//API takes the CS value (0, 1, 2) and returns void
void Spi_transferSize16Bits (uint32_t cs_channel){
	spi_set_bits_per_transfer(SPI, cs_channel, 16_BITS);
}

//configure the SPI clock by setting its polarity, phase, set the baud rate
//API takes the channel of the CS (0, 1, 2), the clock polarity, clock phase and the baudrate_divider .. it returns void
void Spi_clockConfiguration (uint32_t cs_channel, uint32_t polarity, uint32_t phase, uint8_t baudrate_divider ) {
	int8_t success;
	
	spi_set_clock_polarity(SPI, cs_channel, polarity);
	spi_set_clock_phase(SPI, cs_channel, phase);
	success = spi_set_baudrate_div(SPI, cs_channel, baudrate_divider);
	if (success == -1) {
		#warning "baudrate error in clock configuration"

	}
	else {}
}


// needs editing
/** void Spi_setDelays (uint32_t ul_value_before_edit, uint32_t dly_bcs, uint32_t cs_channel, uint8_t dly_bs, uint8_t dly_bct){
	
	//set delay between CS's
	//since we are dealing with just 1 CS, then we can initiate it only once .. change this if other CS's added 
	spi_set_delay_between_chip_select(SPI, dly_bcs);

	//set SPCK delay and the delay between transfers
	spi_set_transfer_delay(SPI, cs_channel, dly_bs, dly_bct);
} **/


