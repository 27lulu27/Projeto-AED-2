#include "Graph.h"


Airport graph::FindAirport(const string code) const {
    for (Airport v : AirportSet){
        if(v.getCode() == code){
            return v;
        }
    }
}

void graph::newAirport(const Airport a) {
    AirportSet.push_back(a);
}

void graph::addFlight(const string source, const string dest, Airline airline) {
    auto asource = FindAirport(source);
    asource.addFlight(airline, dest);
}
