#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
#include <omp.h>

#include "ccs_matrix.h"
#include "graph.h"
#include "residuals.h"
#include "spmv_csc.h"
#include "lsolve.h"

using namespace std;

/* 
* Reads matrix and vector files given from first two path arguments
* and solves the lower triangular linear system using forward substitution
*/ 
int main(int argc, char** argv)
{ 
  if (argc != 4) {return (1);}
  printf("------------------------------------------------\n");
  string A_path = argv[1];        // path to market matrix file of matrix
  string b_path = argv[2];        // path to market matrix file of vector
  string mode = argv[3];          // "naive" | "sparse"

  
  CCSMatrix matrix(A_path);       // compressed column lhs matrix
  DenseVector vector(b_path);     // rhs
  
  double wt_start, wt_end;
  std::vector<double> soln;
  std::vector<double> L_soln;
  if (mode == "naive")
  {
    wt_start = omp_get_wtime();
    soln = lsolve(vector.n, matrix.Lp, matrix.Li, matrix.Lx, vector.x);
    wt_end = omp_get_wtime();
  }
  else if (mode == "sparse")
  {
    // Construct dependency graph and compute reach set to 
    DependencyGraph graph(matrix);
    std::vector<int> reach_set = graph.ReachSet(vector);

    wt_start = omp_get_wtime();
    soln = sparse_lsolve(vector.n, matrix.Lp, matrix.Li, matrix.Lx, vector.x, reach_set);
    wt_end = omp_get_wtime();  
  } else {
    return (1);
  }
  L_soln = spmv_csc(vector.n, matrix.Lp, matrix.Li, matrix.Lx, soln);
  residual_error(soln, L_soln);

  printf("... took %f seconds \n------------------------------------------------\n\n", wt_end-wt_start);


  
  // TODO
  // 
  // cout << "\n" << endl; 
  // wt_start = omp_get_wtime();
  // soln = parallel_sparse_lsolve(matrix.n, matrix.Lp, matrix.Li, matrix.Lx, vector.x, reach_set);
  // printf("took f% seconds \n", omp_get_wtime() - wt_start);
  // L_soln = spmv_csc(vector.n, matrix.Lp, matrix.Li, matrix.Lx, soln);
  // residual = residual_error(soln, L_soln);

  return (0);
}