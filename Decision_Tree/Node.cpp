#include <iostream>
#include <Node.h>

void Node::setStats() {
    stats["lowerYellow"] = 0;
    stats["lowerRed"] = 0;
    stats["lowerGreen"] = 0;
    stats["upperYellow"] = 0;
    stats["upperRed"] = 0;
    stats["upperGreen"] = 0;
    stats["totalPiece"] = 0;
    std::vector<class Piece>::iterator it;
    for (it=dataPieces.begin();it<dataPieces.end();it++) {
        if (split_axis == 0) {
            if (it.base()->x<split_coord) {
                addColor(it, 0);
            } else {
                addColor(it, 1);
            }
        } else if (split_axis == 1) {
            if (it.base()->y<split_coord) {
                addColor(it, 0);
            } else {
                addColor(it, 1);
            }
        }
    }
    stats["totalPiece"] = stats["lowerYellow"] + stats["lowerRed"] + stats["lowerGreen"] + stats["upperYellow"] + stats["upperRed"] + stats["upperGreen"];
}

void Node::setChildNodes() {
    std::vector<class Piece>::iterator it;
    for (it=dataPieces.begin();it<dataPieces.end();it++) {
        if (split_axis == 0) {
            if (it.base()->x<split_coord) {
                leftNode->dataPieces.push_back(*it);
            } else {
                rightNode->dataPieces.push_back(*it);
            }
        } else if (split_axis == 1) {
            if (it.base()->y<split_coord) {
                leftNode->dataPieces.push_back(*it);
            } else {
                rightNode->dataPieces.push_back(*it);
            }
        }
    }
}

void Node::addColor(std::vector<class Piece>::iterator it, int pos) {
    if (pos == 0) {
        if (it.base()->color == "yellow") {
            stats["lowerYellow"]++;
        } else if (it.base()->color == "red") {
            stats["lowerRed"]++;
        } else if (it.base()->color == "green") {
            stats["lowerGreen"]++;
        }
    } else if (pos == 1) {
        if (it.base()->color == "yellow") {
            stats["upperYellow"]++;
        } else if (it.base()->color == "red") {
            stats["upperRed"]++;
        } else if (it.base()->color == "green") {
            stats["upperGreen"]++;
        }
    }
}

void Node::printInfo() {
    std::cout << "Split Axis: " << split_axis << std::endl;
    std::cout << "Split Coordinate: " << split_coord << std::endl;
    std::cout << "Information Gain Value: " << I << std::endl;
}
