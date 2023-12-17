//
// Created by gluca on 17/12/2023.
//

#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H
#include "Airport.h"
#include <vector>
class graph{
private:
    vector<Airport> AirportSet;
public:
Airport FindAirport(const string code) const;
void newAirport(const Airport a);
void addFlight(const string source, const string dest, Airline airline);
vector<Airport> getairports();
vector<string> quickestconnection(string source, string dest);
vector<string> dfs(Airport source, Airport dest, vector<string> airportscodes) ;
void markallnotvisited();
};
#endif //PROJETOAED2_GRAPH_H
