#ifndef _AIRPORT_H
#define _AIRPORT_H

#include <iostream>
#include <list>
#include <vector>
#include "Flight.h"

class Flight;

using namespace std;

class Airport{
    private:
        string code, name, city, country;
        double latitude, longitude;
        bool visited;
        int numberofflights = 0;
public:
        vector<Flight> adj;
        Airport();
        Airport(string code, string name, string city, string country, double latitude, double longitude);
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLatitude() const;
        double getLongitude() const;
        vector<Flight> getAdj() const;
        void addFlight(Airline airline, string target);
        void setvisited(const bool v);
        bool isvisited();
        int getNumberOfFlights();
};

#endif
