#include "MCMC.h"

int main()
{
	FILE* fp = fopen("D:/����/��ٻ���/����/RR6.dat", "rb");//��ȡ����R
	const int length = 9 * 9 * 2;
	double* p = new double[length];
	fread(p, sizeof(double), length, fp);
	fclose(fp);
	Matrix<complex<double>> RR(9, 9);//����R����
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			int k = 9 * i + j;
			RR[i][j] = complex<double>(p[2 * k], p[2 * k + 1]);
		}
	}
	/***************************����MCMC������**************************/
	double r = 0.58;
	double f = 500 * 1e6;
	const int sig_num = 3;
	Vector<double> angles(sig_num);
	Vector<double> amplitudes(sig_num);
	MCMC(RR, angles, amplitudes, sig_num, f, r);
	cout << "������Ϊ��" << endl;
	for (int i = 0;i < sig_num;i++)
	{
		cout << angles[i] << " ";
	}
	cout << endl;
	cout << endl << "��Ӧ��ֵ�ֱ�Ϊ��" << endl;
	for (int i = 0;i < sig_num;i++)
	{
		cout << amplitudes[i] << endl;
	}
	cout << endl;
}