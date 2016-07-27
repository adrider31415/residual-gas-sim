#ifndef SIMUTILS_H
#define SIMUTILS_H

//Function for wrinting array to file.
void write_arr(double *arr, string fname, int n)
{
  ofstream myfile;
  myfile.open(fname);
  for (int j=n;j>0; j--)
    {
      myfile << *(arr + n-j) << " ";
    }
  myfile.close();  
}


#endif
