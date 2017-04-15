#include <bits/stdc++.h>
#include <cstdlib>
#include <cstdio>
using namespace std;


int main(){
	int k;
	scanf("%d", &k);
	int init[k];
	int final[k];
	int delta[k];

	for (int i=0; i<k; ++i){
		scanf("%d", &init[i]);
	}
	for (int i=0; i<k; ++i){
		scanf("%d", &final[i]);
	}
	for (int i=0; i<k; ++i){
		scanf("%d", &delta[i]);
	}

	bool pos = true;
	int lcm = -1;
	int length[k];
	int sum = 0;

	for (int i=0; i<k; ++i){
		int a = init[i];
		int b = final[i];
		int c = delta[i];

		if (c==0){
			if (a!=b){
				pos = false; break;
			} 
			sum += a;
			length[i] = 0;
		}
		else {
			if (abs(a-b)%c != 0){
				pos = false;
				break;
			} 
			int steps = abs(a-b)/c;
			sum += ((steps+1)*(a+b))/2;
			length[i] = steps;

			if (lcm == -1){
				lcm = steps;
			}
			else if (steps == 0){

			}
			else {
				if (abs(steps-lcm)%2 == 1){
					pos = false; break;
				}
				lcm = max(steps, lcm);
			}
		}
	}
	
	if (pos){
		for (int i=0; i<k; ++i){
			int diff = (lcm - length[i])/2;
			int val = max(init[i], final[i]);
			int del = delta[i];

			if (diff != 0){
				sum += val; sum += val + del*diff;
				sum += (del-1)*(2*(val+diff) + (del-2)*diff);
			}
		}
		printf("1\n");
		if (lcm == -1){
			printf("0\n");
		}
		else {
			printf("%d\n", lcm);
		}
		printf("%d\n", sum);
	}
	else {
		printf("0\n");
	}
	return 0;
}