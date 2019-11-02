/*
 ============================================================================
 * @file    i2c-example.cpp (180.ARM_Peripherals/Snippets)
 * @brief   Basic C++ demo of using I2C interface
 *
 *  Created on: 10/6/2017
 *      Author: podonoghue
 ============================================================================
 */

#include "hardware.h"
#include "i2c.h"
#include "smc.h"
#include "PortExpander.h"
#include "testing.h"
#include "Accelerometer.h"
#include "PITController.h"
using namespace USBDM;

using StartSwitch = GpioC<0, ActiveLow>;

int main() {
	StartSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_None);
	bool lastSwitchValue = false;
	bool currentSwitchValue;
   // Declare I2C interface
   initialisePIT();
   setDirection(0b00000000);

   for(;;)
   {
	   currentSwitchValue = StartSwitch::isPressed();

	   if (currentSwitchValue && !lastSwitchValue)
	   {
		   console.writeln("Game starts!");
		   resetGame();
	   }
	   lastSwitchValue = currentSwitchValue;
   }
}
