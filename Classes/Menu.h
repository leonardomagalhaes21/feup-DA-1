#ifndef FEUP_DA_1_MENU_H
#define FEUP_DA_1_MENU_H

#include "Data.h"
#include "WaterSupplyManager.h"

class Menu {
public:

    /**
     * @brief Constructs a Menu object
     * @details Time complexity: O(1)
     */
    Menu();

    /**
     * @brief Displays the menu
     * @details Time complexity: O(1)
     */
    static void showMenu();

    /**
     * @brief Draws the top part of the menu
     * @details Time complexity: O(1)
     */
    static void drawTop();

    /**
     * @brief Draws the bottom part of the menu
     * @details Time complexity: O(1)
     */
    static void drawBottom();

};


#endif //FEUP_DA_1_MENU_H
