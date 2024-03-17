#ifndef FEUP_DA_1_WATERSUPPLYMANAGER_H
#define FEUP_DA_1_WATERSUPPLYMANAGER_H


#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>

class WaterSupplyManager {
public:
    WaterSupplyManager(const Data &d);

    void maxFlowToCities();

    void demandCoverage();

    void pumpMaxFlow();

    void resetFlow();

private:
    std::unordered_map<std::string, WaterReservoir> reservoirs;
    std::unordered_map<std::string, PumpingStation> stations;
    std::unordered_map<std::string, DeliverySite> sites;
    Graph<std::string> graph;


};


#endif //FEUP_DA_1_WATERSUPPLYMANAGER_H
