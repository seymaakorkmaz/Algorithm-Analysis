#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int no;
  	char name[100];
  	char surname[100];
  	int inDegree;
  	struct Follow *followed;  // dügümün takip ettikleri, adjacency list (linkli liste halind tutulur)
  	int eliminate;  // in-degree degeri M sayisindan kücük oldugu icin elendi mi
  	int influencer; // influencer mý
  	int connection; // doðrudan ve dolaylý olarak toplam baglanti sayisi
}typedef NODE;

struct Follow{
	int no;  // takip edilen dügümün numarasi
	struct Follow *next;
}typedef FOLLOW;

void read_file(NODE **node, int *numNodes);
int calculate_inDegree(NODE **nodes, int i, int numNodes);
void eliminate_nodes(NODE **nodes, int M, int i);
void find_connections(NODE *node,int i, int *dizi);
void find_influencers(NODE * node, int numNodes,int X, int Y);

int main(){
	
	int modeSelection=0;  // normal mode, detailed mode secimi
	int M,X,Y;
	int numNodes,i,j;
	
	NODE *node = (NODE*)malloc(sizeof(NODE));


	
	do{
		printf("\n");
		printf("\n		- SEYMANUR KORKMAZ 20011055-\n");
		printf("\n		1.NORMAL MODE\n");
		printf("\n		2.DETAILED MODE\n");
		printf("\n		3.EXIT\n");
		printf("\n		->SELECT MODE : ");
		scanf("%d",&modeSelection);
		
		switch(modeSelection){
			case 1:
				
				printf("\n		Enter the value of M : ");
				scanf("%d",&M);
				printf("\n		Enter the value of X : ");
				scanf("%d",&X);
				printf("\n		Enter the value of Y : ");
				scanf("%d",&Y);
				
				read_file(&node,&numNodes); //dosyadan veri okunur
				
				for (i = 0; i < numNodes; i++) {
      				node[i].inDegree = calculate_inDegree(&node, i, numNodes); // tüm node'lar icin in-degree degeri hesaplanýr
  				}
  				
  				for(i=0;i<numNodes;i++){
					eliminate_nodes(&node,M,i);  //in-degree degeri, verilen M degerinden kücük olan node'lar elenir
				}
				
				int *visited = (int*)malloc(numNodes*sizeof(int));
				for(i=0;i<numNodes;i++){
					if(node[i].eliminate == 0){
						for(j=0; j<numNodes;j++){
    						visited[j] = 0;
						}
						find_connections(node,i,visited);  // tüm node'lar icin toplam dogrudan ve dolayli baglanti sayisi bulunur.
					}
				}
				
				find_influencers(node,numNodes, X, Y);  // M,X ve Y degerlerine gore influencer olan kulanicilar bulunur
				printf("\n\n			INFLUENCERS\n");
				for(i=0;i<numNodes;i++){
					if(node[i].influencer == 1){
						printf("\n		%d - %s %s\n",node[i].no,node[i].name,node[i].surname);
					//	printf("	in-degree value : %d\n",node[i].inDegree);
						
					}
				}
				
				printf("\n		Press any key to continue...");
				getch();
				break;
			
			case 2:
				
				printf("\n		- SEYMANUR KORKMAZ 20011055-\n");
				printf("\n		Enter the value of M : ");
				scanf("%d",&M);
				printf("\n		Enter the value of X : ");
				scanf("%d",&X);
				printf("\n		Enter the value of Y : ");
				scanf("%d",&Y);
				
			//	read_file(&node,&numNodes); //dosyadan veri okunur
				for(i=0;i<numNodes;i++){ // bulunan degerler yeniden hesaplanacagi icin ifirlaniyor.
					node[i].eliminate = 0;
					node[i].connection = 0;
					node[i].influencer = 0;
					node[i].inDegree = 0;
				}
			
					
				for (i = 0; i < numNodes; i++) {
      				node[i].inDegree = calculate_inDegree(&node, i, numNodes); // tüm node'lar için in-degree degeri hesaplanýr
  				}
  				
  				printf("\n			IN-DEGREE VALUES OF ALL NODES\n");
  				for(i=0;i<numNodes;i++){
  					printf("\n		%d - %s %s",node[i].no,node[i].name,node[i].surname);
  					printf("	in-degree value : %d\n",node[i].inDegree);
				}
				
				for(i=0;i<numNodes;i++){
					eliminate_nodes(&node,M,i);  
				}
				
				printf("\n			NODES THAT ARE NOT ELIMINATED FOR THE GIVEN M VALUE\n");
				for(i=0;i<numNodes;i++){
					if(node[i].eliminate == 0){
						printf("\n		%d - %s %s",node[i].no,node[i].name,node[i].surname);
  						printf("	in-degree value : %d\n",node[i].inDegree);
					}
				}
				
								
				visited = (int*)malloc(numNodes*sizeof(int));
				for(i=0;i<numNodes;i++){
    				if(node[i].eliminate == 0){
						for(j=0; j<numNodes;j++){
    						visited[j] = 0;
						}
						find_connections(node,i,visited);  
					} 
				}
				
				find_influencers(node,numNodes, X, Y);  
				printf("\n\n			INFLUENCERS\n");
				for(i=0;i<numNodes;i++){
					if(node[i].influencer == 1){
						printf("\n		%d - %s %s",node[i].no,node[i].name,node[i].surname);
						printf("	in-degree value : %d total number of direct and indirect connections : %d\n",node[i].inDegree,node[i].connection);
					}
				}
				
				printf("\n		Press any key to continue...\n");
				getch();
			break;
		}
		
		
	}while(modeSelection != 3);


	return 0;
	
}


void read_file(NODE **node, int *numNodes){ //dosyadan okuma islemi
	
	FILE *file = fopen ("socialNET.txt","r");
	int i=0,k;
	char takip[100];
	char kisi[100];

	while(!feof(file)){
		fscanf(file,"%d,%[^,],%s\n",&((*node)[i].no),(*node)[i].name,(*node)[i].surname); 
		
	//	printf("%d,%s,%s \n",((*node)[i].no),(*node)[i].name,(*node)[i].surname);
		fgets(takip,sizeof(takip),file);
		char *token = strtok(takip,",");
		FOLLOW *f = (FOLLOW*)malloc(sizeof(FOLLOW));
		(*node)[i].followed = NULL; 
		while(token != NULL ){  // takip edilen node'larýn numaralarý linkli liste seklinde tutulur.
		if(atoi(token) != 0){
			if((*node)[i].followed == NULL){  // ilk node NULL ise malloc islemi yapilir. 
				(*node)[i].followed = f;
			}else{
				f->next=(FOLLOW*)malloc(sizeof(FOLLOW));    // ilk node NULL degilse next'ine yeni node eklenir. 
				f = f->next;
			}
			f->no =  atoi(token);
			f->next = NULL;
			
			}
			token = strtok(NULL, ","); 
		}
		(*node)[i].eliminate = 0;
		(*node)[i].connection = 0;
		i++;
    	(*node) = (NODE*)realloc((*node),sizeof(NODE)*(i+1)); // her adýmda tum node'larýn tutulduðu node dizisi realloc edilir.
	
	}
	(*numNodes) = i; //toplam node sayisi
	fclose(file);
	
}

int calculate_inDegree(NODE **nodes, int i, int numNodes) { //node'larin in-degree degerleri hesaplanýr
	
  	(*nodes)[i].inDegree = 0;
  	int k;
	
  	for (k = 0; k < numNodes; k++){  // tum node'lar gezilir
  		FOLLOW * f = (*nodes)[k].followed; 
  		while(f != NULL){
  			if ((*nodes)[i].no ==  f->no) {  // eger bir node'un takip edilen listesinde aranan node'un numarasi bulunuyorsa node'un in-degree degeri 1 artirilir.
	      		(*nodes)[i].inDegree++;
	    	}
	  		f= f->next;
		}
  	}
	return (*nodes)[i].inDegree; 
}

void eliminate_nodes(NODE **nodes, int M, int i) {  

			
	if((*nodes)[i].eliminate == 1)  //node zaten elenmisse islem yapilmadan return edilir.
			return;
	else{
		FOLLOW *f = (*nodes)[i].followed;
		if ((*nodes)[i].inDegree < M) {  //o anki node'un in-degree degeri M'in altindaysa
			(*nodes)[i].eliminate = 1;   // eliminate flagi 1 yapýlýr.
			
			while(f != NULL){
				(*nodes)[f->no-1].inDegree--;   // elenen node'un takip ettiði node'larýn in-degree degerleri 1 azaltilir.
				eliminate_nodes(nodes, M, (f->no-1));   // azaltma sonucunda takip edilen node'un in-degree degeri M altýna düstü mü diye kontrol edilir.
				f = f->next;
			}
		}
	}	
	
}

void find_connections(NODE *node,int i, int *visited){ //DFS yaklasimi kullanilarak yazilmistir.
	int j;
	FOLLOW *f = node[i].followed; //bulundugumuz node'un takip edilenler listesini bir degiskene kopyala.
	visited[i]=1;  // geldigimiz node'u ziyaret edildi olarak isaretle.
	
    while (f != NULL ){
 		if(visited[f->no-1] == 0 ){  // eger node ziyaret edilmemisse uzerinde islem yap.
 			node[f->no-1].connection++;  // node'un takip ettigi node'larýn cconnection sayisini 1 artir.
    		visited[f->no-1] = 1; // connection degeri artirilan node'u visited olarak isaretle.
    		find_connections(node,(f->no-1),visited); // takip edilen node'un takip ettiklerini de hesaba katabilmek icin o node icin de fonksiyon 
															//cagrilarak en sona kadar gidilir.
		}
        f = f->next;
    }
}


void find_influencers(NODE * node, int numNodes,int X, int Y){  
	int i;
	for(i=0;i<numNodes;i++){
		if(node[i].inDegree >= X && node[i].connection >= Y && node[i].eliminate == 0) // // M, X ve Y degerlerine gore influencer olan dugumler bulunur.
			node[i].influencer = 1;  // influencer flagi 1 yapilir.
		else
			node[i].influencer = 0;
	}
	
}










