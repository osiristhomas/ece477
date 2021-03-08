/* Osiris Thomas
 * ECE 477 Lab 4
 * cool.c
 * Pong-esque game using GPIO
 */

#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define FW 0
#define BW 1

// Configure gpio to match hardware.
void init_gpio(void);
// Cycle through LED array depending on speed and direction
void cycle_leds(int, int);

int main(int argc, char *argv[])
{
	// Initial time delay is half a second
	int del = 512 * 1000;
	int level = 1;
	int A;
	int prevA = 0;
	wiringPiSetup();
	init_gpio();

	while (1) {
		// "Serve" the ball
		cycle_leds(del, BW);
		// Read the current value on GPIO pin 0
		A = digitalRead(0);
		// Check to make sure A is a new press
		if (A && !prevA) {
			// Return the ball if A is pressed
			cycle_leds(del, FW);
		} else {
			printf("Made it to level %d!\n", level);
			return 0;	
		}
		// Incrememt level and make the time delay shorter by 50%
		level++;
		del /= 1.5;
	}
}

// Configure gpio to match hardware.
void init_gpio(void)
{
	/* Pins 0 and 1 are inputs and are pulled up to 3.3V.
	 * Pins 2-7 are outputs tied to LEDs.
	 */
	int i;
	for (i = 0; i < 2; i++) {
		pinMode(i, INPUT);
		pullUpDnControl(i, PUD_UP);
	}
	for (i = 2; i < 8; i++) {
		pinMode(i, OUTPUT);
	}
}

// Cycle LEDs 
void cycle_leds(int delay, int dir)
{
	int i;
	if (dir == FW) {
		for (i = 2; i < 7; i++) {
			digitalWrite(i, HIGH);
			usleep(delay);
			digitalWrite(i, LOW);	
		}	
	} else {
		for (i = 7; i > 2; i--) {
			digitalWrite(i, HIGH);
			usleep(delay);
			digitalWrite(i, LOW);
		}
	}
}

