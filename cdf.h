#ifndef CDF_H
#define CDF_H

#include <iterator>
#include <cctype>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
//#include "spline.h"
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include "piecewiseLinear.h"
#include "randomNums.h"
//#include "cdf.h"

using namespace std;
double rand01();
double cdf(double vf);

double vel_returned(){
  vector<double> Parr; 
  vector<double> Vfarr;

   // Parr: very small intervals, cut 0 to 20 into 10,000 partitions
   for(int i = 0; i <= 99999; i++){
     Vfarr.push_back(i * 1.0 * (20.0000000000/99999.000000000));
   }

   // Vfarr: vector containing all the cdf values for each Parr value
   for(int i = 0 ; i < Vfarr.size(); i++){
     double cdf_val = cdf(Vfarr[i]);
     Parr.push_back(cdf_val);
   }

   //std::ofstream f1("Parr.txt");
   // std::ostream_iterator<double> output_iterator1(f1, "\n");
   // std::copy(Parr.begin(), Parr.end(), output_iterator1);

   //std::ofstream f2("Vfarr.txt");
   // std::ostream_iterator<double> output_iterator2(f2, "\n");
   // std::copy(Vfarr.begin(), Vfarr.end(), output_iterator2);

  solve_sys(Vfarr, Parr);

 // store these values into a Ps vector
    std::vector<double> Ps;

   // generate random numbers and store into Vs
       for(int i = 0; i < 1e7; i++){
           double randnum = rand01();
          Ps.push_back(randnum);
       }

   // Get Vs values to store in vector from using s()
        std::vector<double> Vs;

   //int counter = 0;

      for(int i = 0; i < Ps.size(); i++){
     
          double Ps_i = Ps[i];

	  double value = linear_extrapolate(Ps_i, Parr);
  
      Vs.push_back(value);
     
      }

      //double value = linear_extrapolate(d, Parr);

      // std::ofstream f("somefile.txt");
      //std::ostream_iterator<double> output_iterator(f, "\n");
      //std::copy(Vs.begin(), Vs.end(), output_iterator);

    int randInt = getRandomInt();
    //std::cout<<Vs[randInt] << "" <<std::endl;
    return Vs[randInt];

}

double cdf(double vf){
  // return 0.5*(2.0-(exp(-pow(vf,2.0)/2.0)*(2.0+pow(vf,2.0))));
  double result;
  double A;
  //A = erf(vf / sqrt(2.0));
  A = -exp(-pow(vf, 2.0)/2.0);
  double B;
  B = pow(vf, 2.0)+ 2.00000000;
  //B = sqrt(2.0/3.14159265) * vf * exp(-pow(vf, 2.0)/2.0);
  result = (2.00000000 + A*B)*0.5;
  return result;
}

double rand01(){
   double randn = rand();
   return randn/RAND_MAX;
}
