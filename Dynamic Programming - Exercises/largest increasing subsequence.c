#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a) > (b)  ? (a) : (b) )
int lis(int array[], int *list, int n);
int main(){
	
	int arr[] = { 35, 22, 9, 33, 21, 50, 41, 60 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    
	int *list = (int*)malloc((n)*sizeof(int*));
	
	int max = lis(arr,list,n);
	printf("\n length: %d",max);
	

	
	return 0;
}

int lis_brute_force(int array[],int n){
	
	int i,j;
	int max = 0;
	int temp;
	int temp2;
	for(i=0;i<n;i++){
		temp = 1;
		temp2 = array[i];
		for(j=i+1;j<n;j++){
			if(temp2 < array [j]){
				temp2 = array[j];
				temp++;
			}
		
		}
		if(temp > max)
			max = temp;
		
	}
	
	return max;
	
}

int lis(int array[], int *list, int n){
	int i,j;
	int max;
	int max2 = 0;
	for(i=0;i<n;i++){
		list[i]=1;
	}
	
	for(i=n-1;i>=0;i--){
		max = 1;
		for(j = i+1; j<n;j++){
			if(array[i]<array[j]){
				list[i] = MAX(list[i],1+list[j]);
				max =list[i];
			}
		}
		
		if(max>max2)
			max2 = max;
	}
	
	
	return max2;
}
