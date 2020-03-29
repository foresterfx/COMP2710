/*
 * Midterm Exam 2
 * Software Construction COMP2710
 * Instructor: Xuechao Li @ Auburn University
 */
 /*******************************************************************************
 * AUTHOR: Joseph Forester Warren
 * DATE: 03/28/20
 * COURSE: COMP2710-001
 * AU ID: JFW0006
 * FILE NAME: warren_jfw0006.cpp
 * COMPILE: g++ warren_jfw0006.cpp -o e2
 * RUN: ./e2
 *******************************************************************************/

#include<iostream>
#include<time.h>
using namespace std;

//tower of HANOI function implementation
void moveDisk(int n, char Aa, char Bb, char Cc)
{
	if (n > 0) {
		moveDisk(n-1, Aa, Cc, Bb); // recursive call until n - 1 = 0
		cout << "Move Disk " << n << " from " << Aa << " to " << Cc << endl;
		// prints cout once n = 1 and above recursive call "fails" if statement
		moveDisk(n-1, Bb, Aa, Cc); // recursive call following rules of game
	}
	// Example of calls with 3 Disk game //
	//						Aa Bb Cc
	// 					3| a  b  c
	// 					2| a  c  b
	// 					1| a  b  c
}
//main program
int main()
{
	int n;
    time_t start, end;

	cout << "Enter the number of disks:";
	cin >> n;

	//calling the moveDisk
    time (&start);
	moveDisk(n,'A','B','C');
	time (&end);

    double elapse = difftime (end, start);
    cout << "The elapsed time is " << elapse << " seconds" << " for moving " << n << " disks " << endl;

	return 0;
}
