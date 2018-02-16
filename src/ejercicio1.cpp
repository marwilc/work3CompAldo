//============================================================================
// Name        : ejercicio1.cpp
// Author      : Marwil Campos ci 21484386
// Version     :
// Copyright   : Your copyright notice
// Description :  Ansi-style
//============================================================================

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
	return(1e0 / (1e0 + pow((5e0 * x/ (3e0 + D)), 2e0)));
}
void generarArray(vector<double>& arrayX, int nodes, int value)
{
	double spacing =  value*2e0 / nodes;
	arrayX.push_back(-value);
	for (int i = 1; i <= nodes; ++i) {
			arrayX.push_back(arrayX.at(i-1) + spacing);
	}
}

void interpolacionNewton(vector< vector<double> >& arrayY, vector<double>& arrayX, int n)
{
	for (int k = 0; k <= n; ++k) {
			for (int i = 0; i <= n; ++i) {
				arrayY[k][i]=0e0;
				arrayY[k][0]=fEvaluateInX(arrayX.at(k)); // coloca los fx en la matriz arrayY
			}

		}

		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				arrayY[j][i]= ((arrayY[j][i-1]- arrayY[j-1][i-1])/(arrayX[j]-arrayX[j-i]));
			}
		}
}

void imprimir(vector< vector<double> > arrayY ,vector<double> arrayX)
{
	for (int i = 0; i < arrayX.size(); ++i) {
		cout << left<< setw(12) << arrayX[i];
		for (int j = 0; j <= i; ++j) {
			cout <<setprecision(4)<<left<< setw(12)<< arrayY[i][j];
		}
		cout <<endl;
	}
}

void construirPolinomio(vector<vector<double> > arrayY, vector<double> arrayX){
	int cont;
	for (int i = 0; i < arrayX.size(); ++i) {
				cout <<setprecision(4)<<left<< arrayY[i][i];
				cont = 0;

				while(cont<i){
					cout << "(x";

					if(arrayX[cont]>0)
						cout << '-';
					else if(arrayX[cont]<0)
						cout << '+';

					if(arrayX[cont]!=0)
						cout << fabs(arrayX[cont]);
					cout <<") ";

					cont++;
				}

				if(i < arrayX.size() - 1)
				{
					if(arrayY[i+1][i+1]>0)
						cout<< "+ ";
				}
			}
}
int main() {
	int b = D+3e0;
	vector< vector<double> > arrayY(N2+1,vector<double>(N2+1));
	vector<double> arrayX;

	generarArray(arrayX, N1, b); // genera el primer array bidimensional para n+1 nodos o puntos en el eje x
	interpolacionNewton(arrayY, arrayX, N1);
	imprimir(arrayY, arrayX);
	cout << endl;
	cout << 'P'<< arrayX.size()-1<< "(x) = ";
	construirPolinomio(arrayY, arrayX);
	cout << endl;
	arrayX.clear();
	//arrayY.clear();
	generarArray(arrayX, N2, b);
	interpolacionNewton(arrayY, arrayX, N2);
	imprimir(arrayY, arrayX);
	cout << endl;
	cout << 'P'<< arrayX.size()-1<< "(x) = ";
	construirPolinomio(arrayY, arrayX);
	return 0;
}
