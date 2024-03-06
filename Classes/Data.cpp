#include <iostream>
#include "Data.h"

using namespace std;

Data::Data(){
    readReservoirs("../dataset/Reservoirs_Madeira.csv");
    readStations("../dataset/Stations_Madeira.csv");
    readSites("../dataset/Cities_Madeira.csv");
}

const unordered_map<string, WaterReservoir> &Data::getReservoirs() const {
    return reservoirs;
}

const std::unordered_map<string, PumpingStation> &Data::getStations() const {
    return stations;
}

const std::unordered_map<std::string, DeliverySite> &Data::getSites() const {
    return sites;
}

void Data::readReservoirs(const std::string& filename){
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string temp;
        string name, municipality, code;
        int id, maxDelivery;

        getline(ss, name, ',');
        getline(ss, municipality, ',');
        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, code, ',');
        getline(ss, temp, ',');
        maxDelivery = stoi(temp);

        WaterReservoir wr(name, municipality, id, code, maxDelivery);
        reservoirs.insert({code, wr});
    }
}

void Data::readStations(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string temp;
        string code;
        int id;

        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, code, ',');

        PumpingStation ps(id, code);
        stations.insert({code, ps});
    }
}

void Data::readSites(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string temp;
        string name, code;
        int id, population;
        double demand;

        getline(ss, name, ',');
        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, code, ',');
        getline(ss, temp, ',');
        demand = stod(temp);
        getline(ss, temp, '\"');
        getline(ss, temp, '\"');
        temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
        population = stoi(temp);

        DeliverySite ds(name, id, code, demand, population);
        sites.insert({code, ds});
    }
}

void Data::readPipes(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);



    //ifstream file(filename);
    //
    //    flights = Graph(airports);
    //
    //    string source, target, airline, aLine;
    //    getline(file, aLine);
    //    while (getline(file, aLine)){
    //        istringstream inn(aLine);
    //        getline(inn, source, ',');
    //        getline(inn, target, ',');
    //        getline(inn, airline, ',');
    //        Position p1 = airports.find(source)->second.getPosition();
    //        Position p2 = airports.find(target)->second.getPosition();
    //        flights.addEdge(source, target, airline, p1.haversineDistance(p2));
    //    }
    //    for (auto vertex : flights.getVertexSet()){
    //        vertex->setOutdegree((int) vertex->getAdj().size());
    //        vertex->setIndegree(0);
    //    }
    //    for (auto vertex : flights.getVertexSet()){
    //        for (const auto& edge : vertex->getAdj()){
    //            edge.getDest()->setIndegree(edge.getDest()->getIndegree() + 1);
    //        }
    //    }
}
