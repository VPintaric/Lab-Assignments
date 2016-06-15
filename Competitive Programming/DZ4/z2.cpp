#include<iostream>
#include<stdlib.h>

using namespace std;

long long unsigned N;
int K;
long long unsigned P;
long long unsigned frame[10];
long long unsigned sum;
int cur;

int main(void){
	cin >> K >> N >> P;
	
	long long unsigned i;
	long long unsigned next, prev;
	for(i = 0; i < K; i++) frame[i] = 1;
	sum = next = K;
	prev = 1;
	
	for( ; i < N; i++){
		prev = frame[cur];
		frame[cur++] = next;
		if(cur == K) cur = 0;
		sum = (sum + next) % P;
		next = (next + next - prev) % P;
		
	}
	cout << sum << endl;
	return 0;
}
