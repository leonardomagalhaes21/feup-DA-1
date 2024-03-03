#ifndef FEUP_DA_1_DATA_H
#define FEUP_DA_1_DATA_H

#include <unordered_map>
#include <sstream>
#include <fstream>
#include "WaterReservoir.h"


class Data {
    public:
        void readReservoirs(const std::string& filename);

    private:
        std::unordered_map<int, WaterReservoir> reservoirs;
};


#endif //FEUP_DA_1_DATA_H
