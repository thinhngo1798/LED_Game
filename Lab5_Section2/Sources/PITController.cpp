/*
 ============================================================================
 * @file    PITController.cpp
 * @brief   PIT to control the game status frequently.
 *
 *  Created on: 17/10/19
 *      Author: Dac Thanh Chuong Ho
 *      Co-autor: Quang Thinh Ngo
 ============================================================================
 */

#include "hardware.h"
#include "pit.h"
#include "Accelerometer.h"
#include "PITController.h"
#include "PortExpander.h"
using namespace USBDM;

using Timer        = Pit;
using TimerChannel = Timer::Channel<0>;

static constexpr int MAX_OFFSET = 4;
static constexpr int MIN_OFFSET = -4;
static constexpr int MAX_SCORE  = 1000;
static volatile int delayTime = 1000;
static volatile int score = 0;
static volatile int LEDPosition = 4;
static volatile bool hasLost = false;

/**
 *
 * @return
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

/**
 *calculate and return the LED Position.
 * @return
 */
int updateLEDPosition()
{
	int temp = calculateTheDegree() + randomWalk();

	if (temp > 7) return 7;
	else if (temp < 0) return 0;
	     else return temp;
}

/**
 *
 * @param position
 */
void displayLEDBar(unsigned int position)
{
	write(1<<position);
}

/**
 *
 */
void resetGame()
{
	delayTime = 1000;
	score = 0;
	hasLost = false;
	LEDPosition = 4;
}

/**
 * Callback function to execute all the program update
 * Update LED position
 * Display new LED position
 * Decrease the time between each interrupt
 * Update the score
 * Check if the player has lost the game
 * Update the score and speed to the mainline.
 */
void PITCallback()
{
	if (!hasLost)
	{
		LEDPosition = updateLEDPosition();
		displayLEDBar(LEDPosition);

		//reduce the time
		if (delayTime > 200)
		{
			delayTime-=25;
		}
		//score+=getScore(delayTime);
		score += 1;
		//
		if (LEDPosition == 0 || LEDPosition == 7)
		{
			//When the player loses the game, print out the score to the terminal
			//and to the LED bar in binary number.
			console.writeln("You have lost the game.");
			console.write("Final Score: ").writeln(score);
			write(score);
			hasLost = true;
		}
		else
		{
			console.write("Score: ").write(score).write(" | Speed: ").write(delayTime).writeln(" ms each interval.");
		}

		//set new time delay.
		TimerChannel::setPeriod(delayTime*ms);
	}
}

/**
 * Configure the PIT interrupt
 */
void initialisePIT()
{
   Timer::configure(PitDebugMode_Stop);

   TimerChannel::setCallback(PITCallback);

   TimerChannel::configure(delayTime*ms, PitChannelIrq_Enabled);

   TimerChannel::enableNvicInterrupts(NvicPriority_Normal);
   checkError();
}
