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
    /**
     * @brief Constructs a Data object
     * @details Time complexity: O(1)
     * @param Path to the data file
     */
    Data(const std::string& s);

    /**
     * @brief Fetches the reservoirs data
     * @details Time complexity: O(1)
     * @return Map of reservoirs
     */
    const std::unordered_map<std::string, WaterReservoir> &getReservoirs() const;

    /**
     * @brief Fetches the pumping stations data
     * @details Time complexity: O(1)
     * @return Map of pumping stations
     */
    const std::unordered_map<std::string, PumpingStation> &getStations() const;

    /**
     * @brief Fetches the delivery sites data
     * @details Time complexity: O(1)
     * @return Map of delivery sites
     */
    const std::unordered_map<std::string, DeliverySite> &getSites() const;

    /**
     * @brief Fetches the graph data
     * @details Time complexity: O(1)
     * @return Graph data
     */
    const Graph<std::string> &getGraph() const;

    /**
     * @brief Reads reservoirs data from a file
     * @details Time complexity: O(n), where n is the number of lines in the file
     * @param filename Name of the file to read from
     */
    void readReservoirs(const std::string &filename);

    /**
     * @brief Reads pumping stations data from a file
     * @details Time complexity: O(n), where n is the number of lines in the file
     * @param filename Name of the file to read from
     */
    void readStations(const std::string &filename);

    /**
     * @brief Reads delivery sites data from a file
     * @details Time complexity: O(n), where n is the number of lines in the file
     * @param filename Name of the file to read from
     */
    void readSites(const std::string &filename);

    /**
     * @brief Reads pipes data from a file
     * @details Time complexity: O(n), where n is the number of lines in the file
     * @param filename Name of the file to read from
     */
    void readPipes(const std::string &filename);

private:
    std::unordered_map<std::string, WaterReservoir> reservoirs;
    std::unordered_map<std::string, PumpingStation> stations;
    std::unordered_map<std::string, DeliverySite> sites;
    Graph<std::string> graph;
};


#endif //FEUP_DA_1_DATA_H
