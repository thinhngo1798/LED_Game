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
static const unsigned I2C_ADDRESS = 0x20<<1;

I2c0 i2c{I2C_SPEED, I2cMode_Polled};

void writeRegister(RegAddress regAddress, uint8_t data)
{
	const uint8_t arraySent[] = {regAddress, data};
	i2c.startTransaction();
	i2c.transmit(I2C_ADDRESS, sizeof(arraySent), arraySent);
	i2c.endTransaction();
}

uint8_t readRegister(RegAddress regAddress)
{
	const uint8_t arrayTx[] = {regAddress};
	uint8_t arrayRx[1];
	i2c.startTransaction();
	i2c.txRx(I2C_ADDRESS, sizeof(arrayTx), arrayTx, sizeof(arrayRx), arrayRx);
	i2c.endTransaction();
	return arrayRx[0];
}

void write(uint8_t data)
{
	writeRegister(RegAddress_OLAT, data);
}

void setDirection(uint8_t direction)
{
	writeRegister(RegAddress_IODIR, direction);
}

uint8_t read()
{
	return readRegister(RegAddress_GPIO);
}

void setPinDirection(uint8_t pinNumber)
{
	uint8_t directionValue = readRegister(RegAddress_IODIR);
	directionValue |= (1<<pinNumber);
	setDirection(directionValue);
}
