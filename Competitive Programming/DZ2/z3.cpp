#include<iostream>
#include<string.h>
#include<stdlib.h>


using namespace std;

int N, size, offset;
unsigned long* T;

int firstLargeEnough(int n){
	int x = 1;
	while(x < n) x*=2;
	return x;
	}

void change(int index, unsigned long time){
	T[offset+index] = time;
	for(int i = (offset + index)>>1; i > 0; i >>= 1){
		unsigned long T1 = T[i*2];
		unsigned long T2 = T[i*2 + 1];
		if(T1 <= T2 || T2 == 0) T[i] = T1;
		else T[i] = T2;
		}
	}

void find(int a, int b){
	int sizeOfInterval = b-a+1;
	int checkedSize = 0;
	int this_turn = 1;
	a += offset;
	unsigned long min = T[a];
	while(sizeOfInterval != checkedSize){
		if(T[a] < min && T[a] > 0) min = T[a];
		
		if((a%2 == 0) && (checkedSize+this_turn<<1 <= sizeOfInterval)) { a = a >> 1; this_turn = this_turn << 1; }
		else{
			while(a < size/2) a = (a<<1) + 1;
			a += 1;
			checkedSize += this_turn;
			this_turn = 1;
			}
		}
	cout << min << endl;
	}

int main(void){
	cin >> N;
	size = firstLargeEnough(N)*2;
	offset = size/2 - 1;
	T = (unsigned long*) calloc(size, sizeof(unsigned long));

	for(int i=1; i <= N; i++){
		unsigned long time;
		cin >> time;
		change(i, time);
		}

	int K;
	cin >> K;
	for(int i = 0; i < K; i++){
		char comm[10];
		unsigned long arg1, arg2;
		cin >> comm >> arg1 >> arg2;
		if(strcmp(comm, "sef") == 0)
			find(arg1, arg2);
		else if(strcmp(comm, "promjena") == 0)
			change(arg1, arg2);
		}
	free(T);
	return 0;
	}
