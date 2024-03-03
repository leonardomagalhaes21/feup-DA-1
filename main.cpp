#include <iostream>
#include "Classes/Data.h"

int main() {
    Data d = Data();
    // provisório -> testar o parsing
    std::cout << d.getReservoirs().find("R_1")->second.getName() << std::endl;
    std::cout << d.getStations().find("PS_7")->second.getId() << std::endl;
    std::cout << d.getSites().find("C_4")->second.getPopulation() << std::endl;
    return 0;
}
