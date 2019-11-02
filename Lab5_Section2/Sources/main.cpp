/*
 ============================================================================
 * @file    main.cpp
 * @brief   Mainline for the Accelerometer LED game
 *
 *  Created on: 17/10/19
 *      Author: Dac Thanh Chuong Ho
 *      Co-autor: Quang Thinh Ngo
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
	//Switch to start the game
	StartSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_None);
	bool lastSwitchValue = false;
	bool currentSwitchValue;

	// Set up the PIT
   initialisePIT();
   //Set all pins as outputs.
   setDirection(0b00000000);

   for(;;)
   {
	   currentSwitchValue = StartSwitch::isPressed();
	   //Detect when the Switch is pressed to restart the game.
	   if (currentSwitchValue && !lastSwitchValue)
	   {
		   console.writeln("Game starts!");
		   //set up the game again.
		   resetGame();
	   }
	   lastSwitchValue = currentSwitchValue;
   }
}
