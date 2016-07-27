//test of vector roation code.
#include <iostream>
#include <math.h>
#include <limits>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include "linalg.h"
#include "particle.h"
#include "geoms.h"
#include "simutils.h"
using namespace std;



Vec3 sim_pos(int nsim,bool write, int ntherm = 1000, string fbase = "junk")
{

  double sep = 0.3;
  double l = 10.*sep;
  double d = sep+0.025;
  string sstr = to_string(sep);
  
  //initialize sim
  time_t timer = time(NULL);
  int seed = timer + getpid();
  //cout << seed << endl;
srand(seed);
  Rotater r;
  
  //geoms
  Box b(-l, l, -l, l, -l, l);
  Vec3 cent(0, 0, 0);
  Sphere s(cent, 0.025);
  Cantilever c(-l, l, d, l, -0.05, 0.05);

  //particle
  Particle p;
  p.x0.set_values(0, 0, 1);
  p.v.set_values(0, 0, -1);

  //thermalize
  for (int n=ntherm; n>0; n--)
    {
      p = collision(p, b, s, c, r);	  
    }
  p.t = 0;
  p.smom.set_values(0, 0, 0);
	
  if (write)
    {
      //allocate memory for saving poistions
      double xarr[nsim];
      double yarr[nsim];
      double zarr[nsim];
      
      //loop over collisions
      for (int n=nsim; n>0; n--)
	{
	  *(xarr + nsim-n) = p.x0.x; *(yarr + nsim-n) = p.x0.y; *(zarr + nsim-n) = p.x0.z;

	  p = collision(p, b, s, c, r);	  
	}

    
      write_arr(xarr, fbase + "x.txt", nsim);
      write_arr(yarr, fbase + "y.txt", nsim);
      write_arr(zarr, fbase + "z.txt", nsim);
    }
  else
    {
      for (int n=nsim; n>0; n--)
	{
	  p = collision(p, b, s, c, r);	  
	}
	  
    }
  Vec3 vret = p.smom;
  vret.scale(1/p.t);
  return vret;
}

void rep_sim(int nreps, string fbase, int ncollisions = 100000000)
{
  double xarr[nreps];
  double yarr[nreps];
  double zarr[nreps];
  Vec3 fret;
  for (int n = 0; n < nreps; n++)
    {
      fret  = sim_pos(ncollisions, 0);
       *(xarr + n) = fret.x; *(yarr + n) = fret.y; *(zarr + n) = fret.z;
    }
  write_arr(xarr, fbase + "x.txt", nreps);
  write_arr(yarr, fbase + "y.txt", nreps);
  write_arr(zarr, fbase + "z.txt", nreps);
}

int main(int argc, char* argv[])
{
  rep_sim(10, argv[1]);
  return 0;
  }

    
