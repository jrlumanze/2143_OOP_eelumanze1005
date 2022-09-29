/*****************************************************************************
*                    
*  Author:           Emmanuel Lumanze Jr
*  Email:            jr.lumanze@gmail.com
*  Label:            A03
*  Title:            Object Oriented Program
*  Course:           CMPS 2143
*  Semester:         Fall 2022
* 
*  Description:
*        T 
*        
*  Usage: 
*       - $ ./main filename
*       
*  Files:            
*       main.cpp    : driver program 

*****************************************************************************/
#include <iostream>

using namespace std;

/**
 * Huffman
 * 
 * Description:
 *      This class implements a compressions algorithm called Huffman Coding.
 *      Huffman coding assigns codes to characters such that the length of the 
 *      code depends on the relative frequency or weight of the corresponding 
 *      character. Huffman codes are of variable-length, and prefix-free
 * 
 * Public Methods:
 *                          Huffman()                               
 *      void                BuildFrequencyTable(string filename)
 *      string              LookupCode(char key)
 *      void                Analyze()
 *      map<char, string>   GetCodes()
 * 
 * Private Methods:
 *      void                _BuildLookupTable
 *      void                _BuildTree
 *      int                 _maxDepth
 * 
 * Usage: 
 * 
 *      Huffman H(filename):                        // Create Instance of Huffman
 *                                                  // and build freq table. 
 *      H.GetCodes();                               // get map <char,string> of codes
 * 
 *                                                  // or
 *      
 *      Huffman H;                                  // do seperately
 *      H.BuildFrequencyTable(filename);            // or use to re-build another file
 *      H.LookupCode('s')                           // get code for 's' 
 *      
 */

class CircularArrayQue {
private:
    int *Container;
    int Front;
    int Rear;
    int QueSize; // items in the queue
    int CurrentSize;
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }
        /**
     * Public : Push
     * 
     * Description:
     *      pushes items.
     * 
     * Params:
     *      item     :  int
     * 
     * Returns:
     *      void   : doesn't return anything.
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }
    /**
     * Public : Pop
     * 
     * Description:
     *      Loads an array of integerts into a linked list.
     * 
     * Params:
     *      int     :  temp
     * 
     * Returns:
     *      temp.
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};
  /**
     * Public : ostream
     * 
     * Description:
     *      accesses private info.
     * 
     * Params:
     *      int     :  front, CurrentSize, QueSize, Container
     * 
     * Returns:
     *      os.
     */
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5); //calls function and passes in 5

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1); //pushes 1
    C1.Push(2); //pushes 2
    C1.Push(3); //pushes 3
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl; //prints C1

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl; //prints C1
}
