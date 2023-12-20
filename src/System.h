
#ifndef PROJETOAED2_SYSTEM_H
#define PROJETOAED2_SYSTEM_H
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "Graph.h"
#include <iostream>
#include <unordered_map>

using namespace std;
class System{
private:
    graph g;
    unordered_map<std::string, Airport> airportsMap;        //usado para facilitar o parsing
    unordered_map<std::string, Airline> airlinesMap;
public:
    System();

    void readAirlines(const string &filename);

    void readAirports(const string &filename);

    void readFlights(const string &filename);

    void FastConnection(const string& source, const string& dest);

    void showgraph();
};
#endif //PROJETOAED2_SYSTEM_H
