/**
 * \file
 *
 * \brief Serial Peripheral Interface (SPI) driver for SAM.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "spi.h"
#include "sysclk.h"

/**
 * \defgroup sam_drivers_spi_group Serial Peripheral Interface (SPI)
 *
 * See \ref sam_spi_quickstart.
 *
 * The SPI circuit is a synchronous serial data link that provides communication
 * with external devices in Master or Slave mode. Connection to Peripheral DMA
 * Controller channel capabilities optimizes data transfers.
 *
 * @{
 */
#ifndef SPI_WPMR_WPKEY_PASSWD
#define SPI_WPMR_WPKEY_PASSWD SPI_WPMR_WPKEY((uint32_t) 0x535049)
#endif

/** YES
 * \brief Enable SPI clock.
 *
 * \param p_spi Pointer to an SPI instance.
 */
void spi_enable_clock(Spi *p_spi)
{
#if (SAM4S || SAM3S || SAM3N || SAM3U || SAM4E || SAM4N || SAMG51|| SAMG53|| SAMG54)
	UNUSED(p_spi);
	sysclk_enable_peripheral_clock(ID_SPI);
#elif (SAM3XA || SAM4C || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
	if (p_spi == SPI0) {
		sysclk_enable_peripheral_clock(ID_SPI0);
	}
	#ifdef SPI1
	else if (p_spi == SPI1) {
		sysclk_enable_peripheral_clock(ID_SPI1);
	}
	#endif
#elif (SAMG55)
	if (p_spi == SPI0) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM0);
	}
	#ifdef SPI1
	else if (p_spi == SPI1) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM1);
	}
	#endif
	#ifdef SPI2
	else if (p_spi == SPI2) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM2);
	}
	#endif
	#ifdef SPI3
	else if (p_spi == SPI3) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM3);
	}
	#endif
	#ifdef SPI4
	else if (p_spi == SPI4) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM4);
	}
	#endif
	#ifdef SPI5
	else if (p_spi == SPI5) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM5);
	}
	#endif
	#ifdef SPI6
	else if (p_spi == SPI6) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM6);
	}
	#endif
	#ifdef SPI7
	else if (p_spi == SPI7) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM7);
	}
	#endif
#elif SAM4L
	sysclk_enable_peripheral_clock(p_spi);
#endif
}

/**
 * \brief Disable SPI clock.
 *
 * \param p_spi Pointer to an SPI instance.
 */
void spi_disable_clock(Spi *p_spi)
{
#if (SAM4S || SAM3S || SAM3N || SAM3U || SAM4E || SAM4N || SAMG51|| SAMG53|| SAMG54)
	UNUSED(p_spi);
	sysclk_disable_peripheral_clock(ID_SPI);
#elif (SAM3XA || SAM4C || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
	if (p_spi == SPI0) {
		sysclk_disable_peripheral_clock(ID_SPI0);
	}
	#ifdef SPI1
	else if (p_spi == SPI1) {
		sysclk_disable_peripheral_clock(ID_SPI1);
	}
	#endif
#elif (SAMG55)
	if (p_spi == SPI0) {
		sysclk_disable_peripheral_clock(ID_FLEXCOM0);
	}
	#ifdef SPI1
	else if (p_spi == SPI1) {
		sysclk_disable_peripheral_clock(ID_FLEXCOM1);
	}
	#endif
	#ifdef SPI2
		else if (p_spi == SPI2) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM2);
		}
	#endif
	#ifdef SPI3
		else if (p_spi == SPI3) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM3);
		}
	#endif
	#ifdef SPI4
		else if (p_spi == SPI4) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM4);
		}
	#endif
	#ifdef SPI5
		else if (p_spi == SPI5) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM5);
		}
	#endif
	#ifdef SPI6
		else if (p_spi == SPI6) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM6);
		}
	#endif
	#ifdef SPI7
		else if (p_spi == SPI7) {
			sysclk_disable_peripheral_clock(ID_FLEXCOM7);
		}
	#endif
#elif SAM4L
	sysclk_disable_peripheral_clock(p_spi);
#endif
}

/** YES, before each read
 * \brief Set Peripheral Chip Select (PCS) value.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_value Peripheral Chip Select value.
 *                 If PCS decode mode is not used, use \ref spi_get_pcs to build
 *                 the value to use.
 *                 On reset the decode mode is not enabled.
 *                 The decode mode can be enabled/disabled by follow functions:
 *                 \ref spi_enable_peripheral_select_decode,
 *                 \ref spi_disable_peripheral_select_decode.
 */
void spi_set_peripheral_chip_select_value(Spi *p_spi, uint32_t ul_value)
{
	p_spi->SPI_MR &= (~SPI_MR_PCS_Msk);
	p_spi->SPI_MR |= SPI_MR_PCS(ul_value);
}

/** YES
 * \brief Set delay between chip selects (in number of MCK clocks).
 *  If DLYBCS <= 6, 6 MCK clocks will be inserted by default.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_delay Delay between chip selects (in number of MCK clocks).
 */
void spi_set_delay_between_chip_select(Spi *p_spi, uint32_t ul_delay)
{
	p_spi->SPI_MR &= (~SPI_MR_DLYBCS_Msk);
	p_spi->SPI_MR |= SPI_MR_DLYBCS(ul_delay);
}

/** YES
 * \brief Read the received data and it's peripheral chip select value.
 * While SPI works in fixed peripheral select mode, the peripheral chip select
 * value is meaningless.
 *
 * \param p_spi Pointer to an SPI instance.
 *
 * \retval the information to read
 * 
 */
uint32_t spi_read(Spi *p_spi)
{
	uint32_t timeout = SPI_TIMEOUT;
	static uint32_t reg_value;
	
	//if the RDR is full, wait for it to be read first
//	while (spi_is_rx_full(SPI));

	while (!(p_spi->SPI_SR & SPI_SR_RDRF)) {
		if (!timeout--) {
			return SPI_ERROR_TIMEOUT;
		}
	}
	
	
	
	//assign the value of the RDR to the variable "reg_value"
	reg_value = p_spi->SPI_RDR;
	
	
	return reg_value;
}

/** YES
 * \brief Write the transmitted data with specified peripheral chip select value.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param us_data The data to transmit.
 * .. da etshal .. yb2a lazm nkoon 3arfeen el CS 2bl ma n call el function. \param uc_pcs Peripheral Chip Select Value while SPI works in peripheral select
 * mode, otherwise it's meaningless.
 * \param uc_last Indicate whether this data is the last one while SPI is working
 * in variable peripheral select mode.
 *
 * \retval SPI_OK on Success.
 * \retval SPI_ERROR_TIMEOUT on Time-out.
 */
spi_status_t spi_write(Spi *p_spi, uint16_t us_data, uint8_t uc_last)
{
	uint32_t timeout = SPI_TIMEOUT;
	uint32_t value;

	//loop 15000 times, if after all this the TDR isn't loaded, then there is an error and the function terminates
	while (!(p_spi->SPI_SR & SPI_SR_TDRE)) {
		if (!timeout--) {
			return SPI_ERROR_TIMEOUT;
			}
		}

	//edited .. for the use of the fixed peripheral only .. risk 1 --> LASRXFER is written in CR not in TDR .. risk 2 --> LASTXFER is written after the last data transfer not before it (eldatasheet 2ayla kda w el ASF 2ayel 3ks kda)	
	
	//assign the us_data to the variable named "value"
	value = SPI_TDR_TD(us_data);
	//copy the value to the SPI_TDR to start transmitting the information
	p_spi->SPI_TDR = value;
	
	//no new transfer until the current one is complete
	//while (!(spi_is_tx_ready(SPI)));
	
	
	//if last transfer .. set the LASTXFER bit in the CR
	if (uc_last){
		
	//code stucks until all transfers all complete and the TDR is empty
	while (!(spi_is_tx_empty(SPI)));
	
	spi_set_lastxfer(SPI);
	}
	
	//if not .. do nothing and the current CS is still activated
	else {}
		
	return SPI_OK;
}

/** YES
 * \brief Set clock default state.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 * \param ul_polarity Default clock state is logical one(high)/zero(low).
 */
void spi_set_clock_polarity(Spi *p_spi, uint32_t ul_pcs_ch,
		uint32_t ul_polarity)
{
	if (ul_polarity) {
		p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_CPOL;
	} else {
		p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_CPOL);
	}
}

/** YES
 * \brief Set Data Capture Phase.
 *
 * \param p_spi Pointer to an SPI instance.
 *  \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 *  \param ul_phase Data capture on the rising/falling edge of clock.
 */
void spi_set_clock_phase(Spi *p_spi, uint32_t ul_pcs_ch, uint32_t ul_phase)
{
	if (ul_phase) {
		p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_NCPHA;
	} else {
		p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_NCPHA);
	}
}

/** YES
 * \brief Configure CS behavior for SPI transfer (\ref spi_cs_behavior_t).
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 * \param ul_cs_behavior Behavior of the Chip Select after transfer.
 */
void spi_configure_cs_behavior(Spi *p_spi, uint32_t ul_pcs_ch,
		uint32_t ul_cs_behavior)
{
	if (ul_cs_behavior == SPI_CS_RISE_FORCED) {
		p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_CSAAT);
		p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_CSNAAT;
	} else if (ul_cs_behavior == SPI_CS_RISE_NO_TX) {
		p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_CSAAT);
		p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_CSNAAT);
	} else if (ul_cs_behavior == SPI_CS_KEEP_LOW) {
		p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_CSAAT;
	}
}

/** YES
 * \brief Set number of bits per transfer.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 * \param ul_bits Number of bits (8~16), use the pattern defined
 *        in the device header file.
 */
void spi_set_bits_per_transfer(Spi *p_spi, uint32_t ul_pcs_ch,
		uint32_t ul_bits)
{
	p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_BITS_Msk);
	p_spi->SPI_CSR[ul_pcs_ch] |= ul_bits;
}

/** 
 * \brief Calculate the baudrate divider.
 *
 * \param baudrate Baudrate value.
 * \param mck      SPI module input clock frequency (MCK clock, Hz).
 *
 * \return Divider or error code.
 *   \retval > 0  Success.
 *   \retval < 0  Error.
 */
int16_t spi_calc_baudrate_div(const uint32_t baudrate, uint32_t mck)
{
	int baud_div = div_ceil(mck, baudrate);

	/* The value of baud_div is from 1 to 255 in the SCBR field. */
	if (baud_div <= 0 || baud_div > 255) {
		return -1;
	}

	return baud_div;
}

/** YES
 * \brief Set Serial Clock Baud Rate divider value (SCBR).
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 * \param uc_baudrate_divider Baudrate divider from MCK.
 *
 * \return
 * \retval is 0 Success.
 * \retval is -1 Error.
 */
int16_t spi_set_baudrate_div(Spi *p_spi, uint32_t ul_pcs_ch,
		uint8_t uc_baudrate_divider)
{
    /* Programming the SCBR field to 0 is forbidden */
    if (!uc_baudrate_divider){
        return -1;
	}
	p_spi->SPI_CSR[ul_pcs_ch] &= (~SPI_CSR_SCBR_Msk);
	p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_SCBR(uc_baudrate_divider);
    return 0;
}

/** yes
 * \brief Configure timing for SPI transfer.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_pcs_ch Peripheral Chip Select channel (0~3).
 * \param uc_dlybs Delay before SPCK (in number of MCK clocks).
 * \param uc_dlybct Delay between consecutive transfers (in number of MCK clocks).
 */
void spi_set_transfer_delay(Spi *p_spi, uint32_t ul_pcs_ch,
		uint8_t uc_dlybs, uint8_t uc_dlybct)
{
	p_spi->SPI_CSR[ul_pcs_ch] &= ~(SPI_CSR_DLYBS_Msk | SPI_CSR_DLYBCT_Msk);
	p_spi->SPI_CSR[ul_pcs_ch] |= SPI_CSR_DLYBS(uc_dlybs)
			| SPI_CSR_DLYBCT(uc_dlybct);
}


/** YES
 * \brief Enable or disable write protection of SPI registers.
 *
 * \param p_spi Pointer to an SPI instance.
 * \param ul_enable 1 to enable, 0 to disable.
 */
void spi_set_writeprotect(Spi *p_spi, uint32_t ul_enable)
{
#if SAM4L
	if (ul_enable) {
		p_spi->SPI_WPCR = SPI_WPCR_SPIWPKEY_VALUE | SPI_WPCR_SPIWPEN;
	} else {
		p_spi->SPI_WPCR = SPI_WPCR_SPIWPKEY_VALUE;
	}
#else
	if (ul_enable) {
		p_spi->SPI_WPMR = SPI_WPMR_WPKEY_PASSWD | SPI_WPMR_WPEN;
	} else {
		p_spi->SPI_WPMR = SPI_WPMR_WPKEY_PASSWD;
	}
#endif
}

/**
 * \brief Indicate write protect status.
 *
 * \param p_spi Pointer to an SPI instance.
 *
 * \return SPI_WPSR value.
 */
uint32_t spi_get_writeprotect_status(Spi *p_spi)
{
	return p_spi->SPI_WPSR;
}

/**
 * @}
 */
