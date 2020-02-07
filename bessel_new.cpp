//  file: bessel_new.cpp
//
//  Spherical Bessel functions via up and down recursion, HW1 Problem 3
//                                                                     
//
//  Programmer:  Dylan Smith  smithdy6@msu.edu
//
//  Because of finite numerical precision, the computed values for j_l(x) will become a
//  mixture of j_l and n_l such that j_l^computed(x)=j_l(x)+eps*n_l(x). Thus, the region
//  in the middle with the lowest error is where this mixing of upward and
//  downward recursion has the lowest error combined; at either end of the graph,
//  the upward or downward error become the main source of error, so the middle is
//  essentially the error minimum where both upward and downward recursion error have
//  the combined lowest error.
//
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>
using namespace std;		// we need this when .h is omitted

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	        // upward algorithm
double gsl_sf_bessel_jl (int l, double x);

// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.1;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main ()
{
  double ans_down, ans_up, spher;

  // open an output file stream
  ofstream my_out ("bessel_new.dat");

  my_out << "# Spherical Bessel functions via up and down recursion" 
         << endl;
  my_out <<"       x                 down                  up                  j_10(x)                   rel err" << endl;

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      spher = gsl_sf_bessel_jl (order, x);

    my_out << fixed << setprecision (12) << setw (8) << x << "    "
	<< scientific << setprecision (12)
	<< setw (13) << ans_down << "    "
	<< setw (13) << ans_up << "    "
    << setw (13) << spher << "    "
    << setw (13) << abs(ans_down-ans_up)/(abs(ans_down)+abs(ans_up)) << "   "
        << endl;
    }
  cout << "data stored in bessel_new.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2.* double(k) + 1.) / x) * j[k] - j[k + 1];  // recur. rel.
    }
  double scale = (sin (x) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    { // recurrence relation
      term_three = ((2.*double(k) + 1.) / x) * term_two - term_one;	       
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}
