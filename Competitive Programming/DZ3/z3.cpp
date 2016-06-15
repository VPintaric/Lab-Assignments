#include<iostream>
#define MAX_N 150000
using namespace std;

int A[MAX_N], B[MAX_N], C[MAX_N], MEM[MAX_N], N;
int sumB;

int findMin(){
	int minSum, sum;
	minSum = sum = A[0] + sumB;
	minSum = minSum - B[N-1] + C[N-1];
	
	for(int i = N-1; i >= 2; i--){
		sum = sum - B[i] + C[i];
		if(minSum > sum) minSum = sum;
		if(minSum > sum+MEM[i-2]) minSum = sum+MEM[i-2];
		}
	return minSum;
	}

int main(void){
	cin >> N;
	
	for(int i=0; i < N; i++)
		cin >> A[i];

	cin >> B[0];
	int cumSum = 0;
	for(int i=1; i < N; i++){
		cin >> B[i];
		sumB += B[i];
		int dif = A[i] - B[i];
		cumSum += dif;
		if(cumSum < MEM[i-1]) MEM[i] = cumSum;
		else MEM[i] = MEM[i-1];
		}
	for(int i=0; i < N; i++)
		cin >> C[i];

	cout << findMin() << endl; //REMOVE THIS 'ENDL' IF THERE WILL BE A PROBLEM WITH OUTPUT FORMAT
	return 0;
	}
