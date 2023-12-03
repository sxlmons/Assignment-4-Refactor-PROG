/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - interface.c

  Details
        -> All menus/ui stuff here

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/

#include "creators.h"
#include "interface.h"
#include "sort.h"
#include "seats.h"

void flightSelectionMenu()
{
    printf("\n  Flight Menu\n\n");
    printf("1. Flight 102\n");
    printf("2. Flight 311\n");
    printf("3. Flight 444\n");
    printf("4. Flight 519\n");
    printf("0. Quit\n");
    printf("\n  Selection: ");
}

void SeatManagementMenu()
{
    printf("a) Show empty seats\n");
    printf("b) Show number of empty seats\n");
    printf("c) Show alphabetical list\n");
    printf("d) Assign a seat\n");
    printf("e) Delete a seat\n");
    printf("f) Confirm a seat\n");
    printf("g) Return to top level menu\n");
    printf("\nEnter your choice: ");
}

void sortPassengersMenu(PLANE plane, int flightNumber)
{
    // Ask the user to choose sorting by first name or last name
    printf("Sort by (f)irst name or (l)ast name? ");

    char sortChoice;

    if (scanf(" %c", &sortChoice) != 1)
    {
        printf("Failed to read input.\n");
        return;
    }

    while (getchar() != '\n');

    if (sortChoice == 'f')
    {
        // Sort passengers by first name
        sortPassengers(getFlight(plane, flightNumber), true);
    }
    else if (sortChoice == 'l')
    {
        // Sort passengers by last name
        sortPassengers(getFlight(plane, flightNumber), false);
    }
    else
    {
        // Handle invalid choice
        printf("Invalid choice. Please try again.\n");
    }
}

void SeatManagementInterface(PLANE plane, int flightNumber)
{
    char userChoice;

    do
    {
        // Print the flight number
        printf("\n\tFlight %d\n\n", flightNumber);

        // Display seat management menu
        SeatManagementMenu();

        if (scanf(" %c", &userChoice) != 1)
        {
            printf("Failed to read input.\n");
        }
        while (getchar() != '\n');

        // selection for user
        switch (tolower(userChoice))
        {
        case 'a':
            showEmptySeats(getFlight(plane, flightNumber));
            break;
        case 'b':
            numberOfEmptySeats(getFlight(plane, flightNumber));     
            break;
        case 'c':
            sortPassengersMenu(plane, flightNumber);   
            break;
        case 'd':
            assignSeat(getFlight(plane, flightNumber));   
            break;
        case 'e':
            deleteSeat(getFlight(plane, flightNumber));
            break;
        case 'f':
            confirmSeat(getFlight(plane, flightNumber));
            break;
        case 'g':
            printf("\nReturning to the Flight menu...\n");
            return;
        default:
            printf("\nInvalid Input, Returning to Menu... \n");  
        }

    } while (userChoice != 'g');
}