/* Osiris Thomas
 * main.c
 * 
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "led.h"

int main(void)
{
	int i;
	char pins[8][3] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	char pin[3];
	// export all used pins
	for (i = 0; i < 8; i++) {
		//snprintf(pin, 2, "%d", i);
		strcpy(pin, pins[i]);
		printf("Initializing GPIO %s\n", pin);
		exportpin(pin);
		direction(pin, "out");
		sleep(1);
	}
	sleep(1);
	for (i = 0; i < 8; i++) {
		//snprintf(pin, 2, "%d", i);
		strcpy(pin, pins[i]);
		value(pin, "1");
		sleep(1);
	}

	// unexport all used pins	
	for (i = 0; i < 8; i++) {
		//snprintf(pin, 2, "%d", i);
		strcpy(pin, pins[i]);
		printf("Unexporting GPIO %s\n", pin);
		unexport(pin);
		sleep(1);
	}
	return 0; 
}
