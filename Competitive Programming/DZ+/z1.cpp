#include<iostream>

using namespace std;

int W, H, MaxP;
bool isStalagmite[150];
int K[150];
int MEM[300][301][31]; // [col][row][leftBreaks]


int calculate(int col, int row, int curP){
	if(col == W) //got to the end
		return 0;

	if(MEM[col][row][curP] != 0) //already was in this situation
		return MEM[col][row][curP];

	int nextColInfo = (col+1)>>1;
	if((isStalagmite[nextColInfo] && row > K[nextColInfo]) || (!isStalagmite[nextColInfo] && row < (H - K[nextColInfo] + 1))){ //no obstacle
		MEM[col][row][curP] = 2 + calculate(col+2, row, curP);
		return MEM[col][row][curP];
		}

	//there is an obstacle
	//a)don't break it
	int dist = isStalagmite[nextColInfo] ? K[nextColInfo] - row + 3 + calculate(col+2, K[nextColInfo]+1, curP) : 
						row - H + K[nextColInfo] + 2 + calculate(col+2, H-K[nextColInfo], curP);

	//b)if you can break it, break it
	if(curP > 0){
		int distBreak = 2 + calculate(col+2, row, curP-1);
		dist = dist > distBreak ? distBreak : dist;
	}

	MEM[col][row][curP] = dist;
	return dist;
}

int main(void){
	cin >> W >> H;
	cin >> MaxP;
	for(int i = 1; i <= ((W-1)>>1); i++){
		char string[10];
		int k;
		cin >> string >> k;
		isStalagmite[i] = (string[0] == 'd');
		K[i] = k;
	}

	for(int p = 0; p <= MaxP; p++){
		int min = calculate(1, 1, p);
		for(int start = 2; start <= H; start++){
			int newVal = calculate(1, start, p);
			min = newVal < min ? newVal : min;
		}
		cout << min << endl;
	}
}
