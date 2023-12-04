#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include "Airline.h"
#include "Airport.h"
using namespace std;

class Flight{
    private:
        Airport source, target;
        Airline airline;
    public:
        Flight();
        Flight(Airport source, Airport target, Airline airline);
        Airport getSource();
        Airport getTarget();
        Airline getAirline();
};

#endif