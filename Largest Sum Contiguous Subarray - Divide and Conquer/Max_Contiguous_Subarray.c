#include <stdio.h>
#include <stdlib.h>
#define MIN -10000
#define MAX 100
#define BIGGEST(x, y, z) ( (x > y && x > z) ? x : ( y > z) ? y : z 


typedef struct Max {   // Structure declaration
  int start;          
  int end;
  int sum;       
}MAX_ARRAY;

int DivideAndConquer(int A[],int l,int r,MAX_ARRAY **result);
void FindMaxSum(int A[],int l,int r,MAX_ARRAY **max);
int MaxBul(int A[],int l,int r,MAX_ARRAY **result);
 
int main(){
	int A[MAX];
	int N,i;
	
	printf("\n	                                  -- SEYMANUR KORKMAZ - 20011055 --                                  ");
	
	printf("\n\n	           Blok adetini giriniz : ");
	scanf("%d",&N);
	
	for(i=0;i<N;i++){
		printf("	           %d. blok degeri : ",i);
		scanf("%d",&A[i]);
	}
	///////////////////////////// DIVIDE AND CONQUER /////////////////////////////
	printf("\n	##################################################################################################");
	printf("\n\n	                            -- DIVIDE AND CONQUER YAKLASIMI ILE COZUM --");
	
	MAX_ARRAY *result = (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	DivideAndConquer(A,0,(N-1),&result);
	
	printf("\n\n	       MADENCININ EN BUYUK KAZANCI SAGLAYACAGI KESINTISIZ BLOKLAR SUTUNU : %d ile %d arasi \n",result->start,result->end);
	printf("	       KAZANC MIKTARI : %d\n\n",result->sum);
	printf(" 	##################################################################################################\n");
	///////////////////////////// DIVIDE AND CONQUER /////////////////////////////
	
	
	
	
	/////////////////////////////     BRUTE FORCE    /////////////////////////////
	printf(" 	##################################################################################################");
	printf("\n\n	                               -- BRUTE FORCE YAKLASIMI ILE COZUM --");
	
	int *start = malloc (sizeof(int)); 
	int *end = malloc (sizeof(int));
	int sonuc;
	sonuc = BruteForce(A,N,&start,&end);
	
	printf("\n\n	       MADENCININ EN BUYUK KAZANCI SAGLAYACAGI KESINTISIZ BLOKLAR SUTUNU : %d ile %d arasi \n",start,end);
	printf("	       KAZANC MIKTARI : %d\n\n",sonuc);
	printf(" 	##################################################################################################\n\n");
	////////////////////////////     BRUTE FORCE    /////////////////////////////
	

	return 0;
}

int BruteForce(int A[],int N,int *start,int *end){  
	int max_sum = 0,sum;
	int i,j,k; 
	(*start) = 0;
	(*end) = 0;
	for(i=0;i<N;i++){
		sum=0;
		for(j=i;j<N;j++){
				sum = sum + A[j];
				
				if(sum > max_sum){
					max_sum = sum;
					(*start) = i;
					(*end) = j;
				}
			
		}
	}
	return max_sum; 
}

int DivideAndConquer(int A[],int l,int r, MAX_ARRAY **result){
	int m = (l+r)/2;
	if(l > r){
		return -10000;
	}else if(l == r){
		(*result)->start = l;
		(*result)->end = l; 
		(*result)->sum = A[l];
		return (*result)->sum;
	}
	
	return BIGGEST(DivideAndConquer(A,l,m-1,result), 
				DivideAndConquer(A,m+1,r,result),
				FindMaxBlock(A,l,r,result)));  
}



void FindMaxSum(int A[],int t,int m,MAX_ARRAY **max){  //FMS(0,2) t=0, m=2
	(*max) = (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	int max_sum = MIN; //-10000
	int sum = 0;
	int start,end;
	int i;
	if(t > m){ 
		start = m;
		i = m;
		while(i<=t){
	        sum += A[i];
			if(sum > max_sum){
				max_sum = sum;
				end = i;
			}
			i++;
		}
	}else{
		end = m;
		i = m;
		while(i>=t){
	        sum += A[i];
			if(sum > max_sum){
				max_sum = sum;
				start = i;
			}
			i--;
		}
	}
	(*max)->start = start;
    (*max)->end = end;
	(*max)->sum = max_sum;
}



int FindMaxBlock(int A[],int l,int r,MAX_ARRAY **result){
	int i;
	(*result) = (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	MAX_ARRAY *bmax =  (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	MAX_ARRAY *cmax = (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	MAX_ARRAY *dmax =  (MAX_ARRAY*)malloc(sizeof(MAX_ARRAY)*1);
	int m = (l+r)/2;  
	FindMaxSum(A,l,m,&bmax);   
	FindMaxSum(A,r,m,&cmax);            
	
	if((bmax->sum+cmax->sum-A[m])>bmax->sum && (bmax->sum+cmax->sum-A[m])>cmax->sum){  //dmax 
		dmax->start = bmax->start; 
		dmax->end = cmax->end;
		dmax->sum = bmax->sum+cmax->sum-A[m];
		(*result) = dmax;
	}else if(bmax->sum > cmax->sum){
		(*result) = bmax; 
	}else{
		(*result) = cmax;
	}
	return (*result)->sum;
}

