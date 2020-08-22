#ifndef NODE_H
#define NODE_H
#include <vector>
#include <DataPiece.h>
#include <map>
class Node {
public:
    std::vector<class Piece> dataPieces;
    std::map<std::string, int> stats;
    float split_coord;
    int split_axis;
    float I;
    Node *leftNode;
    Node *rightNode;
    void setStats();
    void addColor(std::vector<class Piece>::iterator it, int pos);
    void printInfo();
};

#endif // NODE_H
