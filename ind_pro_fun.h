#pragma once
#ifndef IND_PRO_FUN_H_
#define IND_PRO_FUN_H_

#include <iostream>
#include <ctime>
#include <random>
#include <vector.h>
using namespace std;
using namespace splab;
//独立马尔科夫链采样
Vector<double> proposal_fun(int sig_num)
{
	Vector<double> theta(sig_num);
	random_device rd;
	mt19937_64 gen(rd());//设置种子
	uniform_int_distribution<int> dis(0, 359);//0~359随机产生候选样本
	for (int i = 0;i < sig_num;i++)
	{
		theta[i] = dis(gen);
	}
	return theta;
}
#endif // !IND_PRO_FUN_H_

