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

vector<Airport> graph::getairports() {
    return AirportSet;
}




vector<string> graph::dfs(Airport source, Airport dest, vector<string> airportscodes) {
    source.setvisited(true);
    airportscodes.push_back(source.getCode());
    for(auto i =  source.getAdj().begin(); i != source.getAdj().end(); i++){
        auto v = i->getTarget();
        auto airp = FindAirport(v);
        if(!airp.isvisited()){
            dfs(airp, dest, airportscodes);
        }
        if(airp.getCode() == dest.getCode()){
            return airportscodes;
        }
    }
}

vector<string> graph::quickestconnection(string source, string dest) {
    vector<string> airportscodes;
    auto s = FindAirport(source);
    auto d = FindAirport(dest);
    for(auto a : s.getAdj()){
       if( a.getTarget() == dest){
           airportscodes.push_back(dest);
           return airportscodes;  //se o vetor estiver que tem conecção direta enrte os aeroportos
       }
    }
    markallnotvisited();
    dfs(s, d, airportscodes);
    if (airportscodes.empty()) {
        cout << "Não há conexão entre " << source << " e " << dest << endl;
    }
    return airportscodes;
}

void graph::markallnotvisited(){
    for(auto a : AirportSet){
        a.setvisited(false);
    }
}