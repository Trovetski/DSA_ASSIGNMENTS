#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct STACK
{
	int top;
	int* arr;
}stack;

void push(stack** s, int val)
{
	(*s)->arr[(*s)->top] = val;
	(*s)->top = (*s)->top + 1;
}

void pop(stack** s)
{
	(*s)->top = (*s)->top - 1;
}

int stackTop(stack** s)
{
	return (*s)->arr[(*s)->top -1];
}

int isValid(int* input, int n)
{
	stack* s = (stack*)malloc(sizeof(stack*));
	s->top = 0;
	s->arr[0] = 0;

	int i, next = 1;
	for(i = 0;i < n;i++)
	{
		while(stackTop(&s) < input[i])
		{
			push(&s, next);
			next++;
		}
		if(stackTop(&s) == input[i])
		{
			pop(&s);
		}
		else
		{
			return 0;
		}
	}
	free(s);
	return 1;
}

void displaySeq(int* input, int n)
{
	stack* s = (stack*)malloc(sizeof(stack*));
	s->top = 0;
	s->arr[0] = 0;

	int i, next = 1;
	for(i = 0;i < n;i++)
	{
		while(stackTop(&s) < input[i])
		{
			push(&s, next);
			printf("push(%d) ",next);
			next++;
		}
		if(stackTop(&s) == input[i])
		{
			printf("pop(%d) ",stackTop(&s));
			pop(&s);
		}
	}
	free(s);
}	

int main()
{
	int n, i;
	printf("Enter max value n: ");
	scanf("%d",&n);

	int *input = (int *)malloc(sizeof(int)*n);

	printf("Enter the given sequence: ");
	for(i = 0;i < n;i++)
	{
		scanf("%d", &input[i]);
	}

	if(isValid(input, n))
	{
		printf("Yes\n");
		displaySeq(input, n);
	}else
	{
		printf("No\n");
	}
}
