#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-6

int main()
{
	double cmax, dis, davg;
	double p[505], d[505], temp;
	int n;
	scanf("%lf%lf%lf%d", &cmax, &dis, &davg, &n);
	int i, j;
	double curV = 0, curPri = 0;

	for (i = 0; i < n; i++)
	{
		scanf("%lf%lf", &p[i], &d[i]);
	}
	
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		if (d[i]>d[j])
		{
		temp = d[i]; d[i] = d[j]; d[j] = temp;
		temp = p[i]; p[i] = p[j]; p[j] = temp;
		}
	
	if (d[0]>0)
	{
		printf("The maximum travel distance = %.2lf", 0);
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		if (i > 0){
			if (curV * davg + EPS < d[i] - d[i - 1])
			{
				printf("The maximum travel distance = %.2lf", d[i - 1] + curV * davg);
				return 0;
			}
			else
				curV -= (d[i] - d[i-1]) / davg;
		}

		int hasSmall = 0;
		for (j = i + 1; j < n; j++)
		{
			if (p[j] < p[i])	//开到下一个加油站
			{
				hasSmall = 1;
				if (curV *davg + EPS >= d[j] - d[i])
					break;
				else{
					if ((d[j] - d[i]) / davg < cmax){ // 加到下一个站的油
						curPri += ((d[j] - d[i]) / davg - curV)*p[i];
						curV = (d[j] - d[i]) / davg;						
					}
					else{									//加满油
						curPri += (cmax - curV) * p[i];
						curV = cmax;
					}
				}
				break;
			}	
		}
		if (!hasSmall){
			if ((dis - d[i]) / davg > cmax){
				curPri += (cmax - curV) / davg;
				curV = cmax;
			}
			else {
				curPri += ((dis - d[i]) / davg - curV) * p[i];
				curV = (dis - d[i]) / davg;
			}
		}
	}
	
	if ((dis - d[n - 1]) > davg * curV){
		printf("The maximum travel distance = %.2lf", d[n - 1] + curV * davg);
	}else{
		printf("%.2lf", curPri);
	}	
	system("pause");
}
