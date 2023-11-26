#pragma once

/* PROG71985 - F23 - Nov 2023 - Joshua Salmons
*
*  Assignment #4 - Question #2 - data.h
*
*  Revision History
*
*  1.0		2023 - Nov - 10		initial
*
*/

#define MAX_NAME_LENGTH		25
#define ARRAY_SIZE			12
#include <stdbool.h>

typedef struct
{
	int seatID;			// identification of each seat on the plance
	bool assigned;		// if the seat is empty or assigned
	char firstName[MAX_NAME_LENGTH];  
	char lastName[MAX_NAME_LENGTH];
}SEAT;

// array of 12 structs
SEAT seats[ARRAY_SIZE]; 

void saveData(SEAT seats[], int size);
void loadData(SEAT seats[], int size);