#ifndef FEUP_DA_1_PUMPINGSTATION_H
#define FEUP_DA_1_PUMPINGSTATION_H


#include <string>

class PumpingStation {
public:
    PumpingStation(int id, std::string code);

    int getId() const;

    const std::string &getCode() const;

private:
    int id;
    std::string code;

};


#endif //FEUP_DA_1_PUMPINGSTATION_H
