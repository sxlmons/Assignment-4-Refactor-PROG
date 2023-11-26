/* 
  This program manages seating reservations for Colossus Airlines, which has a 
  single plane with 12 seats.The program uses an array of 12 structures, each
  representing a seat with its ID, assignment status, and the seat holder's name. 
  It provides a menu for users to view empty seats, view seats in alphabetical
  order, assign or delete seat assignments, and quit the program.The program
  saves data between runs, and upon restart, it populates itself with that data.
 
  PROG71985 - F23 - Nov 2023 - Joshua Salmons
 
  Assignment #4 - Question #2 - main.c
 
  Revision History
 
		1.0      2023-Nov-10          initial
		1.1		 2023-Nov-25		  refactor
Feedback:

 Question 2: Modeling a (single) airline/airplane reservation system

o Specifications: 8.0/8.0 
(The program works and meets all of the specifications.)

o Readability+Design: 8.0/8.0 
(The code is exceptionally well organized and readable due to the use of good variable names, data and function structure.
The code is designed ‘defensively’ (meaning garbage is kept out). The code allows for both effective testing and extension.)

o Reusability: 2.0/4.0
(The code appears to be designed/implemented by machine and/or without regard to
readability or design concepts taught in the course or the following issues were noted:)
 —Having hard coded (magic) values in function limits reusability
 —Globally scoped variables should be avoided unless absolutely required

o Documentation: 4.0/4.0 
(The documentation is well written and clearly explains what the code is accomplishing and how.)

 New Requirements:

 - Colossus Airlines expanded to four daily flights (102, 311, 444, 519) with two planes.
 - Top-level menu: flight selection or return to main menu.
 - Flight-specific menu: seat assignment confirmation by passenger name.
 - Quit option replaced with return to main menu.
 - Displays show current flight, seat assignment indicates confirmation status.
 - Output for options a) and b) grouped by 'Flight #.'
 - Option c) includes 'Flight #' in output; option d) checks seat availability before booking.
 - Sub-menu option f) returns to main menu.
 - Flight data saved to disk on program completion, loaded on start.

*/
#define _CRT_SECURE_NO_WARNINGS
#define INPUT_LENGTH	1

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "menu.h"
//#include "data.h"
//#include "seats.h"
//#include "utility.h"
#include "airline.h"



int main(void) {
    // Initialize the seats array for both planes
    initializeSeats(&Planes[0].seats);
    initializeSeats(&Planes[1].seats);

    // Variable to store the user's menu choice
    char choice;
    int planeNumber;

    // Main loop of the program
    do {
        printf("Enter plane number (1 or 2, 0 to exit): ");
        scanf_s("%d", &planeNumber);

        if (planeNumber >= 1 && planeNumber <= NUM_PLANES) 
        {
            PLANE* plane = &Planes[planeNumber - 1];

            // Print menu
            airlineMenu();

            // Menu selection variable
            scanf_s(" %c", &choice, INPUT_LENGTH);
            clearInputBuffer();

            switch (tolower(choice)) 
            {
            case 'a':
                // Show the number of empty seats
                show_empty_seats(&plane->seats);
                break;
            case 'b':
                // Show a list of empty seats
                show_list_of_empty_seats(&plane->seats);
                break;
            case 'c':
                // Show an alphabetical list of seats
                show_alphabetical_list_of_seats(&plane->seats);
                break;
            case 'd':
                // Assign a customer to a seat
                assign_customer_to_seat(&plane->seats);
                break;
            case 'e':
                // Delete a seat assignment
                delete_seat_assignment(&plane->seats);
                break;
            case 'f':
                printf("Exiting plane %d. Program Exit Successful.\n", planeNumber);
                break;
            default:
                // Handle invalid menu choices
                printf("Invalid Input.\n");
            }
        }
        else if (planeNumber != 0) 
        {
            printf("Invalid plane number.\n");
        }

        // End the loop when the user chooses to exit (enters 0)
    } while (planeNumber != 0);

    return 0;
}