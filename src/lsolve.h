#ifndef LSOLVE_H
#define LSOLVE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
#include <omp.h>

using namespace std;

/* 
* Lower triangular solver Lx=b 
* L is stored in the compressed column storage format 
* Inputs are: 
* n : the matrix dimension 
* Lp : the column pointer of L 
* Li : the row index of L 
* Lx : the values of L 
* In/Out: 
* x : the right hand-side b at start and the solution x at the end. */ 
vector<double> lsolve (int &n, vector<int> &Lp, vector<int> &Li, vector<double> &Lx, vector<double> &x)
{
  std::printf("solving system Lx=b with size %i \n", n);
  int p, j; 
  for (j = 0 ; j < n ; j++) { 
    x [j] /= Lx [Lp [j]] ; 
    for (p = Lp [j]+1 ; p < Lp [j+1] ; p++) { 
      x [Li [p]] -= Lx [p] * x [j] ; 
    } 
  }
  return x;
}


/* 
* Lower triangular solver Lx=b 
* L is stored in the compressed column storage format 
* Inputs are: 
* n : the matrix dimension 
* Lp : the column pointer of L 
* Li : the row index of L 
* Lx : the values of L 
* reach_set : column indices of L that contribute to non-zero rhs b
* In/Out: 
* x : the right hand-side b at start and the solution x at the end. */ 
vector<double> sparse_lsolve (int &n, vector<int> &Lp, vector<int> &Li, vector<double> &Lx, vector<double> &x, vector<int> &reach_set)
{
  std::printf("sparsely solving system Lx=b with size %i \n", n);

  int p, j; 
  for (int px = 0; px < int(reach_set.size()); px++) {
    j = reach_set[px];
    x [j] /= Lx [Lp [j]] ; 
    for (p = Lp [j]+1 ; p < Lp [j+1] ; p++) { 
      x [Li [p]] -= Lx [p] * x [j] ; 
    } 
  }
  return x;
}


/* 
* Lower triangular solver Lx=b with openMP
* L is stored in the compressed column storage format 
* Inputs are: 
* n : the matrix dimension 
* Lp : the column pointer of L 
* Li : the row index of L 
* Lx : the values of L 
* reach_set : column indices of L that contribute to non-zero rhs b
* In/Out: 
* x : the right hand-side b at start and the solution x at the end. */ 
vector<double> parallel_sparse_lsolve (int n, vector<int> Lp, vector<int> Li, vector<double> Lx, vector<double> x, vector<int> reach_set)
{
  std::printf("sparsely solving system Lx=b with size %i with openmp parallelism \n", n);

  int p, j; 

  // // Parallel bookkeeping
  // int nthreads;
  // #define NUM_THREADS 4
  // omp_set_num_threads(NUM_THREADS);

  for (int px = 0; px < int(reach_set.size()); px++) { //Serial loop over reach set
    j = reach_set[px];

    x [j] /= Lx [Lp [j]] ; 
    for (p = Lp [j]+1 ; p < Lp [j+1] ; p++) {
      x [Li [p]] -= Lx [p] * x [j];
    }

    // x [j] /= Lx [Lp [j]] ; 
    // vector<double> sums(n, 0.);
    // #pragma omp parallel for
    // for (p = Lp [j]+1 ; p < Lp [j+1] ; p++) {
    //   sums[p] += Lx [p] * x [j];
    //   // x [Li [p]] -= Lx [p] * x [j];
    // }
    // for (p = Lp [j]+1 ; p < Lp [j+1] ; p++) {
    //   // x [Li [p]] -= sums[p];
    // }



    // #pragma omp parallel
    // {
    //   int thread_num = omp_get_thread_num();
    //   int nthrds = omp_get_num_threads();
    //   if (thread_num == 0) {nthreads = nthrds;}
    //   // printf("hello world from ID %i of %i num_threads\n", thread_num, nthrds); 
    // }
  }
  return x;
}

#endif