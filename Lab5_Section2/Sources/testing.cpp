///*
// * testing.cpp
// *
// *  Created on: Oct 31, 2019
// *  Author: Quang Thinh Ngo
// *  Author: Chuong Ho
// */
//
#include "testing.h"

using namespace USBDM;
using outputTest = GpioDField<3,1,ActiveHigh>;
/**
 * Testing the seting direction function by setting all GPIO to input
 * Result: Console returns the value in the register of Input Output Direction.
 * Expected result: 255
 */
void testSetDirection()
{
	setDirection(0b11111111);
	console.write("The direction is ").writeln(readRegister(RegAddress_IODIR));
}

/**
 * Testing the display LED by setting all GPIO direction to output and write binary value from 0 to 32 into the register.
 * Expected result: LED is on showing the binary value of integer 0 to 32.
 */
void testDisplay()
{
	setDirection(0b00000000);
   for (int i = 0; i < 64; ++i)
   {
	   write(i);
	   waitMS(700);
   }
}

/**
 * Testing setting pin direction individually.
 * Test detail: set the fourth pin to output and write 1 to that pin.
 * Expected result: Console show the value of the port is 8.
 */
void testsetPinDirection()
{
	setPinDirection(3,0);
	write(0b00001000);
	console.writeln(read());
}

/**
 * Testing the ability of reading pin value on the I/O Port.
 * Test detail:
 * Case 1: Setting 3 least significant bits to 1 and reading this value and print to the console.
 * Case 1: Setting 3 least significant bits to 0 and reading this value and print to the console.
 * Expected result:
 * Case 1: Value in console is 7.
 * Case 2: Value in console is 0.
 */
void testReadPinFunction()
{
	int choice=0;
	console.writeln("Please input the test you want to do, 1 for reading 3 pins are all 1, 2 for reading 3 pins are all 0").readln(choice);
	outputTest::setOutput(PinDriveStrength_High, PinDriveMode_PushPull, PinSlewRate_Slow);
	///The last 3 pins are input.
	setDirection(0b00000111);
	write(0b00000000);
	switch(choice)
	{
	case 1:
		///Setting all the output for testing to 1.
		outputTest::write(0b111);
		console.writeln(read());
		break;
	case 2:
		///Setting all the output for testing to 0.
		outputTest::write(0b000);
		console.writeln(read());
		break;
	default:
		console.writeln("Please try again");
	}
}

/**
 * Overal testing on the system
 * Test detail:
 * Getting input from users to determine the direction of each individual pin.
 * Write 1 to all the output pin.
 * Expected result: LEDs corresponding to all the output direction pin are on.
 */
void testSystem()
{
   unsigned numberOfInput;
   unsigned choice[8];
   console.writeln("Please enter the number of input in 8-bits: ");
   console.readln(numberOfInput);
   for (unsigned i=0;i<numberOfInput;i++)
   {
   console.writeln("Please input the position of your input right to left from 0 to 7th");
		   //a 8-bit unsigned integer indicating the preferable direction (0 for transmitting and 1 for receiving):");
   console.readln(choice[i]);
   }
   uint8_t Mask =0b00000000;
   for (unsigned l=0;l<numberOfInput;l++)
   {
	   Mask |= 1<<choice[l];
   }

   setDirection(Mask);
   //All the output LED will be on;
   write(0b11111111);

}
