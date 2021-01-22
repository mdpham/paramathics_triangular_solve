#ifndef RESIDUALS_H
#define RESIDUALS_H

#include <bits/stdc++.h>
#include <cmath>
#include <vector>


// p-norms
double linf_distance(vector<double> x, vector<double> y)
{
  double max = 0.; double diff;
  for (int i=0; i<int(x.size()); ++i) {
    diff = abs(x[i] - y[i]);
    if (max <= diff) { max = diff; }
  }
  return max;
}

double linf_norm(vector<double> x)
{
  double max = 0.;
  for (int i=0; i<int(x.size()); ++i) { if (max <= abs(x[i])) { max = abs(x[i]); } }
  return max;
}

double l1_distance(vector<double> x, vector<double> y)
{
  double accum = 0.;
  for (int i = 0; i < int(x.size()); ++i) {accum += abs(x[i] - y[i]);};
  return accum;
}

double l1_norm(vector<double> x)
{
  double accum = 0.;
  for (int i = 0; i < int(x.size()); ++i) {accum += abs(x[i]);};
  return accum;
}

double l2_distance(vector<double> x, vector<double> y)
{
  double accum = 0.;
  for (int i = 0; i < int(x.size()); ++i) {accum += pow(x[i] - y[i], 2);};
  accum = sqrt(accum);
  return accum;
}

double l2_norm(vector<double> x)
{
  double accum = 0.;
  for (int i = 0; i < int(x.size()); ++i) {accum += pow(x[i], 2);};
  accum = sqrt(accum);
  return accum;
}

double residual_error(vector<double> b, vector<double> A_x)
{
  // backward error is norm of residual r = b - A * x_approx
  double relative_r = linf_distance(b, A_x)/linf_norm(b);
  printf("\trelative backward error in l_inf: %f \n", relative_r);
  relative_r = l1_distance(b, A_x)/l1_norm(b);
  printf("\trelative backward error in l1: %f \n", relative_r);
  relative_r = l2_distance(b, A_x)/l2_norm(b);
  printf("\trelative backward error in l2: %f \n", relative_r);
  
  return relative_r;
}

#endif