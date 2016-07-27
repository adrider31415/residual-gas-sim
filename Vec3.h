//file for
#include <iostream>

#ifndef VEC3_H
#define VEC3_H
using namespace std;

class Vec3
{
public:
  double x;
  double y;
  double z;
  Vec3 (double, double, double);
  Vec3 ();
  void print()
  {
    cout<<x<<","<<y<<","<<z<<endl;
  }
  void set_values(double i, double j, double k)
  {
    x=i;y=j;z=k;
  }
  double dot(Vec3 v)
  {
    return v.x*x + v.y*y + v.z*z;
  }
  double vi(int i)
  {
    if (i == 0) {return x;}
    else if (i == 1) {return y;}
    else if (i == 2) {return z;}
  }
};

#endif
