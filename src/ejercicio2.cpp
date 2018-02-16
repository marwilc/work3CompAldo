/*
 * ejercicio2.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: marwilc
 */


#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int D = 6;
const int N1 = 6;
const int N2 = 10;

double fEvaluateInX(double x)
{
	return(1e0 / (1e0 + pow((5e0 * x/ (3e0 + D)), 2e0)));
}
void generarArray(double X[], double Y[], int n)
{
	double spacing =  (D+3e0)*2e0 / n;
	X[0]=0e0;
	Y[0]=0e0;
	X[0]=(-(D+3e0));
	Y[0]=fEvaluateInX(X[0]);
	for (int i = 1; i <= n; i++) {
			X[i]=0e0;
			Y[i]=0e0;
			X[i]=(X[i-1] + spacing);
			Y[i]= fEvaluateInX(X[i]);

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
	double Y[N2+1];
	double X[N2+1];

		generarArray(X, Y, N1); // genera el primer array bidimensional para n+1 nodos o puntos en el eje x
		splines_cubic(X, Y, N1);
		cout << endl;
		generarArray(X, Y, N2);
		splines_cubic(X, Y, N2);


	return 0;
}


