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
#include "pit.h"
#include "smc.h"
#include "PortExpander.h"
#include "testing.h"
#include "Accelerometer.h"

using namespace USBDM;
using outputSpeedTesting = GpioC<0,ActiveHigh>;
using Timer        = Pit;
using TimerChannel = Timer::Channel<0>;
using DebugLed = GpioC<0>;

// Address (LSB = R/W bit)

static const unsigned I2C_SPEED   = 400*kHz;
static constexpr int MAX_OFFSET = 4;
static constexpr int MIN_OFFSET = -4;
static constexpr int MAX_SCORE  = 1000;
static int delayTime = 1000;
static int score = 0;
static int LEDPosition = 4;
static bool hasLost = false;
/**
 * Provides an offset value that may vary by up to +/- 1 on each call.
 *
 * @return offset value in range [MIN_OFFSET .. MAX_OFFSET]
 */
int randomWalk()
{
   static int offset = 0;

   switch(rand()%2) {
      case 0: offset -= 1; break;
      case 1: offset += 1; break;
   }
   if (offset < MIN_OFFSET) {
      offset = MIN_OFFSET;
   }
   if (offset > MAX_OFFSET) {
      offset = MAX_OFFSET;
   }
   return offset;
}

int updateLEDPosition()
{
	int temp = calculateTheDegree();
console.write(calculateTheDegree());

	if (temp > 7) return 7;
	else if (temp < 0) return 0;
	else return temp;
}

int getScore(int speed)
{
	return MAX_SCORE - speed;
}
/**
 *
 */
void displayLEDBar(unsigned int position)
{
	write(1<<position);
}

void PITCallback()
{
	LEDPosition = randomWalk()+ updateLEDPosition();
	displayLEDBar(LEDPosition);
	if (delayTime > 200)
	{
		delayTime-=50;
	}
	score+=getScore(delayTime);

	if (LEDPosition == 0 || LEDPosition == 7)
	{
		console.writeln("You have lost the game.");
		console.write("Final Score: ").writeln(score);
		score=0;
	}
	else
	{
		console.write("Score: ").write(score).write(" | Speed: ").write(delayTime).writeln(" ms each interval.");
	}
	TimerChannel::setPeriod(delayTime*ms);
}
/**
 * Initialise PIT for interupt
 */
void initialisePIT()
{
	// PIT configure
   Timer::configure(PitDebugMode_Stop);

   // Set handler for PIT channel programmatically
   TimerChannel::setCallback(PITCallback);

   // Setup de-bouncer to execute @DEBOUNCE_SAMPLE_TIME interval
   TimerChannel::configure(delayTime*ms, PitChannelIrq_Enabled);

   // Enable interrupts via NVIC for the PIT channel
   TimerChannel::enableNvicInterrupts(NvicPriority_Normal);
   checkError();
}

int main() {
	//For playing the game
    //Declare I2C interface
   initialisePIT();
   initializeTheAccelerometer();
   I2c0 i2c{I2C_SPEED, I2cMode_Polled};
   setDirection(0b00000000);

   while(true)
   {}
//	outputSpeedTesting::setOutput(PinDriveStrength_High, PinDriveMode_PushPull, PinSlewRate_Fast);
//	int choice=0;
//   for(;;)
//   {
//	   console.writeln("Enter the test case that you want").
//			   writeln("1 for testing setDirection. Set all direction to be input").
//			   writeln("2 for testing Display. Write to 8 output from 0 to 256").
//			   writeln("3 for testing Read Pin Function.").
//			   writeln("4 for system testing").readln(choice);
//	   //
//	   setDirection(0b00000000);
//	   write(0b11111111);
//	   write(0b00000000);
//	   console.writeln("huhu");
//	   outputSpeedTesting::on();
//	   outputSpeedTesting::off();
//	   waitMS(10);
//   }

}


