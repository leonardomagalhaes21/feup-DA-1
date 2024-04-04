#ifndef FEUP_DA_1_PUMPINGSTATION_H
#define FEUP_DA_1_PUMPINGSTATION_H


#include <string>

class PumpingStation {
public:

    /**
     * @brief Constructs a PumpingStation object
     * @details Time complexity: O(1)
     * @param ID of the pumping station
     * @param Code of the pumping station
     */
    PumpingStation(int id, std::string code);

    /**
     * @brief Fetches the ID of the pumping station
     * @details Time complexity: O(1)
     * @return ID of the pumping station
     */
    int getId() const;

    /**
     * @brief Fetches the code of the pumping station
     * @details Time complexity: O(1)
     * @return Code of the pumping station
     */
    const std::string &getCode() const;

private:
    int id;
    std::string code;

};


#endif //FEUP_DA_1_PUMPINGSTATION_H
