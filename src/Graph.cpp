#include <queue>
#include <unordered_set>
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