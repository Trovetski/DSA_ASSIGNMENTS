#include<stdio.h>
#include<stdlib.h>

/*
this code is written by
Aditya Gadhavi(B19EE004)

All code is 100% original

asummptions:

distinct inputs
valid inputs
*/

typedef struct NODE//tree nodes
{
	int data;
	struct NODE* left;
	struct NODE* right;
	int height;
}node;

node* root = NULL;//the root n0de

int getHeight(node* n)
{
	if(n == NULL)
	{
		return 0;
	}else
	{
		return n->height;
	}
}

int getBalanceFactor(node* n)
{
	if(n == NULL)
	{
		return 0;
	}else
	{
		return getHeight(n->right) - getHeight(n->left);
	}
}

void leftRotate(node** n)
{
	node* right = (*n)->right;
	node* new = right->left;

	right->left = (*n);
	(*n)->right = new;

	int a = getHeight((*n)->left);
	int b = getHeight((*n)->right);
	(*n)->height = 1 + a?(a>b):b;

	a = getHeight(right->left);
	b = getHeight(right->right);
	right->height = 1 + a?(a>b):b;

	*n = right;
}

void rightRotate(node** n)
{
	node* left = (*n)->left;
	node* new = left->right;

	left->right = (*n);
	(*n)->left = new;

	int a = getHeight((*n)->left);
	int b = getHeight((*n)->right);
	(*n)->height = 1 + a?(a>b):b;

	a = getHeight(left->left);
	b = getHeight(left->right);
	left->height = 1 + a?(a>b):b;

	*n = left;
}

void insertNode(int data)
{
	node* n = (node*)malloc(sizeof(node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;

	node** temp = &root;//this is a double pointer
	//the double pointer reduces number of requires pointer
	node* arr[16];
	int i = 0;

	arr[i] = *temp;
	i++;
	while((*temp) != NULL)
	{
		if((*temp)->data <= data)
		{
			temp = &((*temp)->right);
			arr[i] = *temp; i++;
			n->height += 1;
		}else if((*temp)->data > data)
		{
			temp = &((*temp)->left);
			arr[i] = *temp; i++;
			n->height += 1;
		}
	}
	n->height -= 1;
	*temp = n;
	printf("a: %d\n",(*temp)->height );

	while(i > -1)
	{
		int balance = getBalanceFactor(arr[i]);
	
		if(balance < -1)
		{
			if(((arr[i])->left)->data > data)
			{
				rightRotate(&arr[i]);
			}else
			{
				leftRotate(&((arr[i])->left));
				rightRotate(&arr[i]);
			}
		}else if(balance > 1)
		{
			if((arr[i])->right->data < data)
			{
				leftRotate(&arr[i]);
			}else
			{
				rightRotate(&((arr[i])->right));
				leftRotate(&arr[i]);
			}
		}
		i--;
	}
}

void deleteNode(int data){};

void printInOrder(node* head)
{
	if(head == NULL)
	{
		return;
	}

	printInOrder(head->left);
	printf("(%d, %d, %d)\n", head->data, head->height, getBalanceFactor(head));
	printInOrder(head->right);
};

int main()
{
	int choice = 0, data, n = 0;
	while(1)
	{
		printf("Enter Input : ");
		scanf("%d", &choice);
		getchar();

		if(choice > 7)
		{
			printf("Terminating\n");
			break;
		}

		switch(choice)
		{
			case 1:
				scanf("%d", &n);
				getchar();
				while(n>0)
				{
					scanf("%d", &data);
					insertNode(data);
					n--;
				}getchar();

				break;
			case 2:
				scanf("%d", &data);
				insertNode(data);
				getchar();

				break;
			case 3:
				scanf("%d", &data);
				deleteNode(data);
				getchar();

				break;
			case 4:
				printInOrder(root);
				printf("\n");

				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
		}
	}
	return 0;
}
