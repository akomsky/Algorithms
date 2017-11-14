//
//  main.cpp
//  Project 3
//
//  Created by Amanda Komsky on 9/13/17.
//  Copyright © 2017 Amanda Komsky. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

void printArray(int arr[], ostream &os) {
    int idx = 0;
    char symbol;
    while (idx < 256) {
        if (arr[idx] > 0) {
            symbol = (char)idx;
            os << symbol << "\t" << arr[idx] << endl;
        }
        idx++;
    }
}

// List class
class linkedList {
    // listNode class
    class listNode {
    public:
        string symbol;
        int count;
        string codePattern;
        listNode* next;
        listNode* left;
        listNode* right;
        listNode* parent;
        listNode() {
            symbol = "dummy";
            count = 0;
            codePattern = "";
            next = NULL;
            left = NULL;
            right = NULL;
            parent = NULL;
            
        };
        listNode(string sym, int ct) {
            symbol = sym;
            count = ct;
            codePattern = "";
            next = NULL;
            left = NULL;
            right = NULL;
            parent = NULL;
        };
        void setSymbol(string sym) { symbol = sym; }
        void setCount(int ct) { count = ct; }
        void setNext(listNode* n) { next = n; }
        void setParent(listNode* p) { parent = p; }
        void setLeft(listNode* l) { left = l; }
        void setRight(listNode* r) { right = r; }
        string Symbol() { return symbol; }
        int Count() { return count; }
        listNode* Next() { return next; }
    }; // end of node class
    
    listNode* listhead;
    listNode* oldhead;
public:
    linkedList() {
        listNode* dummyNode = new listNode;
        listhead = dummyNode;
        oldhead = dummyNode;
    }
    bool isEmpty() {
        listNode *walker = listhead;
        if (walker->Next() == NULL)
            return true;
        else
            return false;
    }
    void insert(string sym, int ct, ofstream &of){
        listNode* newNode = new listNode(sym, ct);
        listNode *walker = oldhead;
        while (walker->Next() != NULL && (ct > walker->Next()->Count())) {
            walker = walker->Next();
        }
        newNode->setNext(walker->Next());
        walker->setNext(newNode);
        
        print(of);
    }
    void listDelete(string da) {
    }
    // make Huffman binary tree:
    void HufBinTree(ofstream &of) {
       // oldhead = listhead;
        listNode* newNode = new listNode;
       // listNode* walker = listhead;
        while (listhead != NULL) {
            newNode->setSymbol(listhead->Symbol() + listhead->Next()->Symbol());
            newNode->setLeft(listhead);
            newNode->setRight(listhead->Next());
            newNode->setCount(listhead->Count() + listhead->Next()->Count());
            listhead = listhead->Next()->Next();
            cout << "The list head is : " << listhead->Symbol() << endl;
            insert(newNode->Symbol(), newNode->Count(), of);
        }
    }

    void print(ofstream &os) {
        listNode *walker = listhead;
        os << "listHead --> ";
        while(walker != NULL) {
            os << "(" << walker->Symbol() << ":" << walker->Count() << ")" << " --> ";
            walker = walker->Next();
        }
        os << endl << endl;
        //os << "(" << walker->Symbol() << ":" << walker->Count() << ")" << endl;
    }
};
int main(int argc, char** argv) {
    ofstream outFile;
    outFile.open(argv[2]); // output.txt
    
    ifstream inFile;
    char charIn;
    int index;
    int charCounts[256] = {0};
    
    inFile.open(argv[1]); // input.txt;
    if( !inFile) {
        cout << "Unable to read file";
        exit(1);
    }
    while (inFile >> charIn) {
        index = (int)charIn;
        charCounts[index]++;
    }
    printArray(charCounts, outFile);
    inFile.close();
    outFile.close(); // this file has the new info for the nodes
    
    inFile.open(argv[2]); // open up the char file
    outFile.open(argv[3]); // output it to a new file
    string sym;
    int ct;
    linkedList list;
    
    if ( !inFile) {
        cout << "Unable to read new file";
        exit(1);
    }
    while (inFile >> sym >> ct) {
        list.insert(sym, ct, outFile);
    }
    list.HufBinTree(outFile);
    inFile.close();
    
    return 0;
}
