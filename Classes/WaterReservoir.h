#ifndef FEUP_DA_1_WATERRESERVOIR_H
#define FEUP_DA_1_WATERRESERVOIR_H

#include <string>

class WaterReservoir {
public:

    /**
     * @brief Constructs a WaterReservoir object
     * @details Time complexity: O(1)
     * @param Name of the water reservoir
     * @param Municipality where the water reservoir is located
     * @param ID of the water reservoir
     * @param Code of the water reservoir
     * @param MaxDelivery capacity of the water reservoir
     */
    WaterReservoir(std::string name, std::string municipality, int id, std::string code, int maxDelivery);

    /**
     * @brief Fetches the name of the water reservoir
     * @details Time complexity: O(1)
     * @return Name of the water reservoir
     */
    std::string getName() const;

    /**
     * @brief Fetches the municipality of the water reservoir
     * @details Time complexity: O(1)
     * @return Municipality of the water reservoir
     */
    std::string getMunicipality() const;

    /**
     * @brief Fetches the ID of the water reservoir
     * @details Time complexity: O(1)
     * @return ID of the water reservoir
     */
    int getId() const;

    /**
     * @brief Fetches the code of the water reservoir
     * @details Time complexity: O(1)
     * @return Code of the water reservoir
     */
    std::string getCode() const;

    /**
     * @brief Fetches the maximum delivery capacity of the water reservoir
     * @details Time complexity: O(1)
     * @return Maximum delivery capacity of the water reservoir
     */
    int getMaxDelivery() const;

private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;

};


#endif //FEUP_DA_1_WATERRESERVOIR_H
