#include "WaterReservoir.h"

using namespace std;

WaterReservoir::WaterReservoir(string name, string municipality, int id, string code, int maxDelivery)
        : name(name), municipality(municipality), id(id), code(code), maxDelivery(maxDelivery) {}


string WaterReservoir::getName() const {
    return name;
}

string WaterReservoir::getMunicipality() const {
    return municipality;
}

int WaterReservoir::getId() const {
    return id;
}

std::string WaterReservoir::getCode() const {
    return code;
}

int WaterReservoir::getMaxDelivery() const {
    return maxDelivery;
}



