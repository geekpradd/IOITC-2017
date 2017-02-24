#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
// Solved 24/2/2017. 

char* power_2[137];
int size_2[137];

void lshift(char * num, int * size){
	int carry = 0;

	for (int i=0; i<= 40; ++i){
		int cur = *(num + i) - '0';
		int mod = 2*cur + carry;
		*(num + i) = '0' + (mod % 10);
		carry = mod/10;
	}

	char val = *(num + *(size));
	if (val != '0'){
		*(size) = *(size) + 1;
	} 

}

void rshift(char *num, int * size){
	int mov = 0;

	for (int i = *(size) - 1; i>=0; --i){
		int cur = *(num + i) - '0';
		int m = cur/2 + mov;

		if (cur % 2) {
			mov = 5;
		}
		else {
			mov = 0;
		}
		*(num + i) = '0' + (m % 10);
	}

	int leading = *(num + *(size) - 1) - '0';
	if (leading == 0){
		*(size) = *(size) - 1;
	}

}

int compare(char* a, int* size_a, char* b, int* size_b){
	// Compares two BigNum char arrays a and b
	// Return Value      Condition
	//     0				a > b
	// 	   1                b > a
	//     2                a = b
	
	if (*(size_a) > *(size_b)) {
		return 0;
	}
	else if (*(size_a) < *(size_b)){
		return 1;
	}
	else {
		for (int i = *(size_a) - 1; i>=0; --i){
			int cur_a = *(a + i) - '0';
			int cur_b = *(b + i) - '0';

			if (cur_a > cur_b) {
				return 0;
			}
			else if (cur_a < cur_b){
				return 1;
			}
		}

		return 2;
	}
}

int log2(char * num, int * size){
	int *binary_search_holder = upper_bound(size_2, size_2 + 137, (*size) - 1);
	int start_index = binary_search_holder - size_2;

	for (int i=start_index; i<=136; ++i){
		int res = compare(num, size, power_2[i], &size_2[i]);
		
		if (res==2){
			return i;
		}
		else if (res == 1){
			return i-1;
		}
	}
}


signed main(){
	char* p;
	char* x;
	int len_p = 1;

	p = new char[41];
	x = new char[41];

	for (int i=0; i<=40; ++i){
		p[i] = '0';
		x[i] = '0';
	}

	p[0] = '1';
	x[0] = '1';

	power_2[0] = x;
	size_2[0] = 1;

	for (int i=1; i<=136; ++i){
		lshift(p, &len_p);

		char *k;
		k = new char[41];
		for (int j=0; j<=40; ++j){
			k[j] = p[j];
		}

		power_2[i] = k;
		size_2[i] = len_p;
	}

	int q;
	scanf("%d", &q);

	while (q--){

		char a[41];
		char b[41];

		scanf("%s", a);
		scanf("%s", b);

		char* num_a;
		char* num_b;
		num_a = new char[41];
		num_b = new char[41];

		int len_a;
		int len_b;

		for (int i=0; i<=40; ++i){
			if (a[i] == '\0'){
				len_a = i;
				break;
			}
		}
		for (int i=0; i<=40; ++i){
			if (b[i] == '\0'){
				len_b = i;
				break;
			}
		}

		for (int i=0; i<len_a; ++i){
			num_a[i] = a[len_a - 1 - i];
		}
		for (int i=0; i<len_b; ++i){
			num_b[i] = b[len_b - 1 - i];
		}

		if (compare(num_a, &len_a, num_b, &len_b) == 1){
			swap(len_a, len_b);
			for (int i=0; i<=40; ++i){
				swap(num_a[i], num_b[i]);
			}
		}

		int height_a = log2(num_a, &len_a);
		int height_b = log2(num_b, &len_b);

		int dist = 0;

		while (height_a != height_b){
			dist++;
			rshift(num_a, &len_a);

			height_a = log2(num_a, &len_a);
		}

		while (compare(num_a, &len_a, num_b, &len_b) != 2){
			dist += 2;
			rshift(num_a, &len_a);
			rshift(num_b, &len_b);
		}

		printf("%d\n", dist);
	}

	return 0;
}