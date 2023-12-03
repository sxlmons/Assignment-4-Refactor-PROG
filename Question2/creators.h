/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - creators.h

  Details
        -> initializers of plane, flights, seats
        -> get flight function

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define MAXNAME             20
#define MAXNAME_REDUCED     15 //needed a buffer, or else werid stuff happens 
#define MAX_SEATS           12
#define MIN_SEATS           1
#define MAX_FLIGHTS         4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Define structures for Plane, Flight, and Seat
typedef struct Seat {
    int seatID;
    char passengerFirstName[MAXNAME];
    char passengerLastName[MAXNAME];
    bool isAssigned;
    struct Seat* nextSeat;
}*SEAT;

typedef struct Flight {
    int flightID;
    SEAT seats;  // Head of the linked list of seats
    struct Flight* nextFlight;
}*FLIGHT;

typedef struct Plane {
    int planeID;
    FLIGHT flights;  // Head of the linked list of flights 
    struct Plane* nextPlane;
}*PLANE;

SEAT createSeat(int seatID, const char* firstName, const char* lastName);

FLIGHT createFlight(int flightID);

PLANE createPlane(int planeID, int* flightIDs, int numFlights);

FLIGHT getFlight(PLANE plane, int flightNumber);
