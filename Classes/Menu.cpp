#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {}


void Menu::drawTop() {
    cout << "____________________________________________________" << endl;
    cout << "|" << "====================== Menu ======================" << "|" << endl;
    cout << "|__________________________________________________|" << endl;
}

void Menu::drawBottom() {
    cout << "|__________________________________________________|" << endl;
    cout << "|==================================================|" << endl;
    cout << "|__________________________________________________|" << endl;
}

void Menu::showMenu() {
    char key;
    bool flag2 = true;
    bool flag = true;

    WaterSupplyManager wsm;
    string system;

    while (flag2) {
        drawTop();
        cout << "| 1. Portugal's continental water supply network   |" << endl;
        cout << "| 2. Madeira water supply network                  |" << endl;
        drawBottom();
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case '1': {
                system = "continental";
                Data d = Data(system);
                wsm = WaterSupplyManager(d);
                flag2 = false;
                break;
            }
            case '2': {
                system = "madeira";
                Data d = Data(system);
                wsm = WaterSupplyManager(d);
                flag2 = false;
                break;
            }
            default: {
                cout << endl << "Invalid option!" << endl;
                break;
            }
        }
    }

    while (flag) {
        drawTop();
        cout << "| 1. Basic Service Metrics                         |" << endl;
        cout << "| 2. Reliability and Sensitivity to Failures       |" << endl;
        cout << "| 3. Reset Water Supply System                     |" << endl;
        cout << "| 4. Print Network Details                         |" << endl;
        cout << "| Q. Exit                                          |" << endl;
        drawBottom();
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case '1': {
                char key1;
                drawTop();
                cout << "| 1. Maximum amount of water that reaches each city|" << endl;
                cout << "| 2. View cities that have less water than demand  |" << endl;
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key1;
                switch (key1) {
                    case '1': {
                        wsm.maxFlowToCities();
                        break;
                    }
                    case '2': {
                        wsm.demandCoverage();
                        break;
                    }

                    case 'Q' : {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                break;

            }
            case '2': {
                char key1;
                drawTop();
                cout
                        << "| 1. Evaluate the impact of a water reservoir      | \n|  that is temporarily unavailable                 |"
                        << endl;
                cout
                        << "| 2. Evaluate the impact of a pumping station      | \n|  that is temporarily unavailable                 |"
                        << endl;
                cout
                        << "| 3. Evaluate the impact of a pipe that is         | \n|  temporarily unavailable                         |"
                        << endl;
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key1;
                switch (key1) {
                    case '1': {
                        string reservoir;
                        cout << "Enter the code of the reservoir (ex:R_1,R_2...): ";
                        cin >> reservoir;
                        wsm.evaluateVertexRemoval(reservoir);

                        break;
                    }
                    case '2': {
                        string pumpingStation;
                        cout << "Enter the code of the pumping station (ex:PS_1,PS_2...): ";
                        cin >> pumpingStation;
                        wsm.evaluateVertexRemoval(pumpingStation);
                        break;
                    }
                    case '3': {
                        string source, destination;
                        cout << "Enter the code of the source: ";
                        cin >> source;
                        cout << "Enter the code of the destination: ";
                        cin >> destination;
                        wsm.evaluateEdgeRemoval(source, destination);
                        break;
                    }


                    case 'Q' : {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                break;

            }
            case '3' : {
                cout << "Water Supply System reset successfully ";
                Data data = Data(system);
                wsm = WaterSupplyManager(data);
                break;
            }
            case '4' : {
                char key1;
                drawTop();
                cout << "| 1. Print Cities Details                          |" << endl;
                cout << "| 2. Print Reservoirs Details                      |" << endl;
                cout << "| 3. Print Pumping Stations Details                |" << endl;
                cout << "| Q. Exit                                          |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key1;
                switch (key1) {
                    case '1': {
                        wsm.printCitiesDetails();
                        break;
                    }
                    case '2': {
                        wsm.printReservoirsDetails();
                        break;
                    }
                    case '3': {
                        wsm.printStationsDetails();
                        break;
                    }
                    case 'Q' : {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                break;
            }
            case 'Q' : {
                break;
            }
            default: {
                cout << endl << "Invalid option!" << endl;
            }

        };

        cout << endl;
        cout << "Would you like to do something else? (Y/N) \n";
        char newCicle;
        cin >> newCicle;
        if (newCicle == 'N') flag = false;
        while (newCicle != 'Y') {
            if (newCicle == 'N') {
                flag = false;
                break;
            }
            cout << "Please type \"Y\" or \"N\"." << endl;
            cin >> newCicle;
        }
    }
}
