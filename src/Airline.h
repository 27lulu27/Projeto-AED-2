#ifndef AIRLINE_H
#define AIRLINE_H

#include <iostream>
#include <string>
using namespace std;

class Airline{
    private:
        string code, name, callsign, country;
    public:
        Airline();
        Airline(string code, string name, string callsign, string country);
        string getCode() const;
        string getName() const;
        string getCallsign() const;
        string getCountry() const;
};

#endif
