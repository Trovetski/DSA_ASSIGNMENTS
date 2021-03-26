#include<stdio.h>
#include<stdlib.h>

typedef struct PROF
{
	int id;
	int t;
	int d;
}prof;

void insert(prof* arr[], int t,int d,int id)
{
	prof* p = (prof*)malloc(sizeof(prof));
	p->id = id;
	p->t = t;
	p->d = d;

	arr[id-1] = p;
}

int compare(const void * a, const void * b)
{
	prof* prof1 = *((prof**)a);
	prof* prof2 = *((prof**)b);

	return (prof1->d) - (prof2->d);
}

int annoyance(prof* arr[], int n)
{
	int tt = 0;
	int a = 0;

	for(int i=0;i<n;i++)
	{
		int temp = (arr[i])->t + tt - (arr[i])->d;
		tt += (arr[i])->t;

		if(temp > 0)
		{
			a += temp;
		}
	}
	return a;
}

int main()
{
	int t, d;
	int n;
	scanf("%d", &n);
	getchar();

	prof* profarr[16];

	int i;
	for(i=0;i<n;i++)
	{
		scanf("%d", &t);
		scanf("%d", &d);
		getchar();

		insert(profarr, t, d, i+1);
	}

	qsort(profarr, n, sizeof(prof*), compare);

	for(int j=0;j<i;j++)
	{
		printf("%d ", (profarr[j])->d);
	}

	printf("\n%d", annoyance(profarr, n));
}
