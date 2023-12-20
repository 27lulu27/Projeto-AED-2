#include <fstream>
#include <sstream>
#include "System.h"

System::System() {
    readAirlines("C:\\Users\\gluca\\Projeto-AED-2\\data\\airlines.csv");
    readAirports("C:\\Users\\gluca\\Projeto-AED-2\\data\\airports.csv");
    readFlights("C:\\Users\\gluca\\Projeto-AED-2\\data\\flights.csv");
}

void System::readAirlines(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream s(line);
        string code, name, callsign, country;
        if (getline(s, code, ',') && getline(s, name, ',') && getline(s, callsign, ',') && getline(s, country, ',')) {
            Airline airline(code, name, callsign, country);
            airlinesMap[code] = airline;
        }
    }

    file.close();
}

void System::readAirports(const std::string& filename) {
    ifstream file2(filename);
    string line;
    std::getline(file2, line); // Ignora a primeira linha (cabeçalho)
    if (!file2.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }

    while (getline(file2, line)) {
        istringstream s(line);
        string code, name, city, country;
        double latitude, longitude;
        char comma;
        if (getline(s, code, ',') && getline(s, name, ',') && getline(s, city, ',') && getline(s, country, ',') &&
            s >> latitude >> comma && s >> longitude) {
            Airport airport(code, name, city, country, latitude, longitude);
            airportsMap[code] = airport;
        }
    }

    file2.close();
}

void System::readFlights(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        string source, target, airlineCode;
        if (getline(s,source, ',') && getline(s, target, ',') && getline(s, airlineCode, ',')) {
            auto airportIt = airportsMap.find(source);
            if (airportIt != airportsMap.end()) {
                auto airlineIt = airlinesMap.find(airlineCode);
                if (airlineIt != airlinesMap.end()) {
                    airportIt->second.addFlight(airlineIt->second, target);

                 }
                }
            }
        }
    for(auto i : airportsMap){
        g.newAirport(i.second);
    }
    file.close();
}

void System::FastConnection(const std::string& source, const std::string& dest) {
    auto result = g.quickestConnection(source, dest);

    if (!result.empty()) {
        std::cout << "Caminho mais curto: ";
        for (auto it = result.begin(); it != result.end(); ++it) {
            if (it != result.begin()) {
                std::cout << " -> ";
            }
            std::cout << *it;
        }
        std::cout << std::endl;
    }
}


