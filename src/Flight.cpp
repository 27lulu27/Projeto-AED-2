#include "Flight.h"

Flight::Flight(){}

Flight::Flight(Airport source, Airport target, Airline airline):
               source(source), target(target), airline(airline){}


Airport Flight::getSource(){
    return source;
}

Airport Flight::getTarget(){
    return target;
}

Airline Flight::getAirline(){
    return airline;
}