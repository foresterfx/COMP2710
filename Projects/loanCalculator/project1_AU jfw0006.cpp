// Joseph Forester Warren
// Project1: project1_AU jfw0006.cpp
// compile in terminal using: g++ project1_AU\ jfw0006.cpp -o p1
// run code using: ./p1
//
// This code is a loan and interest calculator. It prompts the user for:
// * Their loan amount
// * Their yearly interest rate
// * Their monthly payment
// If the user can't pay the loan, then it prompts the user to enter payment again.
// It then displays an Amortization Table detailing: 
// Month, Balance, Payment, Rate, Interest, Principle
// Followed by the total months spent paying the loan and the total interest paid.
// 
//
// I got help from the notes on canvas and from the instructors on Piazza.
// I also began watching "C++ Tutorial for Beginners - Full Course"
//             by freecodecamp.org on YouTube.
// I watched "C++ Tutorial: Format Output Using Stream Manipulators"
//             by Professor Hank Stalica on YouTube.
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
   double loanAmount, interestRate, interest, monthlyPayments, payment, principal, interestCount;
   int month = 0;
   cout.precision(2);

   // User Loan input
   cout << "Loan Amount: ";
   cin >> loanAmount;
   // Interest Rate on Loan input
   cout << "Interest Rate (% per year): ";
   cin >> interestRate;
   interestRate = interestRate / 12 / 100;
   // Loop until user enters viable payment
   do { // user Monthly Payment input
      cout << "Monthly Payments: ";
      cin >> payment;
   } while ((payment - loanAmount * interestRate) <= 0);
   // Table Header -> sets 58 blank spaces = *
   cout << endl << setw(58) << setfill('*') << "" << endl
      << "       Amortization Table" << endl
      << setw(58) << "" << endl << setfill(' '); // sets blanks to empty
   // Column Labels
   cout << setw(8) << left << "Month" 
      << setw(11) << left << "Balance" 
      << setw(10) << left << "Payment" 
      << setw(10) << left << "Rate" 
      << setw(11) << left << "Interest" 
      << setw(10) << left << "Principal" << endl;
   // Loops while loanAmount is more than payment
   while (loanAmount >= payment && loanAmount > 0){
      if (month == 0) { // Month 0 Amortization values
         cout << setw(8) << left << month 
            << "$" << fixed << setw(10) << left << loanAmount 
            << setw(10) << left << "N/A" 
            << setw(10) << left << "N/A" 
            << setw(11) << left << "N/A" 
            << setw(10) << left << "N/A" << endl;
      } else { // Standard Amortization values
         interest = loanAmount * interestRate;
         principal = payment - interest;
         loanAmount = loanAmount - principal;

         cout << setw(8) << left << month 
            << "$" << fixed << setw(10) << left << loanAmount 
            << "$" << fixed << setw(9) << left << payment
            << setw(10) << left << interestRate * 100 
            << "$" << fixed << setw(10) << left << interest 
            << "$" << fixed << setw(10) << left << principal << endl;
      }
      month++; // month counter
      interestCount += interest; // interest counter per month
   }
   interest = loanAmount * interestRate; // final interest charge
   payment = loanAmount + interest; // final payment
   // Final month Amortization values
   cout << setw(8) << left << month 
      << "$" << fixed << setw(10) << left << 0.00 
      << "$" << fixed << setw(9) << left << payment
      << setw(10) << left << interestRate  * 100
      << "$" << fixed << setw(10) << left << interest 
      << "$" << fixed << setw(10) << left << loanAmount << endl;
   // Tallies total interest paid and lists months paid
   interestCount += interest;
   cout << setw(58) << setfill('*') << "" << endl
      << "\nIt takes " << month << " months to pay off the loan." << endl
      << "Total interest paid is: $" << interestCount << endl;
   return 0;
}