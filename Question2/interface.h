/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - interface.h

  Details
        -> menus condensed into prototypes

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/
#pragma once

#include "creators.h"
#include "sort.h"
#include "seats.h"

#include <stdio.h> 

void flightSelectionMenu();
void SeatManagementMenu();
void sortPassengersMenu(PLANE plane, int flightNumber);
void SeatManagementInterface(PLANE plane, int flightNumber);