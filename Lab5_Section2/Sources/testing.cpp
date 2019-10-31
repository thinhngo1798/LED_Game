///*
// * testing.cpp
// *
// *  Created on: Oct 31, 2019
// *      Author: PLH
// */
//
#include "testing.h"

using namespace USBDM;

void testSetDirection()
{
	setDirection(0b11111111);
	console.write("The direction is ").writeln(readRegister(RegAddress_IODIR));
}

void testDisplay()
{
   for (int i = 0; i < 256; ++i)
   {
	   write(i);
	   waitMS(1000);
   }
}

void testSystem()
{
   unsigned numberOfInput;
   unsigned choice[8];
   console.writeln("Please enter the number of input in 8-bits: ");
   console.readln(numberOfInput);
   for (int i=0;i<numberOfInput;i++)
   {
   console.writeln("Please input the position of your input right to left from 0 to 7th");
		   //a 8-bit unsigned integer indicating the preferable direction (0 for transmitting and 1 for receiving):");
   console.readln(choice[i]);
   }
   uint8_t Mask =0b00000000;
   for (int l=0;l<numberOfInput;l++)
   {
	   Mask |= 1<<choice[l];
   }

   setDirection(Mask);
   //All the output LED will be on;
   write(0b11111111);
   waitMS(5000);

   //All output will be 0 and then capture the input for testing.
   write(0b00000000);
   waitMS(500);

   //All the bits are output and flashing 1 light from right to left.
   Mask=0;
   setDirection(Mask);
   for (int l=0;l<=7;l++)
   {
	   write(1<<l);
	   waitMS(500);
   }
}
