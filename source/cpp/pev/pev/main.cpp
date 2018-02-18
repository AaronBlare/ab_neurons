#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <complex>
#include <mkl.h>
#include <omp.h>
#include <numeric>
#include <algorithm>
#define N 2

using namespace std;

double ax, ai, a1, a2, k0, A1, A2, gam1, gam2, tet1, tet2, tetx, kx, k1, k2, gk, ek, gl, el, gn, en, Idc;

void RUNGE4(const int Size, double *y, double t, double ff(int, double *, double, double*), double h, double *Hx);

double am(double x) { return (0.1*(x + 40.)) / (1. - exp(0.1*(-40. - x))); }
double bm(double x) { return (4.*exp((-x - 65.) / 18.)); }
double ah(double x) { return 0.07*exp(0.05*(-x - 65.)); }
double bh(double x) { return 1. / (1. + exp(0.1*(-35. - x))); }
double an(double x) { return (0.01*(x + 55.)) / (1. - exp(0.1*(-55. - x))); }
double bn(double x) { return (0.125*exp((-x - 65.) / 80.)); }

double SYS(int ir, double *x, double t, double *Hx)
{
	if (ir == 0)
	{
		double tmp = -x[10] / (1. + exp(-(x[8] + x[9] - tetx) / kx)) + Idc - gl*(x[0] - el) - gn*x[1] * x[1] * x[1] * x[2] * (x[0] - en) - gk*x[3] * x[3] * x[3] * x[3] * (x[0] - ek) + (0.*(x[0] + 90.)) / (2.*(1. + exp(-5.*(x[4] - 0.))));
		return tmp;
	}
	if (ir == 1)
	{
		double tmp = am(x[0])*(1. - x[1]) - bm(x[0])*x[1];
		return tmp;
	}
	if (ir == 2)
	{
		double tmp = ah(x[0])*(1. - x[2]) - bh(x[0])*x[2];
		return tmp;
	}
	if (ir == 3)
	{
		double tmp = an(x[0])*(1. - x[3]) - bn(x[0])*x[3];
		return tmp;
	}

	if (ir == 4)
	{
		double tmp = -x[11] / (1. + exp(-(x[8] + x[9] - tetx) / kx)) + Idc - gl*(x[4] - el) - gn*x[5] * x[5] * x[5] * x[6] * (x[4] - en) - gk*x[7] * x[7] * x[7] * x[7] * (x[4] - ek) + (0.*(x[4] + 90.)) / (2.*(1. + exp(-5.*(x[0] - 0.))));
		return tmp;
	}
	if (ir == 5)
	{
		double tmp = am(x[4])*(1. - x[5]) - bm(x[4])*x[5];
		return tmp;
	}
	if (ir == 6)
	{
		double tmp = ah(x[4])*(1. - x[6]) - bh(x[4])*x[6];
		return tmp;
	}
	if (ir == 7)
	{
		double tmp = an(x[4])*(1. - x[7]) - bn(x[4])*x[7];
		return tmp;
	}

	if (ir == 8) 
	{ 
		double tmp = -ax*(x[8] - k0*(1. + gam1*x[12])*Hx[0]);
		return tmp;
	}
	if (ir == 9) 
	{
		double tmp = -ax*(x[9] - k0*(1. + gam1*x[12])*Hx[1]);
		return tmp;
	}

	if (ir == 10) 
	{ 
		double tmp = ai*(-x[10] - A1*Hx[0]);
		return tmp;
	}
	if (ir == 11) 
	{ 
		double tmp = ai*(-x[11] - A2*Hx[1]);
		return tmp;
	}

	if (ir == 12) 
	{	
		double tmp = -a1*(x[12] - 1. / (1. + exp(-(x[8] + x[9] - tet1) / k1)));
		return tmp;
	}
	if (ir == 13) 
	{ 
		double tmp = -a2*(x[13] - 1. / (1. + exp(-(x[8] + x[9] - tet2) / k2)));
		return tmp;
	}
}

//void main()
//{
//	VSLStreamStatePtr * streams_p = new VSLStreamStatePtr[2];	// Streams for Poisson
//	VSLStreamStatePtr * streams_w = new VSLStreamStatePtr[2];	// Stream for Weibull
//	vslNewStream(&(streams_p)[0], VSL_BRNG_MCG31, 77778888);
//	vslNewStream(&(streams_w)[0], VSL_BRNG_MCG31, 77778888);
//	for (int n_id = 1; n_id < 2; n_id++)
//	{
//		vslCopyStream(&(streams_p)[n_id], (streams_p)[0]);
//		vslCopyStream(&(streams_w)[n_id], (streams_w)[0]);
//	}
//
//	for (int n_id = 0; n_id < 2; n_id++)
//	{
//		vslLeapfrogStream((streams_p)[n_id], 8 + n_id, 1000000);
//		vslLeapfrogStream((streams_w)[n_id], 8 + n_id, 1000000);
//	}
//
//	gk = 36.;
//	ek = -77.;
//	gl = 0.3;
//	el = -54.4;
//	gn = 120.;
//	en = 50.;
//	Idc = 6.3;
//
//	ax = 0.1;
//	ai = 0.1;
//	k0 = 2.;
//	gam1 = -3.;
//	gam2 = 0.;
//	a1 = 0.01; a2 = 0.01;
//	tet1 = 1.; tet2 = 1.;
//	k1 = 0.1; k2 = 0.1;
//	tetx = 1.; kx = 0.01;
//
//	double *X = new double[14];
//	double *Hx = new double[2];
//	double *Ipre = new double[2];
//	double t = 0., tout = 100.01, t_b = 0.;
//	double hs, ti1, ti2, rti, tau, pti1, pti2, pti, fin;
//	double G1, G2;
//
//	int num_sec = 100;
//	int num_steps = 1000;
//	hs = 1.0 / double(num_steps);
//
//	fin = 1.;//до 30 только //на самом деле частота f=1/0.007=143 Hz
//	
//
//	tau = 1.;
//
//	double Am, b, b0;
//
//	int curr_id = 0;
//
//	t = 0.;
//	int i, flag_1 = 0, flag_2 = 0;
//	b0 = 15.;
//	b = b0; //b=b0*(1.+gam2*Y2);
//	Am = sqrt(0.5*b*b);
//
//	// Получение pti, распределенного по Пуассону, из rti, распределенного равномерно на (0;1)
//	double p, k;
//	double *PD1 = new double[1000000];
//	double *PD2 = new double[1000000];
//
//	//---Формирование Пуссон-выборки СВ для первого нейрона--------------------  
//	int tmp = 0;
//	for (i = 0; i < 1000000; i++)
//	{
//		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, streams_p[0], 1, &tmp, fin);
//		PD1[i] = double(tmp);
//	}
//
//	//--------------------------------------------------------------------------
//
//	//---Формирование Пуссон-выборки СВ для второго нейрона--------------------  
//
//	for (i = 0; i < 1000000; i++)
//	{
//		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, streams_p[1], 1, &tmp, fin);
//		PD2[i] = double(tmp);
//	}
//	//--------------------------------------------------------------------------
//
//	for (i = 0; i < 14; i++)
//	{
//		X[i] = 0.0;
//	}
//
//	FILE *fbb;
//	fbb = fopen("Sync(gam1)fin5gam2-5d.txt", "w");
//
//	ofstream ofs = ofstream("V.txt");
//	ofs << setprecision(16) << scientific;
//
//	ti1 = pti1 = PD1[0];
//	ti2 = pti2 = PD2[0];
//	int si_1 = 0, si_2 = 0, flag1 = 0, flag2 = 0, prt = 20, cor = 0, prs = 400, prs1 = 400, prs2 = 400, cor1 = 0, cor2 = 0;
//
//	for (size_t sec_id = 0; sec_id < num_sec; sec_id++)
//	{
//		ofs << X[0] << " " << X[4] << endl;
//
//		for (size_t step_id = 0; step_id < num_steps; step_id++)
//		{
//			t = double(sec_id) + double(step_id) * hs;
//
//			if (t < ti1)
//			{
//				Ipre[0] = 0.;
//			}
//			else
//			{
//				if (flag_1 == 0)
//				{
//					Ipre[0] = 1.;
//					si_1++;
//					pti1 = PD1[si_1];
//					if (pti1 - tau > 0)
//					{
//						flag1 = 1;
//					}
//					flag_1 = 1;
//				}
//
//			}
//			if (t < ti2)
//			{
//				Ipre[1] = 0.;
//			}
//			else
//			{
//				if (flag_2 == 0)
//				{
//					Ipre[1] = 1.;
//					si_2++;
//					pti2 = PD2[si_2];
//					if (pti2 - tau > 0) flag2 = 1;
//					flag_2 = 1;
//				}
//
//			}
//
//			if (t > ti1 + tau && flag1 == 1)
//			{
//				Ipre[0] = 0.;
//				flag_1 = 0;
//				ti1 = t + pti1 - tau;
//			}
//
//			if (t > ti2 + tau && flag2 == 1)
//			{
//				Ipre[1] = 0.;
//				flag_2 = 0;
//				ti2 = t + pti2 - tau;
//			}
//
//			if (Ipre[0] - 0.5 > 0.)
//			{
//				Hx[0] = 1.;
//				b = b0*(1. + gam2*X[13]);
//
//				vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, streams_w[0], 1, &(A1), 2.0, 0.0, b);
//			}
//			else
//			{
//				Hx[0] = 0.;
//			}
//
//			if (Ipre[1] - 0.5 > 0.)
//			{
//				Hx[1] = 1.;
//				b = b0*(1. + gam2*X[13]);
//
//				vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, streams_w[1], 1, &(A2), 2.0, 0.0, b);
//			}
//			else
//			{
//				Hx[1] = 0.;
//			}
//
//			RUNGE4(14, X, t, SYS, hs, Hx);
//
//			curr_id++;
//
//
//			if (prs1 > 4000 && X[0] > -40.) // считаем число спайков первого нейрона
//			{
//				cor1++;
//				prs1 = 0;
//			}
//			if (prs2 > 4000 && X[4] > -40.) // считаем число спайков второго нейрона
//			{
//				cor2++;
//				prs2 = 0;
//			}
//			if (prs > 4000 && X[0] > -40. && X[4] > -40.) // считаем общее число спайков (длительность спайка 3 -> 300 шагов)
//			{
//				cor++;
//				prs = 0;
//			}
//
//			prs++;
//			prs1++; prs2++;
//		}
//	}
//	ofs << X[0] << " " << X[4] << endl;
//		
//	double et;
//	et = 2.*(double)cor / ((double)(cor1 + cor2));
//	printf("\n %f %d %d %d Eta =%f", gam1, cor1, cor2, cor, et);
//	fprintf(fbb, "%f %d %d %d %f %f\n", gam1, cor1, cor2, cor, et, 0.0005*(double)(cor1 + cor2));
//	fclose(fbb);
//
//	ofs.close();
//
//	delete[]PD1;
//	delete[]PD2;
//
//
//	delete[]X;
//	delete[]Hx;
//	delete[]Ipre;
//}

void main()
{
	VSLStreamStatePtr * streams_p = new VSLStreamStatePtr[2];	// Streams for Poisson
	VSLStreamStatePtr * streams_w = new VSLStreamStatePtr[2];	// Stream for Weibull
	vslNewStream(&(streams_p)[0], VSL_BRNG_MCG31, 77778888);
	vslNewStream(&(streams_w)[0], VSL_BRNG_MCG31, 77778888);
	for (int n_id = 1; n_id < 2; n_id++)
	{
		vslCopyStream(&(streams_p)[n_id], (streams_p)[0]);
		vslCopyStream(&(streams_w)[n_id], (streams_w)[0]);
	}

	for (int n_id = 0; n_id < 2; n_id++)
	{
		vslLeapfrogStream((streams_p)[n_id], 8 + n_id, 1000000);
		vslLeapfrogStream((streams_w)[n_id], 8 + n_id, 1000000);
	}

	gk = 36.;
	ek = -77.;
	gl = 0.3;
	el = -54.4;
	gn = 120.;
	en = 50.;
	Idc = 6.3;

	ax = 0.1;
	ai = 0.1;
	k0 = 2.;
	gam1 = -3.;
	gam2 = 0.;
	a1 = 0.01; a2 = 0.01;
	tet1 = 1.; tet2 = 1.;
	k1 = 0.1; k2 = 0.1;
	tetx = 1.; kx = 0.01;

	double *X = new double[14];
	double *Hx = new double[2];
	double *Ipre = new double[2];
	double t = 0., tout = 100.01, t_b = 0.; //=90min
	double hs, ti1, ti2, rti, tau, pti1, pti2, pti, fin;
	double G1, G2;

	fin = 1.;//до 30 только //на самом деле частота f=1/0.007=143 Hz
	hs = 0.001;

	tau = 1.;

	double Am, b, b0;

	int curr_id = 0;

	t = 0.;
	int i, flag_1 = 0, flag_2 = 0;
	b0 = 15.;
	b = b0; //b=b0*(1.+gam2*Y2);
	Am = sqrt(0.5*b*b);

	// Получение pti, распределенного по Пуассону, из rti, распределенного равномерно на (0;1)
	double p, k;
	double *PD1 = new double[1000000];
	double *PD2 = new double[1000000];

	//---Формирование Пуссон-выборки СВ для первого нейрона--------------------  
	int tmp = 0;
	for (i = 0; i < 1000000; i++)
	{
		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, streams_p[0], 1, &tmp, fin);
		PD1[i] = double(tmp);
	}

	//--------------------------------------------------------------------------

	//---Формирование Пуссон-выборки СВ для второго нейрона--------------------  

	ofstream ofs_p = ofstream("Poisson.txt");
	ofs_p << setprecision(16) << scientific;
	for (i = 0; i < 1000000; i++)
	{
		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, streams_p[1], 1, &tmp, fin);
		ofs_p << tmp << endl;
		PD2[i] = double(tmp);
	}
	//--------------------------------------------------------------------------

	for (i = 0; i < 14; i++)
	{
		X[i] = 0.0;
	}

	FILE *fbb;
	fbb = fopen("Sync(gam1)fin5gam2-5d.txt", "w");

	ofstream ofs = ofstream("V.txt");
	ofs << setprecision(16) << scientific;

	ofstream ofs_H = ofstream("H.txt");
	ofs_H << setprecision(16) << scientific;

	ti1 = pti1 = PD1[0];
	ti2 = pti2 = PD2[0];
	ofs_p << PD2[0] << endl;
	int si_1 = 0, si_2 = 0, flag1 = 0, flag2 = 0, prt = 20, cor = 0, prs = 400, prs1 = 400, prs2 = 400, cor1 = 0, cor2 = 0;

	while (t < tout)
	{
		if (t < ti1)
		{
			Ipre[0] = 0.;
		}
		else
		{
			if (flag_1 == 0)
			{
				Ipre[0] = 1.;
				si_1++;
				pti1 = PD1[si_1];
				if (pti1 - tau > 0)
				{
					flag1 = 1;
				}
				flag_1 = 1;
			}

		}
		if (t < ti2)
		{
			Ipre[1] = 0.;
		}
		else
		{
			if (flag_2 == 0)
			{
				Ipre[1] = 1.;
				si_2++;
				pti2 = PD2[si_2];
				if (pti2 - tau > 0) flag2 = 1;
				flag_2 = 1;
			}

		}

		if (t > ti1 + tau && flag1 == 1)
		{
			Ipre[0] = 0.;
			flag_1 = 0;
			ti1 = t + pti1 - tau;
		}

		if (t > ti2 + tau && flag2 == 1)
		{
			Ipre[1] = 0.;
			flag_2 = 0;
			ti2 = t + pti2 - tau;
		}

		if (Ipre[0] - 0.5 > 0.)
		{
			Hx[0] = 1.;
			b = b0*(1. + gam2*X[13]);

			vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, streams_w[0], 1, &(A1), 2.0, 0.0, b);
		}
		else
		{
			Hx[0] = 0.;
		}

		if (Ipre[1] - 0.5 > 0.)
		{
			Hx[1] = 1.;
			b = b0*(1. + gam2*X[13]);

			vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, streams_w[1], 1, &(A2), 2.0, 0.0, b);
		}
		else
		{
			Hx[1] = 0.;
		}

		if (curr_id % 1000 == 0)
		{
			ofs << X[0] << " " << X[4] << endl;
		}

		ofs_H << Hx[1] << endl;
		RUNGE4(14, X, t, SYS, hs, Hx);

		curr_id++;
		

		if (prs1 > 4000 && X[0] > -40.) // считаем число спайков первого нейрона
		{
			cor1++;
			prs1 = 0;
		}
		if (prs2 > 4000 && X[4] > -40.) // считаем число спайков второго нейрона
		{
			cor2++;
			prs2 = 0;
		}
		if (prs > 4000 && X[0] > -40. && X[4] > -40.) // считаем общее число спайков (длительность спайка 3 -> 300 шагов)
		{
			cor++;
			prs = 0;
		}

		prs++;
		prs1++; prs2++;

		t += hs;

	}
	double et;
	et = 2.*(double)cor / ((double)(cor1 + cor2));
	printf("\n %f %d %d %d Eta =%f", gam1, cor1, cor2, cor, et);
	fprintf(fbb, "%f %d %d %d %f %f\n", gam1, cor1, cor2, cor, et, 0.0005*(double)(cor1 + cor2));
	fclose(fbb);

	ofs.close();
	ofs_p.close();
	ofs_H.close();

	delete[]PD1;
	delete[]PD2;


	delete[]X;
	delete[]Hx;
	delete[]Ipre;

}

void RUNGE4(const int Size, double *y, double t, double ff(int, double *, double, double*), double h, double *Hx)
{
	double *k1 = new double[Size];
	double *k2 = new double[Size];
	double *k3 = new double[Size];
	double *k4 = new double[Size];
	double *y0 = new double[Size];
	double *yy = new double[Size];
	double *yy1 = new double[Size];
	int j;

	for (j = 0; j < Size; j++)
		y0[j] = y[j];

	for (j = 0; j < Size; j++) {
		k1[j] = ff(j, y0, t, Hx);
		yy[j] = y0[j] + 0.5*h*k1[j];
	}
	for (j = 0; j < Size; j++) {
		k2[j] = ff(j, yy, t + 0.5*h, Hx);
		yy1[j] = y0[j] + 0.5*h*k2[j];
	}
	for (j = 0; j < Size; j++) {
		k3[j] = ff(j, yy1, t + 0.5*h, Hx);
		yy[j] = y0[j] + h*k3[j];
	}

	for (j = 0; j < Size; j++) {
		k4[j] = ff(j, yy, t + h, Hx);
		y[j] = y0[j] + h*(k1[j] + 2.*k2[j] + 2.*k3[j] + k4[j]) / 6.;
	}

	delete[]y0;
	delete[]yy;
	delete[]yy1;
	delete[]k1;
	delete[]k2;
	delete[]k3;
	delete[]k4;

}
