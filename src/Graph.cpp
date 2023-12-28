#include <queue>
#include <unordered_set>
#include <map>
#include <set>
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
    airportMap.emplace(a.getCode(), a);
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

int graph::reachabledestinationsmax(string code, int max, int num) {
    auto air = FindAirport(code);
    if(num == 1){
        return bfsairportnumber(air, max);
    }
    else if(num == 2){
        return bfscitiesnumber(air, max);
    }
    return bfscountrynumber(air, max);
}


int graph::bfsairportnumber(Airport source, int max) {
    vector<string> res;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return res.size();
}

int graph::bfscitiesnumber(Airport source, int max) {
    vector<string> res;
    set<string> cities;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            cities.insert(currentairp.getCity());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return cities.size();
}

int graph::bfscountrynumber(Airport source, int max) {
    vector<string> res;
    set<string> countries;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            countries.insert(currentairp.getCountry());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return countries.size();
}

pair<int, pair<string, string>> graph::maximumtrip() {
    int maxDiameter = 0;
    pair<string, string> maxDiameterVertices;

    for (const auto& entry : airportMap) {
        const string& startCode = entry.first;
        pair<int, string> currentDiameter = bfsmax(startCode);
        if (currentDiameter.first > maxDiameter) {
            maxDiameter = currentDiameter.first;
            maxDiameterVertices = {startCode, currentDiameter.second};
        }
    }

    return {maxDiameter, maxDiameterVertices};
}

pair<int , string> graph::bfsmax(const string& startCode) {
    queue<pair<int, string>> q;  // Pares (distância, vértice)
    unordered_map<string, int> distances;  // Armazena as distâncias mínimas para cada vértice

    q.push({0, startCode});
    distances[startCode] = 0;

    pair<int, string> maxDistanceVertex = {0, startCode};

    while (!q.empty()) {
        auto currentPair = q.front();
        q.pop();

        int currentDistance = currentPair.first;
        const string& currentCode = currentPair.second;

        if (currentDistance > maxDistanceVertex.first) {
            maxDistanceVertex = {currentDistance, currentCode};
        }

        const auto& currentAirport = airportMap[currentCode];
        for ( auto neighborCode : currentAirport.getAdj()) {
            auto i = FindAirport(neighborCode.getTarget());
            if (!i.isvisited()) {
                distances[i.getCode()] = currentDistance + 1;
                q.push({currentDistance + 1, i.getCode()});
            }
        }
    }

    return maxDistanceVertex;
}


vector<Airport> graph::topairports(int k) {
    markallnotvisited();
    vector<Airport> res;
    for(int i = 1; i <= k; i++){
        auto maxElement = std::max_element(
                AirportSet.begin(),
                AirportSet.end(),
                [](Airport a,  Airport b) {
                    // Ordena com base no número de voos, mas aeroportos não visitados têm prioridade
                    if (a.isvisited() != b.isvisited()) {
                        return a.isvisited() > b.isvisited();
                    } else {
                        return a.getNumberOfFlights() < b.getNumberOfFlights();
                    }
                }
        );
    maxElement->setvisited(true);
    res.push_back(*maxElement);
    }
    return res;
}


int graph::essentialairports() {
    markallnotvisited();
    int articulationPointsCount = 0;
    for (auto& airport : AirportSet) {
        if (!airport.isvisited()) {
            BFSArticulationPoints(airport, articulationPointsCount);
            break;
        }
    }
    return articulationPointsCount;
}

void graph::BFSArticulationPoints( Airport& startAirport, int& articulationPointsCount) {
    startAirport.setvisited(true);
    std::queue<string> q;  // Usar ponteiros para evitar cópias desnecessárias
    std::unordered_map<std::string, int> num;
    std::unordered_map<std::string, int> low;
    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, std::string> parent;

    // Inicialize as estruturas de dados
    num[startAirport.getCode()] = 0;
    low[startAirport.getCode()] = 0;
    visited[startAirport.getCode()] = true;
    q.push(startAirport.getCode());

    while (!q.empty()) {
        const std::string& currentCode = q.front();
        q.pop();
        Airport currentAirport = FindAirport(currentCode);

        for ( auto& flight : currentAirport.getAdj()) {
            const std::string& neighborCode = flight.getTarget();
            if (!visited[neighborCode]) {
                // Tree Edge
                visited[neighborCode] = true;
                num[neighborCode] = low[neighborCode] = num[currentCode] + 1;
                parent[neighborCode] = currentCode;
                q.push(neighborCode);

                // Lógica para verificar se o vértice atual é um ponto de articulação
                if (parent.find(currentAirport.getCode()) != parent.end() && low[neighborCode] >= num[currentAirport.getCode()]) {
                    currentAirport.setvisited(true);
                    articulationPointsCount++;
                }
            }
        }
    }
}



vector<pair<Airport, double>> graph::ClosestAirport(double lat, double lon) {
    const double earthRadius = 6371.0; // Earth radius in kilometers

    std::vector<pair<Airport,double>> closestAirports;
    double minDistance = std::numeric_limits<double>::max();

    for (const auto &airport : AirportSet) {
        double deltaLat = airport.getLatitude() - lat;
        double deltaLon = airport.getLongitude() - lon;

        double distance = earthRadius * 2.0 * asin(sqrt(
                pow(sin(deltaLat / 2.0), 2.0) + cos(lat) * cos(airport.getLatitude()) * pow(sin(deltaLon / 2.0), 2.0)
        ));

        if (distance < minDistance) {
            minDistance = distance;
            closestAirports.clear();
            closestAirports.push_back({airport,distance});
        }
    }

    return closestAirports;
}



