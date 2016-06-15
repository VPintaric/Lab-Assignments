#include<iostream>
using namespace std;

int N, M;
long B[1000000];
	

long sum(long p){
	long sum = 0;
	for(int i = 0; i<N; i++)
		if(p < B[i])
			sum += B[i] - p;
	return sum;
	}



int main(void){
	
	cin >> N;
	cin >> M;
	for (int i = 0; i < N; i++)
		cin >> B[i];

	long pmin = 1;
	long pmax = 1000000000L;
	long p, pProsli=-1;
	while(true){
		p = (pmax+pmin)/2;
		if(pProsli != -1 && pProsli == p)
			break;
		long suma = sum(p);
		if(suma < M) pmax = p;
		else if(suma > M) pmin = p;
		else break;
		pProsli = p;
		}	
	cout << p;
	return 0;
}
