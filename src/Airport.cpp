#include "Airport.h"

Airport::Airport(){}

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude):
                 code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude){}


string Airport::getCode() const{
    return code;
}

string Airport::getName() const{
    return name;
}

string Airport::getCity() const{
    return city;
}

string Airport::getCountry() const{
    return country;
}

double Airport::getLatitude() const{
    return latitude;
}

double Airport::getLongitude() const{
    return longitude;
}