#include <iterator>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "spline.h"
#include <cstdio>
#include <cstdlib>

double r01();
double cdf(double vf);
bool checkSort(std::vector<double> vec);

int main() {
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

   bool p = checkSort(Vfarr);
   bool p2 = checkSort(Parr);

   if(p == true){
     std::cout<<"true" << std::endl;
   }else {
     std::cout<<"false"<<std::endl;
   }
   if(p2 == true){
     std::cout<<"true"<<std::endl;
   } else {
     std::cout<<"false"<<std::endl;
   }

     for(int i = Parr.size()-10 ;i < Parr.size(); i++){
    std::cout<< "" << Vfarr[i]<<", "<<Parr[i]<<std::endl;
   }

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

   std::ofstream f("somefile.txt");
    std::ostream_iterator<double> output_iterator(f, "\n");
    std::copy(Vs.begin(), Vs.end(), output_iterator);

    std::cout << "Done" << std::endl;

   return 0;
}

double r01(){
   double randn = rand();
   return (double)randn/RAND_MAX;
}

double cdf(double vf){
  return 0.5*(2.0-(exp(-pow(vf,2.0)/2.0)*(2.0+pow(vf,2.0))));
}

bool checkSort(std::vector<double> vec){
  for(int i = 0; i < vec.size(); i++){
    if(i != 0){
      if(vec[i] <= vec[i-1]){
	return false;
      }
    }
  }
  return true;
}





