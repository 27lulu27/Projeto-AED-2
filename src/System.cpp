#include <fstream>
#include <sstream>
#include "System.h"

System::System() {
    readAirlines("C:\\Users\\gluca\\Documents\\GitHub\\Projeto-AED-2\\data\\airlines.csv");
    readAirports("C:\\Users\\gluca\\Documents\\GitHub\\Projeto-AED-2\\data\\airports.csv");
    readFlights("C:\\Users\\gluca\\Documents\\GitHub\\Projeto-AED-2\\data\\flights.csv");
}

Airline System::findAirline(const string& code) const {
    for (const auto& a : airlines) {
        if (a.getCode() == code) {
            return a;
        }
    }
    return Airline();
}

void System::readAirlines(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    while (getline(file, line)) {
        istringstream s(line);
        string code, name, callsign, country;
        char comma;
        if (getline(s, code, ',') && getline(s, name, ',') && getline(s, callsign, ',') && getline(s, country, ',')) {
            Airline airline(code, name, callsign, country);
            airlines.push_back(airline);
        }
    }

    file.close();
}

void System::readAirports(const std::string& filename) {
    ifstream file2(filename);
    string line;
    std::getline(file2, line); // Ignora a primeira linha (cabeçalho)

    while (getline(file2, line)) {
        istringstream s(line);
        string code, name, city, country;
        double latitude, longitude;
        char comma;
        if (getline(s, code, ',') && getline(s, name, ',') && getline(s, city, ',') && getline(s, country, ',') &&
            s >> latitude >> comma && s >> longitude) {
            Airport airport(code, name, city, country, latitude, longitude);
            g.newAirport(airport);
        }
    }

    file2.close();
}

void System::readFlights(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    while (getline(file, line)) {
        istringstream s(line);
        string source, target, airlineCode;
        char comma;
        if (getline(s,source, ',') && getline(s, target, ',') && getline(s, airlineCode, ',')) {
                for (auto& airport : g.getairports()) {
                    if (airport.getCode() == source) {
                        airport.addFlight(findAirline(airlineCode), target);
                    }
                }
            }
        }
    file.close();
}

void System::Fastconection(string source, string dest) {
    g.quickestconnection(source, dest);
}


