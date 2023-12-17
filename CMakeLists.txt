cmake_minimum_required(VERSION 3.26)
project(ProjetoAED2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetoAED2 src/main.cpp
        src/Airline.h
        src/Flight.h
        src/Airline.cpp
        src/Airport.cpp
        src/Flight.cpp
        src/Graph.h
        src/Graph.cpp
        src/System.h
        src/System.cpp
        src/Menu.h
        src/Menu.cpp
)
