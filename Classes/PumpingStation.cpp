#include "PumpingStation.h"

using namespace std;

PumpingStation::PumpingStation(int id, string code) : id(id), code(code) {}

int PumpingStation::getId() const {
    return id;
}

const string &PumpingStation::getCode() const {
    return code;
}

