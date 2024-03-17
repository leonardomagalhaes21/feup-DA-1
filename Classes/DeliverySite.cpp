#include "DeliverySite.h"

using namespace std;

DeliverySite::DeliverySite(string name, int id, string code, double demand, int population)
        : name(name), id(id), code(code), demand(demand), population(population) {}


const string &DeliverySite::getName() const {
    return name;
}

int DeliverySite::getId() const {
    return id;
}

const string &DeliverySite::getCode() const {
    return code;
}

double DeliverySite::getDemand() const {
    return demand;
}

int DeliverySite::getPopulation() const {
    return population;
}

