#include<iostream>

using namespace std;

int N, M, K;
bool didntHappen[26][26];
int MEM[26][26];

int rec(int a, int b){
	if(a == 0 && b == 0) return 1;
	if(a < 0 || b < 0) return 0;
	if(didntHappen[a][b]) return 0;

	int left=0, right=0;
	if(a >= 1){
		if(MEM[a-1][b] >= 0) left = MEM[a-1][b];
		else left = MEM[a-1][b] = rec(a-1,b);
		}
	if(b >= 1){
		if(MEM[a][b-1] >= 0) left = MEM[a][b-1];
		else left = MEM[a][b-1] = rec(a,b-1);
		}
		
	return left + right;
	}

int main(void){
	cin >> N >> M;
	
	cin >> K;
	for(int i=0; i < K; i++){
		int a, b;
		cin >> a >> b;
		didntHappen[a][b] = true;
		}
	for(int i=0; i < 26; i++)
		for(int j=0; j < 26; j++)
			MEM[i][j] = -1;
	cout << rec(N, M);

	return 0;
	}
