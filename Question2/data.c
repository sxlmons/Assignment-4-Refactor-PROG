/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - data.c

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/

#include "creators.h"
#include "data.h"

// Function to save the data of a plane to a file
void saveData(PLANE plane, const char* filename)
{
    // Open the file for writing
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Unable to open file for writing.\n");
        return;
    }

    // Initialize flight to the head of the flights list
    FLIGHT flight = plane->flights;

    // Loop through the flights in the plane
    while (flight != NULL)
    {
        // Initialize seat to the head of the seats list
        SEAT seat = flight->seats;
        // Initialize seat to the head of the seats list
        while (seat != NULL)
        {
            // Only save the seat if it is assigned
            if (seat->isAssigned)
            {
                // Check if fprintf successfully wrote the data
                if (fprintf(file, "%d %d %s %s %d\n", flight->flightID, seat->seatID, seat->passengerFirstName, seat->passengerLastName, seat->isAssigned) < 0)
                {
                    printf("Error writing to file.\n");
                    fclose(file);
                    return;
                }
            }
            // Move to the next seat in the list
            seat = seat->nextSeat;
        }
        // Move to the next flight in the list
        flight = flight->nextFlight;
    }

    if (fclose(file) != 0)
    {
        printf("Error closing file.\n");
    }
}

// Function to load the data of a plane from a file
void loadData(PLANE plane, const char* filename)
{
    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open file for reading.\n");
        return;
    }

    // Declare variables for flight ID, seat ID, assignment status, and passenger name
    int flightID, seatID, isAssigned;
    char firstName[MAXNAME], lastName[MAXNAME];

    // Loop until the end of the file is reached
    while (!feof(file))
    {
        // Read the flight ID, seat ID, passenger name, and assignment status from the file
        if (fscanf(file, "%d", &flightID) != 1)
            break;
        if (fscanf(file, "%d", &seatID) != 1)
            break;
        if (fscanf(file, "%s", firstName) != 1)
            break;
        if (fscanf(file, "%s", lastName) != 1)
            break;
        if (fscanf(file, "%d", &isAssigned) != 1)
            break;

        // Ensure strings are null-terminated
        firstName[MAXNAME - 1] = NULL;
        lastName[MAXNAME - 1] = NULL;

        // Get the flight with the read flight ID
        FLIGHT flight = getFlight(plane, flightID);
        if (flight != NULL)
        {
            // Initialize seat to the head of the seats list
            SEAT seat = flight->seats;
            while (seat != NULL)
            {
                // If the current seat's ID matches the read seat ID
                if (seat->seatID == seatID)
                {
                    // Copy the passenger name and assignment status to the seat
                    strncpy(seat->passengerFirstName, firstName, MAXNAME - 1);
                    seat->passengerFirstName[MAXNAME - 1] = '\0';
                    strncpy(seat->passengerLastName, lastName, MAXNAME - 1);
                    seat->passengerLastName[MAXNAME - 1] = '\0';

                    seat->isAssigned = isAssigned;
                    break;
                }
                // Move to the next seat in the list
                seat = seat->nextSeat;
            }
        }
    }
    // If there was an error reading from the file
    if (ferror(file))
    {
        printf("Error reading from file.\n");
    }

    fclose(file);
}

// Function to free the memory allocated for a Plane node and its associated Flight and Seat nodes
void freePlane(PLANE plane)
{
    // Initialize flight to the head of the flights list
    FLIGHT flight = plane->flights;
    while (flight != NULL)
    {
        // Initialize seat to the head of the seats list
        SEAT seat = flight->seats;
        while (seat != NULL)
        {
            // Store the next seat in the list
            SEAT nextSeat = seat->nextSeat;

            free(seat);

            // Move to the next seat in the list
            seat = nextSeat;
        }
        // Store the next flight in the list
        FLIGHT nextFlight = flight->nextFlight;

        free(flight);

        // Move to the next flight in the list
        flight = nextFlight;
    }
    free(plane);
}
