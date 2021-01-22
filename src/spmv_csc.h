#ifndef SPMV_H
#define SPMV_H

#include <vector>

/* 
* Sparse matrix-vector multiply: y = A*x 
* A is stored in the compressed column storage format 
* Inputs: 
* Ap : the column pointer of A 
* Ai : the row index of A 
* Ax : the values of A 
* x : is a dense vector 
* Output: 
* y : is a dense vector that stores the result of multiplication */ 
std::vector<double> spmv_csc (int n, vector<int> Ap, vector<int> Ai, vector<double> Ax, vector<double> x)
{ 
  std::vector<double> y(n, 0.);
  // std::printf("%i, %i", p, j);
  // if (!Ap || !x || !y) return (0) ; /* check inputs */ for (j = 0 ; j < n ; j++)
  for (int j = 0 ; j < n ; j++)
  {
    for (int p = Ap [j] ; p < Ap [j+1] ; p++) { 
      y [Ai [p]] += Ax [p] * x [j];
    }
  }  
  return y ; 
}

#endif