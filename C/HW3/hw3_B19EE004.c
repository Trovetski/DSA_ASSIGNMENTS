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
}node;

node* root = NULL;//the root n0de

void insertNode(int data)
{
	node* n = (node*)malloc(sizeof(node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;

	node** temp = &root;//this is a double pointer
	//the double pointer reduces number of requires pointer

	while((*temp) != NULL)
	{
		if((*temp)->data <= data)
		{
			temp = &((*temp)->right);
		}else if((*temp)->data > data)
		{
			temp = &((*temp)->left);
		}
	}
	*temp = n;
}

void delete(int data)
{
	node** temp = &root;
	while(((*temp) != NULL)&&(*temp)->data != data)//this while loop finds the node to be deleted
	{
		if(*temp == NULL)
		{
			printf("Data Not Present\n");
			return;
		}else if((*temp)->data <= data)
		{
			temp = &((*temp)->right);
		}else if((*temp)->data > data)
		{
			temp = &((*temp)->left);
		}else
		{
			printf("Data Not Present\n");
			return;
		}
	}
	if((*temp) == NULL)//if dosent exsist then
	{
		printf("EMPTY TREE!\n");
		return;
	}

	node* temp0 = NULL;
	if((*temp)->left == NULL)//left case, also takes care of no child
	{
		temp0 = *temp;
		*temp = (*temp)->right;
		free(temp0);
	}else if((*temp)->right == NULL)//right case
	{
		temp0 = *temp;
		*temp = (*temp)->left;
		free(temp0);
	}else//if two children, find and replace
	{
		node* temp1 = NULL;
		temp0  = (*temp)->left;
		while(temp0->right != NULL)
		{
			temp1 = temp0;
			temp0 = temp0->right;
		}
		if(temp1 == NULL)
		{
			temp0->right = (*temp)->right;
			free(*temp);
			*temp = temp0;
		}else
		{
			temp1->right = temp0->left;
			temp0->right = (*temp)->right;
			temp0->left = (*temp)->left;
			free(*temp);
			*temp = temp0;
		}
	}
}

int getLeaves(node* n)
{
	if(n == NULL)
	{
		return 0;
	}
	if((n->left == NULL)&&(n->right == NULL))
	{
		return 1;
	}else
	{
		int i = 0;
		if(n->left != NULL)
		{
			i += getLeaves(n->left);
		}
		if(n->right != NULL)
		{
			i += getLeaves(n->right);
		}
		return i;
	}
}

//all below do what they say:)

int getInternalNodes(node* n)
{
	if(n == NULL)
	{
		return 0;
	}
	if((n->left == NULL)&&(n->right == NULL))
	{
		return 0;
	}else
	{
		int i = 1;
		if(n->left != NULL)
		{
			i += getInternalNodes(n->left);
		}
		if(n->right != NULL)
		{
			i += getInternalNodes(n->right);
		}
		return i;
	}
}

int getHeight(node* n)
{
	if(n == NULL)
	{
		return 0;
	}
	if((n->left == NULL)&&(n->right == NULL))
	{
		return 1;
	}else
	{
		int lenLeft = 1;
		int lenRight = 1;
		if(n->left != NULL)
		{
			lenLeft += getHeight(n->left);
		}
		if(n->right != NULL)
		{
			lenRight += getHeight(n->right);
		}
		return (lenLeft>=lenRight)?lenLeft:lenRight;
	}
}

void printInOrder(node* head)
{
	node* arr[24];
	int top = 0;

	arr[0] = head;
	while((top != -1)&&(arr[0] != NULL))
	{
		while(arr[top] != NULL)
		{
			arr[top+1] = arr[top]->left;
			top++;
		}
		if((arr[top] == NULL)&&(top != -1))
		{
			top--;
			printf("%d ",arr[top]->data);
			arr[top] = arr[top]->right;
		}
	}
}

void printPreOrder(node* head)
{
	node* arr[24];
	int top = 0;

	arr[0] = head;
	while((top != -1)&&(arr[0] != NULL))
	{
		while(arr[top] != NULL)
		{
			arr[top+1] = arr[top]->left;
			printf("%d ",arr[top]->data);
			top++;
		}
		if((arr[top] == NULL)&&(top != -1))
		{
			top--;
			arr[top] = arr[top]->right;
		}
	}
}

void printPostOrder(node* head)
{
	node* arr[24];
	int top = 0;

	int data;
	arr[0] = head;
	while((top != -1)&&(arr[0] != NULL))
	{
		while(arr[top] != NULL)
		{
			arr[top+1] = arr[top]->left;
			data = arr[top]->data;
			top++;
		}
		if((arr[top] == NULL)&&(top != -1))
		{
			top--;
			if(arr[top]->right == NULL)
			{
				printf("%d ", arr[top]->data); top--;
				if(top == -1)
				{
					break;
				}
				if(data > arr[top]->data)
				{
					printf("%d ", arr[top]->data);
					data = arr[top]->data;
					arr[top] = NULL;
				}else
				{
					arr[top+1] = arr[top]->right;
					top++;
				}
			}else
			{
				if(data > arr[top]->data)
				{
					printf("%d ", arr[top]->data);
					data = arr[top]->data;
					arr[top] = NULL;
				}else
				{
					arr[top+1] = arr[top]->right;
					top++;
				}
			}
		}
	}		
}

void deleteTree(node* head)
{
	node* arr[24];
	int top = 0;

	int data;
	arr[0] = head;
	while((top != -1)&&(arr[0] != NULL))
	{
		while(arr[top] != NULL)
		{
			arr[top+1] = arr[top]->left;
			data = arr[top]->data;
			top++;
		}
		if((arr[top] == NULL)&&(top != -1))
		{
			top--;
			if(arr[top]->right == NULL)
			{
				free(arr[top]); top--;
				if(top == -1)
				{
					break;
				}
				if(data > arr[top]->data)
				{
					free(arr[top]);
					data = arr[top]->data;
					arr[top] = NULL;
				}else
				{
					arr[top+1] = arr[top]->right;
					top++;
				}
			}else
			{
				if(data > arr[top]->data)
				{
					free(arr[top]);
					data = arr[top]->data;
					arr[top] = NULL;
				}else
				{
					arr[top+1] = arr[top]->right;
					top++;
				}
			}
		}
	}	
}
int main()
{
	printf("Please enter the input directly\n");
	printf("Please do not enter number of elements\n");
	int choice = 0, i;
	while(choice<7)
	{
		printf("Enter your choice: ");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			case 1:
				printf("Enter input: ");
				do
				{
					scanf("%d", &i);
					insertNode(i);

				}while(getchar() != '\n');
				break;
			case 2:
				printf("Enter value: ");
				scanf("%d", &i);
				delete(i);
				break;
			case 3:
				printf("No of Leaves: %d\n", getLeaves(root));
				printf("No of Internal nodes: %d\n", getInternalNodes(root));
				printf("Height of tree: %d\n", getHeight(root) - 1);
				break;
			case 4:
				printInOrder(root);
				printf("\n");
				break;
			case 5:
				printPreOrder(root);
				printf("\n");
				break;
			case 6:
				printPostOrder(root);
				printf("\n");
				break;
		}
	}
	deleteTree(root);
	printf("Exited Successfully\n");
}		
