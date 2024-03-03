#include <iostream>
#include "Data.h"

using namespace std;

void Data::readReservoirs(const string& filename){
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

        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, code, ',');
        getline(ss, municipality, ',');
        getline(ss, temp, ',');
        maxDelivery = stoi(temp);

        WaterReservoir wr(id, name, code, municipality, maxDelivery);
        reservoirs.insert({id, wr});
    }
}
