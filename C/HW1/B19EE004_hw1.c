#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<mem.h>

/*
written by Aditya Gadhavi(B19EE004)

this code saves all cases in a linked list
then loops over each case and prints desired output
after which it procceds to the next case
and finally clears memory at end of main

*/


typedef struct SNODE//super node
{
	char P1[64];// polynomial 1
	char P2[64];

	int x;      //test number

	struct SNODE* next;

}snode;

void addCase(char P1[],char P2[], int x, snode** head_ptr)// adds test cases
{
	if(*head_ptr != NULL) //since we need to add at end make sure head isnt null
	{
		snode* temp = *head_ptr;
		while(temp->next != NULL)//find the end
		{
			temp = temp->next;
		}

		snode *sn = (snode*)malloc(sizeof(snode));//append there
		strcpy(sn->P1, P1);
		strcpy(sn->P2, P2);
		sn->x = x;
		sn->next = NULL;
		temp->next = sn;
	}else{
		snode *sn = (snode*)malloc(sizeof(snode));//same as above
		strcpy(sn->P1, P1);
		strcpy(sn->P2, P2);
		sn->x = x;
		sn->next = NULL;
		*head_ptr = sn;
	}
}

typedef struct NODE//the actual node that stores polynomials
{
	int coeff; //coefficient
	int power;   //power

	struct NODE* next;//next element
}node;

void nodeFromNodes(node* p1, node* p2, node** head, int len, int flag)//to evaluate p3 and p4
{
	node* p1_ = p1;// to loop over p1
	node* p2_ = p2;// to loop over p2

	int coeff = 0;
	int flagx = 0;
	node* temp_ = NULL;
	
	while(len>=0)
	{
		coeff = 0;
		if((p1_ != NULL)&&(p1_->power == len)){
			coeff += p1_->coeff;
			p1_ = p1_->next;
		}
		if((p2_ != NULL)&&(p2_->power == len)){
			coeff += flag*(p2_->coeff);
			p2_ = p2_->next;
		}
		if(coeff != 0)
		{
			node* temp = (node*)malloc(sizeof(node));
			temp->coeff = coeff;
			temp->power = len;
			temp->next = NULL;
			if(flagx == 0)
			{
				*head = temp;
				temp_ = temp;
				flagx = 1;
			}else{
				temp_->next = temp;
				temp_ = temp;
			}
		}
		len--;
	}
}

int* coeffFromString(char arr[]) //to extract coeff from input
{
	int* out = (int*)malloc(sizeof(int)*15);
	int j = 0;
	
	int num = 0; //to keep track of the num
	int isNeg = 1;//to check if its negative

	int i = 1;//iterator
	int flag = 0;
	while((arr[i] != '\0')&&(arr[i] != '\n'))
	{
		if(arr[i] != ' ')
		{
			if(arr[i] == '-')
			{
				isNeg = -1;
			}else{
				num = 10*num + (arr[i] - '0');
			}
			flag = 1;
		}else{
			if(flag == 1)
			{
				num = isNeg*num;
				out[j] = num;
				j++;
				num = 0;
				flag = 0;
				isNeg = 1;
			}
		}
		i++;
	}
	out[j] = isNeg*num;
	return out;
}

int nodeFromString(char arr[], node** p)//convert user input into linked list
{
	int* coeffArr = coeffFromString(arr);//get all coefficients from input

	int power = arr[0] - '0';// power and coeff of first node
	int coeff = coeffArr[0];

	node* fn = (node*)malloc(sizeof(node));
	fn->power = power;
	fn->coeff = coeff;
	fn->next = NULL;

	*p = fn; //set the head to first node
	
	int i;//iterator
	int c = power;//another iterator
	node* temp = *p;//guess what.....another iterator:)
	
	for(i = 1; i <= c ; i++)
	{
		power--;
		coeff = coeffArr[i];
		if(coeff != 0)
		{
			node* temp_ = (node*)malloc(sizeof(node));
			temp_->power = power;
			temp_->coeff = coeff;
			temp_->next = NULL;

			temp->next = temp_;
			temp = temp_;
		}
	}
	return c;
}

double evalFromNode(node* head, int x)//to evaluate the p(x)
{
	double out = 0.00;
	while(head != NULL)
	{
		int coeff = head->coeff;
		int power = head->power;

		out += (coeff)*pow(x,power);
		head = head->next;
	}
	return out;
}

void display(node* head) // to display a polynomial
{
	char arr[128];
	int count = 0;
	int temp = 0;

	if(head!= NULL)
	{
		temp = head->coeff;
		if(temp<0)
		{
			arr[count] = '-';
			count++;
		}
		temp = fabs(temp);
		if(temp>100)
		{
			arr[count] = temp/100 + '0';count++;
			temp = temp%100;
			arr[count] = temp/10 + '0';count++;
			temp = temp%10;
			arr[count] = temp + '0';count++;
		}else if(temp>=10)
		{
			arr[count] = temp/10 + '0';count++;
			temp = temp%10;
			arr[count] = temp + '0';count++;
		}else{
			arr[count] = temp + '0';count++;
		}
		if(head->power != 0)
		{
			arr[count] = 'x'; count++;
			arr[count] = '^'; count++;
			arr[count] = head->power + '0';count++;
		}
		head = head->next;
	}else{
		printf("0");
	}
	while(head != NULL)
	{
		temp = head->coeff;
		if(temp>0) //add leading sign, fuck the first one
		{
			arr[count] = ' ';count++;
			arr[count] = '+';count++;
			arr[count] = ' ';count++;
		}else{
			arr[count] = ' ';count++;
			arr[count] = '-';count++;
			arr[count] = ' ';count++;
		}
		temp = fabs(temp);
		if(temp>100)
		{
			arr[count] = temp/100 + '0';count++;
			temp = temp%100;
			arr[count] = temp/10 + '0';count++;
			temp = temp%10;
			arr[count] = temp + '0';count++;
		}else if(temp>=10)
		{
			arr[count] = temp/10 + '0';count++;
			temp = temp%10;
			arr[count] = temp + '0';count++;
		}else{
			arr[count] = temp + '0';count++;
		}
		if(head->power != 0)
		{
			arr[count] = 'x'; count++;
			arr[count] = '^'; count++;
			arr[count] = head->power + '0';count++;
		}
		if((head->power == 0)&&(temp == 0))
		{
			arr[count] = '0'; count++;
			arr[count] = '\n'; count++;
		}
		head = head->next;
	}
	arr[count] = '\0';
	printf("%s\n", arr);
}

void freeLinkedList(node* head)
{
	while(head != NULL)
	{
		node* temp = head;
		head = head->next;
		free(temp);
	}
}

int main()
{
	int K = 0; // test cases
	snode* sHead = NULL;

	printf("Enter number of test cases: ");
	scanf("%d", &K);
	getchar();

	int i;     //iterator
	for(i = K;i > 0;i--)
	{
		char P1[64]; //same as above

		printf("Enter P1: ");
		fgets(P1, 64, stdin);

		char P2[64];

		printf("Enter P2: ");
		fgets(P2, 64, stdin);

		int x;

		printf("Enter x: ");
		scanf("%d", &x);
		getchar();

		addCase(P1, P2, x, &sHead);
	}

	while(sHead != NULL)
	{
		node* p1 = NULL;
		node* p2 = NULL;
		node* p3 = NULL;
		node* p4 = NULL;

		int p1p = nodeFromString(sHead->P1, &p1); //make LL for p1
		int p2p = nodeFromString(sHead->P2, &p2); //make LL for p2

		nodeFromNodes((p1p>=p2p)?p1:p2, (p1p>=p2p)?p2:p1, &p3, (p1p>p2p)?p1p:p2p, 1);
		nodeFromNodes((p1p>=p2p)?p1:p2, (p1p>=p2p)?p2:p1, &p4, (p1p>p2p)?p1p:p2p, -1);

		double p1x = evalFromNode(p1,sHead->x);
		double p2x = evalFromNode(p2,sHead->x);
		double p3x = evalFromNode(p3,sHead->x);
		double p4x = evalFromNode(p4,sHead->x);

		printf("P1(x) : ");
		display(p1);
		printf("P2(x) : ");
		display(p2);
		printf("P3(x) = P1(x) + P2(x) : ");
		display(p3);
		printf("P4(x) = P1(x) - P2(x) : ");
		display(p4);
		printf("P1(%d): %f\n",sHead->x,p1x);
		printf("P2(%d): %f\n",sHead->x,p2x);
		printf("P3(%d): %f\n",sHead->x,p3x);
		printf("P4(%d): %f\n",sHead->x,p4x);

		freeLinkedList(p1);
		freeLinkedList(p2);
		freeLinkedList(p3);
		freeLinkedList(p4);
		
		snode* temp = sHead;
		sHead = sHead->next;
		free(temp);
	}

	return 0;
}
