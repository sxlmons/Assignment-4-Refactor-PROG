/* PROG71985 - F23 - Nov 2023 - Joshua Salmons
*
*  Assignment #4 - Question #2 - menu.c
*
*  Revision History
*
*  1.0      2023 - Nov - 10          initial
*
*/

#define _CRT_SECURE_NO_WARNINGS   

#include "menu.h"
#include <stdio.h>

void airlineMenu()
{
	//print menu
	printf("** Welcome to Colossus Airlines **\n");   
	printf("a) Show number of empty seats\n");
	printf("b) Show list of empty seats\n");
	printf("c) Show alphabetical list of seats\n");
	printf("d) Assign a customer to a seat assignment\n");
	printf("e) Delete a seat assignment\n");
	printf("f) Quit\n");
}