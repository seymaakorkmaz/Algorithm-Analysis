#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(int **matrix, int rotate_row, int N);
void printMatrix(int **matrix, char **colors, int N);
void copyMatrix(int **matrix1, int **matrix2, int N);

int main(){
	int mode; 
	int N,i,j;
	int colorNumber = 0;
	char color[20];  
	int **matrix;
	
	printf("\n	Enter the number of colors : ");  
	scanf("%d",&N);
	

	
	int **matrix1 = (int**)malloc(N*sizeof(int*));   // memory allocation N*N matrix
	for(i=0;i<N;i++){
		matrix1[i] =  (int*)malloc(N*sizeof(int));  
	}
	
	char **colors =  (char **)malloc(N*sizeof(char*));  // memory allocation colors array 
	for (i = 0; i < N; i++)
        colors[i] = malloc(254 * sizeof(char*));
        
    printf("\n	Enter the initial state of the N*N matrix : \n\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("	  ");
			scanf("%s",color);
			matrix1[i][j] = colorize(colors,color,&colorNumber);
		}
	}
	
	system("cls");
	printf("\n	 	INITIAL STATE OF THE BOARD : ");
	printMatrix(matrix1, colors, N);
	
	

		
	do{
			printf("\n		1.NORMAL MODE");
			printf("\n		2.DETAILED MODE");
			printf("\n		3.EXIT");
			printf("\n		->SELECT MODE : ");
			scanf("%d",&mode);
			
			switch(mode){
				case 1:
					
					matrix = (int**)malloc(N*sizeof(int*));   // memory allocation N*N matrix
					for(i=0;i<N;i++){
						matrix[i] =  (int*)malloc(N*sizeof(int));  
					}
	
					copyMatrix(matrix1,matrix, N); //matrixin ilk halini kaybetmemek için yeni bir matrise kopyalýyoruz.
					
					if (backTracking(matrix, 0 , N, colors, mode)) {
  	  					printf("\n		ARRANGED BOARD");
    					printMatrix(matrix, colors, N);
 					} else {
    					printf("\n		Arrange failed.\n");
  					}
					printf("\n		Press any key to continue...");
					getch();
					break;
				
				case 2:
					
						
					matrix = (int**)malloc(N*sizeof(int*));   // memory allocation N*N matrix
					for(i=0;i<N;i++){
						matrix[i] =  (int*)malloc(N*sizeof(int));  
					}
	
					copyMatrix(matrix1,matrix, N);
					
					if (backTracking(matrix, 0 , N, colors, mode)) {
  	  					printf("\n		ARRANGED BOARD");
    					printMatrix(matrix, colors, N);
 					} else {
    					printf("\n		Arrange failed.\n");
  					} 
				
					printf("\n		Press any key to continue...\n");
					getch();
				break;
			}
			
			
	}while(mode != 3);
}

void copyMatrix(int **matrix1, int **matrix2, int N){  //matris kopyalama f
	int i,j;
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			matrix2[i][j] = matrix1[i][j];
		}
	}
}


int colorize(char **colors, char *color, int *N){
	
	int i;
	
	for(i=0;i<*N;i++){ //eger o renk daha once eklendiyse onun numarasi yazilir
		if(strcmp(colors[i],color) == 0){
			return i;
		}
	}
	(*N)++;
	strcpy(colors[(*N)-1], color);  // renk, renk dizisinde yoksa diziye eklenir
	return (*N)-1;
	
}

void rotate(int **matrix, int rotate_row, int N){ //saga kaydirma
	
	int temp = matrix[rotate_row][N-1];
	int i;
	
	for (i = N-1; i >0 ; i--) {
		matrix[rotate_row][i] = matrix[rotate_row][i-1];
	}
	
	matrix[rotate_row][0] = temp;
	
}


int backTracking(int **matrix, int i, int N, char **colors, int mode){
	int k;
	
	for(k = 0; k<N; k++){			
		if(isValid(matrix, N, i)){  // mevcut satýra kadar olan satirlar sarti sagliyorsa bir sonraki satir icin backtracking fonk. cagrilir
			if (i == N-1) {  //backTracking ile son satira kadar gidildiyse tahta duzenlendi demektir.
				return 1;
			}else {		
				if(backTracking(matrix,(i + 1),N,colors,mode)){
					return 1; //backTracking ile son satira kadar gidildiyse tahta duzenlendi demektir.
				}else{
					rotate(matrix, i, N); //mevcut satira kaar olan satirlar sarti saglamýyorsa mevcut satir rotate edilir
					if(mode == 2){     // detay modda tüm adýmlarýn tek tek yazdýrýlmasý mý isteniyor yoksa yalnýzca þartý saðlayan durumlar mý adým adým steniyor çözemedim
					printMatrix(matrix,colors,N);
					}
				}	
			}
		}else{
			rotate(matrix, i, N); //mevcut satira kaar olan satirlar sarti saglamýyorsa mevcut satir rotate edilir		
			if(mode == 2){     // detay modda tüm adýmlarýn tek tek yazdýrýlmasý mý isteniyor yoksa yalnýzca þartý saðlayan durumlar mý adým adým steniyor çözemedim
				printMatrix(matrix,colors,N);
			}	
		}	
	}
	return 0;

}

int isValid(int **matrix, int N, int row) {
		
	int i,j;

	for (i=0; i < row; i++) {
	    for(j=0 ; j < N; j++){
	    	if(matrix[row][j] == matrix[i][j]){ 
	    		return 0;
			}	
		}
	}

  	return 1;
}


void printMatrix(int **matrix, char **colors, int N){
	int i,j;
	printf("\n\n");
	for(i=0; i<N; i++){
		printf("	");
		for(j=0; j<N; j++){
			printf("	");
			printf("%s",colors[matrix[i][j]]);
		}
		printf("\n");
	}
}







  
