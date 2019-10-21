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
static const uint8_t IODIR_ADDRESS = 0x00<<1;

//Input Polarity
static const uint8_t IPOL_ADDRESS = 0x01<<1;

//Pull-up configuration
static const uint8_t GPPU_ADDRESS = 0x06<<1;

//Port (GPIO) register
//reading from this register reads the port.
//writing to this register modifies the OUTPUT latch.
static const uint8_t GPIO_ADDRESS = 0x09<<1;

//a write to this register modifies the pins configured as outputs.
static const uint8_t OLAT_ADDRESS = 0x0A<<1;


/*
* may not be neccessary but not completely forgetting
//Interrupt: may not need this
static const uint8_t GPINTEN_ADDRESS = 0x02<<1;

static const uint8_t DEFVAL_ADDESS = 0x03<<1;

static const uint8_t INTCON_ADDRESS = 0x04<<1;

static const uint8_t IOCON_ADDRESS = 0x05<<1;

static const uint8_t INTF_ADDRESS = 0x07<<1;

static const uint8_t INTCAP_ADDRESS = 0x08<<1;
*/


void setDirection(uint8_t direction);

//think about adding function to setting individual bit/clear bit

uint8_t read();



void write(uint_t direction);



#endif /* SOURCES_PORTEXPANDER_H_ */
