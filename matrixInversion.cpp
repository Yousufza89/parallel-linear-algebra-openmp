#include "matrix.cpp"
#include <fstream>

vector<vector<long double>> generateInverseOMP(vector<vector<long double>> matrix, int threads) {
	const long long int size = matrix.size(); 
	vector<vector<long double>> identityMatrix = generateIdentity(size);
	omp_set_num_threads(threads);
	for(long long int i = 0 ; i < size ; i++) {
		if(matrix[i][i] != 1.0) {
			const long double dividingFactor = matrix[i][i];
			#pragma omp parallel for
			for(long long int k = 0 ; k < size ; k++) {
				matrix[i][k] = matrix[i][k] / dividingFactor;
				identityMatrix[i][k] = identityMatrix[i][k] / dividingFactor;
			}
		}
		#pragma omp parallel for
		for(long long int l = i+1; l < size ; l++) {
			long double multiplyingFactor = -1*(matrix[l][i]/matrix[i][i]);
			#pragma omp parallel for
			for(long long int m = 0 ; m < size ; m++) {
				matrix[l][m] += (multiplyingFactor * matrix[i][m]); 
				identityMatrix[l][m] += (multiplyingFactor * identityMatrix[i][m]);
			} 
		}
		#pragma omp parallel for
		for(long long int l = i-1 ; l >= 0 ; l--) {
			long double multiplyingFactor = -1*(matrix[l][i]/matrix[i][i]);
			#pragma omp parallel for
			for(long long int m = 0 ; m < size ; m++) {
				matrix[l][m] += (multiplyingFactor * matrix[i][m]); 
				identityMatrix[l][m] += (multiplyingFactor * identityMatrix[i][m]);
			} 
		}
	}
	
	return identityMatrix;
}

vector<vector<long double>> generateInverse(vector<vector<long double>> matrix) {
	const long long int size = matrix.size(); 
	vector<vector<long double>> identityMatrix = generateIdentity(size);
	
	for(long long int i = 0 ; i < size ; i++) {
		if(matrix[i][i] != 1.0) {
			const long double dividingFactor = matrix[i][i];
			for(long long int k = 0 ; k < size ; k++) {
				matrix[i][k] = matrix[i][k] / dividingFactor;
				identityMatrix[i][k] = identityMatrix[i][k] / dividingFactor;
			}
		}
		
		for(long long int l = i+1; l < size ; l++) {
			long double multiplyingFactor = -1*(matrix[l][i]/matrix[i][i]);
			for(long long int m = 0 ; m < size ; m++) {
				matrix[l][m] += (multiplyingFactor * matrix[i][m]); 
				identityMatrix[l][m] += (multiplyingFactor * identityMatrix[i][m]);
			} 
		}
	
		for(long long int l = i-1 ; l >= 0 ; l--) {
			long double multiplyingFactor = -1*(matrix[l][i]/matrix[i][i]);
			for(long long int m = 0 ; m < size ; m++) {
				matrix[l][m] += (multiplyingFactor * matrix[i][m]); 
				identityMatrix[l][m] += (multiplyingFactor * identityMatrix[i][m]);
			} 
		}
	}
	
	return identityMatrix;
}

int main() {
	double time;
	for(long long int i = 1000 ; i <= 5000 ; i+=1000) {
		vector<vector<long double>> matrix = generateRandMatrix(i);

		cout<<"Size :"<<i<<'\n';

		time = omp_get_wtime();
		generateInverse(matrix);
		time = omp_get_wtime() - time;
		

		cout<<"1 Thread :"<<time<<'\n';

		time = omp_get_wtime();
		generateInverseOMP(matrix, 2);
		time = omp_get_wtime() - time;
		

		cout<<"2 Thread :"<<time<<'\n';

		time = omp_get_wtime();
		generateInverseOMP(matrix, 4);
		time = omp_get_wtime() - time;
		

		cout<<"4 Thread :"<<time<<'\n';

		time = omp_get_wtime();
		generateInverseOMP(matrix, 8);
		time = omp_get_wtime() - time;
		

		cout<<"8 Thread :"<<time<<'\n';


		time = omp_get_wtime();
		generateInverseOMP(matrix, 16);
		time = omp_get_wtime() - time;
		

		cout<<"16 Thread :"<<time<<'\n';
		
		
		time = omp_get_wtime();
		generateInverseOMP(matrix, 32);
		time = omp_get_wtime() - time;
		

		cout<<"32 Thread :"<<time<<'\n';


		time = omp_get_wtime();
		generateInverseOMP(matrix, 64);
		time = omp_get_wtime() - time;
		

		cout<<"64 Thread :"<<time<<'\n';


		time = omp_get_wtime();
		generateInverseOMP(matrix, 100);
		time = omp_get_wtime() - time;
		

		cout<<"100 Thread :"<<time<<'\n';


		time = omp_get_wtime();
		generateInverseOMP(matrix, 200);
		time = omp_get_wtime() - time;
		

		cout<<"200 Thread :"<<time<<'\n';
	}

}
