/* PROG71985 - F23 - Nov 2023 - Joshua Salmons
*
*  Assignment #4 - Question #2 - seats.c
*
*  Revision History
*
*  1.0      2023 - Nov - 10          initial
*
*/

#define _CRT_SECURE_NO_WARNINGS   


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "seats.h"
#include "utility.h"

// Initialize the seats array
void seatsInitialization()
{
	// Loop over each seat in the array
	for (int i = 0; i < ARRAY_SIZE; i++) 
	{
		// Set the seatID field to the index plus one
		seats[i].seatID = i + 1;  

		// Set the assigned field to false, indicating that the seat is not assigned
		seats[i].assigned = false;

		// SetlastName/firstName to an empty string
		strncpy(seats[i].lastName, "", sizeof(seats[i].lastName));     
		strncpy(seats[i].firstName, "", sizeof(seats[i].firstName));
	}
}

// Displays the number of empty seats
void show_empty_seats()
{
	// Initialize a counter for the number of empty seats
	int count = 0;

	// Loop over each seat in the array
	for (int i = 0; i < ARRAY_SIZE; i++)  
	{
		// If the current seat is empty
		if (!seats[i].assigned)
		{
			//increment
			count++;
		}
	}
	//Print the number of empty seats
	printf("Number of empty seats: %d\n", count);
}

// Displays a list of empty seats
void show_list_of_empty_seats()
{
	// Begin the list of empty seats
	printf("Empty seats: ");

	// Loop over each seat in the array
	for (int i = 0; i < ARRAY_SIZE; i++) 
	{
		// If the current seat is empty
		if (!seats[i].assigned)
		{
			// Print the seatID of the empty seat
			printf("%d ", seats[i].seatID); 
		}
	}
	// End the list of empty seats
	printf("\n");
}

// deletes a seat assignment
void delete_seat_assignment()
{
	int seatID;

	// Prompt the user to enter the seat ID to delete
	printf("Enter seat ID to delete assignment (1-12): ");
	scanf_s("%d", &seatID);

	// eat newline
	getchar();

	// Check if the seat ID is valid and the seat is assigned
	if (seatID >= 1 && seatID <= ARRAY_SIZE && seats[seatID - 1].assigned) 
	{
		// If the seat is assigned, delete the assignment
		seats[seatID - 1].assigned = false;

		// Clear the firstName field
		strncpy(seats[seatID - 1].firstName, "", sizeof(seats[seatID - 1].firstName));
		// Clear the lastName field
		strncpy(seats[seatID - 1].lastName, "", sizeof(seats[seatID - 1].lastName));

		// Print a success message
		printf("Seat assignment successfully deleted!\n");
	}
	else
	{
		// If the seat is not assigned, print an error message
		printf("Invalid seat ID or seat not assigned.\n");
	}
}

//assigns customer to a seat
void assign_customer_to_seat()
{
	char firstName[MAX_NAME_LENGTH];  // Buffer to store the customer's first name 
	char lastName[MAX_NAME_LENGTH];   // Buffer to store the customer's last name 
	int seatID;          // Variable to store the seat ID

	// Prompt the user to enter the customer's first name
	printf("Enter customer's first name: ");
	fgets(firstName, sizeof(firstName), stdin);
	firstName[strcspn(firstName, "\n")] = 0;  // Remove newline character

	// Prompt the user to enter the customer's last name
	printf("Enter customer's last name: ");
	fgets(lastName, sizeof(lastName), stdin);
	lastName[strcspn(lastName, "\n")] = 0;  // Remove newline character

	// Prompt the user to enter the seat ID to assign
	printf("Enter seat ID to assign (1-12): ");
	scanf_s("%d", &seatID);

	// eat newline
	getchar(); 

	// Check if the seat ID is valid and the seat is not already assigned
	if (seatID >= 1 && seatID <= ARRAY_SIZE && !seats[seatID - 1].assigned) 
	{
		// If the seat is available, assign the seat to the customer
		seats[seatID - 1].assigned = true;

		// Store the customer's first name
		strncpy(seats[seatID - 1].firstName, firstName, sizeof(seats[seatID - 1].firstName));
		// Store the customer's last name
		strncpy(seats[seatID - 1].lastName, lastName, sizeof(seats[seatID - 1].lastName));

		// Print a success message
		printf("Seat successfully assigned!\n");
	}
	else
	{
		// If the seat is not available, print an error message
		printf("Invalid seat ID or seat already assigned.\n");
	}
}

// Displays a list of seats sorted alphabetically by first name or last name.
void show_alphabetical_list_of_seats()
{
	// Variable to store the user's choice of sorting field
	char choice;

	// Prompt the user to choose whether to sort by first name or last name
	printf("Sort by (f)irst name or (l)ast name? ");
	scanf_s("%c", &choice, 1);

	// eat newline
	getchar();

	// Create a copy of the seats array to sort, so we don't disturb the original order god forbid
	SEAT sortedSeats[ARRAY_SIZE]; 
	memcpy(sortedSeats, seats, sizeof(seats));

	// Sort the seats by the chosen field
	if (choice == 'f')
	{
		// If the user chose to sort by first name, sort the seats by first name
		qsort(sortedSeats, ARRAY_SIZE, sizeof(SEAT), compare_first_names); 
	}
	else if (choice == 'l')
	{
		// If the user chose to sort by last name, sort the seats by last name
		qsort(sortedSeats, ARRAY_SIZE, sizeof(SEAT), compare_last_names); 
	}
	else
	{
		// If the user's choice was not 'f' or 'l', default to sorting by last name
		printf("Invalid choice. Defaulting to last name.\n");
		qsort(sortedSeats, ARRAY_SIZE, sizeof(SEAT), compare_last_names); 
	}

	// Print the sorted list of seats
	for (int i = 0; i < ARRAY_SIZE; i++) 
	{
		// Only print the seat if it is assigned
		if (sortedSeats[i].assigned)
		{
			printf("Seat ID: |%2d| |Last Name: %-10s| |First Name: %-10s|\n",
				sortedSeats[i].seatID, sortedSeats[i].lastName, sortedSeats[i].firstName);
		}
	}
}