#include <stdio.h>
#include <stdlib.h>
const int MOD = 10007;
int Power(int N, int k)
{
	if (!k)
		return 1;
	if (k == 1)
		return N;
	if (k % 2){
		return (Power(N, (k - 1) / 2) * Power(N, (k - 1) / 2) % MOD *N) % MOD;
	}
	else {
		return Power(N, k / 2) *  Power(N, k / 2) % MOD;
	}
}

int main()
{
	int N, k;
	scanf("%d%d", &N, &k);
	printf("%d\n", Power(N, k));
	system("pause");
	return 0;
}