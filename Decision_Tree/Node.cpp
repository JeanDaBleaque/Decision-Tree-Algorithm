#include <iostream>
#include <Node.h>
#include <fstream>
void Node::setStats() {//Set status for curNode.
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

void Node::setChildNodes() {//Sets nodes which are child nodes of curNode.
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

void Node::addColor(std::vector<class Piece>::iterator it, int pos) {//Adds color values to node's status map.
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

void Node::printInfo() {//Prints node's axis, coordiante and inf. gain value.
    std::cout << "Split Axis: " << split_axis << std::endl;
    std::cout << "Split Coordinate: " << split_coord << std::endl;
    std::cout << "Information Gain Value: " << I << std::endl;
}

void Node::writeInfo() {//Writes node status to nodes.json file.
    std::ifstream fileRead("nodes.json");
    nlohmann::json json;
    if (fileRead.is_open()) {
        fileRead >> json;
        fileRead.close();
        std::ofstream fileWrite("nodes.json");
        if (fileWrite.is_open()) {
            int nodeCount = json["node_count"];
            json["node_count"] = nodeCount+1;
            json["nodes"][nodeCount]["split_axis"] = split_axis;
            json["nodes"][nodeCount]["split_coordinate"] = split_coord;
            json["nodes"][nodeCount]["information_gain"] = I;
            json["nodes"][nodeCount]["lower_yellow"] = stats["lowerYellow"];
            json["nodes"][nodeCount]["lower_red"] = stats["lowerRed"];
            json["nodes"][nodeCount]["lower_green"] = stats["lowerGreen"];
            json["nodes"][nodeCount]["upper_yellow"] = stats["upperYellow"];
            json["nodes"][nodeCount]["upper_red"] = stats["upperRed"];
            json["nodes"][nodeCount]["upper_green"] = stats["upperGreen"];
            json["nodes"][nodeCount]["yellow_prob"] = (stats["lowerYellow"]+stats["upperYellow"])/(float)stats["totalPiece"];
            json["nodes"][nodeCount]["red_prob"] = (stats["lowerRed"]+stats["upperRed"])/(float)stats["totalPiece"];
            json["nodes"][nodeCount]["green_prob"] = (stats["lowerGreen"]+stats["upperGreen"])/(float)stats["totalPiece"];
            fileWrite << json;
            fileWrite.close();
        }
    } else {
        std::cout << "File is not available!" << std::endl;
    }
}
