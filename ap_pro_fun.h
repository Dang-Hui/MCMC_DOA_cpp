#pragma once
#ifndef AP_PRO_FUN_H_
#define AP_PRO_FUN_H_

#include <vector.h>
#include <iostream>
#include <cmath>
#include <random>
using namespace std;
using namespace splab;
//自适应马尔科夫链采样
Vector<double> proposal_fun(Vector<double> theta, int i, int iteration, int sig_num)
{
	double sig_max = 180;//标准差可达到的最大值
	double sig;
	sig = sig_max * exp(2.0 * log(sig_max) * ((((double)iteration - (double)i)
		/ (double)iteration) - 1.0));//设置方差，最小值接近0
	Vector<double> theta2(sig_num);
	random_device rd{};
	mt19937_64 gen{rd()};//设置种子
	for (int j = 0;j < sig_num;j++)
	{
		int temp = 0.0;
		normal_distribution<double> dis(theta[j], sig);
		temp = (int)abs(round(dis(gen)));
		temp = temp % 360;
		theta2[j]=temp;
	}
	return theta2;
}
#endif 
