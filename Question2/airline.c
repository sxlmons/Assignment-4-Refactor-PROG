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


void initializeSeats(SEATLIST* seatList)
{
    // Initialize the linked list as empty
    seatList->head = NULL;     
    SEATNODE* current = NULL;   

    for (int i = 0; i < 12; ++i)
    {
        // Create a new seat node
        SEATNODE* newSeat = (SEATNODE*)malloc(sizeof(SEATNODE));   
        if (newSeat == NULL)  
        {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation error\n"); 

            // Free previously allocated nodes
            while (seatList->head != NULL)
            {
                current = seatList->head; 
                seatList->head = current->next; 
                free(current); 
            }

            exit(EXIT_FAILURE); 
        }

        newSeat->seatID = i + 1;
        newSeat->assigned = false;

        // Empty string for unassigned seats
        newSeat->firstName[0] = '\0';          
        newSeat->lastName[0] = '\0';
        newSeat->next = NULL;

        // Add the new seat to the linked list
        if (seatList->head == NULL) 
        {
            seatList->head = newSeat;
        }
        else 
        {
            SEATNODE* current = seatList->head;
            while (current->next != NULL) 
            {
                current = current->next;
            }
            current->next = newSeat;
        }
    }
}

// Helper function to compare seat nodes based on last names for sorting
int compareSeatNodes(const void* a, const void* b) {
    const SEATNODE* seatA = *(const SEATNODE**)a;
    const SEATNODE* seatB = *(const SEATNODE**)b;
    return strcmp(seatA->lastName, seatB->lastName);
}

void show_alphabetical_list_of_seats(SEATLIST* seatList) {
    // Count the number of seats in the list
    int seatCount = 0;
    SEATNODE* current = seatList->head;
    while (current != NULL) {
        seatCount++;
        current = current->next;
    }

    // Create an array of pointers to seat nodes
    SEATNODE** seatArray = malloc(seatCount * sizeof(SEATNODE*));
    if (seatArray == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    // Fill the array with seat nodes
    current = seatList->head;
    for (int i = 0; i < seatCount; i++) {
        seatArray[i] = current;
        current = current->next;
    }

    // Sort the array of seat nodes based on last names
    qsort(seatArray, seatCount, sizeof(SEATNODE*), compareSeatNodes);

    // Print the sorted list
    for (int i = 0; i < seatCount; i++) {
        printf("Seat ID: %d, Assigned: %s, Last Name: %s, First Name: %s\n",
            seatArray[i]->seatID,
            seatArray[i]->assigned ? "Yes" : "No",
            seatArray[i]->lastName,
            seatArray[i]->firstName);
    }

    // Free the allocated memory
    free(seatArray);
}

void assign_customer_to_seat(SEATLIST* seatList) {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int seatID;
    int planeNumber;
    int flightNumber; 

    printf("Enter plane number (1 or 2): ");
    scanf_s("%d", &planeNumber);
    getchar(); // eat newline

    if (planeNumber >= 1 && planeNumber <= NUM_PLANES)
    {
        PLANE* plane = &Planes[planeNumber - 1]; // Adjust the index

        // Explicitly ask the user to input the flight number
        printf("Enter flight number (102, 311, 444, 519): ");
        scanf_s("%d", &flightNumber);
        getchar(); // eat newline

        // Check if the entered flight number is valid
        if (flightNumber == 102 || flightNumber == 311 || flightNumber == 444 || flightNumber == 519)
        {
            SEATNODE* current = plane->seats.head;

            printf("Enter seat ID to assign (1-12): ");
            scanf_s("%d", &seatID);
            getchar(); // eat newline

            if (seatID >= 1 && seatID <= 12)
            {
                while (current != NULL && current->seatID != seatID)
                {
                    current = current->next;
                }

                if (current != NULL && !current->assigned)
                {
                    current->assigned = true;
                    strncpy(current->firstName, firstName, sizeof(current->firstName));
                    strncpy(current->lastName, lastName, sizeof(current->lastName));

                    printf("Seat successfully assigned!\n");
                }
                else
                {
                    printf("Invalid seat ID or seat already assigned.\n");
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
    else
    {
        printf("Invalid plane number.\n");
    }
}

void delete_seat_assignment(SEATLIST* seatList) 
{
    int seatID;
    int planeNumber;

    printf("Enter plane number (1 or 2): ");
    scanf_s("%d", &planeNumber);
    getchar(); // eat newline

    if (planeNumber >= 1 && planeNumber <= NUM_PLANES) 
    {
        PLANE* plane = &Planes[planeNumber - 1]; // Adjust the index
        SEATNODE* current = plane->seats.head;  

        printf("Enter seat ID to delete assignment (1-12): ");
        scanf_s("%d", &seatID);
        getchar(); // eat newline

        if (seatID >= 1 && seatID <= 12) 
        {
            while (current != NULL && current->seatID != seatID) 
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
                printf("Invalid seat ID or seat not assigned.\n");
            }
        }
        else 
        {
            printf("Invalid seat ID.\n");
        }
    }
    else 
    {
        printf("Invalid plane number.\n");
    }
}

void show_empty_seats(SEATLIST* seatList) 
{
    int emptySeatCount = 0;
    SEATNODE* current = seatList->head;

    while (current != NULL) 
    {
        if (!current->assigned) 
        {
            emptySeatCount++;
        }
        current = current->next;
    }

    printf("Number of empty seats: %d\n", emptySeatCount);
}

void show_list_of_empty_seats(SEATLIST* seatList) 
{
    SEATNODE* current = seatList->head;
    bool emptyFound = false;

    printf("List of empty seats:\n");

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

