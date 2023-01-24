#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MIN(a,b) ((a) < (b)  ? (a) : (b) )
#define MIN_THREE(a,b,c) MIN(MIN(a,b),(c))

int **edit_distance(char *word1, char *word2);

int main(){
	int i,j;
	
	char *word1 = "maths";
	char *word2 = "arts";
	
	int len1 = strlen (word1);
    int len2 = strlen (word2);
	
    int **matrix = (int**)malloc((len1+1)*sizeof(int*));

	for(i =0; i<len1+1; i++){
	    matrix[i] = (int*)malloc((len2+1)*sizeof(int));
	}
	
	matrix = edit_distance(word1,word2);
	
	printf("  distance: %d",matrix[len1][len2]);
	
//	printf(" %d",edit(word1,word2,len1,len2));
	
	return 0;
	
}

int edit(char *word1, char *word2, int len1, int len2){
    
    if(len1 == 0)
    	return len2;
    if(len2 == 0)
    	return len1;
	
	if(word1[len1-1] == word2[len2-1])
		return edit(word1,word2,len1-1,len2-1);
		
	return 1+MIN_THREE(edit(word1,word2,len1-1,len2),edit(word1,word2,len1,len2-1),edit(word1,word2,len1-1,len2-1)+(word1[len1-1] == word2[len2-1] ? 0 : 1));
    
}

int **edit_distance(char *word1, char *word2){
	
	int i,j;
	int len1,len2;
	
	len1 = strlen (word1);
    len2 = strlen (word2);
    
    int **matrix = (int**)malloc((len1+1)*sizeof(int*));

	for(i =0; i<len1+1; i++){
	    matrix[i] = (int*)malloc((len2+1)*sizeof(int));
	}
	
	matrix[0][0] = 0;
	
	for(i=1;i<=len2;i++)
		matrix[0][i] = matrix[0][i-1]+1;
	
	for(j=1;j<=len1;j++)
		matrix[j][0] = matrix[j-1][0]+1;
		
	for(i=1;i<=len1;i++){
		for(j=1;j<=len2;j++){
			matrix[i][j] = MIN_THREE(matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
		}
	}
	
	return matrix;
    
}
