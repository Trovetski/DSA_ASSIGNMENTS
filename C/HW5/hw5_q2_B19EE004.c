#include<stdio.h>
#include<stdlib.h>

typedef struct NODE
{
	int key;
	struct NODE* next;
}node;

int hash(int key)
{
	return key%19;
}

void insert(node* arr[], int key)
{
	int index = hash(key);

	node* n = (node*)malloc(sizeof(node*));
	n->key = key;
	n->next = NULL;

	if(arr[index] == NULL)
	{
		arr[index] = n;
	}else
	{
		node** temp = &arr[index];
		while((*temp) != NULL)
		{
			temp = &((*temp)->next);
		}
		*temp = n;
	};
}

void printPairs(node* arr[], int k)
{
	node* temp;
	int i, x, flag = 0;
	for(i=0;i<19;i++)
	{
		temp = arr[i];
		while(temp != NULL)
		{
			x = k - temp->key;
			if(x < 0)
			{
				break;
			}
			x = hash(x);
			if(arr[x] != NULL)
			{
				printf("found pair (%d, %d)\n", temp->key, x);
				flag = 1;
				arr[x] = NULL;
			}
			temp = temp->next;
		}
	}
	if(flag == 0)
	{
		printf("Not found");
	}
}

int main()
{
	node* arr[19];
	int i, n1, key, k;
	for(i=0;i<19;i++)
	{
		arr[i] = NULL;
	}i = 0;

	printf("Enter array: ");
	scanf("%d", &n1); getchar();
	while(n1 > 0)
	{
		scanf("%d", &key);
		insert(arr, key);
		getchar();
		n1--;
	}

	printf("Enter k: ");
	scanf("%d", &k); getchar();

	printPairs(arr, k);

	return 0;
}
