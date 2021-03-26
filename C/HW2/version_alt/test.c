#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void push(int *stack, int *top, int val)
{
	stack[*top] = val;
	*top = *top + 1;
}

void pop(int *stack, int *top)
{
	stack[*top] = 0;
	*top = *top - 1;
}

int stackTop(int *stack, int* top)
{
	return stack[*top - 1];
}

int getPossible(int n, int stack[])
{
	int top = 1;//top of our stack
	int next = 1;//next element
	int *a = (int*)malloc(sizeof(int)*n);
	a[0] = 0;

	int i;//iterator...
	for(i = 0;i < n;i++)
	{
		while(stackTop(a, &top) < stack[i])
		{
			push(a, &top, next);
			next++;
		}
		if(stackTop(a, &top) == stack[i])
		{
			pop(a, &top);
		}
		else
		{
			return 0;
		}
	}
	return 1;
}


void printSequence(int n, int stack[])
{
	int top = 1;//top of our stack
	int next = 1;//next element
	int *a = (int*)malloc(sizeof(int)*n);
	a[0] = 0;

	int i;//iterator...
	for(i = 0;i < n;i++)
	{
		while(stackTop(a, &top) < stack[i])
		{
			printf("push(%d) ",next);
			push(a, &top, next);
			next++;
		}
		if(stackTop(a, &top) == stack[i])
		{
			printf("pop(%d) ",stackTop(a, &top));
			pop(a, &top);
		}
	}
}

int main()
{
	int n, i;
	printf("Enter max value n: ");
	scanf("%d",&n);

	int *stack = (int *)malloc(sizeof(int)*n);

	printf("Enter the given sequence: ");
	for(i = 0;i < n;i++)
	{
		scanf("%d", &stack[i]);
	}

	if(getPossible(n, stack))
	{
		printf("Yes\n");
		printSequence(n, stack);
	}else
	{
		printf("No");
	}

}
