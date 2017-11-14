#include <iostream>
#include <fstream>
using namespace std;

void printArray(int arr[], ostream &os){
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

int main(int argc, char** argv) {
    ofstream outFile;
    outFile.open(argv[2]);
    
    ifstream inFile;
    char charIn;
    int index;
    int charCounts[256] = {0};
    
    inFile.open(argv[1]);
    if (!inFile) {
        cout << "Unable to read file";
        exit(1);
    }
    while(inFile >> charIn) {
        index = (int)charIn;
        charCounts[index]++;
    }
    printArray(charCounts, outFile);
    inFile.close();
    outFile.close();
    return 0;
}

