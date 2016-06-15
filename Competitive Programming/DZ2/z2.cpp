#include<iostream>
#include<string.h>
#include<stdlib.h>

#define N 1000001
using namespace std;

unsigned long mass[N] = {0};
unsigned long A[N] = {0};

int lobit(int x){
	int i = 1;
	while((x & i) == 0) i <<= 1;
	return i;
	}

void add(int i, unsigned long weight){
	if(mass[i] + weight > 1000000000UL){
		weight = 1000000000UL - mass[i];
		mass[i]= 1000000000UL;
		}
	else
		mass[i] += weight;
		
	for( ; i < N; i += lobit(i))
		A[i] += weight;
	}

void remove(int i, unsigned long weight){
	if(mass[i] < weight){
		weight = mass[i];
		mass[i] = 0;
		}
	else
		mass[i] -= weight;

	for( ; i < N; i += lobit(i))
		A[i] -= weight;
	}

int sum(int i){
	unsigned long total = 0;
	for( ; i > 0; i -= lobit(i))
		total += A[i];
	return total;
	}

int main(void){
	int n, K;
	cin >> n;
	cin >> K;
	for(int i = 0; i < K; i++){
		char string[10];
		int arg1, arg2;
		cin >> string >> arg1 >> arg2;
		
		if(strcmp(string, "posadka") == 0)
			add(arg1+1, arg2);
		else if(strcmp(string, "razgruzka") == 0)
			remove(arg1+1, arg2);
		else
			cout << sum(arg2+1) - sum(arg1) << endl;
		}
	return 0;
	}
