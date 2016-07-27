#ifndef PARTICLE_H
#define PARTICLE_H
using namespace std;

double dubinf = numeric_limits<double>::infinity();
double PI = 3.14159265359;

//Class representing a particle.
class Particle
{
public:
  Vec3 smom; //momentum transfered to sphere;
  Vec3 x0;
  Vec3 v;
  double t;
  //particles position at time t2
  Vec3 p_t(double t2)
  {
    Vec3 vr;
    vr.set_values(x0.x + v.x*t2, x0.y + v.y*t2, x0.z + v.z*t2);
    return vr;
  }
  
  //time particle's indx'th coordinate reaches x1
  double t_x(double x1, int indx)
  {
    double tret;
    if (v.vi(indx) !=0.)
      {
	tret = (x1 - x0.vi(indx))/(v.vi(indx));
	if (tret > 0.) {return tret;}
	else {return dubinf;}
      }
    else {return dubinf;}
  }
    
};

#endif
