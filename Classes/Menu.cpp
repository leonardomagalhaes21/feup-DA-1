#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {}


void Menu::drawTop(){
    cout << "____________________________________________________" << endl;
    cout << "|" << "====================== Menu ======================" << "|" << endl;
    cout << "|__________________________________________________|" << endl;
}

void Menu::drawBottom(){
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
                        cout << "CITIES LIST:" << endl;
                        wsm.maxFlowToCities();
                        break;
                    }
                    case '2': {
                        cout << "CITIES LIST:" << endl;
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
