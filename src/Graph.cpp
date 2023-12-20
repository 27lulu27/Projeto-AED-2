#include <queue>
#include "Graph.h"

Airport graph::FindAirport(const string code) const {
    for (Airport v : AirportSet){
        if(v.getCode() == code){
            return v;
        }
    }
    cout << "Not found";
    Airport V;
    return V;
}               //se nao encontrar retorna oq?

void graph::newAirport(const Airport a) {
    AirportSet.push_back(a);
}

void graph::addFlight(const string source, const string dest, Airline airline) {
    auto asource = FindAirport(source);
    asource.addFlight(airline, dest);
}

vector<Airport> graph::getairports() {
    return AirportSet;
}



std::vector<std::string> graph::bfs(Airport source, Airport dest) {
    vector<string> currentPath;
    queue<Airport> fila;
    bool empty = false;
    fila.push(source);
    while(!fila.empty()){
        if(empty){
            break;
        }
        Airport V = fila.front();
        currentPath.push_back(V.getCode());
        fila.pop();
        for(auto neighbor : V.getAdj()){
            auto W = neighbor.getTarget();
            if(W == dest.getCode()){
                empty = true;
                currentPath.push_back(W);
                break;
            }
            auto airp = FindAirport(W);
            if(!airp.isvisited()){
                fila.push(airp);
                airp.setvisited(true);
            }
        }
    }
    return currentPath;
}

std::vector<std::string> graph::quickestConnection(std::string source, std::string dest) {
    Airport startAirport = FindAirport(source);
    Airport destinationAirport = FindAirport(dest);

    markallnotvisited();
    auto shortestPath = bfs(startAirport,destinationAirport);

    if (shortestPath.empty()) {
        std::cout << "Não há conexão entre " << source << " e " << dest << std::endl;
    }

    return shortestPath;
}


void graph::markallnotvisited(){
    for(auto &a : AirportSet){
        a.setvisited(false);
    }
}