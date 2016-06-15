#include<iostream>
using namespace std;

int next[5000001] = {0};
char amnt[5000001] = {0};

void add(int num){
	if(amnt[num] > 0){
		amnt[num]++;
		return;
		}
	if(next[0] == 0){
		next[0] = num;
		amnt[num]++;
		return;
		}
	int cur = 0;
	while(num > next[cur] && next[cur] != 0) cur = next[cur];
	int tmp = next[cur];
	next[cur] = num;
	next[num] = tmp;
	amnt[num]++;
	}

void find(int lo, int hi, int k){
	if(next[0] == 0){
		cout << "NEMA" << endl;
		return;
		}
	int cur = 0;
	while(lo > next[cur] && next[cur] != 0) cur = next[cur];
	cur = next[cur];
	for(int i = amnt[cur]; cur <= hi && cur != 0; ){
		if(i >= k){
			cout << cur << endl;
			return;
			}
		cur = next[cur];
		i += amnt[cur];
		}
	cout << "NEMA" << endl;
	}

int main(void){
	int numOfIters;
	cin >> numOfIters;
	
	for(int i = 0; i < numOfIters; i++){
		char comm;
		cin >> comm;
		if(comm == 'u'){
			int num;
			cin >> num;
			add(num);
			}
		else if(comm == 'n'){
			int lo, hi, k;
			cin >> lo >> hi >> k;
			find(lo, hi, k);
			}
		/*
		for(int j = 0; j < 10; j++)
			cout << next[j] << " ";
		cout << endl;
		for(int j = 0; j < 10; j++)
			cout << amnt[j] << " ";
		cout << endl;
		*/
		}
	return 0;
	}
