//
//  main.cpp
//  project3_take 2
//
//  Created by Amanda Komsky on 9/14/17.
//  Copyright © 2017 Amanda Komsky. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class listBinTreeNode {
public:
    string chSt;
    int prob;
    listBinTreeNode* next;
    listBinTreeNode* left;
    listBinTreeNode* right;
    listBinTreeNode() {};
    listBinTreeNode(string chStr, int p) {
        chSt = chStr;
        prob = p;
        next = NULL;
        left = NULL;
        right = NULL;
    }
    string ChSt() { return chSt; }
    int Prob() { return prob; }
    void setNext(listBinTreeNode* n) { next = n; }
    listBinTreeNode* Next() { return next; }
    listBinTreeNode* Left() { return left; }
    listBinTreeNode* Right() { return right; }
    
    void printNode(ostream &os) {
        os << "chSt: " << this->ChSt() << "\nProb: " << this->Prob() << "\nLeft: "
        << this->Left()->ChSt() << "\nRight: " << this->Right()->ChSt();
        if ( this->Next() != NULL)
            os << "\nNext: " << this->Next()->ChSt() << endl;
        else {
            os << "\nNext: NULL\n";
        }
    };
};


class HuffmanLinkedList {
public:
    listBinTreeNode* listhead;
    listBinTreeNode* oldhead;

    HuffmanLinkedList() {
        listBinTreeNode* dummyNode = new listBinTreeNode("dummy",0);
        listhead = dummyNode;
    }
    listBinTreeNode* findSpot(int prob) {
        listBinTreeNode* walker = listhead;
        if (walker == NULL)
            return walker;
        while (walker->Next() != NULL && (prob > walker->Next()->Prob())){
            walker = walker->Next();
        }
        return walker;
    }
    void listInsert(listBinTreeNode* spot, listBinTreeNode* newNode) {
        if ((spot == NULL) || newNode->Prob() <= spot->Prob()){
            newNode->setNext(spot);
            listhead = newNode;
        }
        else {
            newNode->setNext(spot->Next());
            spot->setNext(newNode);
        }
    }
    bool isEmpty() {
        listBinTreeNode *walker = listhead;
        if (walker->Next() == NULL)
            return true;
        else
            return false;
    }
    void printList(ostream &os) {
        listBinTreeNode *walker = listhead;
        os << "listHead --> ";
        while(walker->Next() != NULL) {
            os << "(" << walker->ChSt() << "," << walker->Prob() << "," << walker->Next()->ChSt() <<  ")" << " --> ";
            walker = walker->Next();
        }
        os << "(" << walker->ChSt() << "," << walker->Prob() << ",NULL)" << endl;
    }
};

class HuffmanBinaryTree {
    struct charInfo {
        string chSt;
        int prob;
        string code;
    };
public:
    HuffmanBinaryTree(HuffmanLinkedList list, ostream &os) {
        listBinTreeNode* dummyNode = new listBinTreeNode("dummy",0);
        list.oldhead = dummyNode;
        list.oldhead->setNext(list.listhead->Next());
        list.listhead = list.listhead->Next();

        while(list.listhead->Next() != NULL) {
            listBinTreeNode* newNode = new listBinTreeNode(
                list.listhead->ChSt() + list.listhead->Next()->ChSt(),
                list.listhead->Prob() + list.listhead->Next()->Prob()
            );
            newNode->left = list.listhead;
            newNode->right = list.listhead->Next();
            
            list.listhead = list.listhead->Next()->Next();
            newNode->printNode(os);
            listBinTreeNode* spot = list.findSpot(newNode->Prob());
            list.listInsert(spot, newNode);
            list.printList(os);
        }
        Root = list.listhead;
        os << "The root is: " << Root->ChSt() << endl;
    }
    
    void preOrderTraversal(listBinTreeNode* T, ostream &os) {
        if ( T == NULL)
            return;
        else {
            os << T->ChSt() << ", ";
            preOrderTraversal(T->Left(), os);
            preOrderTraversal(T->Right(), os);
        }
    }
    void postOrderTraversal(listBinTreeNode* T, ostream &os) {
        if ( T == NULL)
            return;
        else {
            postOrderTraversal(T->Left(), os);
            postOrderTraversal(T->Right(), os);
            os << T->ChSt() << ", ";
        }
    }
    void inOrderTraversal(listBinTreeNode* T, ostream &os){
        if ( T == NULL)
            return;
        else {
            inOrderTraversal(T->Left(), os);
            os << T->ChSt() << ", ";
            inOrderTraversal(T->Right(), os);
        }
    }
    bool isLeaf(listBinTreeNode* node) {
        if (node->Left() == NULL && node->Right() == NULL)
            return true;
        else
            return false;
    }
    void constructCharCode(listBinTreeNode* T, string code, ostream &os) {
        if ( T == NULL)
            return;
        else if (isLeaf(T)){
            os << T->ChSt() << "\t" << code << endl;
        }
        else {
            constructCharCode(T->Left(), code + "0", os);
            constructCharCode(T->Right(), code + "1", os);
        }
    }
    listBinTreeNode* Root;
    
};
int main(int argc, char** argv) {
    // STEP 2: Construct Huffman ordered linked list, by the prob, and in ascending order.
    ofstream outFile1;
    ofstream outFile2;
    ofstream outFile3;
    ofstream outFile4;
    ofstream outFile5;
    outFile1.open(argv[2]); // Huffman <char code> pairs
    outFile2.open(argv[3]); // pre-order traversal of HBT
    outFile3.open(argv[4]); // in-order traversal of HBT
    outFile4.open(argv[5]); // post-order traversal of HBT
    outFile5.open(argv[6]); // for debugging outputs
    
    
    ifstream inFile;
    string chSt;
    int prob;
    HuffmanLinkedList list; // creates dummynode 
    
    inFile.open(argv[1]);
    if (!inFile) {
        cout << "Unable to read file";
        exit(1);
    }
    while (inFile >> chSt >> prob) {
        listBinTreeNode* spot = list.findSpot(prob);
        listBinTreeNode* newNode = new listBinTreeNode(chSt, prob);
        list.listInsert(spot, newNode);
        list.printList(outFile5);
    }
    inFile.close();
    
    // STEP 3: Construct Huffman binary tree.
    HuffmanBinaryTree* tree = new HuffmanBinaryTree(list, outFile5);
    tree->constructCharCode(tree->Root,"", outFile1);
    tree->postOrderTraversal(tree->Root, outFile4);
    tree->inOrderTraversal(tree->Root, outFile3);
    tree->preOrderTraversal(tree->Root, outFile2);
    
    return 0;
}

