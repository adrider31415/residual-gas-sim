#ifndef LINALG_H
#define LINALG_H
using namespace std;

//Class to hold 3 vectors
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
  void scale(double s)
  {
    x = x*s; y = y*s; z = z*s;
  }
};

Vec3::Vec3 (double i, double j, double k)
{
  x=i; y=j; z=k;
}

Vec3::Vec3 ()
{
  x=0.; y=0.; z=0.;
  }

Vec3 v3sum(Vec3 v0, Vec3 v1)
{
  Vec3 vret;
  vret.set_values(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z);
  return vret;
}

Vec3 v3sub(Vec3 v0, Vec3 v1)
{
  Vec3 vret;
  vret.set_values(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
  return vret;
}


//Class to hold 3x3 matricies
class M3x3
{
public:
  Vec3 m0; //row 0
  Vec3 m1; //row 1
  Vec3 m2; //row 2
  void assign_row(double i, double j, double k, int r)
  {
    if (r == 0)
      {
	m0.x=i; m0.y=j; m0.z=k; 
      }
    else if (r == 1)
      {
	m1.x=i; m1.y=j; m1.z=k;
      }
    else if (r == 2)
      {
	m2.x=i; m2.y=j; m2.z=k;
      }
  }
  Vec3 matmult(Vec3 v)
  {
    Vec3 vret;
    vret.set_values(v.dot(m0), v.dot(m1), v.dot(m2));
    return vret;
  }
  void print()
  {
    m0.print();m1.print();m2.print();
  }
};

//class to rotate vectors to a coordinate system with z in normal.
class Rotater
{
  double cq;
  double sq;
public:
  //Vec3 vret;
  Vec3 a;
  M3x3 M;
  Vec3 rot_to_n(Vec3 v, Vec3 n)
  {
    if ((n.x != 0) || (n.y != 0))
      {
	Vec3 vret;
	//calculate intermediate results
	cq = n.z;
        sq = sqrt(1-cq*cq);
	a.set_values(-1.*n.y/sq, 1.*n.x/sq, 0.);

	//populate rotation matrix
	M.assign_row(cq+a.x*a.x*(1.-cq), a.x*a.y*(1-cq), a.y*sq, 0);
	M.assign_row(a.x*a.y*(1-cq), cq+a.y*a.y*(1-cq), -1.*a.x*sq, 1);
	M.assign_row(-1.*a.y*sq, a.x*sq, cq, 2);
	//M.print();

	//rotate vector
	vret = M.matmult(v);
	return vret;
      }
    else if (n.z == 1.)
      {
	return v;
      }
    else if (n.z == -1.)
      {
	v.scale(-1.);
	return v;
      }
  }
};

#endif
