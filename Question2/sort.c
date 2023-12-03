/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - creators.c

  Details
        -> bubble sort function
        -> creates a copy of linked list as to not mess with the original

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/

#include "creators.h"
#include "sort.h"

SEAT copySeat(SEAT seat)
{
    // Create a new seat with the same ID and passenger name as the original seat
    SEAT newSeat = createSeat(seat->seatID, seat->passengerFirstName, seat->passengerLastName);

    // Assign the ID of the original seat to the new seat
    newSeat->seatID = seat->seatID;
    return newSeat;
}

// Function to sort passengers on a given flight by their first or last name
void sortPassengers(FLIGHT flight, bool sortByFirstName)
{
    // Create a copy of the linked list of seats
    SEAT copiedSeats = NULL;
    SEAT lastCopiedSeat = NULL;
    for (SEAT currentSeat = flight->seats; currentSeat != NULL; currentSeat = currentSeat->nextSeat)
    {
        SEAT copiedSeat = copySeat(currentSeat);
        if (lastCopiedSeat == NULL)
        {
            copiedSeats = copiedSeat;
        }
        else
        {
            lastCopiedSeat->nextSeat = copiedSeat;
        }
        lastCopiedSeat = copiedSeat;
    }
    // Sort the copied linked list using bubble sort
    SEAT currentSeat, indexSeat;
    for (currentSeat = copiedSeats; currentSeat != NULL; currentSeat = currentSeat->nextSeat)
    {
        for (indexSeat = currentSeat->nextSeat; indexSeat != NULL; indexSeat = indexSeat->nextSeat)
        {
            char str1[MAXNAME], str2[MAXNAME];
            if (sortByFirstName)
            {
                strcpy(str1, currentSeat->passengerFirstName);
                strcpy(str2, indexSeat->passengerFirstName);
            }
            else
            {
                strcpy(str1, currentSeat->passengerLastName);
                strcpy(str2, indexSeat->passengerLastName);
            }
            // Convert the names to lower case for case-insensitive comparison
            for (int i = 0; str1[i]; i++) str1[i] = tolower(str1[i]);
            for (int i = 0; str2[i]; i++) str2[i] = tolower(str2[i]);

            // Swap names if they are in the wrong order
            if (strcmp(str1, str2) > 0)
            {
                SEAT temp = createSeat(currentSeat->seatID, currentSeat->passengerFirstName, currentSeat->passengerLastName);

                currentSeat->seatID = indexSeat->seatID;
                strcpy(currentSeat->passengerFirstName, indexSeat->passengerFirstName);
                strcpy(currentSeat->passengerLastName, indexSeat->passengerLastName);

                indexSeat->seatID = temp->seatID;
                strcpy(indexSeat->passengerFirstName, temp->passengerFirstName);
                strcpy(indexSeat->passengerLastName, temp->passengerLastName);

                free(temp);
            }
        }
    }
    // Print the sorted list of passengers
    printf("\n\t\t\tFlight %d\n", flight->flightID); 
    printf("\n\t\t First Name\t    Last Name\t\tSeat ID\n");
    for (currentSeat = copiedSeats; currentSeat != NULL; currentSeat = currentSeat->nextSeat)
    {
        // since all empty seats seats are empty strings they have a character count of 1
        // therefore if we exclude all strings of a length of 1 it only displays passengers with names 
        if (strlen(currentSeat->passengerFirstName) > 1 && strlen(currentSeat->passengerLastName) > 1)
        {
            //each tab is 8 characters long... so max name of 20 works out
            printf("Passenger Name |%-16s | %-16s|  Seat ID [%2d]\n", currentSeat->passengerFirstName, currentSeat->passengerLastName, currentSeat->seatID);
        }
    }
    // Free the memory allocated for the copied linked list
    while (copiedSeats != NULL)
    {
        SEAT nextSeat = copiedSeats->nextSeat;
        free(copiedSeats);
        copiedSeats = nextSeat;
    }
}