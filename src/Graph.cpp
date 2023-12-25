#include <queue>
#include <unordered_set>
#include <map>
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

vector<Airport> graph::FindAirportviaCity(const std::string city) const {
    vector<Airport> airportsinacity;
    for (const Airport& V : AirportSet) {
        if (V.getCity() == city) {
            airportsinacity.push_back(V);
        }
    }
    return airportsinacity;
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



vector<vector<string>> graph::bfs(Airport source, Airport dest) {
    vector<vector<string>> allPaths;  // Lista para armazenar todos os caminhos
    queue<vector<string>> q;  // Fila para processar caminhos
    unordered_set<string> visitedAirports;  // Conjunto para armazenar aeroportos visitados

    q.push({source.getCode()});  // Inicializa a fila com um caminho contendo o aeroporto de origem
    visitedAirports.insert(source.getCode());  // Marca o aeroporto de origem como visitado

    while (!q.empty()) {
        vector<string> currentPath = q.front();  // Obtém o próximo caminho da fila
        q.pop();

        string currentAirportCode = currentPath.back();  // Obtém o código do último aeroporto no caminho
        if (currentAirportCode == dest.getCode()) {
            allPaths.push_back(currentPath);  // Se chegou ao destino, adiciona o caminho à lista
            continue;  // Continua para explorar outros caminhos
        }
        Airport currentAirport = FindAirport(currentAirportCode);
        for (auto neighbor : currentAirport.getAdj()) {
            auto neighborCode = neighbor.getTarget();
            if (visitedAirports.find(neighborCode) == visitedAirports.end()) {
                visitedAirports.insert(neighborCode);  // Marca o aeroporto vizinho como visitado
                vector<string> newPath = currentPath;  // Cria um novo caminho baseado no caminho atual
                newPath.push_back(neighborCode);  // Adiciona o aeroporto vizinho ao novo caminho
                q.push(newPath);  // Adiciona o novo caminho à fila para processamento futuro
            }
        }
    }
    return allPaths;  // Retorna a lista de todos os caminhos encontrados
}


std::vector<vector<string>> graph::quickestConnection(std::string source, std::string dest) {
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

vector<pair<string, vector<vector<string>>>> graph::quickestConnectionCity(string citysource, string citydest) {
    vector<pair<string, vector<vector<string>>>> airports;
    vector<Airport> start = FindAirportviaCity(citysource); // Aeroportos da cidade de origem
    vector<Airport> dest = FindAirportviaCity(citydest);    // Aeroportos da cidade de destino
    for (auto i : start) {  // Para cada aeroporto da cidade de origem
        for (auto j : dest) {  // Para cada aeroporto da cidade de destino
            markallnotvisited();
            string newpair = "Aeroport of "+ citysource + ":" + i.getName() + " " + "Aeroport of " + citydest+ ":"  + j.getName();
            vector<vector<string>> paths = bfs(i, j);
            airports.push_back(make_pair(newpair, paths));  // Adiciona ao vetor 'airports' os caminhos entre os dois aeroportos
        }
    }
    if (airports.empty()) {
        std::cout << "Não há conexão entre " << citysource << " e " << citydest << std::endl;
    }
    return airports;
}

void graph::NumberofFofAir(string code) {
    int numberofflights = 0;
    map<string, int> airlinesMap;

    Airport airport = FindAirport(code);

    for(auto flight : airport.getAdj()) {
        numberofflights++;
        airlinesMap[flight.getAirline().getCode()]++;
    }

    cout << "The Airport " << code << " has " << numberofflights << " flights from " << airlinesMap.size() << " different airlines." << endl;
}

int graph::NumberofFofCity(string city) {
    int num = 0;
    for(auto i : AirportSet){
        if(i.getCity() == city){
            num += i.getAdj().size();
        }
    }
    return num;
}

int graph::NumberofFofAirline(string code) {
    int num = 0;
    for(auto i : AirportSet){
        for(auto j : i.getAdj()){
            if(j.getAirline().getCode() == code){
                num++;
            }
        }
    }
    return num;
}

int graph::NumberofDContriesairport(string code){
    auto air = FindAirport(code);
    map<string, int> countries;
    for(auto i : air.getAdj()){
        auto dest = FindAirport(i.getTarget());
        countries[dest.getCountry()]++;
    }
    return countries.size();
}

int graph::NumberofDContriescity(std::string city) {
    auto air = FindAirportviaCity(city);
    map<string, int> countries;
    for(auto i : air){
       for(auto j : i.getAdj()){
           auto dest = FindAirport(j.getTarget());
           countries[dest.getCountry()]++;
       }
    }
    return countries.size();
}

int graph::avaliabledestinations(string code, int num) {
    auto air = FindAirport(code);
    map<string, int> airports;
    if(num == 1){
        for(auto i : air.getAdj()){
            auto dest = FindAirport(i.getTarget());
            airports[dest.getCode()]++;
        }
        return airports.size();
    }
    else if(num == 2){
        for(auto i : air.getAdj()){
            auto dest = FindAirport(i.getTarget());
            airports[dest.getCity()]++;
        }
        return airports.size();
    }
    for(auto i : air.getAdj()){
        auto dest = FindAirport(i.getTarget());
        airports[dest.getCountry()]++;
    }
    return airports.size();
}
