#include<stdio.h>
#define MOD 1000000007L
#define MEM_SIZE 1048576

long long MEM[MEM_SIZE];
int X[20];
int Y[20];
int N;
long long exp2[20];

long long calc(int n, int taken){
	if(n == N)
		return 1;
	if(MEM[taken] != -1)
		return MEM[taken];

	long long res = 0;	
	for(int mask = exp2[X[n]-1]; mask <= exp2[Y[n]-1]; mask <<= 1){
		if(!(mask & taken))
			res = (res + calc(n+1, taken + mask)) % MOD;
	}

	return (MEM[taken] = res);
}

void init(){
	exp2[0] = 1;
	for(int i = 1; i < 20; i++)
		exp2[i] = exp2[i-1]<<1;
}

int main(void){
	init();
	for(int i = 0; i < MEM_SIZE; i++)
		MEM[i] = -1;
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
		scanf("%d %d", &X[i], &Y[i]);

	printf("%lld\n", calc(0, 0));
	return 0;
}
