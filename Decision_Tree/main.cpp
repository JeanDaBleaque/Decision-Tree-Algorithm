#include <iostream>
#include "json.hpp"
#include "DataManager.h"
#include "Node.h"
#include "DataPiece.h"
#include "Calculations.h"
nlohmann::json j;

void process(Node *curNode);

int main()
{
    j = readData();
    if (j == nullptr) {
        return 0;
    }
    std::cout << j["data_count"] << std::endl;
    Node *startNode = new Node;
    process(startNode);
    return 0;
}

void process(Node *curNode) {
    if (curNode->leftNode == nullptr && curNode->rightNode == nullptr) {
        for (int i=0;i<j["data_count"];i++) {
            Piece dataPiece;
            dataPiece.x = j["data"][i]["x"];
            dataPiece.y = j["data"][i]["y"];
            dataPiece.color = j["data"][i]["color"];
            curNode->dataPieces.push_back(dataPiece);
        }
    }
    CalculationObject *calcObj = new CalculationObject;
    calcObj->checkPossibilities(curNode);
    curNode->printInfo();
}
