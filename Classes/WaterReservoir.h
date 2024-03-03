#ifndef FEUP_DA_1_WATERRESERVOIR_H
#define FEUP_DA_1_WATERRESERVOIR_H

#include <string>

class WaterReservoir {
    public:
        WaterReservoir(std::string name, std::string municipality, int id, std::string code, int maxDelivery);
        std::string getName() const;
        std::string getMunicipality() const;
        int getId() const;
        std::string getCode() const;
        int getMaxDelivery() const;

    private:
        std::string name;
        std::string municipality;
        int id;
        std::string code;
        int maxDelivery;

};


#endif //FEUP_DA_1_WATERRESERVOIR_H
