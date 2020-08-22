#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include "Node.h"
class CalculationObject {
public:
    int axis;
    float coordinate;
    void setRnd();
    void checkPossibilities(Node *curNode);
    float calculateInfGain(Node *curNode);
    void getCurrentStat(Node *curNode);
};

#endif // CALCULATIONS_H
