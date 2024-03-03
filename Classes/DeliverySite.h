#ifndef FEUP_DA_1_DELIVERYSITE_H
#define FEUP_DA_1_DELIVERYSITE_H


#include <string>

class DeliverySite {
    public:
        DeliverySite(std::string name, int id, std::string code, double demand, int population);
        const std::string & getName() const;
        int getId() const;
        const std::string & getCode() const;
        double getDemand() const;
        int getPopulation() const;

    private:
        std::string name;
        int id;
        std::string code;
        double demand;
        int population;

};


#endif //FEUP_DA_1_DELIVERYSITE_H
