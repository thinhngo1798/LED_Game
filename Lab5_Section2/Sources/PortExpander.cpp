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

/**
 * transmit the data to write the regAddress register
 * @param regAddress :
 * @param data :
 */
void writeRegister(RegAddress regAddress, uint8_t data)
{
	const uint8_t arraySent[] = {regAddress, data};
	i2c.startTransaction();
	i2c.transmit(I2C_ADDRESS, sizeof(arraySent), arraySent);
	i2c.endTransaction();
}

/**
 * Read the value on the given regAddress register
 * @param regAddress :
 * @return the 8-bit value on the regAddress
 */
uint8_t readRegister(RegAddress regAddress)
{
	const uint8_t arrayTx[] = {regAddress};
	uint8_t arrayRx[1];
	i2c.startTransaction();
	i2c.txRx(I2C_ADDRESS, sizeof(arrayTx), arrayTx, sizeof(arrayRx), arrayRx);
	i2c.endTransaction();
	return arrayRx[0];
}

/**
 * Set pins which are outputs to be high or low.
 * @param data : 8 bit number, bit 1 for high, bit 0 for output.
 */
void write(uint8_t data)
{
	writeRegister(RegAddress_OLAT, data);
}

/**
 * Set direction in the input/output for the GPIO
 * @param direction: 8 bit number, bit 1 for input, bit 0 for output.
 */
void setDirection(uint8_t direction)
{
	writeRegister(RegAddress_IODIR, direction);
}

/**
 * Read the actual value in the port pins GPIO.
 * @return 8-bit value - bit 1 for high, bit 0 for low.
 */
uint8_t read()
{
	return readRegister(RegAddress_GPIO);
}

/**
 * Set the direction of a single pin.
 * @param pinNumber the order of the pin (0 ... 7)
 */
void setPinDirection(uint8_t pinNumber)
{
	uint8_t directionValue = readRegister(RegAddress_IODIR);
	directionValue |= (1<<pinNumber);
	setDirection(directionValue);
}

/**
 * Set the direction of a single pin.
 * @param pinNumber the order of the pin (0 ... 7)
 */
void setPinDirection(uint8_t pinNumber, uint8_t isInput)
{
	uint8_t directionValue = readRegister(RegAddress_IODIR);
	if (isInput) {
		directionValue |= (1<<pinNumber);
	}
	else
	{
		directionValue &= ~(1 << pinNumber);
	}
	setDirection(directionValue);
}
