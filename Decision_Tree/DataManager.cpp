#include "DataManager.h"
#include <iostream>
#include "json.hpp"
#include <string>
#include <fstream>

nlohmann::json readData(){//Reads data.json file for data pieces.
    std::ifstream new_file("data.json");
    nlohmann::json jsonFile;
    if(!new_file) {
        std::cout << "Data file not found!" << std::endl;
    } else {
        new_file >> jsonFile;
    }
    new_file.close();
    return jsonFile;
}

void createNodeJson() {//Creates nodes.json file for node saving.
    std::ofstream file("nodes.json");
    nlohmann::json nullJson;
    if (file.is_open()) {
        nullJson["node_count"] = 0;
        file << nullJson;
        file.close();
    }
}
