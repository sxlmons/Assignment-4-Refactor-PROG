/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 - Question #2 - airline.c

  Revision History

  1.0      2023 - Nov - 10          initial
  1.1	   2023 - Nov - 25			refactor

*/
#define _CRT_SECURE_NO_WARNINGS 

#include "airline.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define flightNumbers in one of the source files
int flightNumbers[NUM_FLIGHTS] = { 102, 311, 444, 519 };

// Define the array of planes
PLANE Planes[NUM_PLANES];


void initializeSeats(PLANE* plane, int flightNumber)
{
    plane->seats.head = NULL;
    SEATNODE* current = NULL;

    for (int i = 0; i < 12; ++i)
    {
        SEATNODE* newSeat = (SEATNODE*)malloc(sizeof(SEATNODE));
        if (newSeat == NULL)
        {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation error\n");
            while (plane->seats.head != NULL)
            {
                current = plane->seats.head;
                plane->seats.head = current->next;
                free(current);
            }
            exit(EXIT_FAILURE);
        }

        newSeat->seatID = i + 1;
        newSeat->flightNumber = flightNumber;
        newSeat->assigned = false;
        newSeat->firstName[0] = '\0';
        newSeat->lastName[0] = '\0';
        newSeat->next = NULL;

        if (plane->seats.head == NULL)
        {
            plane->seats.head = newSeat;
        }
        else
        {
            current = plane->seats.head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newSeat;
        }
    }

    // Set the selectedFlight for the plane
    plane->selectedFlight = flightNumber;
}





// Helper function to compare seat nodes based on last names for sorting
int compareSeatNodes(const void* a, const void* b)
{
    const SEATNODE* seatA = *(const SEATNODE**)a;
    const SEATNODE* seatB = *(const SEATNODE**)b;
    return strcmp(seatA->lastName, seatB->lastName);
}

void showAlphabeticalListOfSeats(PLANE* plane)
{
    SEATNODE* current = plane->seats.head;

    // Count the number of seats in the list
    int seatCount = 0;
    while (current != NULL)
    {
        seatCount++;
        current = current->next;
    }

    // Create an array of pointers to seat nodes
    SEATNODE** seatArray = malloc(seatCount * sizeof(SEATNODE*));
    if (seatArray == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    // Fill the array with seat nodes
    current = plane->seats.head;
    for (int i = 0; i < seatCount; i++)
    {
        seatArray[i] = current;
        current = current->next;
    }

    // Sort the array of seat nodes based on last names
    qsort(seatArray, seatCount, sizeof(SEATNODE*), compareSeatNodes);

    // Print the sorted list
    printf("Alphabetical List of Seats for Flight %d:\n", plane->selectedFlight);
    for (int i = 0; i < seatCount; i++)
    {
        printf("Seat ID: %2d, Assigned: %s, Last Name: %s, First Name: %s\n",
            seatArray[i]->seatID,
            seatArray[i]->assigned ? "Yes" : "No",
            seatArray[i]->lastName,
            seatArray[i]->firstName);
    }

    // Free the allocated memory
    free(seatArray);
}

bool isValidFlightNumber(int flightNumber)
{
    for (int i = 0; i < NUM_FLIGHTS; ++i)
    {
        if (flightNumber == flightNumbers[i])
        {
            return true;
        }
    }
    return false;
}

void assignCustomerToSeat(PLANE* plane)
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int seatID;
    int confirmedFlightNumber;

    // Prompt user for flight number confirmation
    printf("Confirm Flight Number (102, 311, 444, 519): ");
    scanf_s("%d", &confirmedFlightNumber);
    clearInputBuffer(); // Clear input buffer to handle newline

    // Determine the correct plane number based on the confirmed flight number
    int planeNumber;
    if (confirmedFlightNumber == 102 || confirmedFlightNumber == 444)
    {
        planeNumber = 1;
    }
    else if (confirmedFlightNumber == 311 || confirmedFlightNumber == 519)
    {
        planeNumber = 2;
    }
    else
    {
        printf("Invalid flight number.\n");
        return;
    }

    // Prompt user for seat ID to assign
    printf("Enter seat ID to assign (1-12): ");
    scanf_s("%d", &seatID);
    clearInputBuffer(); // Clear input buffer to handle newline

    if (seatID < 1 || seatID > 12)
    {
        printf("Invalid seat ID.\n");
        return;
    }

    // Add these print statements for debugging
    printf("Confirmed Flight Number: %d\n", confirmedFlightNumber);
    printf("Selected Flight Number: %d\n", plane->selectedFlight);

    SEATNODE* current = plane->seats.head;

    // Find the selected seat in the plane's seat list
    while (current != NULL && current->seatID != seatID)
    {
        current = current->next;
    }

    if (current != NULL && !current->assigned)
    {
        // Prompt user for passenger's first and last names
        printf("Enter passenger first name: ");
        scanf_s("%s", firstName, MAX_NAME_LENGTH);
        printf("Enter passenger last name: ");
        scanf_s("%s", lastName, MAX_NAME_LENGTH);

        // Assign seat details
        current->assigned = true;
        firstName[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(current->firstName, firstName, MAX_NAME_LENGTH - 1);

        lastName[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(current->lastName, lastName, MAX_NAME_LENGTH - 1);

        printf("Seat successfully assigned!\n");
    }
    else
    {
        printf("Invalid seat ID or seat already assigned.\n");
    }
}







void deleteSeatAssignment(PLANE* plane)
{
    int seatID;
    int flightNumber;

    printf("Enter flight number (102, 311, 444, 519): ");
    scanf_s("%d", &flightNumber);
    (void)getchar(); // eat newline

    // Check if the entered flight number is valid
    if (flightNumber == 102 || flightNumber == 311 || flightNumber == 444 || flightNumber == 519)
    {
        printf("Enter seat ID to delete assignment (1-12): ");
        scanf_s("%d", &seatID);
        (void)getchar(); // eat newline

        if (seatID >= 1 && seatID <= 12)
        {
            SEATNODE* current = plane->seats.head;

            // Find the selected seat in the plane's seat list
            while (current != NULL && (current->seatID != seatID || current->flightNumber != flightNumber)) 
            {
                current = current->next;
            }

            if (current != NULL && current->assigned)
            {
                current->assigned = false;
                current->firstName[0] = '\0'; // Clear the first name
                current->lastName[0] = '\0';  // Clear the last name

                printf("Assignment successfully deleted!\n");
            }
            else
            {
                printf("Invalid seat ID, seat not assigned, or mismatched flight number.\n");
            }
        }
        else
        {
            printf("Invalid seat ID.\n");
        }
    }
    else
    {
        printf("Invalid flight number.\n");
    }
}


void show_empty_seats_by_flight(SEATLIST* seatList, int flightNumber)
{
    int emptySeatCount = 0;
    SEATNODE* current = seatList->head;

    while (current != NULL)
    {
        if (!current->assigned && current->flightNumber == flightNumber)
        {
            emptySeatCount++;
        }
        current = current->next;
    }

    printf("Number of empty seats for Flight #%d: %d\n", flightNumber, emptySeatCount);
}



void showEmptySeatsByFlight(PLANE* plane)
{
    SEATNODE* current = plane->seats.head;
    bool emptyFound = false;

    printf("List of empty seats for Flight %d:\n", plane->selectedFlight);

    while (current != NULL)
    {
        if (!current->assigned)
        {
            printf("Seat ID: %d\n", current->seatID);
            emptyFound = true;
        }
        current = current->next;
    }

    if (!emptyFound)
    {
        printf("No empty seats.\n");
    }
}


void clearInputBuffer() {  
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

void confirmSeatAssignment(PLANE* plane)
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    // Prompt user for passenger name
    printf("Enter passenger first name: ");
    scanf_s("%s", firstName, MAX_NAME_LENGTH);

    printf("Enter passenger last name: ");
    scanf_s("%s", lastName, MAX_NAME_LENGTH);

    // Search for the passenger in the seat list
    SEATNODE* current = plane->seats.head;
    bool found = false;

    // Ensure null-terminated strings
    firstName[sizeof(firstName) - 1] = '\0';
    lastName[sizeof(lastName) - 1] = '\0';

    while (current != NULL)
    {
        if (current->assigned && strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0)
        {
            // Passenger found
            printf("Passenger found!\n");

            // Display flight number from the selected plane
            printf("Flight: #%d, Seat ID: %d, Last Name: %s, First Name: %s\n",
                plane->selectedFlight, current->seatID, current->lastName, current->firstName);
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        printf("No passengers matching the provided name on Flight #%d.\n", plane->selectedFlight);
    }
}












