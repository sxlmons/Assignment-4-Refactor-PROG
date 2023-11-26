/* PROG71985 - F23 - Nov 2023 - Joshua Salmons
*
*  Assignment #4 - Question #2 - utility.c
*
*  Revision History
*
*  1.0		2023 - Nov - 10		initial
*
*/

#define _CRT_SECURE_NO_WARNINGS 

#include "utility.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to convert a string to uppercase so ascii argangement order doesn't get mixed up
void str_toupper(char* str)
{
	for (; *str; ++str) 
	{
		// Convert the character to uppercase using the toupper function
		// The character is cast to an unsigned char before it's passed to toupper
		*str = toupper((unsigned char)*str); 
	}
}

// Function to compare the last names for the qsort function
int compare_last_names(const void* a, const void* b)
{
	// Cast the void pointers to SEAT pointers
	SEAT* seatA = (SEAT*)a;
	SEAT* seatB = (SEAT*)b;

	// Create buffers to store the last names
	char lastNameA[MAX_NAME_LENGTH]; 
	char lastNameB[MAX_NAME_LENGTH];

	// Copy the last names from the seats to the buffers
	strncpy(lastNameA, seatA->lastName, sizeof(lastNameA));
	strncpy(lastNameB, seatB->lastName, sizeof(lastNameB));

	// Convert the last names to upper case for case-insensitive comparison
	str_toupper(lastNameA);
	str_toupper(lastNameB);

	// Compare the last names and return the result
	return strcmp(lastNameA, lastNameB);
}

// Function to compare the first names for the qsort function
int compare_first_names(const void* a, const void* b)
{
	// Cast the void pointers to SEAT pointers
	SEAT* seatA = (SEAT*)a;
	SEAT* seatB = (SEAT*)b;

	// Create buffers to store the first names
	char firstNameA[MAX_NAME_LENGTH];
	char firstNameB[MAX_NAME_LENGTH];  

	// Copy the first names from the seats to the buffers
	strncpy(firstNameA, seatA->firstName, sizeof(firstNameA));     
	strncpy(firstNameB, seatB->firstName, sizeof(firstNameB));

	// Convert the first names to upper case for case-insensitive comparison
	str_toupper(firstNameA);
	str_toupper(firstNameB);

	// Compare the first names and return the result
	return strcmp(firstNameA, firstNameB);   
}
