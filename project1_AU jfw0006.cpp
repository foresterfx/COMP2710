/*********************************************************************************
* AUTHOR: Joseph Forester Warren
* DATE: 01/20/20
* COURSE: COMP2710-001
*
* FILE NAME: project1_AU jfw0006.cpp
* COMPILE: g++ project1_AU\ jfw0006.cpp -o p1
* RUN: ./p1
*
* This code is a loan and interest calculator. It prompts the user for:
* .Their loan amount
* .Their yearly interest rate
* .Their monthly payment
* If the user can't pay the loan, then it prompts the user to enter payment again.
* It then displays an Amortization Table detailing: 
* Month, Balance, Payment, Rate, Interest, Principle
* Followed by the total months spent paying the loan and the total interest paid.
*
* I preferred using setw(x) instead of /t because it looked better. 
*
* I got help from the notes on canvas and from the instructors on Piazza.
* I referenced the handout we received in class for some tips.
* I also began watching "C++ Tutorial for Beginners - Full Course"
*             by freecodecamp.org on YouTube.
* I watched "C++ Tutorial: Format Output Using Stream Manipulators"
*             by Professor Hank Stalica on YouTube.
*********************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;
/*******************************************************
* MAIN - function for entire program.
*******************************************************/
int main(){
   // VARIABLE INITIALIZATION
   double loanAmount, interestRate, interest, payment, principal, interestCount;
   int month = 0;
   // CURRENCY FORMATTING
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   /*******************************************************
   * USER INPUT:
   * 
   * For valid input - loan, interest, and payment must
   * be positive. They payment must also be large enough 
   * to terminate the loan.
   *******************************************************/
   // Loan Balance input
   do { // loops until loan is above $0
   cout << "\nLoan Amount: ";
   cin >> loanAmount;
   } while (loanAmount <= 0);

   // Interest Rate on Loan input
   do { // Loops until interest rate is above 0%
   cout << "Interest Rate (% per year): ";
   cin >> interestRate;
   interestRate = interestRate / 12 / 100;
   } while (interestRate <= 0);

   // Monthly Payment input
   do { // Loops until user enters viable payment
      cout << "Monthly Payments: ";
      cin >> payment;
   } while ((payment - loanAmount * interestRate) <= 0);

   /*******************************************************
   * AMORTIZATION TABLE HEADING:
   *******************************************************/   
   cout << endl << setw(59) << setfill('*') << "" << endl
      << "\tAmortization Table" << endl
      << setw(59) << "" << endl << setfill(' '); // sets blank spaces to empty

   // Column Labels
   cout << setw(8) << left << "Month" // filled with int month
      << setw(11) << left << "Balance" // filled with double loanAmount
      << setw(10) << left << "Payment" // filled with double payment
      << setw(10) << left << "Rate" // filled with double interestRate
      << setw(11) << left << "Interest" // filled with double interest
      << setw(10) << left << "Principal" << endl; // filled with double principal

   /*******************************************************
   * AMORTIZATION TABLE FILL:
   *
   * Loops only while loanAmount is more than 0
   * Breaks loop when loanAmount is less than payment
   *******************************************************/
   while (loanAmount >= payment && loanAmount > 0){
      if (month == 0) { // Month 0 Amortization values
         cout << setw(8) << left << month++ 
            << "$" << setw(10) << left << loanAmount 
            << setw(10) << left << "N/A" 
            << setw(10) << left << "N/A" 
            << setw(11) << left << "N/A" 
            << setw(10) << left << "N/A" << endl;

      } else { // Months 1+ values
         interest = loanAmount * interestRate;
         principal = payment - interest;
         loanAmount -= principal;
         // Standard Amortization values
         cout << setw(8) << left << month++ 
            << "$" << setw(10) << left << loanAmount 
            << "$" << setw(9) << left << payment
            << setw(10) << left << interestRate * 100 
            << "$" << setw(10) << left << interest 
            << "$" << setw(10) << left << principal << endl;
      }
      interestCount += interest; // interest counter per month
   }
   /*******************************************************
   * FINAL MONTH PAYMENT:
   *
   * Checks if loan is less than payment and not = 0 
   * to prevent unneccesary lines in case the principle
   * equated the loan to 0 on it's own.
   *******************************************************/   
   if (loanAmount < payment && loanAmount != 0) { 
   interest = loanAmount * interestRate; // final interest charge
   payment = loanAmount + interest; // final payment
   // Final month Amortization values
   cout << setw(8) << left << month 
      << "$" << setw(10) << left << 0.00 
      << "$" << setw(9) << left << payment
      << setw(10) << left << interestRate  * 100
      << "$" << setw(10) << left << interest 
      << "$" << setw(10) << left << loanAmount << endl;
   // Tallies total interest paid and lists months paid
   interestCount += interest;
   }
   /*******************************************************
   * TIME AND INTEREST TOTALS:
   *
   * Prints out the total months and interest until paid.
   *******************************************************/     
   cout << setw(59) << setfill('*') << "" << endl
      << "\nIt takes " << month << " months to pay off the loan." << endl
      << "Total interest paid is: $" << interestCount << endl << endl;
   return 0;
}