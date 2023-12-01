/* 
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 - Question #2 - airline.h

  Revision History

  1.0      2023 - Nov - 10          initial
  1.1	   2023 - Nov - 25			 refactor

*/
#pragma once

#include <stdbool.h>

#define MAX_NAME_LENGTH 25
#define NUM_PLANES      2
#define NUM_FLIGHTS     4

// Define a seat node
typedef struct SeatNode {
    int seatID;
    int flightNumber;  // Added a flightNumber field
    bool assigned;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    struct SeatNode* next;
} SEATNODE;

// Define a linked list of seats for a plane
typedef struct SeatList {
    // Pointer to the first seat in the linked list
    SEATNODE* head;
} SEATLIST;

// Define a plane structure that contains a linked list of seats
typedef struct Plane {
    int selectedFlight;  // Selected flight number for the plane
    SEATLIST seats;
} PLANE;

// Array of planes
extern PLANE Planes[NUM_PLANES];

// Flight numbers
extern int flightNumbers[NUM_FLIGHTS];

// Function prototypes
void initializeSeats(PLANE* plane, int flightNumber);  

void numberOfEmptySeatsByFlight(PLANE* plane); 

void showEmptySeatsByFlight(PLANE* plane);

void deleteSeatAssignment(PLANE* plane);  // Modified prototype

void assignCustomerToSeat(PLANE* plane);  // Modified prototype 

void showAlphabeticalListOfSeats(PLANE* plane);  // Modified prototype

void confirmSeatAssignment(PLANE* plane);  // Modified prototype

void clearInputBuffer();

bool isValidFlightNumber(int flightNumber);  
