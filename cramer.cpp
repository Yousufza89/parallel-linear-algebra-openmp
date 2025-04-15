#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
using namespace std;
const int X = 11;
const int Y = X+1;

void displayMatrix(int mat[X][Y]) {
	for(int i=0;i<X;i++) {
		for(int j=0;j<X;j++) {
			cout<<mat[i][j]<<"\t | ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void getCofactor(long long int mat[X][X], long long int temp[X][X], long long int p, long long int q, long long int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (row != p && col != q) {
				temp[i][j++] = mat[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

long long int determinantOfMatrix(long long int mat[X][X], int n)
{
	long long int D = 0;

	if (n == 1)
		return mat[0][0];

	long long int temp[X][X];

	int sign = 1;

	for (long long int f = 0; f < n; f++)
	{
		getCofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
		sign = -sign;
	}

	return D;
}

void findSolution(int coeff[X][Y])
{
	long long int d[X][X];
	for(int i=0;i<X;i++) {
		for(int j=0;j<X;j++) {
			d[i][j] = coeff[i][j];
		}
	}
	
	long long int dMat[X][X][X];
	for(int i=0;i<X;i++) {
		for(int j=0;j<X;j++) {
			for(int k=0;k<X;k++) {
				if(k==i) {
					dMat[i][j][k] = coeff[j][X];
				} else {
					dMat[i][j][k] = coeff[j][k];
				}
			}
		}
	}
	
	long double _D = double(determinantOfMatrix(d, X));
	//cout<<"det(A) : "<<_D<<endl;
	long double Dets[X];
	for(int i=0;i<X;i++) {
		Dets[i] = double(determinantOfMatrix(dMat[i], X));
		//cout<<"det(A"<<i+1<<") : "<<Dets[i]<<endl;
	}
	
	if (_D != 0) {
		double xVals[X];
		for(int i=0;i<X;i++) {
			xVals[i] = Dets[i] / _D;
			//cout<<"x"<<i+1<<" : "<<xVals[i]<<endl;
		}
	}
}
void findSolutionOMP(int coeff[X][Y], int threadCount)
{
	omp_set_num_threads(threadCount); 
	long long int d[X][X];
	#pragma omp parallel for collapse(2)
	for(int i=0;i<X;i++) {
		for(int j=0;j<X;j++) {
			d[i][j] = coeff[i][j];
		}
	}
	
	long long int dMat[X][X][X];
	for(int i=0;i<X;i++) {
		#pragma omp parallel for collapse(2)
		for(int j=0;j<X;j++) {
			for(int k=0;k<X;k++) {
				if(k==i) {
					dMat[i][j][k] = coeff[j][X];
				} else {
					dMat[i][j][k] = coeff[j][k];
				}
			}
		}
	}
	
	long double _D = double(determinantOfMatrix(d, X));
	cout<<"det(A) : "<<_D<<endl;
	long double Dets[X];
	#pragma omp parallel for
	for(int i=0;i<X;i++) {
		Dets[i] = double(determinantOfMatrix(dMat[i], X));
		cout<<"det(A"<<i+1<<") : "<<Dets[i]<<endl;
	}
	
	if (_D != 0) {
		double xVals[X];

		for(int i=0;i<X;i++) {
			xVals[i] = Dets[i] / _D;
			cout<<"x"<<i+1<<" : "<<xVals[i]<<endl;
		}
	}
}

int main()
{
	cout<<"Size : "<<X<<endl;
	int coeff[X][Y];
	for(int i=0;i<X;i++) {
		for(int j=0;j<Y;j++) {
			coeff[i][j] = (rand() % 20) - 10;
		}
	}
	cout<<"Matrix"<<endl;
	displayMatrix(coeff);
	double time;
	time = omp_get_wtime();
	findSolution(coeff);
	time = omp_get_wtime() - time;
	cout<<"time with 1 threads: "<<time<<endl;
	
	time = omp_get_wtime();
	findSolutionOMP(coeff, 2);
	time = omp_get_wtime() - time;
	cout<<"time with 2 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 4);
	time = omp_get_wtime() - time;
	cout<<"time with 4 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 8);
	time = omp_get_wtime() - time;
	cout<<"time with 8 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 16);
	time = omp_get_wtime() - time;
	cout<<"time with 16 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 32);
	time = omp_get_wtime() - time;
	cout<<"time with 32 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 64);
	time = omp_get_wtime() - time;
	cout<<"time with 64 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 100);
	time = omp_get_wtime() - time;
	cout<<"time with 100 threads: "<<time<<endl;

	time = omp_get_wtime();
	findSolutionOMP(coeff, 200);
	time = omp_get_wtime() - time;
	cout<<"time with 200 threads: "<<time<<endl;
	
	return 0;
}

