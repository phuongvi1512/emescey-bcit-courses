// Fig. 6.8: fig06_08.cpp
// Shifted and scaled random integers.

/*
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstdlib> // contains function prototype for rand
using std::rand;
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
   // loop 20 times
   int counter;
   for ( counter = 1; counter <= 20; counter++ ) 
   {
      // pick random number from 1 to 6 and output it
      //cout << setw( 10 ) << ( 1 + rand() % 6 );
	  printf("%10d",( 1 + rand() % 6 ));

      // if counter is divisible by 5, start a new line of output
      if ( counter % 5 == 0 )
         // cout << endl;
		 printf("\n");
   } // end for

   system("pause");
   return 0; // indicates successful termination
} // end main


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
