#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct line {
	int x1, x2, y1, y2;
} line;

class compare{
	public:
	bool operator() (const line &a, const line &b){
		return a.y1 < b.y1;
	}
};

int N;

int main(void){
	set<line, compare> sweep;
	vector<line> lines;
	
	cin >> N;
	for(int i = 0; i < N; i++){
		line cur;
		cin >> cur.x1 >> cur.y1 >> cur.x2 >> cur.y2;
		
	}
}
