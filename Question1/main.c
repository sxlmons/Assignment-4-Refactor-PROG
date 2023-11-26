/* 
  Program that accepts two command line arguments, first is the name
  of an existing text file, and the second is the name of the output file to be created.
  Program should convert all text from input file to lowercase using tolower() function.

  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 Refactor - Question #1
 
  Revision History

       1.0      2023-Nov-10          initial
	   1.1		2023-Nov-25			 refactor
			- fixed magic values

Feedback:		
	Question 1: File I/O and toLower()

o Specifications: 8.0/8.0 
	(The program works and meets all of the specifications.)

o Readability+Design: 8.0/8.0 
	(The code is exceptionally well organized and readable due to the use of good variable names, data and function structure.
	The code is designed ‘defensively’ (meaning garbage is kept out). The code allows for both effective testing and extension.)

o Reusability: 4.0/4.0 
	(The code is exceptionally well organized into ADTs/modules, demonstrating SRP, coupling and cohesion.)

o Documentation: 4.0/4.0 
	(The documentation is well written and clearly explains what the code is accomplishing and how.)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	// Check if the correct number of arguments are provided
	if (argc != 3) 
	{
		printf("Usage: %s ", argv[0]);
		exit(EXIT_FAILURE);	// line 26: removed magic number   
	}
	// Declare a character variable to hold each character from the source file
	char ch; 

	// Open the source file in read mode
	FILE* fp = fopen(argv[1], "r");
	// If the source file cannot be opened, print  an error message and exit
	if (fp == NULL) 
	{  
		printf("Could not open source file.\n"); 
		exit(EXIT_FAILURE);	// line 37: removed magic number
	}

	// Open the destination file in write mode
	FILE* copy = fopen(argv[2], "w");  
	// If the destination file cannot be opened, print an error message, close the source file, and exit
	if (copy == NULL) 
	{
		printf("Could not open copy file.\n");
		fclose(fp); 
		exit(EXIT_FAILURE); // line 47: removed magic number 
	}

	// Read the source file character by character until the end of the file
	// Write the lowercase version of the character to the destination file
	while ((ch = fgetc(fp)) != EOF) 
	{ 
		fputc(tolower(ch), copy);
	}

	printf("File copied and converted to lowercase successfully.\n");

	// Close the source file and the copy
	fclose(fp); 
	fclose(copy);

	return 0;
}