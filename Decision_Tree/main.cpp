#include <iostream>
#include "json.hpp"
#include "DataManager.h"
#include "Node.h"
#include "DataPiece.h"
#include "Calculations.h"
#include <fstream>
#include <math.h>
nlohmann::json j;
void process(Node *curNode);
void getProbabilities();
int main() {//Starts algorithm
    j = readData();
    if (j == nullptr) {
        return 0;
    }
    std::cout << j["data_count"] << std::endl;
    createNodeJson();
    Node *startNode = new Node(nullptr);
    process(startNode);
    getProbabilities();
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

void getProbabilities() {//Calculates min distance and prints probabilities between object and node.
    float x1, y1;
    std::cout << "Enter object's 'x' coordinate: ";
    std::cin >> x1;
    std::cout << "Enter object's 'y' coordinate: ";
    std::cin >> y1;
    std::ifstream nodeFile("nodes.json");
    nlohmann::json jsonFile;
    if (nodeFile.is_open()) {
        nodeFile >> jsonFile;
        nodeFile.close();
    } else {
        std::cout << "File is not available!" << std::endl;
        return;
    }
    float minDistance;
    int index;
    for (int i=0;i<jsonFile["node_count"];i++) {
        float x2, y2;
        if (jsonFile["nodes"][i]["split_axis"] == 0) {
            x2 = jsonFile["nodes"][i]["split_coordinate"];
            y2 = jsonFile["nodes"][i]["pre_coordinate"];
        } else {
            x2 = jsonFile["nodes"][i]["pre_coordinate"];
            y2 = jsonFile["nodes"][i]["split_coordinate"];
        }
        float distance = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
        if (i==0) {
            minDistance = distance;
            index = i;
        } else {
            if (distance<minDistance) {
                minDistance = distance;
                index = i;
            }
        }
    }
    std::cout << "Yellow probability: " << jsonFile["nodes"][index]["yellow_prob"] << std::endl;
    std::cout << "Red probability: " << jsonFile["nodes"][index]["red_prob"] << std::endl;
    std::cout << "Green probability: " << jsonFile["nodes"][index]["green_prob"] << std::endl;
}
