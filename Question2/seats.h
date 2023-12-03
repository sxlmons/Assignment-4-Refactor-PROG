/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - seats.h

  Details
        ->  seat functions

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/
#pragma once

#include "creators.h"

void showEmptySeats(FLIGHT flight);

void numberOfEmptySeats(FLIGHT flight);

void assignSeat(FLIGHT flight);

void deleteSeat(FLIGHT flight);

void confirmSeat(FLIGHT flight);
