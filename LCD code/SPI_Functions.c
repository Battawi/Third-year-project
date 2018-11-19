#define CS0 0 //define the CS0 to be replaced in code with 0


//write 16 bits to Riverdi, start with sending address from MCU to TFT and then send data
void Riverdi_write_16(uint32_t address,uint16_t data){
	spi_write(SPI, (uint16_t)(address >> 16) | MEM_WRITE, spi_get_pcs(CS0), 0); //need to configure PCS,LASTXFER for fixed mode
	spi_write(SPI, (uint16_t)(address), spi_get_pcs(CS0), 0); //as above
	spi_write(SPI, data, spi_get_pcs(CS0), 1); //as above
}
//---------------------------------------------------
void Riverdi_write_32(uint32_t address,uint32_t data){
	spi_write(SPI,(uint16_t)(address >> 16) | MEM_WRITE,SPI_CHIP_PCS,0); //lesa htt3del
	spi_write(SPI,(uint16_t)(address),SPI_CHIP_PCS,0);
	spi_write(SPI,(uint16_t) (data),SPI_CHIP_PCS,0);
	spi_write(SPI,(uint16_t)(data>> 16) | MEM_WRITE,SPI_CHIP_PCS,1);
	

}
//-----------------------------------------------------
void Riverdi_write_8(uint32_t address,uint8_t data){
	spi_write(SPI,(uint16_t)(address >> 16) | MEM_WRITE); //lesa htt3del
	spi_write(SPI,(uint16_t)(address),SPI_CHIP_PCS,0);
	spi_write(SPI,data,SPI_CHIP_PCS,1);//8-bit
}
//-----------------------------------------------------




void Riverdi_command(uint8_t command){
	spi_write(SPI,command,SPI_CHIP_PCS,0); //8-bit
	spi_write(SPI,0x00,SPI_CHIP_PCS,0);//8-bit
	spi_write(SPI,0X00,SPI_CHIP_PCS,0);//8-bit
}
