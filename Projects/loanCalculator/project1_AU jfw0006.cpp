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
   double loanAmount, interestRate, interest, monthlyRate, monthlyPayments, payment, principal, interestCount;
   int month = 0;
   bool payable = true;
   cout.precision(2);
   cout << "Loan Amount: ";
   cin >> loanAmount;

   cout << "Interest Rate (% per year): ";
   cin >> interestRate;
   monthlyRate = interestRate / 12;
   cout << "Monthly Payments: ";
   cin >> payment;

   cout << setw(58) << setfill('*') << "" << endl;
   cout << "" << setw(10) << "Amortization Table" << endl;
   cout << setw(58) << "" << endl;
   cout << setfill(' ');
   cout << setw(10) << left << "Month" << setw(10) << left << "Balance" << setw(10)
      << left << "Payment" << setw(10) << left << "Rate" << setw(10) << left
      << "Interest" << setw(10) << left << "Principal" << endl;

   while (loanAmount > 0 && loanAmount >= payment){
      if (month == 0) {
         cout << month << " $" << fixed << loanAmount << " N/A " << "N/A " << "N/A" << endl;
         principal = payment - interest;
      }
      else {
         interest = loanAmount * (interestRate / 12 / 100);
         principal = payment - interest;
         loanAmount = loanAmount - principal;

         cout << month << " $" << fixed << loanAmount << " $" << fixed << payment
            << " " << monthlyRate << " $" << fixed << interest << " $" << fixed << principal << endl;
      }
      month++;
      interestCount += interest;
      if (principal <= 0) {
         payable = false;
         break;
      }
   }
   if (payable) {
      interest = loanAmount * (monthlyRate / 100);
      payment = loanAmount + interest;
      cout << month << " $" << 0.00 << " $" << fixed << payment
         << " " << monthlyRate << " $" << fixed << interest << " $" << fixed << loanAmount << endl;
      interestCount += interest;
      cout << setw(58) << setfill('*') << "" << endl;
      cout << "It takes " << month << " months to pay off the loan." << endl;
      cout << "Total interest paid is: $" << interestCount << endl;
      cout << setw(58) << "" << endl;
   }
   else {
      cout << setw(58) << setfill('*') << "" << endl;
      cout << "Indentured Servitude; Please increase payment: $";
      cin >> payment;
   }
   return 0;
}
