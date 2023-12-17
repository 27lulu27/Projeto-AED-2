#include <fstream>
#include <sstream>
#include "System.h"

System::System() {
    ifstream file("C:\\Users\\gluca\\Documents\\GitHub\\Projeto-AED-2\\data\\airlines.csv");
    string line;
    std::getline(file, line);
    while (getline(file, line)) {
        istringstream s(line);
        string code, name, callsign, country;
        char comma;
        if (s >> code && s >> comma && getline(s, name, ',') && getline(s, callsign, ',') && getline(s, country, ',')) {
            Airline airline(code, name, callsign, country);
            airlines.push_back(airline);
        }
    }
    cout << "Passou por aqui";
    file.close();
}
