/*
 * ejercicio4.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: marwilc
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int D = 6;
const int N1 = 17;
const int N2 = 17;

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2-x1,2e0) + pow(y2-y1,2e0));
}
void generarArray(double X[], double Y[], double& tDist)
{
	for(int i = 0; i < N2; i++)
	{
		cin >> X[i];
		cin >> Y[i];
		if(i>0)
		{
			tDist += distance(X[i-1], Y[i-1], X[i], Y[i]);
		}
	}
}
void generarT(double X[], double Y[], double T[], double tDist)
{
	double dist=0;
	T[0]=0e0;
	for (int i = 1; i < N2; i++) {
		dist+=distance(X[i-1], Y[i-1], X[i], Y[i]);
		T[i]=dist/tDist;
	}

}
void splines_cubic(double X[], double Y[], int n)
{
	double H[n];
	double Alfa[n];
	double l[n];
	double u[n];
	double z[n];
	double c[n];
	double b[n];
	double d[n];
	int cont;

	for (int i = 0; i <= n - 1 ; i++) {
		H[i]= X[i+1] - X[i];
	}

	for (int i = 1; i <= n - 1; i++) {
		Alfa[i]= (3e0/H[i]) * (Y[i+1]-Y[i]) - (3e0/H[i-1]) * (Y[i]-Y[i-1]);
	}

	l[0]=1e0;
	u[0]=0e0;
	z[0]=0e0;

	for (int i = 1; i <= n-1; i++) {
		l[i]=(2e0*(X[i+1]-X[i-1])- H[i-1]*u[i-1]);
		u[i]=H[i]/l[i];
		z[i]=(Alfa[i]-H[i-1]*z[i-1])/l[i];
	}

	l[n]=1;
	z[n]=0;
	c[n]=0;

	for (int j = n-1; j >= 0; j--) {
		c[j]= z[j] - u[j] * c[j+1];
		b[j]= (Y[j+1] - Y[j]) / H[j] - H[j] * (c[j+1] + 2e0 * c[j]) / 3e0;
		d[j]= (c[j+1] - c[j]) / (3e0 * H[j]);

	}


	cout <<left << setw(20)<< "ai" <<setw(35)<< "bi"<< setw(35)<< "ci" <<setw(20)<< "di"<<endl;
	for (int j = 0; j <= n-1; j++) {
		cont=0;
		cout << setprecision(5) <<left
			 << setw(15) << Y[j] << setw(5) << '+'
			 << b[j];
		cout << "( x - " << X[j] << ")^" << setw(5) << ++cont << setw(5) << '+'
			 << c[j];
		cout << "( x - " << X[j] << ")^" << setw(5) << ++cont << setw(5) << '+'
			 <<d[j];
		cout << "( x - " << X[j] << ")^" << setw(5) << ++cont << setw(5)
			 << endl;


		}

}

int main ()
{
	double Y[N2];
	double X[N2];
	double totalDist=0e0;
	double T[N2];
		generarArray(X, Y, totalDist); // genera el primer array bidimensional para n+1 nodos o puntos en el eje x
		generarT(X,Y,T, totalDist);
		splines_cubic(T, X, N2);
		cout << endl;
		splines_cubic(T, Y, N2);
		//cout << endl;
		//generarArray(X, Y, N2);



	return 0;
}

