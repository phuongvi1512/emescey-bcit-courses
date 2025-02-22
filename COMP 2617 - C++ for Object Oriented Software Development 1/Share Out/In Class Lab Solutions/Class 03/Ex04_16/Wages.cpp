// Exercise 4.16 Solution: Wages.cpp
// Member-function definitions for class Wages that calculates wages.
#include <iostream>
using std::cin; 
using std::cout; 
using std::fixed;

#include <iomanip> // parameterized stream manipulators
using std::setprecision; // sets numeric output precision

#include "Wages.h" // include definition of class Wages from Wages.h

// function to calculate wages
void Wages::calculateWages()
{
   double hours; // total hours worked
   double rate; // hourly pay rate
   double salary; // gross pay

   // processing phase
   // get first employee's hours worked
   cout << "Enter hours worked (-1 to end): ";
   cin >> hours;

   // set floating-point number format
   cout << fixed << setprecision( 2 );

   // loop until sentinel value read from user
   while ( hours != -1.0 ) 
   {
      // get hourly rate
      cout << "Enter hourly rate of the worker ($00.00): ";
      cin >> rate;
      
      // if employee worked less than 40 hours
      if ( hours <= 40 )
         salary = hours * rate;
      else // else, compute "time-and-a-half" pay
         salary = 40.0 * rate + ( hours - 40.0 ) * rate * 1.5;
      
      cout << "Salary is $" << salary; // display gross pay

      // prompt for next employee's data
      cout << "\n\nEnter hours worked (-1 to end): ";
      cin >> hours;
   } // end while
} // end function calculateWages

/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/