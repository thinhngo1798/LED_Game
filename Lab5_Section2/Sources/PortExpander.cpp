/*
 * PortExpander.cpp
 *
 *  Created on: Oct 25, 2019
 *      Author: PLH
 */

#include "i2c.h"

#include "PortExpander.h"

using namespace USBDM;

	 static const unsigned I2C_SPEED   = 400*kHz;

static const unsigned I2C_ADDRESS = 0x1D<<1;


I2c0 i2c{I2C_SPEED, I2cMode_Polled};


void writeRegister(RegAddress regAddress, uint8_t data)
{
	uint8_t arraySent[] = {regAddress, data};
	i2c.startTransaction();
	i2c.transmit(I2C_ADDRESS, sizeof(arraySent), arraySent);
	i2c.endTransaction();
}

uint8_t readRegister(RegAddress regAddress)
{
	uint8_t arrayTx[] = {regAddress};
	uint8_t arrayRx[2];
	i2c.startTransaction();
	i2c.txRx(I2C_ADDRESS, sizeof(arrayTx), arrayTx, sizeof(arrayRx), arrayRx);
	i2c.endTransaction();
	return arrayRx[0];
}
/**
 * Transmitting data through ports by using OLAT Register address
 *
 * @param[in] unsigned integer 8-bit data
 *
 */
void write(uint8_t data)
{
	writeRegister(RegAddress_OLAT, data);
}
/**
 * Setting direction for ports.
 * @param[in] The direction of the 8 GPIO Port
 *
 * @Note
 */
void setDirection(uint8_t direction)
{
	writeRegister(RegAddress_IODIR, direction);
}
/**
 * Receiving data through ports by using GPIO Register address
 *
 * @param[in] None
 *
 */
uint8_t read()
{
	return readRegister(RegAddress_GPIO);
}

