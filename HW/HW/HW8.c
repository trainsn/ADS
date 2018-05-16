#include <stdio.h>
#include <stdlib.h>

int main()
{
	int m,n,ll,l=0;
	int i,temp;
	int index[200], a[10000], b[10000];
	for (i = 0; i < 200; i++)
		index[i] = -1;
	scanf("%d", &n);
	scanf("%d", &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d", &temp);
		index[temp] = i;
	}
	scanf("%d", &ll);
	for (i = 0; i < ll; i++)
	{
		scanf("%d", &temp);
		if (index[temp] == -1)
			continue;
		a[l++] = index[temp];
	}
	
	int maxl=0;
	for (i = 0; i < l; i++)
		b[i] = 100001;
	b[0] = 0;
	for (i = 0; i < l; i++)
	{
		int left = 0, right = maxl, mid;
		if (b[left]>a[i])
			continue;
		while (left<=right)
		{
			mid = (left + right) / 2;
			if (b[mid] <= a[i] && (b[mid + 1] > a[i] || mid == maxl))
				break;
			if (b[mid] <= a[i])
				left = mid + 1;
			else
				right = mid - 1;
		}
		if (b[mid + 1] >= a[i])
			b[mid + 1] = a[i];
		if (mid + 1 > maxl)
			maxl = mid + 1;
	}
	printf("%d", maxl);
	system("pause");
}