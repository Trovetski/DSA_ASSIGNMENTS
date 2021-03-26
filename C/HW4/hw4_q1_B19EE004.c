#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

int maxarr[MAX];
int minarr[MAX];

void maxHeapify(int arr[],int i)
{
	int left = 2*i;
	int right = 2*i +1;

	int larger = i;
	if((left < arr[0])&&(arr[left] > arr[i]))
	{
		larger = left;
	}

	if((right < arr[0])&&(arr[right] > arr[larger]))
	{
		larger = right;
	}

	if(larger != i)
	{
		int temp = arr[i];
		arr[i] = arr[larger];
		arr[larger] = temp;

		maxHeapify(arr, larger);
	}
};

void minHeapify(int arr[],int i)
{
	int left = 2*i;
	int right = 2*i +1;

	int smaller = i;
	if((left < arr[0])&&(arr[left] < arr[i]))
	{
		smaller = left;
	}

	if((right < arr[0])&&(arr[right] < arr[smaller]))
	{
		smaller = right;
	}

	if(smaller != i)
	{
		int temp = arr[i];
		arr[i] = arr[smaller];
		arr[smaller] = temp;

		minHeapify(arr, smaller);
	}
};

void delMaxHeap(int arr[], int m)
{
	int index = 1;
	while(arr[index] != m)
	{
		index++;
		if(index > arr[0]-1)
		{
			printf("Not Present!\n");
			return;
		}
	}
	arr[index] = arr[arr[0]-1];
	arr[0] = arr[0] - 1;
	maxHeapify(arr, index);
};

void delMinHeap(int arr[], int m)
{
	int index = 1;
	while(arr[index] != m)
	{
		index++;
		if(index > arr[0]-1)
		{
			printf("Not Present!\n");
			return;
		}
	}
	arr[index] = arr[arr[0]-1];
	arr[0] = arr[0] - 1;
	minHeapify(arr, index);

};

void maxSort(int arr[])
{
	while(arr[0] > 1)
	{
		printf("%d ", arr[1]);
		arr[1] = arr[arr[0] - 1];
		arr[0] = arr[0] - 1;

		maxHeapify(arr, 1);
	}
	printf("\n");
};
void minSort(int arr[])
{
	while(arr[0] > 1)
	{
		printf("%d ", arr[1]);
		arr[1] = arr[arr[0] - 1];
		arr[0] = arr[0] - 1;

		minHeapify(arr, 1);
	}
	printf("\n");
};
void print(int arr[])
{
	int i;
	for(i = 1;i < arr[0];i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int choice = 0;
	int data = 0, i;
	char c;

	while(1)
	{
		printf("Enter input: ");
		scanf("%d", &choice);
		getchar();

		if(choice == 6)
		{
			printf("Terminating\n");
			break;
		}

		c = getchar();

		switch(choice)
		{
			case 1:
				if(c == 'X')
				{
					scanf("%d", &data);
					maxarr[0] = data+1;

					for(i = 1;i < maxarr[0];i++)
					{
						scanf("%d", &data);
						maxarr[i] = data;
					}

					for(i = maxarr[0]/2;i > 0; i--)
					{
						maxHeapify(maxarr, i);
					}
					print(maxarr);
				}else if(c == 'N')
				{
					scanf("%d", &data);
					minarr[0] = data+1;

					for(i = 1;i < minarr[0];i++)
					{
						scanf("%d", &data);
						minarr[i] = data;
					}
					for(i = minarr[0]/2;i > 0; i--)
					{
						minHeapify(minarr, i);
					}

					print(minarr);
				}
				break;
			case 2:
				if(c == 'X')
				{
					scanf("%d", &data);
					maxarr[maxarr[0]] = data;
					maxarr[0] = maxarr[0] + 1;

					i = maxarr[0] - 1;
					while(i>1)
					{
						int parent = i/2;
						if(maxarr[parent]<maxarr[i])
						{
							int temp = maxarr[i];
							maxarr[i] = maxarr[parent];
							maxarr[parent] = temp;

							i = parent;
						}else
						{
							break;
						}
					}
					print(maxarr);
				}else if(c == 'N')
				{
					scanf("%d", &data);
					minarr[minarr[0]] = data;
					minarr[0] += 1;

					i = minarr[0] - 1;
					while(i>1)
					{
						int parent = i/2;
						if(minarr[parent]>minarr[i])
						{
							int temp = minarr[i];
							minarr[i] = minarr[parent];
							minarr[parent] = temp;

							i = parent;
						}else
						{
							break;
						}
					}

					print(minarr);
				}
				break;
			case 3:
				if(c == 'X')
				{
					scanf("%d", &data);
					delMaxHeap(maxarr, data);
					print(maxarr);
				}else if(c == 'N')
				{
					scanf("%d", &data);
					delMinHeap(minarr, data);
					print(minarr);
				}
				break;
			case 4:
				if(c == 'X')
				{
					delMaxHeap(maxarr, maxarr[1]);
					print(maxarr);
				}else if(c == 'N')
				{
					delMinHeap(minarr, minarr[1]);
					print(minarr);
				}
				break;
			case 5:
				if(c == 'X')
				{
					maxSort(maxarr);
					print(maxarr);
				}else if(c == 'N')
				{
					minSort(minarr);
					print(minarr);
				}
				break;
			default:
				printf("Invalid input!\n");
				break;
		}
	}
	return 0;
}

