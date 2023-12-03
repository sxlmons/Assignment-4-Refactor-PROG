/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - creators.c

  Details
        -> initializers of plane, flights, seats
        -> get flight function

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/

#include "creators.h"

// Function to create a new Seat node
SEAT createSeat(int seatID, const char* firstName, const char* lastName)
{
    // Allocate memory for a new Seat node
    SEAT newSeat = (SEAT)malloc(sizeof(struct Seat));
    if (newSeat != NULL)
    {
        // Initialize the fields of the new Seat node
        newSeat->seatID = seatID;
        strcpy(newSeat->passengerFirstName, firstName);
        strcpy(newSeat->passengerLastName, lastName);
        newSeat->isAssigned = false;
        newSeat->nextSeat = NULL;
    }
    // Return the new Seat node
    return newSeat;
}


FLIGHT createFlight(int flightID)
{
    // Allocate memory for a new Flight node
    FLIGHT newFlight = (FLIGHT)malloc(sizeof(struct Flight));
    if (newFlight != NULL)
    {
        // Initialize the fields of the new Flight node
        newFlight->flightID = flightID;
        newFlight->nextFlight = NULL;
        newFlight->seats = NULL;  // Initialize seats to NULL

        // Create 12 seats for the flight
        for (int i = 0; i < 12; i++)
        {
            // Create a new seat with ID i + 1 and empty string for passenger name
            SEAT newSeat = createSeat(i + 1, "", "");

            // Add the new seat to the beginning of the seats list
            newSeat->nextSeat = newFlight->seats;
            newFlight->seats = newSeat;
        }
    }
    // Return the new Flight node
    return newFlight;
}

// Function to create a new Plane node
PLANE createPlane(int planeID, int* flightIDs, int numFlights)
{
    // Allocate memory for a new Plane node
    PLANE newPlane = (PLANE)malloc(sizeof(struct Plane));
    if (newPlane != NULL)
    {
        // Initialize the fields of the new Plane node
        newPlane->planeID = planeID;
        newPlane->flights = NULL;
        newPlane->nextPlane = NULL;

        FLIGHT lastFlight = NULL;
        // Create flights for the plane
        for (int i = 0; i < numFlights; i++)
        {
            // Create a new flight with ID from flightIDs array
            FLIGHT newFlight = createFlight(flightIDs[i]);

            // If this is the first flight in the list
            if (lastFlight == NULL)
            {
                newPlane->flights = newFlight;
            }
            // If this is not the first flight in the list
            else
            {
                lastFlight->nextFlight = newFlight;
            }
            lastFlight = newFlight;
        }
    }
    // Return the new Plane node
    return newPlane;
}

// Function to get a flight with a given number from a plane
FLIGHT getFlight(PLANE plane, int flightNumber)
{
    // Initialize currentFlight to the head of the flights list
    FLIGHT currentFlight = plane->flights;
    while (currentFlight != NULL)
    {
        // If the current flight's ID matches the given flight number
        if (currentFlight->flightID == flightNumber)
        {
            return currentFlight;
        }
        // Move to the next flight in the list
        currentFlight = currentFlight->nextFlight;
    }
    // If no flight with the given number is found, return NULL
    return NULL;
}












