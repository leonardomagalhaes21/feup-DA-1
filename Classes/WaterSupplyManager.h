#ifndef FEUP_DA_1_WATERSUPPLYMANAGER_H
#define FEUP_DA_1_WATERSUPPLYMANAGER_H


#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>
#include <iomanip>

class WaterSupplyManager {
public:

    /**
     * @brief Constructs a WaterSupplyManager object
     * @details Time complexity: O(1)
     */
    WaterSupplyManager();

    /**
     * @brief Constructs a WaterSupplyManager object with data
     * @details Time complexity: O(1)
     * @param Data to initialize the water supply manager
     */
    WaterSupplyManager(const Data &d);

    /**
     * @brief Calculates the maximum flow to all cities
     * @details Time complexity: O(VE^2), where V is the number of vertices and E is the number of edges in the graph
     */
    void maxFlowToCities();

    /**
     * @brief Calculates the coverage of water demand
     * @details Time complexity: O(V), where V is the number of delivery sites
     */
    void demandCoverage();

    /**
     * @brief Calculates the maximum flow from the pumping station
     * @details Time complexity: O(VE^2), where V is the number of vertices and E is the number of edges in the graph
     * @return Maximum flow from the network
     */
    int pumpMaxFlow();

    /**
     * @brief Resets the flow in the water supply network
     * @details Time complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph
     */
    void resetFlow();

    /**
     * @brief Evaluates the impact of removing a vertex from the water supply network
     * @details Time complexity: O(VE^2), where V is the number of vertices in the graph
     * @param Vertex to be removed
     */
    void evaluateVertexRemoval(const std::string& vertex);

    /**
     * @brief Evaluates the impact of removing an edge from the water supply network
     * @details Time complexity: O(VE^2), where V is the number of vertices and E is the number of edges in the graph
     * @param Source vertex of the edge
     * @param Destination vertex of the edge
     */
    void evaluateEdgeRemoval(const std::string &source, const std::string &destination);

    /**
     * @brief Prints the details of all cities in a table-like format
     * @details Time complexity: O(V), where V is the number of vertices in the graph.
     */
    void printCitiesDetails();

    /**
     * @brief Prints the details of all reservoirs in a table-like format
     * @details Time complexity: O(V), where V is the number of vertices in the graph.
     */
    void printReservoirsDetails();

    /**
     * @brief Prints the details of all pumping stations.
     * @details Time complexity: O(V), where V is the number of vertices in the graph.
     */
    void printStationsDetails();

private:
    std::unordered_map<std::string, WaterReservoir> reservoirs;
    std::unordered_map<std::string, PumpingStation> stations;
    std::unordered_map<std::string, DeliverySite> sites;
    Graph<std::string> graph;


};


#endif //FEUP_DA_1_WATERSUPPLYMANAGER_H
