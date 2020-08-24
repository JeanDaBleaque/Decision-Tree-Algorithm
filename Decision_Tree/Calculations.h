#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include "Node.h"
class CalculationObject {
public:
    int axis;
    float coordinate;
    int FET = 0;
    void setRnd(Node *curNode);
    void checkPossibilities(Node *curNode);
    float calculateInfGain(Node *curNode);
    void getCurrentStat(Node *curNode);
};

#endif // CALCULATIONS_H
