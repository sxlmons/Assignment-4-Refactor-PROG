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

void airlineFlightMenu()
{
    printf("\nTop-Level Menu\n");
    printf("1. Flight 102\n");
    printf("2. Flight 311\n");
    printf("3. Flight 444\n");
    printf("4. Flight 519\n");
    printf("0. Quit\n");
    printf("Enter your choice: ");
}

void generalSeatMenu()
{  
    printf("a. Show the number of empty seats\n");
    printf("b. Show a list of empty seats\n");
    printf("c. Show an alphabetical list of seats\n");
    printf("d. Assign a customer to a seat\n");
    printf("e. Delete a seat assignment\n");
    printf("f. Confirm Seat Assignment\n"); // Moved this line to the sub-menu
    printf("g. Return to top-level menu\n");
    printf("Enter your choice: ");
}