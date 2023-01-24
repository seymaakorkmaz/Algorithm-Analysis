#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a) > (b)  ? (a) : (b) )

int **lcs2(char *word1, char *word2);
int main(){
	int i,j,k;
	char *word1 = "AGGTAB";
	char *word2 = "GXTXAYB";
	
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	
//	printf("%d",lcs(word1,word2,len1,len2));
	
	int **matrix = (int**)malloc((len1+1)*sizeof(int*));

	for(i =0; i<len1+1; i++){
	    matrix[i] = (int*)malloc((len2+1)*sizeof(int));
	}
	
	matrix = lcs2(word1,word2);
	printf("    length: %d",matrix[len1][len2]);
	
	char *sonuc = (char*)malloc((len1)*sizeof(char*));
	i = len1;
	j = len2;
	k=0;
	printf("\n");
	while(i != 1){
		while(matrix[i][j] == matrix[i][j-1]){
			j = j-1;
		}
		sonuc[k] = word2[j];  //ters ekliyor harfleri
		k++;
		i = i-1;
	}
	
	for(i=0;i<k;i++){
		printf(" %c ",sonuc[i]);
	}
	return 0;
	
}

int lcs(char *word1,char *word2, int len1, int len2){
	
	if(len1 == 0 || len2 == 0)
		return 0;
	
	if(word1[len1-1]==word2[len2-1])
		return 1+lcs(word1,word2,len1-1,len2-1);
	else
		return MAX(lcs(word1,word2,len1,len2-1),lcs(word1,word2,len1-1,len2));
}

int **lcs2(char *word1, char *word2){
	int i,j;
	
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	
	int **matrix = (int**)malloc((len1+1)*sizeof(int*));

	for(i =0; i<len1+1; i++){
	    matrix[i] = (int*)malloc((len2+1)*sizeof(int));
	}
	
	for(i=0;i<=len1;i++){
		for(j=0;j<=len2;j++){
			if(i == 0 || j == 0)
				matrix[i][j] = 0;
			else if(word1[i] == word2[j])
				matrix[i][j] = matrix[i-1][j-1]+1;
			else
				matrix[i][j] = MAX(matrix[i-1][j],matrix[i][j-1]);
		}
	}
	
	return matrix;
}
