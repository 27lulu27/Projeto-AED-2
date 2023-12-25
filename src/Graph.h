#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H
#include "Airport.h"
#include <vector>
#include <algorithm>
#include <cctype>
class graph{
private:
    vector<Airport> AirportSet;
public:
Airport FindAirport(const string code) const;
void newAirport(const Airport a);
void addFlight(const string source, const string dest, Airline airline);
vector<Airport> getairports();
vector<vector<string>> quickestConnection(std::string source, std::string dest);
vector<vector<string>> bfs(Airport source, Airport dest);
void markallnotvisited();
vector<pair<string, vector<vector<string>>>> quickestConnectionCity(string  source, string dest);
vector<Airport> FindAirportviaCity(const std::string city) const;
void NumberofFofAir(string code);
int NumberofFofCity(string city);
int NumberofFofAirline(string code);
int NumberofDContriesairport(string code);
int NumberofDContriescity(std::string city);
int avaliabledestinations(string code, int num);
};
#endif //PROJETOAED2_GRAPH_H
