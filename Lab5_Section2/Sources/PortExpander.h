/*
 * PortExpander.h
 *
 *  Created on: Oct 19, 2019
 *      Author: PLH
 */

#ifndef SOURCES_PORTEXPANDER_H_
#define SOURCES_PORTEXPANDER_H_

#include "i2c.h"

enum RegAddress
{
	RegAddress_IODIR = 0x00,
	RegAddress_GPIO = 0x09,
	RegAddress_OLAT = 0x0A
};

void writeRegister(RegAddress regAddress, uint8_t data);

uint8_t readRegister(RegAddress regAddress);

void setDirection(uint8_t direction);

uint8_t read();

void write(uint8_t direction);

void setPinDirection(uint8_t pinNumber, uint8_t isInput);
#endif /* SOURCES_PORTEXPANDER_H_ */
