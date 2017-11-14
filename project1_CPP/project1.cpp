#include <iostream>
#include <fstream>
using namespace std;



//List class
class linkedList {
    
    //  listNode class
    class listNode {
    public:
        string data;
        listNode* next;
        listNode() {};
        listNode(string d) {
            data = d;
            next = NULL;
        };
        void setData(string d) { data = d;}
        void setNext(listNode* n){ next = n;}
        string Data() { return data; }
        listNode* Next() { return next; }
    };
    
    listNode* listhead;
public:
    linkedList() {
        listNode* dummyNode = new listNode("dummy");
        listhead = dummyNode;
    }
    bool isEmpty() {
        listNode *walker = listhead;
        if (walker->Next() == NULL)
            return true;
        else
            return false;
    }
    void insert(string da, ofstream &of){
        listNode* newNode = new listNode(da);
        listNode *walker = listhead;
        while (walker->Next() != NULL && (da > walker->Next()->Data())) {
            walker = walker->Next();
        }
	newNode->setNext(walker->Next());
        walker->setNext(newNode);
           
        print(of);
    }
    void listDelete(string da) {
    }
    void print(ofstream &os) {
	listNode *walker = listhead;
        os << "listHead --> ";
	while(walker->Next() != NULL) {
            os << "(" << walker->data << "," << walker->Next()->Data() << ")" << " --> ";
            walker = walker->Next();
        }
        os << "(" << walker->data << ",NULL)" << endl;
    }
};
int main(int argc, char** argv) {
    ofstream outFile;
    string filename = argv[2];
    outFile.open(filename); 

    ifstream inFile;
    string item;
    linkedList list;

    inFile.open(argv[1]); 
    if (!inFile){
	cout << "Unable to read file";
	exit(1);
    }
    while (inFile >> item) {
	 list.insert(item, outFile);
    }
    inFile.close();
    outFile.close();
};
