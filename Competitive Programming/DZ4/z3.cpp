#include<iostream>

using namespace std;

int A, B;
bool notPrime[10000001];
long sum;



void nadiIDodajKombinaciju(int x1, int x2){
	int mod = 1, nrDigs = 1;
	long tmp;
	//cout << "x1 = " << x1 << " x2 = "<<x2 << endl;
	for(tmp = x1; tmp > 0; tmp /= 10) mod *= 10;
	for(tmp = x2; tmp > 0; tmp /= 10) nrDigs *= 10;
	int i;
	for(tmp = x2, i = 1; tmp % mod != x1; tmp += x2, i++){
		if(i >= nrDigs){
		tmp = 0;
		break;
		}
	}
	//cout << "tmp = " << tmp << endl;
	sum = (sum + tmp % 1000000007L) % 1000000007L;
	//cout << "sum = " << sum << endl << endl;
}

int main(void){
	cin >> A >> B;
	
	int x1=0, x2=0, i=2;
	
	for( ; i < A || notPrime[i]; i++)
		if(!notPrime[i])
			for(int j = i+i; j <= B; j += i)
				notPrime[j] = true;
	x1 = i;
	for(int j = i+i; j <= B; j += i)
		notPrime[j] = true;
	i++;

	for( ; i <= B; i++){
		if(!notPrime[i]){
			for(int j = i+i; j <= B; j += i)
				notPrime[j] = true;
			x2 = i;
			nadiIDodajKombinaciju(x1, x2);
			x1 = x2;
		}
	}

	cout << sum;
	return 0;
}
