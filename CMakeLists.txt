cmake_minimum_required(VERSION 3.23)
project(feup_DA_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(feup_DA_1 main.cpp
        Classes/Data.cpp
        Classes/Data.h
        Classes/WaterReservoir.cpp
        Classes/WaterReservoir.h
        Classes/PumpingStation.cpp
        Classes/PumpingStation.h
        Classes/DeliverySite.cpp
        Classes/DeliverySite.h
        Classes/Graph.h
        Classes/Menu.cpp
        Classes/Menu.h
        Classes/WaterSupplyManager.cpp
        Classes/WaterSupplyManager.h)
