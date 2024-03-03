#include "WaterReservoir.h"
using namespace std;

WaterReservoir::WaterReservoir(int id, string name, string code, string municipality, int maxDelivery)
    : id(id), name(name), code(code), municipality(municipality), maxDelivery(maxDelivery) {}

int WaterReservoir::getId() const {
    return id;
}

string WaterReservoir::getName() const {
    return name;
}

std::string WaterReservoir::getCode() const {
    return code;
}

string WaterReservoir::getMunicipality() const {
    return municipality;
}

int WaterReservoir::getMaxDelivery() const {
    return maxDelivery;
}



