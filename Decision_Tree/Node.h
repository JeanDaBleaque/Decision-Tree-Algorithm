#ifndef NODE_H
#define NODE_H
#include <vector>
#include <DataPiece.h>
#include <map>
class Node {
public:
    std::vector<class Piece> dataPieces;
    std::map<std::string, int> stats;
    int split_coord;
    int split_axis;
    Node *lowerNode;
    Node *upperNode;
    void setStats();
    void addColor(std::vector<class Piece>::iterator it, std::map<std::string, int> stats, int pos);
};

#endif // NODE_H
