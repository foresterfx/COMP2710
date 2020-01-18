// Joseph Forester Warren
// Project1
// I got help from the notes on canvas mostly
// I also began watching "C++ Tutorial for Beginners - Full Course"
// by freecodecamp.org on YouTube.
// I watched "C++ Tutorial: Format Output Using Stream Manipulators"
// by Professor Hank Stalica on YouTube.

#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;


int main(){
   double loanAmount, interestRate, interest, monthlyPayments, payment, principal, interestCount;
   int month = 0;
   cout.precision(2);

   cout << "Loan Amount: ";
   cin >> loanAmount;

   cout << "Interest Rate (% per year): ";
   cin >> interestRate;
   interestRate = interestRate / 12 / 100;

   cout << "Monthly Payments: ";
   cin >> payment;
   cout << endl;

   while ((payment - loanAmount * interestRate) <= 0){
      cout << setw(58) << setfill('*') << "" << endl;
      cout << "Indentured Servitude; Please increase payment: $";
      cin >> payment;
   }

   cout << setw(58) << setfill('*') << "" << endl;
   cout << "       Amortization Table" << endl;
   cout << setw(58) << "" << endl;
   cout << setfill(' ');

   // Column Labels
   cout << setw(8) << left << "Month" 
      << setw(11) << left << "Balance" 
      << setw(10) << left << "Payment" 
      << setw(10) << left << "Rate" 
      << setw(11) << left << "Interest" 
      << setw(10) << left << "Principal" << endl;

   while (loanAmount > 0 && loanAmount >= payment){
      if (month == 0) {

         cout << setw(8) << left << month 
            << "$" << fixed << setw(10) << left << loanAmount 
            << setw(10) << left << "N/A" 
            << setw(10) << left << "N/A" 
            << setw(11) << left << "N/A" 
            << setw(10) << left << "N/A" << endl;
         principal = payment - interest;
      }
      else {
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
      month++;
      interestCount += interest;
   }
   interest = loanAmount * (interestRate);
   payment = loanAmount + interest;
   cout << setw(8) << left << month 
      << "$" << fixed << setw(10) << left << 0.00 
      << "$" << fixed << setw(9) << left << payment
      << setw(10) << left << interestRate  * 100
      << "$" << fixed << setw(10) << left << interest 
      << "$" << fixed << setw(10) << left << loanAmount << endl;

   interestCount += interest;
   cout << setw(58) << setfill('*') << "" << endl;
   cout << "\nIt takes " << month << " months to pay off the loan." << endl;
   cout << "Total interest paid is: $" << interestCount << endl;
   return 0;
}