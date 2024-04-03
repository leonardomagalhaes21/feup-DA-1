#ifndef FEUP_DA_1_DATA_H
#define FEUP_DA_1_DATA_H

#include <unordered_map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include "WaterReservoir.h"
#include "PumpingStation.h"
#include "DeliverySite.h"
#include "Graph.h"


class Data {
public:
    Data(std::string s);

    const std::unordered_map<std::string, WaterReservoir> &getReservoirs() const;

    const std::unordered_map<std::string, PumpingStation> &getStations() const;

    const std::unordered_map<std::string, DeliverySite> &getSites() const;

    const Graph<std::string> &getGraph() const;

    void readReservoirs(const std::string &filename);

    void readStations(const std::string &filename);

    void readSites(const std::string &filename);

    void readPipes(const std::string &filename);

private:
    std::unordered_map<std::string, WaterReservoir> reservoirs;
    std::unordered_map<std::string, PumpingStation> stations;
    std::unordered_map<std::string, DeliverySite> sites;
    Graph<std::string> graph;
};


#endif //FEUP_DA_1_DATA_H
