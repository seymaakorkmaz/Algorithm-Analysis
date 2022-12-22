#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct data{
	char word[100];
	char link[100];
}DATA;

typedef struct hashTable{
	char word[100];
	char links[50][100];
	int linkNum;
	int stepNum;
	int flag;  //0:bos 1:dolu
}HashTable;

void ReadFromFile(DATA **data, int *uniqueWordNumber, int *wordNumber);
int FindHashSize(int uniqueWordNumber, float loadFactor);
void createTable(DATA *data, HashTable **Hash, int hashSize, int wordNumber);
void initialization(HashTable **Hash,int hashSize);
void SearchEngine(HashTable *Hash, int hashSize, char words[]);
int SearchinHash(HashTable *Hash, int hashSize, char word[]);
void Union(HashTable *Hash, int hashKey1, int hashKey2);
void Intersection(HashTable *Hash, int hashKey1, int hashKey2);
unsigned long hornerMethod(char word[]);
int CalculateHash(unsigned long int key,int tableSize);


int main(){
	int i,j;
	int wordNumber, uniqueWordNumber=0;
	float loadFactor;
	int hashSize;
	int modeSelection=0;
	char sentence[100];
	
	DATA *data = (DATA*)malloc(sizeof(DATA));
	
	ReadFromFile(&data,&uniqueWordNumber,&wordNumber); //dosyadan link ve kelimeler okunur
	
	printf("\n		Enter the load factor : ");
	scanf("%f",&loadFactor);
	
	hashSize = FindHashSize(uniqueWordNumber,loadFactor);  // hash table boyutu bulunur
	HashTable *Hash = (HashTable*)malloc(hashSize*sizeof(HashTable)); 
	initialization(&Hash, hashSize); //hashin baþlangýç deðerleri ayarlanýr
	createTable(data,&Hash,hashSize,wordNumber);
	
	
	do{
		printf("\n		1.NORMAL MODE");
		printf("\n		2.DETAILED MODE");
		printf("\n		3.EXIT");
		printf("\n		->SELECT MODE : ");
		scanf("%d",&modeSelection);
		
		switch(modeSelection){
			case 1:
				printf("\n		Enter the word/words you want to search : ");
				scanf(" %[^\n]",&sentence);
				SearchEngine(Hash,hashSize,sentence); //kullanýcýdan girilen arama cümlemisi için arama yapýlýr
				printf("\n		Press any key to continue...");
				getch();
				break;
			
			case 2:
				printf("\n		LENGTH OF HASHE TABLE => %d",hashSize);
				
				for(i=0;i<hashSize;i++){
					if(Hash[i].flag == 0)
						printf("\n		%d -    ",i);
					else{
						printf("\n		%d - %s ------ settled in the table at the  %dth  attempt ",i,Hash[i].word,Hash[i].stepNum);
						for(j=0;j<Hash[i].linkNum;j++){
							printf("\n		 	-> %s",Hash[i].links[j]);
						}
					}
						
				}
				
				printf("\n		Enter the word/words you want to search : ");
				scanf(" %[^\n]",&sentence);
				SearchEngine(Hash,hashSize,sentence);
				printf("\n		Press any key to continue...\n");
				getch();
			break;
		}
		
		
	}while(modeSelection != 3);



	
	return 0;

}

void ReadFromFile(DATA **data, int *uniqueWordNumber, int *wordNumber){
	FILE *file = fopen ("Sample.txt","r");
	int i=0,j;
	char link[100];
	char words[1000];
	char empty[100];
	
	
	while(!feof(file)){
		fscanf(file,"%s\n",&link);  
	//	printf("link: %s\n",link);
		fgets(words,sizeof(words),file);
	//	printf("words: %s\n",words);
		char *token = strtok(words," "); //satýr þeklinde okunan kelimeler parçalanýr
		
		while(token != NULL ){ 
			if(token[strlen(token)-1] == '\n'){
				token[strlen(token)-2] = '\0';
			}
			strcpy((*data)[i].link,link);
			strcpy((*data)[i].word,token);
		//	printf("%s %s\n",link,token);
			j=0;
			
			while(j<i && (strcmp(((*data)[i].word),((*data)[j].word))) != 0)
				j++;
			
			if(j == i)
				(*uniqueWordNumber)++;  //tekil kelime adeti bulunur
			
			i++;
			(*data) = (DATA*)realloc((*data),sizeof(DATA)*(i+1));
			token = strtok(NULL, " "); 
		}
	}
	
	(*wordNumber) = i;
	fclose(file);
	
}

int FindHashSize(int uniqueWordNumber, float loadFactor){
	int hashSize = uniqueWordNumber/ loadFactor;  
	int flag=0;
	int i;
	while(flag == 0){
		hashSize++;
		if(hashSize%2 != 0 && hashSize%3 != 0){ //hashSize'dan büyük en küçük asal sayý
			for(i=5;i<sqrt(hashSize);i=i+6){
				if(hashSize%i != 0 && hashSize%(i+2) != 0)
				flag=1;
			}
		}
    }
	return hashSize;
}

void initialization(HashTable **Hash,int hashSize){
    int i;
    for (i = 0; i < hashSize; i++){
		(*Hash)[i].flag = 0;
		(*Hash)[i].linkNum = 0;
		(*Hash)[i].stepNum = -1;  ///???
    }
}

void createTable(DATA *data, HashTable **Hash, int hashSize, int wordNumber){
	
	int i,hashKey;
	int stepNum;
	int flag;
	
	
	for(i=0; i < wordNumber;i++){
		stepNum = 0;
		hashKey = CalculateHash(hornerMethod(data[i].word),hashSize);  //key bulunur
		do{
			hashKey = (hashKey+stepNum) % hashSize;
		
			stepNum++;
		
		}while((*Hash)[hashKey].flag == 1 && strcmp((*Hash)[hashKey].word,data[i].word) != 0); //key girmek istediðimizden farklý bir kelimeyle doluysa
	
		if(strcmp((*Hash)[hashKey].word,data[i].word) == 0){
				strcpy((*Hash)[hashKey].links[(*Hash)[hashKey].linkNum], data[i].link); //kelime zaten mevcutsa link eklenir
				(*Hash)[hashKey].linkNum++;
		}else if((*Hash)[hashKey].flag == 0){
			strcpy((*Hash)[hashKey].word,data[i].word);
			strcpy((*Hash)[hashKey].links[(*Hash)[hashKey].linkNum],data[i].link);
			(*Hash)[hashKey].linkNum++;
			(*Hash)[hashKey].stepNum = stepNum;
			(*Hash)[hashKey].flag = 1;
		}
	}
}

void SearchEngine(HashTable *Hash, int hashSize, char words[]){
	char *token[3]; //ALÝ VE VELÝ
	char *w = strtok(words," ");
	int i=0;
	int hashKey_word1,hashKey_word2;
	while(w != NULL){
		token[i] = w;
		w = strtok(NULL, " "); 
		i++;
	}
	if(strcmp(token[1],"or") != 0 && strcmp(token[1],"and") != 0){  //tek kelime girildiyse
		hashKey_word1 = SearchinHash(Hash,hashSize,token[0]);
		if(hashKey_word1 != -1){
			for(i=0;i<Hash[hashKey_word1].linkNum;i++)
				printf("		- %s\n",Hash[hashKey_word1].links[i]);
		}else{
			printf("\n		Word not found!!");
		}
		
			
	}else if(strcmp(token[1],"or") == 0 || strcmp(token[1],"Or") == 0){
		hashKey_word1 = SearchinHash(Hash,hashSize,token[0]);
		hashKey_word2 = SearchinHash(Hash,hashSize,token[2]);
		Union(Hash,hashKey_word1,hashKey_word2); //birleþim fonksiyonu
	}else if(strcmp(token[1],"and") == 0 || strcmp(token[1],"And") == 0){
		hashKey_word1 = SearchinHash(Hash,hashSize,token[0]);
		hashKey_word2 = SearchinHash(Hash,hashSize,token[2]);
		Intersection(Hash,hashKey_word1,hashKey_word2);  //kesiþim fonksiyonu
	}
	
}

void Union(HashTable *Hash, int hashKey1, int hashKey2){
	char link[50][100];
	int linkNum1 = Hash[hashKey1].linkNum;
	int linkNum2 = Hash[hashKey2].linkNum;
	int i,j;
	int flag;
	
	for(i=0;i<linkNum1;i++){
		printf("		- %s\n",Hash[hashKey1].links[i]);
	}
	
	for(i=0;i<linkNum2;i++){
		flag = 1;
		for(j=0;j<linkNum1;j++){
			if(strcmp(Hash[hashKey2].links[i],Hash[hashKey1].links[j]) == 0)
				flag=0;
		}
		if(flag)
			printf("		- %s\n",Hash[hashKey2].links[i]);
	}
	
}

void Intersection(HashTable *Hash, int hashKey1, int hashKey2){
	int linkNum1 = Hash[hashKey1].linkNum;
	int linkNum2 = Hash[hashKey2].linkNum;
	int i,j;
	int count=0;
	
	for(i=0;i<linkNum1;i++){
		for(j=0;j<linkNum2;j++){
			if(strcmp(Hash[hashKey1].links[i],Hash[hashKey2].links[j]) == 0){
				printf("		- %s\n",Hash[hashKey1].links[i]);
				count++;
			}
		}
	}
	
	if(count == 0)
		printf("\n			There is no link where %s and %s are together",Hash[hashKey1].word,Hash[hashKey2].word);
		
	
}
int SearchinHash(HashTable *Hash, int hashSize, char word[]){
	int i,hashKey;
	int stepNum = 0;
	hashKey = CalculateHash(hornerMethod(word),hashSize); //kelimenin keyi bulunarak hashte arama yapýlýr
	 
	do{
		hashKey = (hashKey+stepNum) % hashSize;
		stepNum++;
		
	}while(Hash[hashKey].flag == 1 && strcmp(Hash[hashKey].word,word) != 0);
	
	if(strcmp(Hash[hashKey].word,word) == 0) 
		return hashKey;
	else
		return -1;
}

unsigned long hornerMethod(char word[]){
	int i,tmp;
	unsigned long hashKey=0;
	int R = 31;
	int L = strlen(word);
	for(i=0;i<strlen(word);i++){
		word[i] = tolower(word[i]);
	}
	for(i=0;i<L;i++){
		hashKey += pow(R,(L-i-1))*(word[i]-'A'+1);
	}
	
	return hashKey;
}

int CalculateHash(unsigned long int key,int tableSize){
    return key % tableSize;
}


