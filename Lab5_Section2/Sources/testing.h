/*
 * testing.h
 *
 *  Created on: Oct 31, 2019
 *      Author: PLH
 */

#ifndef SOURCES_TESTING_H_
#define SOURCES_TESTING_H_

#include "hardware.h"
#include "i2c.h"
#include "pit.h"
#include "smc.h"
#include "PortExpander.h"

using namespace USBDM;

//
//Unit level testing
//
void testSetDirection();
void testRead();
void testWrite();
void testReadPinFunction();
//
//System level testing
//
void testSystem();



#endif /* SOURCES_TESTING_H_ */
