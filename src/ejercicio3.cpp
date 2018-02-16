/*
 * ejercicio3.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: marwilc
 */





#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const int D = 6;
const int N1 = 6;
const int N2 = 10;


double fEvaluateInX(double x)
{
	return(1e0 / (1e0 + powf((5e0 * x/ (3e0 + D)), 2e0)));
}
void generarArray(double arrayX[])
{
	for (int k = 0; k <= N2; ++k) {
			arrayX[k]=( (D + 3e0) * cos((2e0 * k + 1e0 )*M_PI/ 22e0 ));
			//cout<<arrayX[k]<<endl;
	}
}

void interpolacionNewton(double arrayY[][N2+1], double arrayX[], int n)
{
	for (int k = 0; k <= n; ++k) {
			for (int i = 0; i <= n; ++i) {
				arrayY[k][i]=0.0;
				arrayY[k][0]=fEvaluateInX(arrayX[k]); // coloca los fx en la matriz arrayY
			}

		}

		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				arrayY[j][i]= ((arrayY[j][i-1]- arrayY[j-1][i-1])/(arrayX[j]-arrayX[j-i]));
			}
		}
}

void imprimir(double arrayY[][N2+1] ,double arrayX[])
{
	for (int i = 0; i <= N2; ++i) {
		cout << left<< setw(12) << arrayX[i];
		for (int j = 0; j <= i; ++j) {
			cout <<setprecision(4)<<left<< setw(12)<< arrayY[i][j];
		}
		cout <<endl;
	}
}

void construirPolinomio(double arrayY[][N2+1], double arrayX[]){
	int cont;
	for (int i = 0; i <= N2; ++i) {
				cout <<setprecision(4)<<left<< arrayY[i][i];
				cont = 0;

				while(cont<i){
					cout << "(x";

					if(arrayX[cont]>0)
						cout << '-';
					else if(arrayX[cont]<0)
						cout << '+';

					if(arrayX[cont]!=0)
						cout << fabs((double)arrayX[cont]);
					cout <<") ";

					cont++;
				}

				if(i < N2 - 1)
				{
					if(arrayY[i+1][i+1]>0)
						cout<< "+ ";
				}
			}
}
int main() {
	int b = D+3;
	double arrayY[N2+1][N2+1];
	double arrayX[N2+1];

	generarArray(arrayX); // genera el primer array bidimensional para n+1 nodos o puntos en el eje x
	interpolacionNewton(arrayY, arrayX, N2);
	imprimir(arrayY, arrayX);
	cout << endl;
	cout << 'P'<< N2<< "(x) = ";
	construirPolinomio(arrayY, arrayX);
	cout << endl;
	return 0;
}
