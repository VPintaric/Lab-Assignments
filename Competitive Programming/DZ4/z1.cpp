#include<iostream>

#define N 10000000
using namespace std;


int nd[N+1];

void initSito(int n){
	for(int i = 2; i <= n; i++){
		if(!nd[i]){
			for(int j = i; j <= n; j += i)
				nd[j] = nd[j] ? nd[j] : i;
		}
	}
}

int main(void){
	int n, sum = 0;
	cin >> n;

	initSito(n);
	for(int i = 2; i <= n; i++){
		int num = i;
		while(num != 1) num /= nd[num], sum++;
	}

	cout << sum;
	return 0;
}
