#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
	freopen("e:/p7-300.out", "w", stdout);
	long n;
	scanf("%ld", &n);
	long i;
	long key[100000], value[100000];
	for (i = 0; i < n; i++)
		key[i] = i;

	srand(time(NULL));
	for (i = n - 1; i > 0; i--){
		long r = rand() % i;
		long temp = key[i];
		key[i] = key[r];
		key[r] = temp;
		value[i] = rand() % n;
	}
	value[0] = rand() % n;
	printf("%ld\n", n);
	for (i = 0; i < n; i++)
		printf("%ld %ld\n", key[i], value[i]);
}
	