#include "MCMC.h"

int main()
{
	FILE* fp = fopen("D:/桌面/暑假华日/数据/RR6.dat", "rb");//读取矩阵R
	const int length = 9 * 9 * 2;
	double* p = new double[length];
	fread(p, sizeof(double), length, fp);
	fclose(fp);
	Matrix<complex<double>> RR(9, 9);//生成R矩阵
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			int k = 9 * i + j;
			RR[i][j] = complex<double>(p[2 * k], p[2 * k + 1]);
		}
	}
	/***************************调用MCMC输出结果**************************/
	double r = 0.58;
	double f = 500 * 1e6;
	const int sig_num = 3;
	Vector<double> angles(sig_num);
	Vector<double> amplitudes(sig_num);
	MCMC(RR, angles, amplitudes, sig_num, f, r);
	cout << "测向结果为：" << endl;
	for (int i = 0;i < sig_num;i++)
	{
		cout << angles[i] << " ";
	}
	cout << endl;
	cout << endl << "对应幅值分别为：" << endl;
	for (int i = 0;i < sig_num;i++)
	{
		cout << amplitudes[i] << endl;
	}
	cout << endl;
}