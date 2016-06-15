#include<iostream>

using namespace std;

bool coinGenInCol[1000][100001]; // [column][second] true -> coin is generated, false -> coin is not generated
int time_limit;
int MEM[1000][100001];
int N;

int calcMax(int pos, int curTime){
	if(curTime > time_limit) return 0;
	
	int max = 0, maxCur = 0;
	if(pos-1 > 0){
		if(MEM[pos-1][curTime+1] >= 0) max = MEM[pos-1][curTime+1];
		else max = MEM[pos-1][curTime+1] = calcMax(pos-1, curTime+1);
		}

	if(MEM[pos][curTime+1] >= 0) maxCur = MEM[pos][curTime+1];
	else maxCur = MEM[pos][curTime+1] = calcMax(pos, curTime+1);
	if(maxCur > max) max = maxCur;
	
	if(pos+1 <= N){
		if(MEM[pos+1][curTime+1] >= 0) maxCur = MEM[pos+1][curTime+1];
		else maxCur = MEM[pos+1][curTime+1] = calcMax(pos+1, curTime+1);
		if(maxCur > max) max = maxCur;
		}

	if(coinGenInCol[pos][curTime]) return 1+max;
	else return max;
	}

int main(void){
	cin >> N;

	for(int i=1; i <= N; i++){
		int K;
		cin >> K;
		for(int j=0; j < K; j++){
			int coinTime;
			cin >> coinTime;
			if(coinTime > time_limit) time_limit = coinTime;
			coinGenInCol[i][coinTime] = true;
			}
		}

	for(int i=1; i <= N; i++)
		for(int j=1; j <= time_limit; j++)
			MEM[i][j] = -1;

	int maxCollected = calcMax(N/2 + 1, 1);
	cout << maxCollected;
	return 0;
	}
