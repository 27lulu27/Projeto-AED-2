#ifndef _AIRPORT_H
#define _AIRPORT_H

#include <iostream>
#include <list>
using namespace std;

class Airport{
    private:
        string code, name, city, country;
        double latitude, longitude;
    public:
        Airport();
        Airport(string code, string name, string city, string country, double latitude, double longitude);
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLatitude() const;
        double getLongitude() const;
};

#endif
