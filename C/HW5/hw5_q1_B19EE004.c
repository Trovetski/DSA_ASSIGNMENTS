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

int insert(node* arr[], int key)
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
			if((*temp)->key == key)
			{
				*temp = (*temp)->next;
				return key;
			}
			temp = &((*temp)->next);
		}
		*temp = n;
	}
	return -1;
}

void display(node* arr[])
{
	int i;
	node* temp;
	for(i=0;i<19;i++)
	{
		temp = arr[i];
		while(temp != NULL)
		{
			printf("%d, ", temp->key);
			temp = temp->next;
		}
	}
	printf("\n");
}

int main()
{
	node* arr[19];
	int i, n1, key, common[19];
	for(i=0;i<19;i++)
	{
		arr[i] = NULL;
		common[i] = -1;
	}i = 0;

	printf("Enter first array: ");
	scanf("%d", &n1); getchar();
	while(n1 > 0)
	{
		scanf("%d", &key);
		if(insert(arr, key) != -1)
		{
			common[i] = key;
			i++;
		}
		getchar();
		n1--;
	}

	printf("Enter second array: ");
	scanf("%d", &n1); getchar();
	while(n1 > 0)
	{
		scanf("%d", &key);
		if(insert(arr, key) != -1)
		{
			common[i] = key;
			i++;
		}
		getchar();
		n1--;
	}

	printf("The symettric diffrence is: ");
	display(arr);

	printf("The common elements are: ");
	while(i > 0)
	{
		i--;
		printf("%d, ", common[i]);
	}
	return 0;
}
