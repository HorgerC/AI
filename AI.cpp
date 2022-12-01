/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <Chris Horger, Ella Coulter, Isabella Vong, Keith Wu>
 * <horgerc, emcoult, isvong, keithwu>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

int store_urgent = 0;
/*
double Floor_Param_Eval(int floor, BuildingState state) {
    double heuristic = 0;
    int num_anger = 0;
    int max_anger = 0;

    for (int i = 0; i < state.floors[floor].numPeople; i++) {
        num_anger += state.floors[floor].people[i].angerLevel;
    }

    for (int i = 0; i < state.floors[floor].numPeople; i++) {
        if (state.floors[floor].people[i].angerLevel >= 8) {
            max_anger = state.floors[floor].people[i].angerLevel;
        }
    }
    heuristic = (0.4 * num_anger + 0.6 * state.floors[floor].numPeople);

    return heuristic;
}

int Floors_Eval(BuildingState state) {
    int most_urgent = 0;
    int most_urgent_val = Floor_Param_Eval(0, state);
    for (int i = 1; i < NUM_FLOORS; i++) {
        if (most_urgent_val < Floor_Param_Eval(i, state)) {
            most_urgent_val = Floor_Param_Eval(i, state);
            most_urgent = i;
        }
    }

    store_urgent = most_urgent;

    return most_urgent;
}

string elevator_avail(BuildingState state) {
    string returnstring = "";
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (!state.elevators[i].isServicing) {
            returnstring.append(to_string(i + 1));
        }
    }
    return returnstring;
}
 */
BuildingState buildingState;
BuildingState state = buildingState;
//int temp_urgent_floor = Floors_Eval(buildingState);
//string temp_urgent = to_string(temp_urgent_floor);

string getAIMoveString(const BuildingState& buildingState) {
    //string elevator_string = elevator_avail(buildingState);
    string return_string;
    //int filler = Floors_Eval(buildingState);

    int urgent_floor = store_urgent;
    string urgent = to_string(store_urgent);

    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (urgent_floor != buildingState.elevators[i].currentFloor
                        && !buildingState.elevators[i].isServicing) {
            return_string.push_back('e');
            return_string.append(to_string(i));
            return_string.push_back('f');
            return_string.append(urgent);
            return return_string;
        }
        else if ((urgent_floor == buildingState.elevators[i].currentFloor) 
                              && (buildingState.floors[urgent_floor].numPeople > 0) 
                              && (!buildingState.elevators[i].isServicing)) {
            return_string.push_back('e');
            return_string.append(to_string(i));
            return_string.push_back('p');
            return return_string;
        }
    }

    if (state.elevators[0].isServicing && state.elevators[1].isServicing && state.elevators[2].isServicing) {
        return "";
    }
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
    const Floor& floorToPickup) {

    string pickupListUp = "";
    string pickupListDown = "";

    int numGoingUp = 0;
    int numGoingDown = 0;

    //calculate people going up / down, and anger level 
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() 
          > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
            numGoingUp++;
            pickupListUp += to_string(i);
        }
        else {
            numGoingDown++;
            pickupListDown += to_string(i);
        }
    }

    //calculate who to take (up or down people)
    if ((numGoingUp >= numGoingDown)) {
        return pickupListUp;
    }
    else {
        return pickupListDown;
    }
    }