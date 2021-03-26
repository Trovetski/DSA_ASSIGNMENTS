#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*

the code is written by Aditya gadhavi(B19EE004)
it assumes n<64 in all real sense
takes input n followed bu the seqeunce

*/

//for the methods pass by refrence is used
//along with array implementation of stack

void push(int *arr, int *top, int val)
{
	arr[*top] = val;
	*top = *top + 1;
}

void pop(int *top)
{
	*top = *top - 1;
}

int stackTop(int *arr, int* top)
{
	return arr[*top - 1];
}


int getAndPrint(int n, int arr[])
{
	int i = 0, top = 1,temp = 1, sT;
	int *s = (int*)malloc(sizeof(int)*n);
	s[0] = 0;

	char *output = (char*)malloc(sizeof(char)*2*n*12);
	strcpy(output, " ");

	char c[12];
	while(i < n)
	{
		sT = stackTop(s, &top);
		if(sT < arr[i])
		{
			push(s, &top, temp);
			sprintf(c,"push(%d) ",temp);
			strcat(output,c);
			temp++;
		}else if(sT == arr[i])
		{
			sprintf(c,"pop(%d) ",sT);
			strcat(output,c);
			pop(&top);
			i++;
		}else
		{
			printf("No");
			free(output);
			free(s);
			return 0;
		}
	}

	printf("Yes\n");
	printf("%s",output);
	free(output);
	free(s);
	return 1;
}
int main()
{
	int n, i;
	printf("Enter the value of n: ");
	scanf("%d",&n);

	int *arr = (int *)malloc(sizeof(int)*n);

	printf("Enter the sequence: ");
	for(i = 0;i < n;i++)
	{
		scanf("%d", &arr[i]);
	}

	getAndPrint(n,arr);
}
