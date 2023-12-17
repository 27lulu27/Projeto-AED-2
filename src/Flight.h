#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include "Airline.h"
using namespace std;

class Flight{
    private:
        string target;
        Airline airline;
    public:
        Flight(Airline airline, string target);
        string getTarget();
        Airline getAirline();
};

#endif