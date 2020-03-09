//************************************************************************ 
//  file: order_of_summation_new.cpp
// 
//  Program for HW1 Problem 2 to demonstrate differences in computing summing up and summing down
//
//
//  Programmer:  Dylan Smith, smithdy6@msu.edu
//
//
//  At lower values of N, the difference divided by the average of summing up and summing down is
//  sporadic, and does not settle on one value or line. However, as N approaches higher values (near
//  10^6.5) the difference log plot has a slope of about 1. This tells us that one was more accurate
//  than another because if they were equally wrong, then we would expect a horizontal line, or no
//  discernible line at all.
//
//*************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>        // note that .h is omitted
#include <cmath>

using namespace std;		// we need this when .h is omitted

// Function to compute summing up to N from 1
float SumUp(float N) {
    float sum=0.;
    for (float i = 1; i <= N; i++)
    {
        sum+=1/i;
    }
    return sum;
}

// Function to compute summing down to 1 from N
float SumDown(float N) {
    float sum=1./N;
    for (float i = 1; i < N; i++)
    {
        sum+=1./(N-i);
    
    }
    return sum;
}

//********************** begin main ******************************
int
main ()
{
  float N = 1e+9;	// Highest value summed up to or summed down from
  ofstream my_out ("order_of_summation_new.dat");

  my_out << "#   N        SumUp       SumDown        Abs. Diff     " << endl;
    
    
  // For loop to sum up to 1/N and sum down to 1
  for (float i = 100; i < N; i=i*2)
    {
      float sum_first_sp =SumUp(i);
      float sum_last_sp =SumDown(i);
    
      my_out << fixed << setprecision (6) << setw (8) << log10(i) << " "
      << scientific << setprecision (6)
      << setw (13) << sum_first_sp << " "
      << setw (13) << sum_last_sp << " "
      << setw (13) << log10(abs(sum_first_sp-sum_last_sp)/(2*(abs(sum_first_sp)+abs(sum_last_sp))))
      << " "
      << endl;
    }
  my_out.close ();
  return (0);
}
