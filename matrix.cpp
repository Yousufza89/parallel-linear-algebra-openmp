#include <iostream>
#include <vector>
#include <time.h>
#include <omp.h>

using namespace std;

vector<long double> generateRandArray(const long long int size) {
	vector <long double> array(size);
	for(long long int i = 0 ; i < size ; i++) {
		array[i] = (double) rand() / rand();
	} 
	
	return array;
}

vector<vector<long double>> generateRandMatrix(const long long int size) {
	vector<vector<long double>> matrix(size);
	for(long long int i = 0 ; i < size ; i++) {
		matrix[i] = generateRandArray(size);
	}
	
	return matrix;
}

void printMatrix(vector<vector<long double>> matrix) {
	const long long int size = matrix.size();
	for(long long int i = 0 ; i < size ; i++) {
		for(long long int j = 0 ; j < size ; j++) {
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

vector<vector<long double>> generateIdentity(const long long int size) {
	vector<vector<long double>> matrix (size, vector<long double> (size, 0));
	for(long long int i = 0 ; i < size ; i++) {
		matrix[i][i] = 1;
	}
	
	return matrix;
}
