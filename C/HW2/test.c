#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//this is written by Aditya Gadhavi

typedef struct STACK
{
	int isOper;
	char* arr;
	struct STACK* next;
}stack;

void push(stack** head, char val[], int isOper)
{
	printf("here\n");
	stack* s = (stack*)malloc(sizeof(stack*));
	s->isOper = isOper;
	printf("here\n");
	strcpy(s->arr,val);
	printf("here\n");
	s->next = *head;

	*head = s;
}

void pop(stack** head)
{
	stack* s = *head;
	(*head) = (*head)->next;

	free(s);
}

int peek(stack* head, char** out)
{
	strcpy((*out), head->arr);
	return head->isOper;
}

int pres(char c[])
{
	if((!strcmp(c,"^"))||(!strcmp(c,"<"))||(!strcmp(c,">")))
	{
		return 3;
	}else if((!strcmp(c,"/"))||(!strcmp(c,"*")))
	{
		return 2;
	}else if((!strcmp(c,"+"))||(!strcmp(c,"-")))
	{
		return 1;
	}else
	{
		return 0;
	}
}

void print(stack* head)
{
	while(head != NULL)
	{
		printf("%s", head->arr);
		head = head->next;
	}
}

void infixToPostfix(char input[],int len)
{
	stack* oper = (stack*)malloc(sizeof(stack*));
	oper->isOper = 0;
	oper->arr = "$";
	oper->next = NULL;

	stack* output = (stack*)malloc(sizeof(stack*));
	output->isOper = 0;
	output->arr = "$";
	output->next = NULL;

	char out[16];

	int i = 0, isOper = 0;
	while(i<len)
	{
		if((input[i]>47)&&(input[i]<58))
		{
			if(isOper == 0)
			{
				itoa(input[i] - '0', out, 10);
				push(&output, out, 1);
				printf("\n%s",out);
				isOper = 1;
			}else
			{
				itoa(atoi(output->arr)*10 + (input[i] - '0'), out, 10);
				printf("\n%s",out);
				strcpy(output->arr,out);
			}
		}else if(input[i] == 94)
		{
			if(isOper == 1)
			{
				strcat(output->arr,"^");
				printf("\n%s",output->arr);
				isOper = 0;
			}else
			{
				printf("Error\n");
				break;
			}
			isOper = 0;
		}else if(input[i] == 60)
		{
			if(input[i+1] == 60)
			{
				while(pres(oper->arr) <= 3)
				{
					push(&output, oper->arr, 0);
					pop(&oper);
				}
				push(&oper, "<", 0);
			}else{
				printf("Error\n");
				break;
			}
			i++;
			isOper = 0;

		}else if(input[i] == 62)
		{
			if(input[i+1] == 62)
			{
				while(pres(oper->arr) >= 3)
				{
					push(&output, oper->arr, 0);
					pop(&oper);
				}
				push(&oper, ">", 0);
			}else{
				printf("Error\n");
				break;
			}
			i++;
			isOper = 0;

		}else if(input[i] == 47)
		{
			while(pres(oper->arr) >= 2)
			{
				push(&output, oper->arr, 0);
				pop(&oper);
			}
			push(&oper, "/", 0);
			isOper = 0;

		}else if(input[i] == 42)
		{
			while(pres(oper->arr) >= 2)
			{
				push(&output, oper->arr, 0);
				pop(&oper);
			}
			push(&oper, "*", 0);
			isOper = 0;

		}else if(input[i] == 43)
		{
			while(pres(oper->arr) >= 1)
			{
				push(&output, oper->arr, 0);
				pop(&oper);
			}
			push(&oper, "+", 0);
			printf("got here mate\n");
			printf("pres = %d\n", pres(oper->arr));
			isOper = 0;

		}else if(input[i] == 45)
		{
			while(pres(oper->arr) >= 1)
			{
				push(&output, oper->arr, 0);
				pop(&oper);
			}
			push(&oper, "-", 0);
			isOper = 0;

		}
		i++;
	}

	print(output);
}

int main()
{
	char arr[100];
	printf("Enter the operation: ");

	char c = ' ';
	int i = 0;
	while(c != '\n')
	{
		c = getchar();
		if(c != ' ')
		{
			arr[i] = c;
			i++;
		}
	}
	infixToPostfix(arr, i);

	return 0;
}
