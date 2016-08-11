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
#include "spline.h"
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "cdf.h"

double r01();
double cdf(double vf);
//int getRandomInt(int min, int max);
//bool checkSort(std::vector<double> vec);
//double v(int rand_int);

std::vector<double> vel_returned() {
  //srand(time(NULL));
   std::vector<double> Parr;
   std::vector<double> Vfarr;

   // Parr: very small intervals, cut 0 to 20 into 10,000 partitions
   for(int i = 0; i <= 9999; i++){
     Vfarr.push_back(i * 1.0 * (8.0000/9999.000));
   }

   // Vfarr: vector containing all the cdf values for each Parr value
   for(int i = 0 ; i < Vfarr.size(); i++){
     double cdf_val = cdf(Vfarr[i]);
     Parr.push_back(cdf_val);
   }

   //bool p = checkSort(Vfarr);
   //bool p2 = checkSort(Parr);

   //if(p == true){
   //  std::cout<<"true" << std::endl;
   //}else {
   //  std::cout<<"false"<<std::endl;
   //}
   //if(p2 == true){
   //   std::cout<<"true"<<std::endl;
   //} else {
   //  std::cout<<"false"<<std::endl;
   //}

   // need to use namespace tk;
   tk::spline s;
   // call on s.set_points and pass in Parr and Vfarr
   s.set_points(Parr, Vfarr);

   // store these values into a Ps vector
   std::vector<double> Ps;

   // generate random numbers and store into Vs
   for(int i = 0; i < 1e7; i++){
     double randnum = r01();
     Ps.push_back(randnum);
   }

   // Get Vs values to store in vector from using s()
   std::vector<double> Vs;
    for(int i = 0; i < Ps.size(); i++){
     
    double Ps_i = Ps[i];
     double s_Psi = s(Ps_i);   
    Vs.push_back(s_Psi);
     
    }

    return Vs;

    //std::ofstream f("somefile.txt");
    // std::ostream_iterator<double> output_iterator(f, "\n");
    //std::copy(Vs.begin(), Vs.end(), output_iterator);

    // std::cout << "Done" << std::endl;

    //int randomInteger;
    //randomInteger = getRandomInt(0, Vs.size()-1); 
    //return Vs[randomInteger];
}

double r01(){
   double randn = rand();
   return (double)randn/RAND_MAX;
}

double cdf(double vf){
  // return 0.5*(2.0-(exp(-pow(vf,2.0)/2.0)*(2.0+pow(vf,2.0))));
  double result;
  double A;
  A = erf(vf / sqrt(2.0));
  double B;
  B = sqrt(2.0/3.14159265) * vf * exp(-pow(vf, 2.0)/2.0);
  result = A-B;
  return result;
}

#endif
