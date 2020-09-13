#ifndef NODE_H
#define NODE_H
#include <vector>
#include <DataPiece.h>
#include <map>
#include "json.hpp"
class Node {
public:
    enum conditions{
        MAX_COORD = 6,
        MIN_DATA = 200,
        MAX_DEPTH = 3,
        MAX_CALC = 10000
    };
    std::vector<class Piece> dataPieces;
    std::map<std::string, int> stats;
    float split_coord;
    int split_axis;
    float I;
    int depth;
    float preCoordinate;
    Node *mainNode;
    Node *leftNode;
    Node *rightNode;
    Node (Node *mainNode) {
        this->mainNode = mainNode;
    }
    void setStats();
    void setChildNodes();
    void addColor(std::vector<class Piece>::iterator it, int pos);
    void printInfo();
    void writeInfo();
    void setPreCoordinate();
};

#endif // NODE_H
