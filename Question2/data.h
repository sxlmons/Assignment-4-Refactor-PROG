/*
  PROG71985 - F23 - Nov 2023 - Joshua Salmons

  Assignment #4 refactor - Question #2 - data.h

  Details
        -> save/load functionality
        -> free memory from plane

  Revision History

        1.0      2023 Nov 10          initial
        1.1		 2023 Nov 25		  refactor
        1.2      2023 Nov 28->Dec 3   refactor2

*/
#pragma once

#include "creators.h"   

void saveData(PLANE plane, const char* filename);
void loadData(PLANE plane, const char* filename);
void freePlane(PLANE plane);