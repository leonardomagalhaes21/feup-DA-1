#ifndef FEUP_DA_1_WATERRESERVOIR_H
#define FEUP_DA_1_WATERRESERVOIR_H

#include <string>

class WaterReservoir {
    public:
        WaterReservoir(int id, std::string name, std::string code, std::string municipality, int maxDelivery);
        int getId() const;
        std::string getName() const;
        std::string getMunicipality() const;
        std::string getCode() const;
        int getMaxDelivery() const;

    private:
        int id;
        std::string name;
        std::string municipality;
        std::string code;
        int maxDelivery;

};


#endif //FEUP_DA_1_WATERRESERVOIR_H
