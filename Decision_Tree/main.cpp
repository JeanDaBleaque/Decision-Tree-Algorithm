#include <iostream>
#include "json.hpp"
#include "DataManager.h"
#include "Node.h"
#include "DataPiece.h"
#include "Calculations.h"
nlohmann::json j;
void process(Node *curNode);

int main() {//Starts algorithm
    j = readData();
    if (j == nullptr) {
        return 0;
    }
    std::cout << j["data_count"] << std::endl;
    createNodeJson();
    Node *startNode = new Node(nullptr);
    process(startNode);
    return 0;
}

void process(Node *curNode) {//Calls functions in node class step by step.
    std::cout << "Current Depth: " << curNode->depth << " Node started!" << std::endl;
    CalculationObject *calcObj = new CalculationObject;
    if (curNode->mainNode == nullptr) {
        for (int i=0;i<j["data_count"];i++) {
            Piece dataPiece;
            dataPiece.x = j["data"][i]["x"];
            dataPiece.y = j["data"][i]["y"];
            dataPiece.color = j["data"][i]["color"];
            curNode->dataPieces.push_back(dataPiece);
            curNode->depth = 0;
        }
    }
    calcObj->checkPossibilities(curNode);
    curNode->printInfo();
    calcObj->getCurrentStat(curNode);
    if (curNode->depth+1 >= curNode->MAX_DEPTH || curNode->dataPieces.size()<curNode->MIN_DATA) {
        curNode->writeInfo();
        delete(curNode);
        return;
    }
    curNode->leftNode = new Node(curNode);
    curNode->rightNode = new Node(curNode);
    curNode->leftNode->depth = curNode->depth+1;
    curNode->rightNode->depth = curNode->depth+1;
    curNode->setChildNodes();
    process(curNode->leftNode);
    process(curNode->rightNode);
    delete(curNode);
}
