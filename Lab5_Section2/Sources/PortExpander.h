/*
 * PortExpander.h
 *
 *  Created on: Oct 19, 2019
 *      Author: PLH
 */

#ifndef SOURCES_PORTEXPANDER_H_
#define SOURCES_PORTEXPANDER_H_

//1: transmit (output)
//0: receive (input)

//Input/Output Direction

enum RegAddress {
	RegAddress_IODIR = 0x00,
	RegAddress_GPIO = 0x09,
	RegAddress_OLAT = 0x0A
};

void writeRegister(RegAddress regAddress, uint8_t data);

uint8_t readRegister(RegAddress regAddress);

void setDirection(uint8_t direction);

//think about adding function to setting individual bit/clear bit

uint8_t read();

void write(uint8_t direction);

#endif /* SOURCES_PORTEXPANDER_H_ */
