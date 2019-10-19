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

void setDirection(uint8_t direction);

//think about adding function to setting individual bit/clear bit

uint8_t read();



void write(uint_t direction);



#endif /* SOURCES_PORTEXPANDER_H_ */
