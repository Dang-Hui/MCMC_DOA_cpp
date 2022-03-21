#pragma once
#include <matrix.h>
#include <vector.h>
#include <complex>
using namespace splab;
void MCMC(Matrix<complex<double>>& R, Vector<double>& angles,
Vector<double>& amplitudes, int sig_num, double f, double r);
