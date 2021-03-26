#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct NODE//the actual node that stores polynomials
{
	int data;
	struct NODE* next;//next element
}node;

void nodeFromList(int arr[], int len, node** head)
{
	node* n = (node*)malloc(sizeof(node*));
	n->data = arr[0];
	n->next = NULL;

	*head = n;
	int i;
	for(i = 1;i < len;i++)
	{
		node* m = (node*)malloc(sizeof(node*));
		m->data = arr[i];
		m->next = NULL;

		n->next = m;
		n = m;
	}
}

void printList(node* head)
{
	while(head != NULL)
	{
		printf("%d ",head->data);
		head = head->next;
	}
}

void invertList(node** head)
{
	node* a = NULL;
	node* b = *head;
	node* c = NULL;

	if(b != NULL)
	{
		c = b->next;
	}

	while(c != NULL)
	{
		b->next = a;
		a = b;
		b = c;
		c = c->next;
	}
	
	b->next = a;
	*head = b;
}


int main()
{
	int n, i;
	printf("Enter length n: ");
	scanf("%d",&n);

	printf("Enter the list: ");
	int* arr = (int*)malloc(sizeof(int)*n);
	for(i = 0;i < n;i++)
	{
		scanf("%d", &arr[i]);
	}getchar();
	
	node* head;
	nodeFromList(arr, n, &head);

	printList(head);
	printf("\n");

	invertList(&head);

	printList(head);
	printf("\n");
}
