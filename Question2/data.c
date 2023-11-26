/* PROG71985 - F23 - Nov 2023 - Joshua Salmons
*
*  Assignment #4 - Question #2 - data.c
*
*  Revision History
*
*  1.0      2023 - Nov - 10          initial
*
*/

#define _CRT_SECURE_NO_WARNINGS   

#include "data.h"
#include <stdio.h>
#include <stdbool.h>

void saveData(SEAT seats[], int size)
{
	// Open a binary file named "datafile.dat" in write mode
	FILE* file = fopen("datafile.dat", "wb");

	// If the file cannot be opened, print an error message and return
	if (file == NULL)
	{
		printf("Error opening file!\n");
		return;
	}

	// Write the seat data to the file
	// fwrite writes the entire seats array to the file in one operation
	fwrite(seats, sizeof(SEAT), size, file);

	// close file
	fclose(file);
}

void loadData(SEAT seats[], int size)
{
	// Open a binary file named "datafile.dat" in read mode
	FILE* file = fopen("datafile.dat", "rb");

	// If the file cannot be opened, print a message,
	// create a new file with saveData, and return
	if (file == NULL)
	{
		printf("No existing datafile found. A new file will be created.\n");
		saveData(seats, size);  // -> Create a new datafile
		return;
	}

	// Read the seat data from the file into the seats array
	// fread reads the entire seats array from the file in one operation
	fread(seats, sizeof(SEAT), size, file);

	// close file
	fclose(file);
}