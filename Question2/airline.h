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
    bool assigned;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    // Pointer to the next seat in the linked list
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
void initializeSeats(SEATLIST* seatList);

void show_empty_seats(SEATLIST* seatList);

void show_list_of_empty_seats(SEATLIST* seatList);

void delete_seat_assignment(SEATLIST* seatList);

void assign_customer_to_seat(SEATLIST* seatList);

void show_alphabetical_list_of_seats(SEATLIST* seatList);

void clearInputBuffer(); 
