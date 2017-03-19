#include <stdio.h>

inline int abs(int num){
	if (num >= 0) return num;
	return (-1)*num;
}

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

	for (int i=0; i<k; ++i){
		int a = init[i];
		int b = final[i];
		int c = delta[i];

		if (c==0){
			if (a!=b){
				pos = false; break;
			} 
			lcm = max(lcm, 0); continue;
		}

		if (abs(a-b)%c != 0){
			pos = false;
			break;
		} 
		int steps = abs(a-b)/c;
		if (lcm == -1){
			lcm = steps;
		}
		else {
			if (abs(steps-lcm)%2 == 1){
				pos = false; break;
			}
			lcm = max(steps, lcm);
		}
	}

	if (pos){
		printf("1\n");
		printf("%d\n", lcm);
	}
	else {
		printf("0\n");
	}
	return 0;
}