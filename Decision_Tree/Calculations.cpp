#include "Calculations.h"
#include <iostream>
#include <time.h>
#include <math.h>
void CalculationObject::setRnd() {
    srand(time(nullptr));
    axis = rand() % 2;
    coordinate = (((float)rand())/RAND_MAX * (float)7);
}

void CalculationObject::checkPossibilities(Node *curNode) {
    int bestAxis = 0;
    float bestCoordinate = 0;
    float bestI = 0;
    for (int i=0;i<10000;i++) {
        float currentI = 0;
        setRnd();
        curNode->split_axis = axis;
        curNode->split_coord = coordinate;
        curNode->setStats();
        currentI = calculateInfGain(curNode);
        if (currentI>bestI) {
            bestAxis = curNode->split_axis;
            bestCoordinate = curNode->split_coord;
            bestI = currentI;
        }
    }
    curNode->split_axis = bestAxis;
    curNode->split_coord = bestCoordinate;
    curNode->I = bestI;
    if (bestI == (float) 0) {
        checkPossibilities(curNode);
    }
}

float CalculationObject::calculateInfGain(Node *curNode) {
    std::map<std::string, float> currentProbs;
    currentProbs["lowerYellowProb"] = ((float)(curNode->stats["lowerYellow"])/curNode->stats["totalPiece"]);
    currentProbs["lowerRedProb"] = ((float)(curNode->stats["lowerRed"])/curNode->stats["totalPiece"]);
    currentProbs["lowerGreenProb"] = ((float)(curNode->stats["lowerGreen"])/curNode->stats["totalPiece"]);

    currentProbs["upperYellowProb"] = ((float)(curNode->stats["upperYellow"])/curNode->stats["totalPiece"]);
    currentProbs["upperRedProb"] = ((float)(curNode->stats["upperRed"])/curNode->stats["totalPiece"]);
    currentProbs["upperGreenProb"] = ((float)(curNode->stats["upperGreen"])/curNode->stats["totalPiece"]);

    currentProbs["totalYellowProb"] = currentProbs["lowerYellowProb"] + currentProbs["upperYellowProb"];
    currentProbs["totalRedProb"] = currentProbs["lowerRedProb"] + currentProbs["upperRedProb"];
    currentProbs["totalGreenProb"] = currentProbs["lowerGreenProb"] + currentProbs["upperGreenProb"];

    std::map<std::string, float>::iterator it;

    for (it=currentProbs.begin();it!=currentProbs.end();it++) {
        if (it->second == (float) 0) {
            it->second = (float) 1;
        }
    }

    float HS, HSL, HSU, I;

    HS = -1*(currentProbs["totalYellowProb"]*log2f(currentProbs["totalYellowProb"]) + currentProbs["totalRedProb"]*log2f(currentProbs["totalRedProb"]) + currentProbs["totalGreenProb"]*log2f(currentProbs["totalGreenProb"]));
    HSL = (currentProbs["lowerYellowProb"]*log2f(currentProbs["lowerYellowProb"]) + currentProbs["lowerRedProb"]*log2f(currentProbs["lowerRedProb"]) + currentProbs["lowerGreenProb"]*log2f(currentProbs["lowerGreenProb"]));
    HSU = (currentProbs["upperYellowProb"]*log2f(currentProbs["upperYellowProb"]) + currentProbs["upperRedProb"]*log2f(currentProbs["upperRedProb"]) + currentProbs["upperGreenProb"]*log2f(currentProbs["upperGreenProb"]));
    I = HS + ((float)(curNode->stats["lowerYellow"]+curNode->stats["lowerRed"]+curNode->stats["lowerGreen"])/(curNode->stats["totalPiece"]))*HSL + ((float)(curNode->stats["upperYellow"]+curNode->stats["upperRed"]+curNode->stats["upperGreen"])/(curNode->stats["totalPiece"]))*HSU;
    return I;
}

void CalculationObject::getCurrentStat(Node *curNode) {
    std::cout << "Lower Yellow: ";
    std::cout << curNode->stats["lowerYellow"] << std::endl;
    std::cout << "Lower Red: ";
    std::cout << curNode->stats["lowerRed"] << std::endl;
    std::cout << "Lower Green: ";
    std::cout << curNode->stats["lowerGreen"] << std::endl;
    std::cout << "Upper Yellow: ";
    std::cout << curNode->stats["upperYellow"] << std::endl;
    std::cout << "Upper Red: ";
    std::cout << curNode->stats["upperRed"] << std::endl;
    std::cout << "Upper Green: ";
    std::cout << curNode->stats["upperGreen"] << std::endl;
}
