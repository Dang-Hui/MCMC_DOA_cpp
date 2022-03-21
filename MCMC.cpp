#include <iostream>
#include <cmath>
#include <matrix.h>
#include <complex>
#include <vector.h>
#include <cstdlib>
#include <inverse.h>
#include <csvd.h>
#include "count.h"
#include "ap_pro_fun.h"
#include "ind_pro_fun.h"
#include "target_fun.h"
using namespace std;
using namespace splab;

void MCMC(Matrix<complex<double>>& R, Vector<double>& angles,
	Vector<double>& amplitudes, int sig_num, double f, double r)
{
	/************************生成理论阵列流形*************************/
	double PI = 3.1416;
	double c = 2.998 * 1e8;
	const complex<double> j1(0.0, 1.0);
	double tp1 = 2.0 * PI * f * r / c;
	const int antenna_num = 9;
	Matrix<complex<double>> A(antenna_num, 360);
	for (int i = 1; i <= 360;i++)
	{
		double tp2 = i * PI / 180.0;
		for (int k = 0; k < antenna_num; k++)
		{
			double tp3 = tp1 * cos(2.0 * PI * (double)k / (double)antenna_num - tp2);
			A[k][i - 1] = exp(j1 * tp3);
		}
	}
	/*********************MCMC主程序(M-H抽样)***************************/
	const int iteration = 300 * pow(2, sig_num);
	Vector<Vector<double>> mcmc_chain(iteration + 1);
	Vector<double> proposal(sig_num);
	Vector<double> startvalue(sig_num);
	double b, C;
	double  j = 0.0;
	double lanmuda;
	default_random_engine gen(time(0));//设置种子
	uniform_int_distribution<> dis(0, 359);
	CSVD<double> svd;
	svd.dec(R);
	b = svd.norm2();
	while (b / 10 > 1)
	{
		j += 1.0;
		b /= 10.0;
	}
	C = pow(10.0, j - 1.0);//寻找平稳分布最佳参数
	for (int i = 0;i < sig_num;i++)
	{
		startvalue[i] = (double)dis(gen);
	}
	mcmc_chain[0] = startvalue;
	srand(time(0));
	double u1, u2;
	for (int i = 0;i < iteration;i++)
	{
		u1 = rand() / double(RAND_MAX);
		//cout << "u1=" << u1 <<" ";
		if (u1 < 0.5)
			proposal = proposal_fun(mcmc_chain[i], i, iteration, sig_num); //自适应马尔科夫链采样
		else
			proposal = proposal_fun(sig_num); //独立马尔科夫链采样
		double t1 = target_fun(proposal, A, R, sig_num, C);
		double t2 = target_fun(mcmc_chain[i], A, R, sig_num, C);
		lanmuda = t1 / t2;
		double alpha;
		alpha = fmin(1, lanmuda);
		u2 = rand() / double(RAND_MAX);
		if (u2 <= alpha)
			mcmc_chain[i + 1] = proposal;
		else
			mcmc_chain[i + 1] = mcmc_chain[i];
	}
	/***********算法结束，计算amplitudes,angles的值*************/
	Count count;
	angles = count.majorityElement(mcmc_chain);
	for (int i = 0;i < sig_num;i++)
	{
		Matrix<complex<double>> Q(1, antenna_num);
		Matrix<double> S(1, 1);
		Matrix<complex<double>> a(antenna_num, 1);
		a.setColumn(A.getColumn((int)angles[i]), 0);
		Q = pinv(trH(a) * a) * trH(a);
		S = real(Q * R * trH(Q));
		amplitudes[i] = S[0][0];
	}
	angles += 1;
}