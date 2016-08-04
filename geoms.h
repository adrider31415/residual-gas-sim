#ifndef GEOMS_H
#define GEOMS_H

#include <vector>
#include "cdf.h"

std::vector<double> Vs_dist = vel_returned();
int getRandomInt(int min, int max);

//double r01()
//{
//  return (double)rand() / (double)RAND_MAX;
//}


//class to store minimum time to collision and minimum time normal vector.
class T_n
{
public:
  double tmin;
  Vec3  nmin;
  T_n();
};

T_n::T_n()
{
  double tmin = dubinf;
  Vec3 nmin;
}

//class representing a box that keeps particles in.
class Box
{
  double xmin, xmax, ymin, ymax, zmin, zmax;
public:
  
  T_n tn_min(Particle part, double thresh = 1e-15)
  {
    T_n tnmin;
    tnmin.tmin = dubinf;
    double t0 = part.t_x(xmin, 0);double t1 = part.t_x(xmax, 0);
    double t2 = part.t_x(ymin, 1);double t3 = part.t_x(ymax, 1);
    double t4 = part.t_x(zmin, 2);double t5 = part.t_x(zmax, 2);
    if (tnmin.tmin>t0 && t0>thresh){tnmin.tmin = t0; tnmin.nmin.set_values(1,0,0);}
    if (tnmin.tmin>t1 && t1>thresh){tnmin.tmin = t1; tnmin.nmin.set_values(-1, 0, 0);}
    if (tnmin.tmin>t2 && t2>thresh){tnmin.tmin = t2; tnmin.nmin.set_values(0,1, 0);}
    if (tnmin.tmin>t3 && t3>thresh){tnmin.tmin = t3; tnmin.nmin.set_values(0,-1,0);}
    if (tnmin.tmin>t4 && t4>thresh){tnmin.tmin = t4; tnmin.nmin.set_values(0,0,1);}
    if (tnmin.tmin>t5 && t5>thresh){tnmin.tmin = t5; tnmin.nmin.set_values(0,0,-1);}
    return tnmin;
  }
  Box(double, double, double, double, double, double);
  };

Box::Box(double xn, double xm, double yn, double ym, double zn, double zm)
{
  xmin = xn; xmax = xm; ymin = yn; ymax = ym; zmin = zn; zmax = zm;
}

//class representing a sphere
class Sphere
{
  Vec3 cent;
  double r, a, b, c, sqarg, tempt1, tempt2;
 
 public:
  Sphere(Vec3, double);
  T_n tn_min(Particle part, double thresh = 1e-15)
  {
    T_n tnmin;
    Vec3 vdiff = v3sub(part.x0, cent);
    b = 2.*part.v.dot(vdiff);
    a = part.v.dot(part.v);
    c = part.x0.dot(part.x0) - 2.*cent.dot(part.x0) - r*r;
    sqarg = b*b - 4.*a*c;
    if (sqarg < 0.)
      {
	//cout << "case0"<< endl;
	tnmin.tmin = dubinf; return tnmin;
      }
    else if (b>=0. && c>0.)
      {
	//cout << "case1"<< endl;
	tnmin.tmin = dubinf; return tnmin;
      }
    
    else
      {
	tempt1 = (-1.*b + sqrt(sqarg))/(2.*a);
	tempt2 = (-1.*b-sqrt(sqarg))/(2.*a);
      }
    if (tempt1<tempt2 && tempt1>thresh)
      {
	//cout << "case2"<< endl;
	tnmin.tmin = tempt1;//(-1.*b + sqrt(sqarg))/(2.*a);
	Vec3 x0n = part.p_t(tnmin.tmin);
	tnmin.nmin = v3sub(x0n, cent);
	//tnmin.nmin = v3sub(cent, x0n);
	tnmin.nmin.scale(1./r);
	return tnmin;
      }
    else
      {
	//cout << "case3"<< endl;
	tnmin.tmin = tempt2;//(-1.*b-sqrt(sqarg))/(2.*a);
        Vec3 x0n = part.p_t(tnmin.tmin);
	tnmin.nmin = v3sub(x0n, cent);
	//tnmin.nmin = v3sub(cent, x0n);
	tnmin.nmin.scale(1./r);
	return tnmin;
      }
  }
  
};

Sphere::Sphere(Vec3 centn, double rn)
{
  cent = centn; r = rn;
}


class Cantilever
{
 double xmin, xmax, ymin, ymax, zmin, zmax;
 
 bool on_cant(Vec3 p, int i)
 {
   bool bret, b1, b2;
   if (i==0)
     {
   b1 = (p.y >= ymin) && (p.y <= ymax );
   b2 = (p.z >= zmin) && (p.z <= zmax );
     }
   else if (i==1)
       {
   b1 = (p.x >= xmin) && (p.x <= xmax );
   b2 = (p.z >= zmin) && (p.z <= zmax );
       }
   else if (i==2)
       {
   b1 = (p.x >= xmin) && (p.x <= xmax );
   b2 = (p.y >= ymin) && (p.y <= ymax );
       }
   
   bret = b1 && b2;
   return bret;
 }
 
public:
 
 T_n tn_min(Particle part, double thresh = 1e-15)
  {
    T_n tnmin;
    tnmin.tmin = dubinf;
    double t0 = part.t_x(xmin, 0);double t1 = part.t_x(xmax, 0);
    double t2 = part.t_x(ymin, 1);double t3 = part.t_x(ymax, 1);
    double t4 = part.t_x(zmin, 2);double t5 = part.t_x(zmax, 2);
    if (tnmin.tmin>t0 && t0>thresh && on_cant(part.p_t(t0), 0)){tnmin.tmin = t0; tnmin.nmin.set_values(-1,0,0);}
    if (tnmin.tmin>t1 && t1>thresh && on_cant(part.p_t(t1), 0)){tnmin.tmin = t1; tnmin.nmin.set_values(1, 0, 0);}
    if (tnmin.tmin>t2 && t2>thresh && on_cant(part.p_t(t2), 1)){tnmin.tmin = t2; tnmin.nmin.set_values(0,-1, 0);}
    if (tnmin.tmin>t3 && t3>thresh && on_cant(part.p_t(t3), 1)){tnmin.tmin = t3; tnmin.nmin.set_values(0,1,0);}
    if (tnmin.tmin>t4 && t4>thresh && on_cant(part.p_t(t4), 2)){tnmin.tmin = t4; tnmin.nmin.set_values(0,0,-1);}
    if (tnmin.tmin>t5 && t5>thresh && on_cant(part.p_t(t5), 2)){tnmin.tmin = t5; tnmin.nmin.set_values(0,0,1);}
    return tnmin;
  }
  Cantilever(double, double, double, double, double, double);
};

Cantilever::Cantilever(double xn, double xm, double yn, double ym, double zn, double zm)
{
   xmin = xn; xmax = xm; ymin = yn; ymax = ym; zmin = zn; zmax = zm;
}

Particle collision(Particle p, Box b, Sphere s, Cantilever c, Rotater r, double thresh = 1e-25)
  
 {
   T_n tnmin = b.tn_min(p);
   T_n tnmins = s.tn_min(p);
   T_n tnminc = c.tn_min(p);
   bool sphereb = 0;
   Vec3 vold;
   if (tnmin.tmin > tnminc.tmin && tnminc.tmin > thresh)
     {
       tnmin = tnminc;
       }
   if (tnmin.tmin > tnmins.tmin && tnmins.tmin > thresh)
     {
       sphereb = 1;
       tnmin = tnmins;
       }
   p.t += tnmin.tmin;
   p.x0 = p.p_t(tnmin.tmin);
   double theta = asin(sqrt(r01()));
   double phi = 2.*PI*r01();

   int randomInt = getRandomInt(0, Vs_dist.size()-1);

   double vf = Vs_dist[randomInt];
   /*if (sphereb)
     {
       vf = 2.;
     }*/
   vold = p.v;
   p.v.set_values(vf*sin(theta)*cos(phi), vf*sin(theta)*sin(phi), vf*cos(theta));
   p.v = r.rot_to_n(p.v, tnmin.nmin);
   if (sphereb)
     {
       Vec3 vdiff = v3sub(vold, p.v);
       p.smom = v3sum(p.smom, vdiff);
       //p.smom.print();
     }
   
   
   return p;
}

int getRandomInt(int min, int max){
  srand(time(NULL));
  int rand_int;
  double fraction = 1.0 / (double) (RAND_MAX + 1.0);
  rand_int = (int)(rand() * fraction * (max-min+1) + min);
  return rand_int;
}

#endif
