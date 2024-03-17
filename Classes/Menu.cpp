#include "Menu.h"
#include "WaterSupplyManager.h"
#include <iostream>
#include <algorithm>

void maxwaterforeachcity();

using namespace std;

void Menu::displayMenu() {
    int choice;
    do {

        std::cout << "1. Basic Service Metrics" << std::endl;
        std::cout << "2. Management options" << std::endl;
        std::cout << "3. Process All Requests" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "1. View the maximum amount of water that can reach each or a specific city " << std::endl;
                std::cout << "2. View if an existing network configuration meet the water needs of its customer " << std::endl;
                std::cout << "3. View list of all UC's " << std::endl;
                std::cout << "0. Exit" << std::endl;

                std::cout << "Enter your choice: ";
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "CITIES LIST:" << endl;
                        maxwaterforeachcity();
                        break;
                    case 2:
                        cout << "CLASSES LIST:" << endl;
                        checkifnetworkmeetsneeds();
                        break;
                    case 3:

                        break;


                    case 4:
                        cout << "VIEW STUDENT SCHEDULE: " << endl;

                        break;
                    case 5:
                        cout << "VIEW CLASS SCHEDULE:" << endl;

                        break;

                    case 6:

                        break;


                    case 0:
                        std::cout << "Exiting the program." << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }


                break;
            case 2:
                std::cout << "1. Join new UC" << std::endl;
                std::cout << "2. Request change of class" << std::endl;
                std::cout << "0. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                switch (choice) {
                    case 1:

                        break;

                    case 2:

                        break;
                    case 0:
                        std::cout << "Exiting the program." << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            case 3:

                break;
        }
    } while (choice != 0);
}

void Menu::maxwaterforeachcity() {
    managementSystem.maxFlowToCities();

}

void Menu::checkifnetworkmeetsneeds() {
    managementSystem.demandCoverage();

}
