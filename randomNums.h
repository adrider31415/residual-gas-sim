#ifndef RANDOMNUMS_H
#define RANDOMNUMS_H

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
//#include "cdf.h"

//std::vector<double> Vs_final = vel_returned();
//int getRandomInt(int min, int max);

using namespace std;
int digit[7];
long int id=0;

int getRandomInt(){
  srand(time(NULL));
  digit[6]=rand()%10; //1,XXX,XXX to 30,XXX,XXX
  for (int i=5; i>=0; i--) {
    digit[i]=rand()%10+1;
  } //Other digits
  id=digit[6]*pow(10,6)+digit[5]*pow(10,5)+digit[4]*pow(10,4)+digit[3]*pow(10,3)+digit[2]*pow(10,2)+digit[1]*10+digit[0]; //Summation
  // cout << id << "\n";
  return (int)id;
}

//void printRandomNumbers(int min, int max){
//    double randDouble = (rand()*1.0/RAND_MAX)*(max-min+1) + min;
//    int randInt = (int) randDouble;
//  std::cout<<randInt<<""<<std::endl;
//}

//double printvf(){
//  std::vector<double> Vs_final = vel_returned();
  // std::vector<double> vs_printed;
// int randomInt = getRandomInt(0, Vs_final.size()-1);
//  double Vs_print = Vs_final[randomInt];

  //std::cout<< Vs_final[randomInt] <<""<<std::endl;
  
//  return Vs_print;
//}

//int getRandomInt(int min, int max){
// srand(time(NULL));
// int rand_int;
  //double fraction = 1.0 / (double) (RAND_MAX + 1.0);
  //rand_int = (int)(rand() * fraction * (max-min+1) + min);
//  double randn = rand();
//  double temp = (double)randn/RAND_MAX;
//  rand_int = (int) temp * Vs_final.size();
// return rand_int;
//}

#endif
