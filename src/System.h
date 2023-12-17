
#ifndef PROJETOAED2_SYSTEM_H
#define PROJETOAED2_SYSTEM_H
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "Graph.h"
#include <iostream>
using namespace std;
class System{
private:
    graph g;
    vector<Airline> airlines;
public:
    System();
};
#endif //PROJETOAED2_SYSTEM_H
