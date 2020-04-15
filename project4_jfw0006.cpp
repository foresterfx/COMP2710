/*******************************************************************************
* AUTHOR: Joseph Forester Warren
* DATE: 04/10/20
* COURSE: COMP2710-001
* AU ID: JFW0006
* FILE NAME: project4_jfw0006.cpp
* COMPILE: g++ project4_jfw0006.cpp -o p4
* RUN: ./p4
*
* GOALS:
*   To learn how to use linked data structures (Note: no array is allowed)
*   To use strings
*   To learn creating multiple versions via conditional compilation
*   To design and implement functions
*   To perform unit testing
*
* CODE DESCRIPTION:
*   Program that allows player 1 to create trivia questions and their answers.
*   Multiple questions are organized and managed using linked data structures.
*   No arrays are allowed. Then asks player 2 those questions & stores their
*   input. Compares p2's input with p1's answer. If matches, award points.
*   If not, then display correct answer. When all questions have been asked,
*   display the total award points that p2 won.
*
* SOURCES:
* 1. I used the Project 4 handout for guidance.
* 2. I referenced my own Project 1/2/3 source code for outlinin.
* 3. I checked cplusplus.com for information on getline
*     http://www.cplusplus.com/reference/istream/istream/getline/
* 4. I asked my tutor for help on getline buffer catching and flag setting.
*******************************************************************************/
#include <assert.h>
#include <iostream>
#include <string>

using namespace std;
/*****************************************************************
* Structure for creating a linked list that holds a trivia
* question, answer, and point amount.
*****************************************************************/
struct trivia_node {
  string question;
  string answer;
  int point;
  trivia_node *next;
};
/*****************************************************************
* Creates a pointer to trivia_node.
*****************************************************************/
typedef trivia_node* ptr_node;
/*****************************************************************
* FUNCTION PROTOTYPES
******************************************************************
* init_question_list sets the default 3 questions
* add_question adds a question to the node list
* ask_question asks the questions in the node list
* Unit_Test is the test case
* contYN is the "Continue [y/n]" loop
* qCount counts the number of questions requested by the user
* getCount counts the number of questions in the node list
*****************************************************************/
void init_question_list(ptr_node& q_list);
void add_question(ptr_node& q_list);
int ask_question(ptr_node q_list, int num_ask);
void Unit_Test(void);
bool contYN(bool run);
int qCount(void);
int getCount(ptr_node& head);
/*****************************************************************
* MAIN - Function for entire program's output.
*****************************************************************/
#define trivia_quiz
// #define UNIT_TESTING
int main() {
  /*****************************************************************
  * VARIABLE INITIALIZATION
  *****************************************************************/
  ptr_node node_list = new trivia_node;
  /*******************
  * Production Mode
  *******************/
#ifdef trivia_quiz
  init_question_list(node_list);
  int num_of_questions = 3; // default questions
  bool run = true;
  //Creates a new trivia game /
  //Sets up three original questions/
  //Sets up loop for user to input his or her own questions.
  //Quiz questions are stored in linked list.
  /*****************************************************************
  * STANDARD INPUT/OUTPUT AND FUNCTION CALLING BEGINS HERE
  *****************************************************************/
  cout << "*** Welcome to Forester's Trivia Quiz Game ***\n";
  num_of_questions = qCount(); // prompts user for how many questions to ask

  if(num_of_questions > 3) {
    // if user wants 4+ questions, prompt to add more
    // otherwise, just pulls from the default questions

    while(run) {
    // while(user says 'y'), add questions
      add_question(node_list);

      if (num_of_questions == getCount(node_list)) break;
      // breaks loop once sufficient # of questions have been added

      run = contYN(run); // Verify if user wants to add more questions
    }
  }
  /*************** This is the start of Trivia game ***************/
  cout << endl;
  ask_question(node_list, num_of_questions);
  cout << "*** Thank you for playing Forester's Trivia Quiz Game. Goodbye! ***\n";
  /**************** This is the end of Trivia game ****************/
  return 0;
}
#endif
/*******************
* Debugging Mode
*******************/
#ifdef UNIT_TESTING
  cout << "*** This is a debugging version. ***\n";
  init_question_list(node_list);
  Unit_Test();
  return 0;
  }
#endif
/*****************************************************************
* FUNCTIONS && TEST DRIVER FUNCTIONS
******************************************************************
* init_question_list(ptr_node& q_list)
* initializes the quiz to have these 3 questions in the linked list.
*****************************************************************/
void init_question_list(ptr_node& q_list) {
  ptr_node ptr1 = new trivia_node;
  ptr_node ptr2 = new trivia_node;
  ptr_node ptr3 = new trivia_node;
  ptr1 = q_list;

  ptr1->next = ptr2;
  ptr2->next = ptr3;
  ptr3->next = NULL;

  ptr1->question = "How long was the shortest war on record?";
  ptr1->answer = "38";
  ptr1->point = 100;

  ptr2->question = "What was Bank of America’s original name? (Hint: Bank of Italy or Bank of Germany)";
  ptr2->answer = "Bank of Italy";
  ptr2->point = 50;

  ptr3->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
  ptr3->answer = "Wii Sports";
  ptr3->point = 20;
}
/*****************************************************************
* getCount(ptr_node& head)
* count of questions
*****************************************************************/
int getCount(ptr_node& head){
  if (head == NULL)
      return 0; // length of 0
  // count is 1 + count of remaining list
  return 1 + getCount(head->next);
}
/*****************************************************************
* contYN(bool run)
* asks user to continue
*****************************************************************/
bool contYN(bool run) {
  string flush;  // flush the rest of the line
  char choice; // users' y/n answer to loop

  do {
    cout << "Continue? [y/n]: ";
    cin >> choice; // catches first character
    choice = tolower(choice);
    getline(cin, flush); // buffer catch for any strings
  } while (flush.length() > 0 || (choice != 'y' && choice != 'n'));
  return choice == 'y';
}
/*****************************************************************
* qCount()
* asks user to specify how many questions they want to answer
*****************************************************************/
int qCount() {
  string flush;  // flush the rest of the line
  int choice;
  cout << "There are 3 default questions.\nYou can add as many as you like!\n";
  string question = "How many questions would you like to answer? ";
  while(cout << question && !(cin >> choice).good())
  { // loops question string while input is not a number
      cin.clear(); // clears cin flags
      string line;
      getline(cin, line); // catches "bad" input
      cout << "'" << line << "' is not a valid entry.\n";
  } // prevents non-numbers from being entered
  getline(cin, flush); // buffer catch for any letters after numbers
  return choice;
}
/*****************************************************************
* add_question(ptr_node& q_list)
* gives user option to add a question to the linked list.
* question is added to the front of the linked list.
*****************************************************************/
void add_question(ptr_node& head) {
  ptr_node qNode = new trivia_node; // added question
  ptr_node end = new trivia_node; // end node
  string flush;

  /* Question Data for Node */
  cout << "\nEnter a new question: ";
  getline(cin, qNode->question);
  cout << "Enter an answer: ";
  getline(cin, qNode->answer);
  while(cout << "Enter award points: " && !(cin >> qNode->point))
  {
    cin.clear();// clears cin flags
    string line;
    getline(cin, line);// catches "bad" input
    cout << "'" << line << "' is not a valid entry.\n";
  } // prevents non-numbers from being entered
  getline(cin, flush); // buffer catch for any letters after numbers

  qNode->next = NULL;
  end = head;

  /* Sets first node, or sets last node */
  if (head == NULL) { // if list is empty, tmp is first node
    head = qNode;
  }
  else {
    while(end->next != NULL) {
      end = end->next;
    } // traverses until final node
    end->next = qNode; // sets last node->next to be new question
  }
}
/*****************************************************************
* ask_question(ptr_node q_list, int num_ask)
* checks for null value, asks questions, starts the game
*****************************************************************/
int ask_question(ptr_node q_list, int num_ask) {
  int num_of_questions = 0; // number of questions in linked list
  int point_total = 0; // users accumulated points
  int value = -1;
  string user_answer; // users answer to question
  ptr_node cur_ptr = q_list; // local temp list

  // counts the amount of questions in linked list
  num_of_questions = getCount(q_list);

  if (q_list == NULL) {
    cout << "Warning - this is impossible. Contact Administrator." << endl;
    return (value = 0); // default list has 3 questions always
  }
  if(num_ask < 1) {
    cout << "Warning - the number of trivia to be asked must "
          << "be equal to or larger than 1." << endl;
    value = 1; // test case 1
  }
  else if(num_of_questions < num_ask) { // not enough questions
    cout << "Warning - There are only " << num_of_questions // amount in list
          << " of " << num_ask // amount requested
          << " question(s) available in the list." << endl;
    value = 4; // test case 4
  }
  else {
    for(int x = 0; x < num_ask; x++) {

      cout << "Question: " << cur_ptr->question << endl;
      cout << "Answer: ";

      getline(cin, user_answer);

      if (user_answer.compare(cur_ptr->answer) == 0) {
        cout  << "Your answer is correct. You receive "
                << cur_ptr->point << " points." << endl;
        point_total += cur_ptr->point;
        value = 3; // test case 2.2
      }
      else {
        // what answer should be
        cout << "Your answer is wrong. The correct answer is: "
              << cur_ptr->answer << endl;
        value = 2; // test case 2.1
      }
      cout << "Your Total Points: " << point_total << endl << endl;
      cur_ptr = cur_ptr->next;
    } // end for
   }
  return value;
}
/*****************************************************************
* Unit_Test()
* Test cases to check whether the methods work.
*****************************************************************/
void Unit_Test() {
  ptr_node node_list = new trivia_node;
  init_question_list(node_list);
  int test;

  cout << "Unit Test Case 1: Ask no questions. The program should"
        << " give a warning message." << endl;
  if ((test = ask_question(node_list, 0)) == 1){
    cout << "\nCase 1 Passed\n\n";
  } else { cout << "\nCase 1 Failed\n\n"; }

  cout << "Unit Test Case 2.1: Ask 1 question in the linked list. "
        << "The tester enters an incorrect answer." << endl;

  if ((test = ask_question(node_list, 1)) == 2){
    cout << "Case 2.1 Passed\n\n";
  } else { cout << "Case 2.1 Failed\n\n"; }

  cout << "Unit Test Case 2.2: Ask 1 question in the linked list. "
        << "The tester enters a correct answer." << endl;

  if ((test = ask_question(node_list, 1)) == 3){
    cout << "Case 2.2 Passed\n\n";
  } else { cout << "Case 2.2 Failed\n\n"; }

  cout << "Unit Test Case 3: Ask all the questions of the last trivia "
        << "in the linked list." << endl;
  if ((test = ask_question(node_list, 3)) != -1) {
    cout << "Case 3 Passed\n\n";
  } else { cout << "Case 3 Failed\n\n"; }

  cout << "Unit Test Case 4: Ask 5 questions in the linked list" << endl;

  if ((test = ask_question(node_list, 5)) == 4){
    cout << "Case 4 Passed\n\n";
  } else { cout << "Case 4 Failed\n\n"; }

  cout << "*** End of the Debugging Version ***" << endl;
}
