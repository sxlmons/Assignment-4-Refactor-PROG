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
#include "airline.h"



int main(void) {
    // Initialize the seats array for both planes
    initializeSeats(&Planes[0].seats, flightNumbers[0]);
    initializeSeats(&Planes[1].seats, flightNumbers[1]);

    // Variable to store the user's menu choice
    char choice;
    int planeNumber;
    int flightNumber;

    // Main loop of the program
    do {
        // Print top-level menu
        airlineFlightMenu();  

        // Get user's choice
        scanf_s(" %c", &choice, 1);
        (void)getchar(); // eat newline; added void for compiler

        switch (choice) {
        case '1':
            planeNumber = 1;
            flightNumber = flightNumbers[0];   
            break;
        case '2':
            planeNumber = 2;
            flightNumber = flightNumbers[1];
            break;
        case '3':
            planeNumber = 1; // Assuming you want to use the same planes for multiple flights
            flightNumber = flightNumbers[2];
            break;
        case '4':
            planeNumber = 2; // Assuming you want to use the same planes for multiple flights
            flightNumber = flightNumbers[3];
            break;
        case '0':
            printf("Exiting the program. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        printf("\nYou selected Flight %d.\n", flightNumber);

        // Sub-menu loop for the chosen flight
        do {
            // Print sub-menu heading the chosen flight
            printf("\nFlight %d Menu\n", flightNumber);
            generalSeatMenu();

            // Get user's choice for the chosen flight
            scanf_s(" %c", &choice, 1);
            getchar(); // eat newline

            switch (choice) {
            case 'a':
                // Show the number of empty seats for the chosen flight
                show_empty_seats_by_flight(&Planes[planeNumber - 1].seats, flightNumber); 
                break;
            case 'b':
                // Show a list of empty seats for the chosen flight
                show_list_of_empty_seats(&Planes[planeNumber - 1].seats);  
                break;
            case 'c':
                // Show an alphabetical list of seats for the chosen flight
                show_alphabetical_list_of_seats(&Planes[planeNumber - 1].seats);
                break;
            case 'd':
                // Assign a customer to a seat for the chosen flight
                assign_customer_to_seat(&Planes[planeNumber - 1].seats);
                break;
            case 'e':
                // Delete a seat assignment for the chosen flight
                delete_seat_assignment(&Planes[planeNumber - 1].seats);
                break;
            case 'f':
                // Confirm seat assignment for the chosen flight
                confirm_seat_assignment(&Planes[planeNumber - 1].seats, planeNumber); 
                break;
            case 'g':
                // Return to the top-level menu
                printf("Returning to the top-level menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 'g'); // Continue the sub-menu loop until the user chooses to return to the top-level menu

    } while (true); // Continue the main loop indefinitely until the user chooses to quit

    return 0;
}