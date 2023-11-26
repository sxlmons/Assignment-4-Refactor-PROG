/* This program manages seating reservations for Colossus Airlines, which has a 
*  single plane with 12 seats.The program uses an array of 12 structures, each
*  representing a seat with its ID, assignment status, and the seat holder's name. 
*  It provides a menu for users to view empty seats, view seats in alphabetical
*  order, assign or delete seat assignments, and quit the program.The program
*  saves data between runs, and upon restart, it populates itself with that data.
* 
*  PROG71985 - F23 - Nov 2023 - Joshua Salmons
* 
*  Assignment #4 - Question #2 - main.c
* 
*  Revision History
* 
*		1.0      2023-Nov-10          initial
* 
*/
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "menu.h"
#include "data.h"
#include "seats.h"
#include "utility.h"



int main(void)
{
	// Initialize the seats array
	seatsInitialization();

	// Load seat data from a file into the seats array
	loadData(seats, 12); 

	// Variable to store the user's menu choice
	char choice;

	// Main loop of the program
	do {
		//print menu
		airlineMenu();

		//menu selection variable
		scanf_s("%c", &choice, 1);   

		//eat newline
		getchar();

		switch (choice)
		{
		case 'a':
			// Show the number of empty seats
			show_empty_seats();

			break;
		case 'b':
			// Show a list of empty seats
			show_list_of_empty_seats();

			break;
		case 'c':
			// Show an alphabetical list of seats
			show_alphabetical_list_of_seats(); 

			break;
		case 'd':
			// Assign a customer to a seat
			assign_customer_to_seat(); 

			break;
		case 'e':
			// Delete a seat assignment
			delete_seat_assignment();

			break;

		//if 'f' is entered user exits program
		case 'f':
			printf("Program Exit Successful.\n");
			break;
		default:
			// Handle invalid menu choices
			printf("Invalid Input.\n");
		}
	// End the loop when the user chooses to exit
	} while (choice != 'f');

	// Save the current state of the seats array to a file
	saveData(seats, 12);

	return 0;
}