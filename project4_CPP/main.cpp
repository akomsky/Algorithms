#include <iostream>
#include <fstream>
using namespace std;

class HeapSort {
public:
    int rootIndex;
    int fatherIndex;
    int leftKidIndex;
    int rightKidIndex;
    int minKidIndex;
    int *heapAry;
    
    HeapSort(int count){
        heapAry = new int[count+1];
        heapAry[0] = 0;
    }
    void buildHeap(ifstream &is, string filename, ostream &os){
        rootIndex = 1;
        int data;
        is.open(filename);
        while (is >> data){
            insertOneDataItem(data);
            int kidIndex = heapAry[0];
            bubbleUp(kidIndex);
            printHeap(os);
        }
    }
   void deleteHeap(ostream &os){
        while(heapAry[0] != 0){
            deleteRoot(os);
        }
    }
    void insertOneDataItem(int data){
        heapAry[0]++;
        heapAry[heapAry[0]] = data;
    }
    int getRoot(){
        return heapAry[1];
    }
    void deleteRoot(ostream &os) {
        int data = getRoot();
        os << data << endl;
        heapAry[1] = heapAry[heapAry[0]];
        heapAry[0]--;
        fatherIndex = rootIndex;
        bubbleDown(fatherIndex);
        printHeap(os);
    }
    void bubbleUp(int kidIndex){
        if(isRoot(kidIndex))
            return;
        else {
            fatherIndex = kidIndex / 2;
            if (heapAry[kidIndex] < heapAry[fatherIndex]) {
                int temp = heapAry[kidIndex];
                heapAry[kidIndex] = heapAry[fatherIndex];
                heapAry[fatherIndex] = temp;
            }
            bubbleUp(fatherIndex);
        }
    }
    void bubbleDown(int fatherIndex){
        if (isLeaf(fatherIndex)){
            return;
        }
        else {
            leftKidIndex = fatherIndex * 2;
            rightKidIndex = fatherIndex * 2 + 1;
            minKidIndex = findMinKidIndex(leftKidIndex, rightKidIndex);
            if (heapAry[minKidIndex] < heapAry[fatherIndex]) {
                int temp = heapAry[minKidIndex];
                heapAry[minKidIndex] = heapAry[fatherIndex];
                heapAry[fatherIndex] = temp;
            }
            bubbleDown(minKidIndex);
        }
    }
    bool isLeaf(int index){
        if ((index * 2 + 1) > heapAry[0] && (index * 2) > heapAry[0] )
            return true;
        else
            return false;
    }
    bool isRoot(int index){
        if (index == 1)
            return true;
        else
            return false;
    }
    int findMinKidIndex(int left, int right){
        if( (left > heapAry[0])  || heapAry[right] < heapAry[left])
            return right;
        else
            return left;
        
    }
    bool isHeapEmpty(){
        if (heapAry[0] == 0)
            return true;
        else
            return false;
    }
    bool isHeapFull(int count){
        if (heapAry[0] == count+1)
            return true;
        else
            return false;
    }
    void printHeap(ostream &os){
        int i = 0;
        while (i <= heapAry[0]) {
            os << heapAry[i] << " ";
            i++;
        }
        os << endl;
    }
};

int main(int argc, char** argv) {
    ifstream inFile;
    int count = 0;
    int data;
    string inFileName = argv[1];
    inFile.open(inFileName);
    if (!inFile){
        cout << "Unable to read file";
        exit(1);
    }
    while (inFile >> data) {
        count++;
    }
    inFile.close();
    HeapSort heapAry = *new HeapSort(count);
    ofstream outFile1;
    outFile1.open(argv[2]);
    ofstream outFile2;
    outFile2.open(argv[3]);
    heapAry.buildHeap(inFile, inFileName, outFile1);
    heapAry.deleteHeap(outFile2);
    outFile1.close();
    outFile2.close();
    
    return 0;
}

