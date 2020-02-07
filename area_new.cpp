//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius. HW1, Problem 1
//
//  Programmer:  Dylan Smith    smithdy6@msu.edu
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//      -Done by defining setprecision() in the output statement
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>	     // this has the cout, cin definitions
#include <iomanip>
#include <fstream>
#include <stdio.h>      /* printf */
#include <math.h>
using namespace std;     // if omitted, then need std::cout, std::cin
using std::endl;
using std::cin;
using std::cout;
using std::setprecision;

//*********************************************************************//

const double pi = 4*atan(1);   // define pi as a constant

inline double square (double x){
    return x*x;
}

int
main ()
{
    
    ofstream out;
    out.open("area_new.dat");
    
  double radius;    // every variable is declared as int or double or ...

  cout << "Enter the radius of a circle: ";    // ask for radius
  cin >> radius;
    
  if(radius < 0)
  {
    cout << "Please enter a positive radius." << endl;
  }
  else {


    double area = pi * square(radius);	// standard area formula

    out << "radius = " << setprecision(10) << radius << ",  area = " << area << endl;
    
    out.close();
  }
  return 0;			// "0" for successful completion
}

//*********************************************************************//

