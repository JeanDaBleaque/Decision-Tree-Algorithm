#include "DataManager.h"
#include <iostream>
#include "json.hpp"
#include <string>
#include <fstream>

nlohmann::json readData(){
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
