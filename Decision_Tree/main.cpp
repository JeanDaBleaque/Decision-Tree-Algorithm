#include <iostream>
#include "json.hpp"
#include "DataManager.h"
int main()
{
    nlohmann::json j = readData();
    if (j == nullptr) {
        return 0;
    }
    std::cout << j["data_count"] << std::endl;
    return 0;
}

