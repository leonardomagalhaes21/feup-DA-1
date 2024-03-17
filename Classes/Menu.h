#ifndef FEUP_DA_1_MENU_H
#define FEUP_DA_1_MENU_H
#include "WaterSupplyManager.h"

class Menu {
public:
    Menu(WaterSupplyManager &system) : managementSystem(system) {};
    void displayMenu();
private:
    WaterSupplyManager &managementSystem;
    void maxwaterforeachcity();

    void checkifnetworkmeetsneeds();
};


#endif //FEUP_DA_1_MENU_H
