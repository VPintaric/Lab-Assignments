#include<stdio.h>
#define MOD 1000000007L

long N, A, B, K, lower;
long long MEM[5001][5001];

long long calc(long cur, long nrMoves, bool lower){
	//printf("cur = %ld, nrMoves = %ld, MEM = %lld\n", cur, nrMoves, MEM[cur][nrMoves]);
	if(MEM[cur][nrMoves] != 0)
		return MEM[cur][nrMoves] == -1 ? 0 : MEM[cur][nrMoves];

	if(nrMoves == 0)
		return (MEM[cur][nrMoves] = 1);

	long diff = lower ? B - cur : cur - B;
	long lo, hi;
	
	if(lower){
		lo = cur-diff+1 < 1 ? 1 : cur-diff+1;
		hi = B-1;
	}

	else{
		lo = B+1;
		hi = cur+diff-1 > N ? N : cur+diff-1;
	}

	if(nrMoves == 1)
		return (MEM[cur][nrMoves] = hi - lo);

	long long res = 0;
	for(long i = lo; i <= hi; i++)
		if(i != cur)
			res = (res + calc(i, nrMoves-1, lower)) % MOD;
	//printf("cur = %ld, nrMoves = %ld, res = %lld\n", cur, nrMoves, res);
	return (MEM[cur][nrMoves] = res);
}


int main(void){
	scanf("%ld %ld %ld %ld", &N, &A, &B, &K);
	lower = A < B;

	if(lower)
		for(int i = 1; i <= K; i++)
			MEM[B-1][i] = -1;
	else
		for(int i = 1; i <= K; i++)
			MEM[B+1][i] = -1;

	printf("%lld\n", calc(A, K, lower));
/*
	for(int i = 1; i <= N; i++)
		for(int j = 0; j <= K; j++)
			printf("MEM[%d][%d] = %lld\n", i, j, MEM[i][j]);
*/
	return 0;
}
