#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

int N;
double X[3000], Y[3000];

double f(double x, double y){
	double sum = 0;
	for(int i = 0; i < N; i++)
		sum += sqrt((x-X[i])*(x-X[i]) + (y-Y[i])*(y-Y[i]));
	return sum;
	}

int main(void){

	cin >> N;
	double avgY = 0, avgX = 0;
	for(int i = 0; i < N; i++){
		cin >> X[i] >> Y[i];
		avgX += X[i];
		avgY += Y[i];
		}
	avgX /= N;
	avgY /= N;
	
	double minX = 0, minY = 0;

	if(avgX - 100 > 0)
		minX = avgX - 100;
	if(avgY - 100 > 0)
		minY = avgY - 100;

	double maxX = 1000, maxY = 1000;
	if(avgX + 100 < 1000)
		maxX = avgX + 100;
	if(avgY + 100 < 1000)
		maxY = avgY + 100;

	while(maxX - minX > 0.0000001 || maxY - minY > 0.0000001){
		double x1 = minX + (maxX - minX) / 3;
		double x2 = maxX - (maxX - minX) / 3;
		double y1 = minY + (maxY - minY) / 3;
		double y2 = maxY - (maxY - minY) / 3;

		double d11 = f(x1, y1);
		double d12 = f(x1, y2);
		double d21 = f(x2, y1);
		double d22 = f(x2, y2);

		int min=0;
		if(d11 < d12)
			if(d11 < d21)
				if(d11 < d22)
					min = 11;
				else
					min = 22;
			else
				if(d21 < d22)
					min = 21;
				else
					min = 22;
		else
			if(d12 < d21)
				if(d12 < d22)
					min = 12;
				else
					min = 22;
			else
				if(d21 < d22)
					min = 21;
				else
					min = 22;
		if(min == 11){
			maxX = x2;
			maxY = y2;
			}
		else if(min == 12){
			maxX = x2;
			minY = y1;
			}
		else if(min == 21){
			minX = x1;
			maxY = y2;
			}
		else if(min == 22){
			minX = x1;
			minY = y1;
			}
		}
	double x = (maxX + minX) / 2;
	double y = (maxY + minY) / 2;
	
	printf("%f", f(x,y));
	return 0;
	}
