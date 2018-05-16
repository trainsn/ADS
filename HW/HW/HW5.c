#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int ans[10], n, h;
int maxac = 0, mintime = 10000;
int  t[10], d[10]; 
int flag[10] = { 0 }, done[10];
void search( int time, int cost, int ac)
{
	if (time > h * 60)
		return;

	if (ac > maxac || (ac == maxac && cost < mintime))
	{
		maxac = ac;
		mintime = cost;
		for (int i = 0; i < ac; i++)
			ans[i] = done[i];
	}
	if (ac == n)
		return;
	for (int i = 0; i < n; i++)
	{
		if (flag[i] == 0)
		{
			flag[i] = 1;
			int rejtime = (time+t[i]-1) / 60;
			int costTemp = cost, timeTemp = time;
			time += rejtime*d[i] + t[i];
			cost += time + rejtime* 20;
			done[ac] = i;
			search(time, cost, ac + 1);
			flag[i] = 0;
			cost = costTemp;
			time = timeTemp;
		}
	}		
}

int main()
{
	int t0,i;
	while (1)
	{
		scanf("%d%d%d", &h, &n, &t0);
		if (h < 0)
			break;

		maxac = 0, mintime = 10000;
		for (i = 0; i < n; i++)
			done[i] = 0;
		char prob[10][20+1];
		for (i = 0; i < n; i++)
		{
			scanf("%s%d%d", prob[i], &t[i], &d[i]);
		}
		search(t0, 0, 0);
		if (mintime == 10000)
			mintime = 0;
		printf("Total Time = %d\n", mintime);
		for (i = 0; i < maxac; i++)
			printf("%s\n", prob[ans[i]]);
	}
	system("pause");
}