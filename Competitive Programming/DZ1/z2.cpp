#include<iostream>

using namespace std;

int N, M;
int T[100000];
int TMinRef;

int time(int m){
	int TMax = 0;
	int doneM = 0;
	for(int i = 0; i < N-1; i++){
		int doM = (int) (m * (((double) TMinRef)/T[i]) + 0.5);
		doneM += doM;
		int cur = doM * T[i];
		if(cur > TMax) TMax = cur;
		}
	{
		int doM = M - doneM;
		int cur = doM * T[N-1];
		if(cur > TMax) TMax = cur;
		}
	return TMax;
	}


int main(void){
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		cin >> T[i];
		if(TMinRef > T[i] || TMinRef == 0) TMinRef = T[i];
		}
	
	int lo = 0, hi = M;
	int cur;
	while(lo != hi){
		cur = (hi - lo) / 2;
		int T1 = time(cur-1);
		int T2 = time(cur);
		int T3 = time(cur+1);

		cout << cur << endl;
		cout << T1 << " " << T2 << " " << T3 << endl << endl;
		
		if(T1 < T2 && T2 < T3) hi = cur-1;
		else if(T1 > T2 && T2 > T3) lo = cur+1;
		else break;
		}
	cout << time(cur);
	return 0;
	}
