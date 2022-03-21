#pragma once
#ifndef TARGET_FUN_H_
#define TARGET_FUN_H_

#include <vector.h>
#include <matrix.h>
#include <iomanip>
#include <pseudoinverse.h>
#include <svd.h>
using namespace splab;
//目标分布函数
double target_fun(Vector<double> theta, Matrix<complex<double>> A , 
	Matrix<complex<double>> R, int sig_num, double C)
{
	int r;
	double value;
	complex<double> trace;
	r = A.rows();
	Matrix<complex<double>> A_theta(r, sig_num);
	Matrix<complex<double>> P_A_theta(r, r);
	for (int i = 0;i < sig_num;i++)
	{
		A_theta.setColumn(A.getColumn((int)theta[i]), i);
	}
	P_A_theta = A_theta * pinv(trH(A_theta) * A_theta) * trH(A_theta);
	trace = sum(diag((P_A_theta * R)));
	value = exp(7.0 * real(trace) / C);
	return value;
}
#endif // !TARGET_FUN_H_

