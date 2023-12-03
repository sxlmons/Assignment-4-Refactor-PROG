/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - main.c

  Revision History

        1.0      2023 Nov 10          initial

        1.1		 2023 Nov 25		  refactor
            -> Fixed globally scoped array
            -> Tried using arrays for things
            -> Things became a mess

        1.2      2023 Nov 28->Dec 3   refactor2
            -> Fresh project, built from ground up
            -> Used LinkedList SEAT->FLIGHT->PLANE
            -> Learned how to bubble sort LinkedLists
            -> Overhaul of save/load feature
            -> LinkedLists are awesome!
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

 Original Requirements:

 - Single plane with 12 seats
 - Seat ID, first name, last name, assignment status
 - Menu for plane
 - View empty seats, num of empty seats
 - Alphabetical order of seats
 - Delete/Assign seats
 - Save/Load functionality

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

#include "creators.h"
#include "interface.h"
#include "data.h"
#include "sort.h"
#include "seats.h"

#include <stdio.h>

int main(void)
{
    //initialize both planes, with two flights each
    int plane1Flights[] = { 102, 311 };
    PLANE plane1 = createPlane(1, plane1Flights, 2);

    int plane2Flights[] = { 444, 519 };
    PLANE plane2 = createPlane(2, plane2Flights, 2);

    // Load data from file
    loadData(plane1, "plane1.txt");
    loadData(plane2, "plane2.txt");

    char userChoice;

    //initialize flight number to zero
    int flightNumber = 0;

    do {

        flightSelectionMenu();

        if (scanf(" %c", &userChoice) != 1)
        {
            printf("Failed to read input.\n");
        }
        while (getchar() != '\n');

        switch (userChoice)
        {
        case '1':
            flightNumber = 102;    
            break;
        case '2':
            flightNumber = 311;   
            break;
        case '3':
            flightNumber = 444;   
            break;
        case '4':
            flightNumber = 519;     
            break;
        case '0':
            printf("Exiting the program...\n");   
            break;
        default:
            printf("Invalid Input, Returning to Menu... \n");
        }
        // If a valid flight number is selected, display seat management interface
        if (userChoice >= '1' && userChoice <= '4')
        {
            if (flightNumber == 102 || flightNumber == 311)
            {
                SeatManagementInterface(plane1, flightNumber);
            }
            else if (flightNumber == 444 || flightNumber == 519)
            {
                SeatManagementInterface(plane2, flightNumber);
            }
        }

    } while (userChoice != '0');

    // Save data to file
    saveData(plane1, "plane1.txt");
    saveData(plane2, "plane2.txt");

    // Free the memory allocated for the planes, flights, and seats
    freePlane(plane1);
    freePlane(plane2);

    return 0;
}
