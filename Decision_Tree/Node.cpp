#include <iostream>
#include <Node.h>

void Node::setStats() {
    stats["lowerYellow"] = 0;
    stats["lowerRed"] = 0;
    stats["lowerGreen"] = 0;
    stats["upperYellow"] = 0;
    stats["upperRed"] = 0;
    stats["upperGreen"] = 0;
    std::vector<class Piece>::iterator it;
    for (it=dataPieces.begin();it<dataPieces.end();it++) {
        if (split_axis == 0) {
            if (it.base()->x<split_axis) {
                addColor(it, stats, 0);
            } else {
                addColor(it, stats, 1);
            }
        } else if (split_axis == 1) {
            if (it.base()->y<split_axis) {
                addColor(it, stats, 0);
            } else {
                addColor(it, stats, 1);
            }
        }
    }
}

void Node::addColor(std::vector<class Piece>::iterator it, std::map<std::string, int> stats, int pos) {
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
