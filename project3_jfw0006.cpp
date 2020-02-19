/*******************************************************************************
* AUTHOR: Joseph Forester Warren
* DATE: 02/16/20
* COURSE: COMP2710-001
* AU ID: JFW0006
* FILE NAME: project3_jfw0006.cpp
* COMPILE: g++ project3_jfw0006.cpp -o p3
* RUN: ./p3
********************************************************************************
* GOALS:
*		To learn streams and file I/O.
* 	To learn how to use tools for stream I/O.
* 	To use arrays to group data elements.
* 	To design and implement functions.
* 	To perform unit testing.
* 	To design a simple algorithm.
********************************************************************************
* CODE DESCRIPTION:
* 	Program that merges the numbers in two files and writes all the numbers into
*   a third file. Takes input from two files and outputs to a third file.
*   Each input file contains a list of numbers of type int in sorted order from
*   smallest to largest. After the program is run, the output file will contain
*   all the numbers in the two input files in one longer list in sorted order.
********************************************************************************
* SOURCES:
* 1. I used the Project 3 handout for guidance.
* 2. I referenced my own Project 1/2 source code for outlining this source code.
* 3. I read user KBW's answer on cplusplus.com on creating arrays from files:
*			http://www.cplusplus.com/forum/general/148263/
* 4. I read cplusplus.com's guide on in/out streams:
*			http://www.cplusplus.com/doc/tutorial/files/
* 5. I used help from the instructors on Piazza.
*******************************************************************************/
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
#include <assert.h>
using namespace std;
/*****************************************************************
* CONSTANT DECLARATIONS ******************************************
******************************************************************
* MAX_SIZE - max array size possible
*****************************************************************/
const int MAX_SIZE = 100;
/*****************************************************************
* FUNCTION PROTOTYPES ********************************************
******************************************************************
* readFile(int, ifstream&)
*		reads file and returns array of data
* sort(int[], int, int[], int)
*		sorts the file arrays into one array
* writeFile(int[], int)
*		creates output file of new sorted array
*****************************************************************/
int readFile(int inputArray[], ifstream& inStream);
int sort(int array1[], int a1Size, int array2[], int a2Size, int output[]);
void writeFile(int output[], int outputSize);
bool checkFile(string filePath, ifstream& inStream);
/*****************************************************************
* MAIN - Function for entire program's output. *******************
*****************************************************************/
int main(){
/*****************************************************************
* VARIABLE INITIALIZATION ****************************************
*****************************************************************/
	ifstream inStream;
	int iArray1[MAX_SIZE];
	int array1Size;
	int iArray2[MAX_SIZE];
	int array2Size;
	int output[MAX_SIZE];
	int outputSize;
	/*****************************************************************
	* STANDARD INPUT/OUTPUT AND FUNCTION CALLING BEGINS HERE *********
	*****************************************************************/
	cout << "\n*** Welcome to Forester's Sorting Program ***\n";
	// first file input
	cout << "Enter the first input file name: ";
	array1Size = readFile(iArray1, inStream);
	// second file input
	cout << "Enter the second input file name: ";
	array2Size = readFile(iArray2, inStream);
	// Prints list of numbers in sorted order and create output array
	outputSize = sort(iArray1, array1Size, iArray2, array2Size, output);
	// name output array and creates file
	writeFile(output, outputSize);
	// complete
	return 0;
}
/*****************************************************************
* FUNCTIONS ******************************************************
******************************************************************
* readFile(int, ifstream&)
*		Reads file and creates array based off data in the file
*****************************************************************/
int readFile(int inputArray[], ifstream& inStream) {
	int index = 0;
	string fName; //file name
	// user enters file to read
	do {
		cin >> fName;
		inStream.open((char*)fName.c_str());
		if(inStream.fail()) {
			cout << "Please enter correct file path: ";
		} // if filename is invalid, loop
	} while(inStream.fail());
	// copies file data to inputArray
	inStream >> inputArray[index];
 	while (!inStream.eof()) {
 		index++;
 		inStream >> inputArray[index];
	} // loops until end of file data
	cout << "The list of " << index << " numbers in file " << fName << " is: \n";
	// lists file data from new array
 	for (int i = 0; i < index; i++) {
 		cout << inputArray[i] << endl;
	}
	cout << endl;
	inStream.close();
	return index;
}
/*****************************************************************
* sort(int[], int, int2[], int2)
* 	Sorts the int data from the two files in ascending order.
*****************************************************************/
int sort(int array1[], int a1Size, int array2[], int a2Size, int output[]) {
	int j = 0; // array1 loop
	int k = 0; // array2 loop
	// Lists the total size of both files' arrays
	cout << "\nThe sorted list of " << (a1Size + a2Size) << " numbers is: ";
	// creates output array that sorts array1 and array2 data
	for (int i = 0; i < (a1Size + a2Size); i++) {
		// if k >= size of array 2 OR
		// if array1 value < array2 value (only when j < a1Size)
		// set array1 as next output index
		if (k >= a2Size || (array1[j] < array2[k] && j < a1Size)) {
			output[i] = array1[j];
			j++; // increment array1 index
		}
		// otherwise set array2 value as next output index
		else {
			output[i] = array2[k];
			k++; // increment array2 index
		}
		cout << output[i] << " ";
		// increment i (output index)
	} // loops until output index (i) equal to a1+a2 size
	return (a1Size + a2Size); // returns size of array1 + array2
}
/*****************************************************************
* writeFile(int[], int)
* 	Writes the sorted data into a new single output file.
*****************************************************************/
void writeFile(int output[], int outputSize) {
	string outputFile; // local variable for output file name
	cout << "\nEnter the output file name: ";
	cin >> outputFile; // user picks file name
	ofstream finalFile(outputFile.c_str());
    for (int i = 0; i < outputSize; i++)
    {
      finalFile << output[i] << endl;
    } // adds output array numbers to new file
	cout << "*** Please check the new file - " << outputFile << " ***\n"
				<< "*** Goodbye ***\n";
}
