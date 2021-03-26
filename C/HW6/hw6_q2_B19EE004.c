#include<stdio.h>
#include<stdlib.h>

typedef struct GAMESTATE
{
	int start, end;
	int scra, scrb;

}gamestate;

gamestate* gs = NULL;

int minimax(int arr[], int turn)
{
	if(gs->start > gs->end)
	{
		int temp = gs->scra - gs->scrb;
		return temp;
	}
	if(turn == 0)
	{
		int best_score;
		gs->scra += arr[gs->start];
		gs->start += 1;

		int score1 = minimax(arr, 1);

		gs->start -= 1;
		gs->scra -= arr[gs->start];
		gs->scra += arr[gs->end];
		gs->end -= 1;

		int score2 = minimax(arr, 1);

		gs->end += 1;
		gs->scra -= arr[gs->end];
		best_score = (score1>=score2)?score1:score2;

		return best_score;
	}else if(turn == 1)
	{
		int best_score;
		gs->scrb += arr[gs->start];
		gs->start += 1;

		int score1 = minimax(arr, 0);

		gs->start -= 1;
		gs->scrb -= arr[gs->start];
		gs->scrb += arr[gs->end];
		gs->end -= 1;

		int score2 = minimax(arr, 0);

		gs->end += 1;
		gs->scrb -= arr[gs->end];
		best_score = (score1>=score2)?score2:score1;

		return best_score;
	}
}

int bestMove(int arr[])
{
	int turn = 0, sum = 0;
	printf("Steps = ");
	while(gs->start <= gs->end)
	{
		if(turn == 0)
		{
		gs->start += 1;
		int score1 = minimax(arr, 1);
	
		gs->start -= 1;
		gs->end -= 1;
		int score2 = minimax(arr,1);
		gs->end += 1;
		if(score1 >= score2)
		{
			printf("%d, ", arr[gs->start]);
			sum += arr[gs->start];
			gs->start += 1;
		}else
		{
			printf("%d, ",arr[gs->end]);
			sum += arr[gs->end];
			gs->end -= 1;
		}
		turn = 1;
		}else
		{
		gs->start += 1;
		int score1 = minimax(arr, 0);
	
		gs->start -= 1;
		gs->end -= 1;
		int score2 = minimax(arr,0);
		gs->end += 1;
		if(score1 <= score2)
		{
			gs->start += 1;
		}else
		{
			gs->end -= 1;
		}
		turn = 0;
		}
	}
	printf("\nSum = %d", sum);
}

int main()
{
	int i;
	printf("Enter Input: ");
	scanf("%d", &i);
	getchar();

	int arr[16];


	int j, input;
	for(j=0;j<i;j++)
	{
		scanf("%d", &input);
		arr[j] = input;
	}

	gs = (gamestate*)malloc(sizeof(gamestate));
	gs->scra = 0;
	gs->scrb = 0;
	gs->start = 0;
	gs->end = j-1;

	bestMove(arr);
}
