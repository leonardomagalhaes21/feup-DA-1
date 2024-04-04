#ifndef FEUP_DA_1_DELIVERYSITE_H
#define FEUP_DA_1_DELIVERYSITE_H


#include <string>

class DeliverySite {
public:

    /**
     * @brief Constructs a DeliverySite object
     * @details Time complexity: O(1)
     * @param Name of the delivery site
     * @param ID of the delivery site
     * @param Code of the delivery site
     * @param Demand of the delivery site
     * @param Population of the delivery site
     */
    DeliverySite(std::string name, int id, std::string code, double demand, int population);

    /**
     * @brief Fetches the name of the delivery site
     * @details Time complexity: O(1)
     * @return Name of the delivery site
     */
    const std::string &getName() const;

    /**
     * @brief Fetches the ID of the delivery site
     * @details Time complexity: O(1)
     * @return ID of the delivery site
     */
    int getId() const;

    /**
     * @brief Fetches the code of the delivery site
     * @details Time complexity: O(1)
     * @return Code of the delivery site
     */
    const std::string &getCode() const;

    /**
     * @brief Fetches the demand of the delivery site
     * @details Time complexity: O(1)
     * @return Demand of the delivery site
     */
    double getDemand() const;

    /**
     * @brief Fetches the population of the delivery site
     * @details Time complexity: O(1)
     * @return Population of the delivery site
     */
    int getPopulation() const;

private:
    std::string name;
    int id;
    std::string code;
    double demand;
    int population;

};


#endif //FEUP_DA_1_DELIVERYSITE_H
