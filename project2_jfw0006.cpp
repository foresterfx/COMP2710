/***********************************************************************************************
* AUTHOR: Joseph Forester Warren
* DATE: 02/07/20
* COURSE: COMP2710-001
* AU ID: JFW0006
* FILE NAME: project2_jfw0006.cpp
* COMPILE: g++ project2_jfw0006.cpp -o p2
* RUN: ./p2
*
* GOALS: 
*	To learn "while" and "do-while" statements, how to define functions, write
* 	a test driver, how to use "assert()", and to generate & use random numbers.
* 
* CODE DESCRIPTION: 
* 	A simulator for a shooting game played between 3 players. The odds for accuracy are 
* 		delcared as constants for those that aren't 100% accurate. The code runs test 
* 		functions to confirm the each function works as intended, then simulates 10,000 
* 		simulations for two different strategies for our player (Aaron) to attempt and 
*		then determines which strategy is the most effective (Strategy 2).
*
* SOURCES:
*	1. I used Piazza for help from the instructors and to clarify some of the project
* 		PDF's requirements. Some if it wasn't totally clear to me.
*	2. I used the Project 2 handout for help in creating the rand() random number
* 		generator for the odds of success in regards to shooting.
* 	3. I referenced my own Project 1 source code for outlining this source code.
*	4. I used StackOverflow for help in regards to defining constants in C++:
*			https://stackoverflow.com/questions/12042549/define-constant-variables-in-c-header
*	5. I used StackOverflow for help in regards to understanding that I must declare
*	 	a function first before main(), then after main() I have to overload the function:
* 			https://stackoverflow.com/questions/36169816/error-call-of-overloaded-is-ambiguous
*	6. I watched a YouTube video on rand() to understand what <ctime> does:
*			https://www.youtube.com/watch?v=PUGn-ctk4Tk
***********************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime> // helps create random number based off computer's local time

using namespace std;
/*****************************************************************
* CONSTANT DECLARATIONS
* 	TEST - the amount of test simulations to be performed
* 	AARON_ODDS - aarons' chance of hitting a target
* 	BOB_ODDS - bobs' chance of hitting a target
*****************************************************************/
const int TEST = 10000;
const double AARON_ODDS = 100.0 / 3.0;
const double BOB_ODDS =  100.0 / 2.0;
/*****************************************************************
* FUNCTION PROTOTYPES
*	at_least_two_alive(bool, bool, bool)
*		checks if at least 2 players are alive
*		returns boolean value
*	Aaron_shoots1(bool&, bool&)
*		checks if Aaron successfully hits target
*		sets boolean if hit && alive
*		no return value
*	Bob_shoots(bool&, bool&)
*		checks if Bob successfully hits target
*		sets boolean if hit && alive
*		no return value
*	Charlie_shoots(bool&, bool&)
*		Charlie always hits target, sets boolean value
*		no return value
*	Aaron_Shoots2(bool&, bool&)
*		Aaron misses first shot if both targets alive
*		checks if Aaron successfully hits 2nd round target
*		sets boolean if hit
*		no return value
*	pressEnter()
*		Function for "Press Enter key to continue"
*****************************************************************/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void pressEnter(); 
/*****************************************************************
* TEST DRIVERS PROTOTYPES
*****************************************************************/
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);
/*****************************************************************
* MAIN - Function for entire program's output.
*****************************************************************/
int main(){
	// PERCENT FORMATTING TO 2 DECIMALS
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	/*****************************************************************
	* VARIABLE INITIALIZATION
	*****************************************************************/
   	srand(time(0)); // random number generator
	int aaronWins = 0; // count of times Aaron survives
	int bobWins = 0; // count of times Bob survives
	int charlieWins = 0; // count of times Charlie survives
	int strat1Wins = 0; // count of times Aaron survives Strat1
	int strat2Wins = 0; // count of times Aaron survives Strat2
	bool aaronAlive = true; // Aaron alive or dead
	bool bobAlive = true; // Bob alive or dead
	bool charlieAlive = true; // Charlie alive or dead
	/*****************************************************************
	* STANDARD OUTPUT AND FUNCTION CALLING BEGINS HERE
	*****************************************************************/	
	cout << "\n***Welcome to Forester's Duel Simulator***\n";
	test_at_least_two_alive(); // checks if 2 players alive
	test_Aaron_shoots1(); // Test for Aaron hitting his target S1
	test_Bob_shoots(); // Test for Bob hitting his target
	test_Charlie_shoots(); // Test for Charlie hitting his target
	test_Aaron_shoots2(); // Test for Aaron hitting his target S2
	/*****************************************************************
	* STRATEGY 1 LOOP
	* 	Aaron attempting strategy 1 where he always shoots at Charlie
	* 	and then Bob and Charlie take their turns shooting. This loops 
	*	until only one player left alive for 10,000 rounds.
	*****************************************************************/
	cout << "Ready to test strategy 1 (run 10000 times):\n";
	pressEnter();
	int i = 0;
	do { // loops until i = 10,000 (i = sum of survivor rounds)
		while (at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
			if (aaronAlive) { // if Aaron is alive
				Aaron_shoots1(bobAlive, charlieAlive); // he shoots
				if (!bobAlive && !charlieAlive) { // if Bob & Charlie die
					aaronWins++; // Aaron wins
				}
			}
			if (bobAlive) { // if Bob is alive
				Bob_shoots(aaronAlive, charlieAlive); // he shoots
				if (!aaronAlive && !charlieAlive) { // if Aaron & Charlie die
					bobWins++; // Bob wins
				}
			}
			if (charlieAlive) { // if Charlie is alive
				Charlie_shoots(aaronAlive, bobAlive); // he shoots
				if (!aaronAlive && !bobAlive) { // if Aaron & Bob die
					charlieWins++; // Charlie wins
				}
			}
			i = aaronWins + bobWins + charlieWins; // sums victories
	} // sets all life values to true
		aaronAlive = true;
		bobAlive = true;
		charlieAlive = true;
	} while (i < TEST); // loops 10,000 times
	strat1Wins = aaronWins; // summation of Aarons' wins for Strat1

	cout << "Aaron won " << aaronWins << "/10000 duels or " << (aaronWins/10000.0) * 100 << "%\n";
	cout << "Bob won " << bobWins << "/10000 duels or " << (bobWins/10000.0) * 100 << "%\n";
	cout << "Charlie won " << charlieWins << "/10000 duels or " << (charlieWins/10000.0) * 100 << "%\n";

	/*****************************************************************
	* STRATEGY 2 LOOP
	*****************************************************************/
	cout << "\nReady to test strategy 2 (run 10000 times):\n";
	// sets individual victories to 0
	aaronWins = 0;
	bobWins = 0;
	charlieWins = 0;
	i = 0; // sets total victories to 0
	// sets all life values to true
	aaronAlive = true;
	bobAlive = true;
	charlieAlive = true;
	pressEnter();
	do { // loops until i = 10,000 (i = sum of survivor rounds)
		while (at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
			if (aaronAlive) { // if Aaron is alive
				Aaron_shoots2(bobAlive, charlieAlive); // Aaron shoots
				if (!bobAlive && !charlieAlive) { // if Bob & Charlie die
					aaronWins++; // Aaron wins
				}
			}
			if (bobAlive) { // if Bob is alive
				Bob_shoots(aaronAlive, charlieAlive); // Bob shoots
				if (!aaronAlive && !charlieAlive) { // if Aaron & Charlie die
					bobWins++; // Bob wins
				}
			}
			if (charlieAlive) { // if Charlie is alive
				Charlie_shoots(aaronAlive, bobAlive); // Charlie shoots
				if (!aaronAlive && !bobAlive) { // if Aaron & Bob die
					charlieWins++; // Charlie wins
				}
			}
			i = aaronWins + bobWins + charlieWins; // sums victories
	} // sets all life values to true
		aaronAlive = true;
		bobAlive = true;
		charlieAlive = true;
	} while (i < TEST); // loops 10,000 times
	strat2Wins = aaronWins; // summation of Aarons' wins for Strat2

	cout << "Aaron won " << aaronWins << "/10000 duels or " << (aaronWins/10000.0) * 100 << "%\n";
	cout << "Bob won " << bobWins << "/10000 duels or " << (bobWins/10000.0) * 100 << "%\n";
	cout << "Charlie won " << charlieWins << "/10000 duels or " << (charlieWins/10000.0) * 100 << "%\n";

	/*****************************************************************
	* STRATEGY COMPARISON - if StratX > StratY, cout Strat(X/Y)
	*****************************************************************/
	if (strat2Wins > strat1Wins) {
		cout << "\nStrategy 2" 
		<< " is better than strategy 1.\n\n";
	}
	else { // Odds are this will NEVER print to output
		cout << "\nStrategy 1" 
		<< " is better than strategy 2.\n\n";
	}

	return 0;
} // END OF MAIN

/*****************************************************************
* FUNCTIONS && TEST DRIVER FUNCTIONS
*****************************************************************/
void pressEnter() {
	cout << "Press Enter key to continue...";
	cin.ignore(); //Pause Command for Linux Terminal
	cout << endl;
}
/*******************************************************
* at_least_two_alive(bool, bool, bool)
* Checks if two players are alive, returns true if so
*******************************************************/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive){
	if ((A_alive && B_alive) || 
		(A_alive && C_alive) || 
		(B_alive && C_alive)) {
		return true;
}
return false;
}
/*******************************************************
* test_at_least_two_alive(void)
* Test Driver for above method with all possible inputs
*******************************************************/
void test_at_least_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";

	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true)); // TTT
	cout << "\tCase passed ...\n";

	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true)); // FTT
	cout << "\tCase passed ...\n";

	cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true)); // TFT
	cout << "\tCase passed ...\n";

	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false)); // TTF
	cout << "\tCase passed ...\n";

	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true)); // FFT
	cout << "\tCase passed ...\n";

	cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false)); // FTF
	cout << "\tCase passed ...\n";

	cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false)); // TFF
	cout << "\tCase passed ...\n";

	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false)); // TFF
	cout << "\tCase passed ...\n";

	pressEnter();
}
/*******************************************************
* Aaron_shoots1(bool&, bool&)
* Checks if Charlie is alive, then shoots at him,
* 	otherwise shoots at other player
* Sets bool value to false if hit.
*******************************************************/
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
	int shootTarget = rand() % 100;
	assert(B_alive || C_alive);
	if (shootTarget <= AARON_ODDS) {
		if (C_alive) {
			C_alive = false;
		}
		else {
			B_alive = false;
		}
	}
}
/*******************************************************
* test_Aaron_shoots1(void)
* Test Driver for above method with all possible inputs
*******************************************************/
void test_Aaron_shoots1(void) {
	bool B_alive = true;
	bool C_alive = true;
	// local variables for testing
	cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";

	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	Aaron_shoots1(B_alive, C_alive);

	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	B_alive = false;
	C_alive = true;
	Aaron_shoots1(B_alive, C_alive);

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	B_alive = true;
	C_alive = false;
	Aaron_shoots1(B_alive, C_alive);

	pressEnter();
}
/*******************************************************
* Bob_shoots(bool&, bool&)
* Checks if Charlie is alive, then shoots at him,
* 	otherwise shoots at other player
* Sets bool value to false if hit.
*******************************************************/
void Bob_shoots(bool& A_alive, bool& C_alive){
	int shootTarget = rand() % 100;
	assert(A_alive || C_alive);
	if (shootTarget <= BOB_ODDS) {
		if (C_alive){
			C_alive = false;
		}
		else {
			A_alive = false;
		}
	}
}
/*******************************************************
* test_Bob_shoots(void)
* Test Driver for above method with all possible inputs
*******************************************************/
void test_Bob_shoots(void) {
	bool A_alive = true;
	bool C_alive = true;
	// local variables for testing
	cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";

	cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	Bob_shoots(A_alive, C_alive);

	cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	A_alive = false;
	C_alive = true;
	Bob_shoots(A_alive, C_alive);

	cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Aaron\n";
	A_alive = true;
	C_alive = false;
	Bob_shoots(A_alive, C_alive);

	pressEnter();
}
/*******************************************************
* Charlie_shoots(bool&, bool&)
* Checks if Bob is alive, then shoots at him,
* 	otherwise shoots at other player
* Sets bool value to false when hit (C = 100% accurate)
*******************************************************/
void Charlie_shoots(bool& A_alive, bool& B_alive){
		assert(A_alive || B_alive);
		if (B_alive) {
			B_alive = false;
		}
		else {
			A_alive = false;
		}
}
/*******************************************************
* test_Bob_shoots(void)
* Test Driver for above method with all possible inputs
*******************************************************/
void test_Charlie_shoots(void) {
	bool A_alive = true;
	bool B_alive = true;

	cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
	cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	Charlie_shoots(A_alive, B_alive);

	cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	A_alive = false;
	B_alive = true;
	Charlie_shoots(A_alive, B_alive);

	cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
	A_alive = true;
	B_alive = false;
	Charlie_shoots(A_alive, B_alive);

	pressEnter();
}
/*******************************************************
* Aaron_shoots2(bool&, bool&)
* Checks if both players are live, then misses shot.
* Checks if Charlie is alive, then shoots at him,
* 	otherwise shoots at other player
* Sets bool value to false if hit.
*******************************************************/
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
	int shootTarget = rand() % 100;
	assert(B_alive || C_alive);
	if (B_alive && C_alive) {
		return;
	} // if both are alive, Aaron muffs his shot
	else if (shootTarget <= AARON_ODDS) {
		if (C_alive) {
		C_alive = false;
		} // shoots at Charlie if alive
		else {
			B_alive = false;
		} // shoots at Bob if alive
	}
}
/*******************************************************
* test_Aaron_Shoots2(void)
* Test Driver for above method with all possible inputs
*******************************************************/
void test_Aaron_shoots2(void) {
	bool B_alive = true;
	bool C_alive = true;
	cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
	cout << "\tCase 1: Bob alive, Charlie alive\n";
	Aaron_shoots2(B_alive, C_alive);
	cout << "\t\tAaron intentionally misses his first shot\n"
				<< "\t\tBoth Bob and Charlie are alive.\n";

	cout << "\tCase 2: Bob dead, Charlie alive\n";
	B_alive = false;
	C_alive = true;
	Aaron_shoots2(B_alive, C_alive);
	cout << "\t\tAaron is shooting at Charlie\n";

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	B_alive = true;
	C_alive = false;
	Aaron_shoots2(B_alive, C_alive);
	cout << "\t\tAaron is shooting at Bob\n";

	pressEnter();
}