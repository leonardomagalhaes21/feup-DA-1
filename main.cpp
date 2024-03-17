#include "Classes/Menu.h"

int main() {
    // provisório -> testar o parsing
//    std::cout << d.getReservoirs().find("R_3")->second.getName() << std::endl;
//    std::cout << d.getStations().find("PS_7")->second.getId() << std::endl;
//    std::cout << d.getSites().find("C_5")->second.getPopulation() << std::endl;
//    for(auto a : d.getGraph().getVertexSet()){
//        std::cout << a->getCode() << " " << a->getSel() << " ";
//        switch(a->getSel()){
//            case 1:
//                std::cout << "Reservoir" << std::endl;
//                break;
//            case 2:
//                std::cout << "Pumping Station" << std::endl;
//                break;
//            case 3:
//                std::cout << "Delivery Site" << std::endl;
//                break;
//        };
//    }
    std::cout << "Loading ..." << std::endl;
    Menu m = Menu();
    m.showMenu();
    std::cout << std::endl;
    return 0;
}
