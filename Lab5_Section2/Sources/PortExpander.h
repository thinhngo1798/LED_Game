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
	RegAddress_IODIR = 0x00<<1,
	RegAddress_GPIO = 0x09<<1,
	RegAddress_OLAT = 0x0A<<1
};

//static const uint8_t IODIR_ADDRESS = 0x00<<1;
//
//static const uint8_t IPOL_ADDRESS = 0x01<<1;
//
//static const uint8_t GPINTEN_ADDRESS = 0x02<<1;
//
//static const uint8_t DEFVAL_ADDESS = 0x03<<1;
//
//static const uint8_t INTCON_ADDRESS = 0x04<<1;
//
//static const uint8_t IOCON_ADDRESS = 0x05<<1;
//
//static const uint8_t GPPU_ADDRESS = 0x06<<1;
//
//static const uint8_t INTF_ADDRESS = 0x07<<1;
//
//static const uint8_t INTCAP_ADDRESS = 0x08<<1;



void writeRegister(RegAddress regAddress, uint8_t data);

uint8_t readRegister(RegAddress regAddress);

void setDirection(uint8_t direction);

//think about adding function to setting individual bit/clear bit

uint8_t read();

void write(uint8_t direction);

#endif /* SOURCES_PORTEXPANDER_H_ */
