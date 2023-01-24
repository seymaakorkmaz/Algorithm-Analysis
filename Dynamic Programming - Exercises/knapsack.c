#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return (a > b)? a : b; }
int** knapsack2(int W, int wt[], int val[], int n);
int main(){
	
	int val[] = {1,6,18,22,28};
    int wt[] = {1,2,5,6,7};
    int W = 11;
    int i,j;
    int n = sizeof(val) / sizeof(val[0]);
    
    int **P = (int**)calloc((n+1),sizeof(int*));

	for(i =0; i<n+1; i++){
	    P[i] = (int*)calloc((W+1),sizeof(int));
	}
	
	int *alinan = (int*)malloc((n)*sizeof(int*));
	
 	P = knapsack2(W,wt,val,n);
 	
 	printf(" max weight: %d",P[n][W]);
 	i=0;
 	while(n != 1){
 		
 		if(P[n][W] != P[n-1][W]){
 			
 			alinan[i] = n;
 			i++;
 			W = W-wt[n-1];
		}
			
		n--;
		
	}
	
	j = i;
	printf("\n\n Items received: \n");
	for(i=0;i<j;i++){
		printf(" %d ",alinan[i]);
	}


	return 0;
}



int** knapsack2(int W, int wt[], int val[], int n)
{
    int i, w;
   
    int **K = (int**)calloc((n+1),sizeof(int*));

	for(i =0; i<n+1; i++){
	    K[i] = (int*)calloc((W+1),sizeof(int));
	}
 
 
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
 
   return K;
}

int knapsack(int weight[], int value[], int W, int n){
	
	if(n == 0 || W == 0)
		return 0;
	
	if(weight[n-1] > W)
		return knapsack(weight, value, W, n-1);
	else
		return max(value[n-1]+knapsack(weight, value, W-weight[n-1], n-1) , knapsack(weight, value, W, n-1));	
	
}
