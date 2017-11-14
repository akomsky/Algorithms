//
//  main.cpp
//  Project6
//
//  Created by Amanda Komsky on 11/1/17.
//  Copyright © 2017 Amanda Komsky. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class DijkstraSSS {
public:
    int numNodes;
    int sourceNode;
    int minNode;
    int currentNode;
    int newCost;
    int **costMatrix;
    int *fatherAry;
    int *toDoAry;
    int *bestCostAry;
    
    DijkstraSSS(int n, int s){
        numNodes = n;
        sourceNode = s;
        // allocate array
        costMatrix = new int*[n+1];
        fatherAry = new int[n+1];
        toDoAry = new int[n+1];
        bestCostAry = new int[n+1];
        
        for (int i=1; i<n+1; i++) {
            costMatrix[i] = new int[n+1];
            fatherAry[i] = i;
            toDoAry[i] = 1;
            bestCostAry[i] = 99999;
            
            for(int j=1; j<n+1; j++) {
                if (i == j)
                    costMatrix[i][j] = 0;
                else
                    costMatrix[i][j] = 99999;
            }
        }
    }
    void loadCostMatrix(istream &is) { // read from input file and fill the costMatrix;
        int from;
        int to;
        int cost;
        
        while (is >> to >> from >> cost) {
            cout << "To: " << to << endl;
            cout << "From: " << from << endl;
            cout << "Cost: " << cost << endl;
            costMatrix[to][from] = cost;
        }
    }
    void setBestCostAry(int sourceNode){
        for(int i=1; i<numNodes+1; i++) {
            bestCostAry[i] = costMatrix[sourceNode][i];
        }
    }
    void setFatherArry(int sourceNode){
        for(int i=1; i<numNodes+1; i++) {
            fatherAry[i] = sourceNode;
        }
    }
    void setToDoAry(int sourceNode) {
        toDoAry[sourceNode] = 0;
    }
    int findMinNode(){
        minNode = 99999;
        for(int i=1; i<numNodes+1; i++){
            if (toDoAry[i] == 1 && (bestCostAry[i] < minNode)) {
                minNode = i;
            }
        }
        return minNode;
    }
    int computeCost(int minNode, int currentNode) {
        return bestCostAry[minNode] + costMatrix[minNode][currentNode];
    }
    void markMinNode(int minNode) {
        toDoAry[minNode] = 0;
    }
    void changeFather(int node, int minNode) {
        fatherAry[node] = minNode;
    }
    void changeCost(int node, int newCost) {
        bestCostAry[node] = newCost;
    }
    void debugPrint(ostream &os) {
        os << "The source node is " << sourceNode << endl;
        os << "The fatherAry is: " << endl;
        for (int i=1; i<numNodes+1; i++) {
            os << fatherAry[i] << " ";
        }
        os << endl;
        os << "The bestCostAry is: " << endl;
        for (int i=1; i<numNodes+1; i++) {
            os << bestCostAry[i] << " ";
        }
        os << endl;
        os << "The toDoAry is: " << endl;
        for (int i=1; i<numNodes+1; i++) {
            os << toDoAry[i] << " ";
        }
        os << endl;
    }
    void printShortestPaths(int currentNode, ostream &os) {
        int walker = currentNode;
        os << "The path from " << this->sourceNode << " to " << walker << ": ";
        while (fatherAry[walker] != this->sourceNode) {
            os << walker << " <-- ";
            walker = fatherAry[walker];
        }
        os << walker << ": cost = " << bestCostAry[currentNode] << endl;
    }
    void Dijkstras(){
        
    }
    
};
int main(int argc, char** argv) {
    ifstream inFile;
    string filename = argv[1];
    inFile.open(filename);
    ofstream outFile1;
    ofstream outFile2;
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    
    int numNodes;
    int sourceNode;
    int currentNode;
    if (!inFile){
        cout << "Unable to read file";
        exit(1);
    }
    inFile >> numNodes >> sourceNode;
    DijkstraSSS G = *new DijkstraSSS(numNodes, sourceNode);
    G.loadCostMatrix(inFile);
//    G.setBestCostAry(sourceNode);
//    G.setFatherArry(sourceNode);
//    G.setToDoAry(sourceNode);
    
//    for(int i=1; i<numNodes+1; i++) {
//        G.minNode = G.findMinNode();
//        G.markMinNode(G.minNode);
//        G.debugPrint(outFile2);
//        currentNode = 1;
//        
//        while (currentNode <= numNodes) {
//            if (G.toDoAry[currentNode] == 1) {
//                int newCost = G.computeCost(G.minNode, currentNode);
//                if(newCost < G.bestCostAry[currentNode]) {
//                    G.changeCost(currentNode, newCost);
//                    G.changeFather(currentNode, G.minNode);
//                    G.debugPrint(outFile2);
//                }
//            }
//            currentNode++;
//        }
//    }
//    currentNode = 1;
//    while (currentNode <= numNodes) {
//        G.printShortestPaths(currentNode, outFile1);
//        currentNode++;
//    }
    
    
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

