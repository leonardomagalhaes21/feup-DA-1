#include <iostream>
#include "Data.h"

using namespace std;

Data::Data(const string &s) {
    if (s == "madeira") {
        readReservoirs("../dataset/Madeira/Reservoirs_Madeira.csv");
        readStations("../dataset/Madeira/Stations_Madeira.csv");
        readSites("../dataset/Madeira/Cities_Madeira.csv");
        readPipes("../dataset/Madeira/Pipes_Madeira.csv");
    } else {
        readReservoirs("../dataset/Reservoir.csv");
        readStations("../dataset/Stations.csv");
        readSites("../dataset/Cities.csv");
        readPipes("../dataset/Pipes.csv");
    }

}

const unordered_map<string, WaterReservoir> &Data::getReservoirs() const {
    return reservoirs;
}

const unordered_map<string, PumpingStation> &Data::getStations() const {
    return stations;
}

const unordered_map<string, DeliverySite> &Data::getSites() const {
    return sites;
}

const Graph<string> &Data::getGraph() const {
    return graph;
}


void Data::readReservoirs(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
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

void Data::readStations(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
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

void Data::readSites(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
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

void Data::readPipes(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string temp;
        string a, b;
        double capacity;
        bool flag;

        getline(ss, a, ',');
        getline(ss, b, ',');
        getline(ss, temp, ',');
        capacity = stod(temp);
        getline(ss, temp, ',');
        flag = (bool) stoi(temp);
        graph.addVertex(a);
        graph.addVertex(b);
        graph.addEdge(a, b, capacity);
        if (!flag) graph.addEdge(b, a, capacity);

    }
    for (auto vertex: graph.getVertexSet()) {
        string s = vertex->getCode();
        string prefix = s.substr(0, s.find('_'));
        if (prefix == "R") { //water reservoir
            vertex->setSel(1);
        } else if (prefix == "PS") { //Pumping station
            vertex->setSel(2);
        } else if (prefix == "C") { //City
            vertex->setSel(3);
        } else {
            cerr << "There was an error reading the pipeline!" << endl;
        }
    }

}
