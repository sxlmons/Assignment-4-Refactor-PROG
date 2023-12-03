/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - seats.c

  Details
        -> all of the functions to manage seat on a flight

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/

#include "creators.h"
#include "seats.h"

void showEmptySeats(FLIGHT flight)
{
    printf("\n\tFlight %d\n ", flight->flightID);
    printf("\n    Available Seats List:\n\n");

    // Get the first seat in the flight
    SEAT currentSeat = flight->seats;

    while (currentSeat != NULL)
    {
        // If the current seat is not assigned, print the seat ID
        if (!currentSeat->isAssigned)
        {
            printf("\tSeat ID [%d]\n", currentSeat->seatID);
        }
        // Move on to the next seat
        currentSeat = currentSeat->nextSeat;
    }
}

void numberOfEmptySeats(FLIGHT flight)
{
    printf("\n\tFlight %d\n ", flight->flightID);
    printf("\n    Available: ");

    //counter
    int i = 0;

    // Get the first seat in the flight
    SEAT currentSeat = flight->seats;
    while (currentSeat != NULL)
    {
        // If the current seat is not assigned, increment the counter
        if (!currentSeat->isAssigned)
        {
            i++;
        }
        // Move on to the next seat
        currentSeat = currentSeat->nextSeat;
    }
    // Print the number of available seats
    if (i == 1)
    {
        printf("%d Seat\n", i);
    }
    else if (i == 0)
    {
        printf("No Seats Available\n");
    }
    else
    {
        printf("%d Seats\n", i);
    }
}

// Function to assign a seat to a passenger on a given flight
void assignSeat(FLIGHT flight)
{
    // Declare variables for seat ID, flight number confirmation, and passenger name
    int seatID, confirmFlightNumber;
    char firstName[MAXNAME];
    char lastName[MAXNAME];

    printf("\n\tFlight %d\n\n", flight->flightID);

    // Ask the user to confirm the flight number or enter 0 to abort
    printf("(0 to abort)\nConfirm the flight number: ");
    if (scanf("%d", &confirmFlightNumber) != 1)
    {
        printf("Failed to read input.\n");
    }
    else if (confirmFlightNumber == 0)
    {
        printf("\nReturning to the menu...\n");
        return;
    }
    else if (confirmFlightNumber != flight->flightID)
    {
        printf("\nFlight number does not match. Returning to the menu...\n");
        return;
    }

    // Ask the user to enter the seat ID
    printf("Enter the seat ID (1-12): ");
    if (scanf("%d", &seatID) != 1)
    {
        printf("Failed to read input.\n");
    }
    // Check if the seat ID is valid
    if (seatID < MIN_SEATS || seatID > MAX_SEATS)
    {
        printf("Invalid seat ID. Please enter a number between 1 and 12.\n");
        return;
    }
    while (getchar() != '\n');

    // first name is stored in a variable with 20 characters of space
    // this gives us 5 characters of buffer to work with
    printf("\n(Maximum 15 Characters)\nEnter the passenger's first name: ");
    fgets(firstName, MAXNAME, stdin);
    firstName[strcspn(firstName, "\n")] = 0;

    //if the name is greater than 15 return
    if (strlen(firstName) > MAXNAME_REDUCED)
    {
        printf("Input exceeded maximum limit. Returning to main menu.\n");
        return;
    }

    printf("\n(Maximum 15 Characters)\nEnter the passenger's last name: ");
    fgets(lastName, MAXNAME, stdin);
    lastName[strcspn(lastName, "\n")] = 0;

    if (strlen(lastName) > MAXNAME_REDUCED) 
    {        
        printf("Input exceeded maximum limit. Returning to main menu.\n");
        return;
    }


    // Loop through the seats in the flight
    SEAT currentSeat = flight->seats;
    while (currentSeat != NULL)
    {
        // If the current seat's ID matches the entered seat ID
        if (currentSeat->seatID == seatID)
        {
            // If the seat is already assigned
            if (currentSeat->isAssigned)
            {
                printf("This seat is already assigned.\n");
            }
            // If the seat is not assigned
            else
            {
                // Assign the seat to the passenger
                strcpy(currentSeat->passengerFirstName, firstName);
                strcpy(currentSeat->passengerLastName, lastName);
                currentSeat->isAssigned = true;
                printf("Seat assigned successfully.\n");
            }
            return;
        }
        currentSeat = currentSeat->nextSeat;
    }
    // If no seat with the entered ID is found
    printf("Invalid seat ID.\n");
}

// Function to delete a seat from a given flight
void deleteSeat(FLIGHT flight)
{
    int seatID;
    printf("\n\tFlight %d\n\n ", flight->flightID);

    // Ask the user to enter the seat ID or 0 to abort
    printf("(0 to abort)\nEnter the seat ID (1-12): ");
    if (scanf("%d", &seatID) != 1)
    {
        printf("Failed to read input.\n");
    }
    else if (seatID == 0)
    {
        printf("\nReturning to the menu...\n");
        return;
    }
    // Check if the seat ID is valid
    else if (seatID < MIN_SEATS || seatID > MAX_SEATS)
    {
        printf("Invalid seat ID. Please enter a number between 1 and 12.\n");
        return;
    }
    while (getchar() != '\n');

    // Initialize currentSeat to the head of the seats list and prevSeat to NULL
    SEAT currentSeat = flight->seats;
    SEAT prevSeat = NULL;

    // Loop through the seats in the flight
    while (currentSeat != NULL)
    {
        // If the current seat's ID matches the entered seat ID
        if (currentSeat->seatID == seatID)
        {
            // If the seat is not assigned
            if (!currentSeat->isAssigned)
            {
                printf("This seat is already empty.\n");
            }
            else
            {
                // If the seat is assigned
                if (prevSeat == NULL)
                {
                    // If this is the first seat in the list
                    flight->seats = currentSeat->nextSeat;
                }
                else
                {
                    // If this is not the first seat in the list
                    prevSeat->nextSeat = currentSeat->nextSeat;
                }
                free(currentSeat);
                printf("Seat deleted successfully.\n");
            }
            return;
        }
        // Move to the next seat in the list
        prevSeat = currentSeat;
        currentSeat = currentSeat->nextSeat;
    }
    // If no seat with the entered ID is found
    printf("Invalid seat ID.\n");
}

// Function to confirm a seat for a passenger on a given flight
void confirmSeat(FLIGHT flight)
{
    char firstName[MAXNAME];
    char lastName[MAXNAME];

    printf("\n\tFlight %d Seat Confirmation\n\n", flight->flightID);

    // Ask the user to enter the passenger's first name or 0 to abort
    printf("(0 to abort)\nEnter the passenger's first name: ");
    fgets(firstName, MAXNAME, stdin);
    if (firstName[0] == '0')
    {
        printf("\nReturning to the menu...\n");
        return;
    }
    firstName[strcspn(firstName, "\n")] = 0;

    // Ask the user to enter the passenger's last name
    printf("Enter the passenger's last name: ");
    fgets(lastName, MAXNAME, stdin);
    lastName[strcspn(lastName, "\n")] = 0;

    // Convert the input names to lower case for case-insensitive comparison
    for (int i = 0; firstName[i]; i++)
    {
        firstName[i] = tolower(firstName[i]);
    }
    for (int i = 0; lastName[i]; i++)
    {
        lastName[i] = tolower(lastName[i]);
    }

    // Initialize currentSeat to the head of the seats list
    SEAT currentSeat = flight->seats;
    while (currentSeat != NULL)
    {
        // Convert the names in the list to lower case before comparing
        char listFirstName[MAXNAME];
        char listLastName[MAXNAME];
        strcpy(listFirstName, currentSeat->passengerFirstName);
        strcpy(listLastName, currentSeat->passengerLastName);
        for (int i = 0; listFirstName[i]; i++)
        {
            listFirstName[i] = tolower(listFirstName[i]);
        }
        for (int i = 0; listLastName[i]; i++)
        {
            listLastName[i] = tolower(listLastName[i]);
        }

        // If the names match
        if (strcmp(listFirstName, firstName) == 0 && strcmp(listLastName, lastName) == 0)
        {
            // Print the passenger's name and seat ID
            printf("\nPassenger: %s %s, Seat ID: %d\n",
                currentSeat->passengerFirstName,
                currentSeat->passengerLastName,
                currentSeat->seatID);
            return;
        }
        // Move to the next seat in the list
        currentSeat = currentSeat->nextSeat;
    }
    // If no passengers matching the entered names are found
    printf("\nNo passengers matching %s %s.\n", firstName, lastName);
}