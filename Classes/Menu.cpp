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
    Data d = Data();
    WaterSupplyManager wsm = WaterSupplyManager(d);

    char key;
    bool flag = true;
    while (flag) {
        drawTop();
        cout << "| 1. Basic Service Metrics                         |" << endl;
        cout << "| 2. Reliability and Sensitivity to Failures       |" << endl;
        cout << "| 3. Reset Water Supply System                     |" << endl;
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
//                        cout << "CITIES LIST:" << endl;
                        wsm.maxFlowToCities();
                        break;
                    }
                    case '2': {
//                        cout << "CITIES LIST:" << endl;
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
                        wsm.evaluateEdgeImpact(source, destination);
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
                Data data = Data();
                wsm = WaterSupplyManager(data);
                break;
            }
            case 'Q' : {
                flag = false;
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
