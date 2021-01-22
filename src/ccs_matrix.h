#ifndef CSS_MATRIX_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CSS_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Class for vector 'b'
class DenseVector {
  public:
    int n;
    std::vector<double> x;
    std::vector<int> B; // Beta, set of (row) indices where vector is non-zero
    DenseVector(string filename);
};
DenseVector::DenseVector(string filename) {
  // Read in raw matrix market format
  // https://stackoverflow.com/questions/57075834/how-to-convert-matrix-market-file-to-matrix-in-c
  std::ifstream file(filename);
  int num_row, num_col, num_lines;
  while (file.peek() == '%') file.ignore(2048, '\n');       // Ignore comments headers
  file >> num_row >> num_col >> num_lines;                  // Read number of rows and columns
  
  for (int l = 0; l < num_row; l++) {x.push_back(0);}
  for (int l = 0; l < num_lines; l++)
  {
    double data;
    int row, col;
    file >> row >> col >> data;
    x.at(row-1) = data;
    B.push_back(row-1);
  }

  file.close(); 

  std::printf("vector size %i with %i nonzero entries\n", num_row, num_lines);
  n = num_row;
};

// Class for matrix 'L' in compressed column format 
class CCSMatrix {
  public:
    int n;
    int nz;
    std::vector<int> Lp;
    std::vector<int> Li;
    std::vector<double> Lx;
    CCSMatrix(string filename);
};
CCSMatrix::CCSMatrix(string filename) {
  // Read in raw matrix market format
  // https://stackoverflow.com/questions/57075834/how-to-convert-matrix-market-file-to-matrix-in-c
  std::ifstream file(filename);
  int num_row, num_col, num_lines;
  while (file.peek() == '%') file.ignore(2048, '\n'); // Ignore comments headers
  file >> num_row >> num_col >> num_lines; // Read number of rows and columns
  

  std::vector<double> vals(num_lines, 0.);
  std::vector<int> rows(num_lines);
  std::vector<int> cols(num_lines);

  // Take lower triangular
  int num_lines_lower = 0;
  for (int l = 0; l < num_lines; l++)
  {
    double data;
    int row, col;
    file >> row >> col >> data;
    if (col <= row)
    {
      rows.at(num_lines_lower) = row-1; //MM is 1-indexed so decrement
      cols.at(num_lines_lower) = col-1;
      vals.at(num_lines_lower) = data;
      num_lines_lower++;
    }
  }
  file.close(); 


  // Compress column matrix
  // Section 3.4 of https://www-users.cs.umn.edu/~saad/IterMethBook_2ndEd.pdf 
  //////
  std::vector<int> col_ptr(num_col+1);
  col_ptr.at(0) = 0;
  col_ptr.at(num_col) = num_lines_lower;
  
  int col_ptr_idx = 1;
  // MM ordered on columns so do adjacent pairwise check to column compress
  
  for (int l = 0; l < num_lines_lower-1; l++)
  {
    int aj = cols[l];
    int next_aj = cols[l+1];
    if (aj != next_aj) { col_ptr.at(col_ptr_idx) = l+1; col_ptr_idx++; };

    // Deal with last element as special case for adjacent check since only looping to num_lines-1
    if (l == num_lines-2) 
    {
      int last_aj = cols[num_lines_lower-1];
      if (next_aj != last_aj){col_ptr.at(col_ptr_idx) = l+1;}
    }
  }
  
  std::printf("matrix size (%i, %i) with %i nonzero entries, taking %i from lower triangular\n", num_row, num_col, num_lines, num_lines_lower);

  // Set attributes
  n = num_col;
  nz = num_lines_lower;
  Lp = col_ptr;
  Li = rows;
  Lx = vals;
};

#endif