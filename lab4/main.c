/* Osiris Thomas
 * ECE 477 Lab 4
 * main.c
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
	int del = 1024 * 1000;
	int dir = FW;
	int A;
	int B;
	int prevA = 0;
	int prevB = 0;
	
	wiringPiSetup();
	init_gpio();
	
	/* Go through loop while both buttons aren't pressed
	 * The previous button press must be 0 for a new button press
	 * to be registered
	 */
	while (1) {
		A = digitalRead(0);
		B = digitalRead(1);
		
		if (A && B)
			return 0;
		else if (A && !prevA && (del > 32 * 1000))
			del /= 2;
		else if (A && !prevA && (del == 32 * 1000))
			dir = BW;
		else if (B && !prevB && (del < 1024 * 1000))
			del *= 2;
		else if (B && !prevB && (del == 1024 * 1000))
			dir = FW;
		prevA = A;
		prevB = B;
		cycle_leds(del, dir);
	}
}

// Configure gpio to match hardware.
void init_gpio(void)
{
	/* Pins 0 and 1 are inputs and are pulled down.
	 * Pins 2-7 are outputs.
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
		for (i = 2; i < 8; i++) {
			digitalWrite(i, HIGH);
			usleep(delay);
			digitalWrite(i, LOW);	
		}	
	} else {
		for (i = 7; i > 1; i--) {
			digitalWrite(i, HIGH);
			usleep(delay);
			digitalWrite(i, LOW);
		}
	}
}
