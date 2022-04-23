#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void acik_cizdir(int board[8][8],int n); //uretilen board sayilari kontrol etmek icin bir fonkisyon 
void cizdir(int board[8][8], char board_c[8][8],int n, int s1, int s2, int x1, int y1, int x2, int y2);
int control(char board[8][8], int n, int s1, int s2);
//int* player_turn(int cards[8][8], char board[8][8], int score[2], int n);
//int* com_turn(int cards[8][8], char board[8][8], int memory[16][3], int n, int count);
void player_turn(int cards[8][8], char board[8][8], int score[2], int n, int *i1, int *j1, int *i2, int *j2);
void com_turn(int cards[8][8], char board[8][8], int memory[16][3], int n, int count, int *i1, int *j1, int *i2, int *j2);
void kaydet(int memory[16][3], int card, int ik, int jk, int count);
void sil(int memory[16][3], int card, int ik, int jk, int n);
void sifirla(int arr[4]);


int main(){
	int cards[8][8];
	char board_p[8][8];
	int hash[32] = {0}, tmp;
	int i, j, n, secim;
	int score[2]={0,0};
	int turn = 0, devam = 1, stop = 0;
	
	int *choosen_card;
	int memory_arr[16][3] = {-1};
	int mem_count, com_counter = 0, player_counter = 0;
	
	choosen_card = (int*) calloc(4,sizeof(int));
	
	srand(time(NULL));
	
	printf("<============Es kart bulma oyunu==========>\n");
	
	printf("1- kolay\n");
	printf("2- orta\n");
	printf("3- zor\n");
	printf("seviye seciniz: ");
	scanf("%d", &secim);
	if(secim>3 || secim<1){
		printf("hatali secim\n");
		return 0;
	}
	n = (secim+1) * 2;
	
//	cards = (int**) calloc(n,sizeof(int*));
//	for(i=0;i<n;++i){
//		cards[i] = (int*) calloc(n,sizeof(int));
//	}
//	board_p = (char**) calloc(n,sizeof(char*));
//	for(i=0;i<n;++i){
//		board_p[i] = (char*) calloc(n,sizeof(char));
//	}
	

	for(i=0;i<n;++i){
		for(j=0;j<n;++j){
			do{
				tmp = rand()%(n*n/2);
			}while(hash[tmp] == 2);
	
			cards[i][j] = tmp;
			hash[tmp]++;
			
			board_p[i][j] = '*';
		}
	}	
	
	if(n == 4){mem_count = 2;}
	else if(n == 6){mem_count = 6;}
	else{mem_count = 16;}
	
	for(i=0;i<mem_count;++i){
		memory_arr[i][0] = -1;
		memory_arr[i][1] = -1;
		memory_arr[i][2] = -1;
	}
	
	printf("\nasagidaki kisim sadece gosterme amacli normal oyunda gozukmeyecek!!!\n");
	printf("oyun tahtasi\n");
	acik_cizdir(cards,n);
	printf("\ndevam etmek icin herhangi bir tusa basiniz...\n");
	getch();
    
    while(devam){
    	system("cls");
    	sifirla(choosen_card);
    	
    	printf("<");
    	for(i=0;i<n;++i){
    		printf("===");
		}
		printf("Es kart bulma oyunu");
		for(i=0;i<n;++i){
    		printf("===");
		}
		printf(">\n\n");
    	cizdir(cards,board_p,n,score[0],score[1],choosen_card[0],choosen_card[1],choosen_card[2],choosen_card[3]);

    	if(turn == 0){
    		printf("oyun sirasi: Oyuncu\n");
    		/*choosen_card = */player_turn(cards,board_p,score,n,&choosen_card[0],&choosen_card[1],&choosen_card[2],&choosen_card[3]);
			++player_counter;  	
		}else{
			printf("oyun sirasi: Bilgisayar\n");
			/*choosen_card = */com_turn(cards,board_p,memory_arr,n,mem_count,&choosen_card[0],&choosen_card[1],&choosen_card[2],&choosen_card[3]);
			++com_counter;
			cizdir(cards,board_p,n,score[0],score[1],choosen_card[0],choosen_card[1],-1,-1);
			printf("secilen kart: %d  kordinatlari: %d, %d\n", cards[choosen_card[0]][choosen_card[1]], choosen_card[0]+1, choosen_card[1]+1);
		}
		
		if(cards[choosen_card[0]][choosen_card[1]] == cards[choosen_card[2]][choosen_card[3]]){
			score[turn]++; 
			cizdir(cards,board_p,n,score[0],score[1],choosen_card[0],choosen_card[1],choosen_card[2],choosen_card[3]);
		    printf("secilen kart: %d  kordinatlari: %d, %d\n", cards[choosen_card[2]][choosen_card[3]], choosen_card[2]+1, choosen_card[3]+1);
			printf("benzer kart buldunuz bravo! sira bir daha sizde\n");
			board_p[choosen_card[0]][choosen_card[1]] = '-';
			board_p[choosen_card[2]][choosen_card[3]] = '-';
			sil(memory_arr,cards[choosen_card[0]][choosen_card[1]],choosen_card[0],choosen_card[1],mem_count);			
			sil(memory_arr,cards[choosen_card[2]][choosen_card[3]],choosen_card[2],choosen_card[3],mem_count);			

			turn++;			
		}else{
			kaydet(memory_arr,cards[choosen_card[0]][choosen_card[1]],choosen_card[0], choosen_card[1],mem_count);
			kaydet(memory_arr,cards[choosen_card[2]][choosen_card[3]],choosen_card[2], choosen_card[3],mem_count);
		
			cizdir(cards,board_p,n,score[0],score[1],choosen_card[0],choosen_card[1],choosen_card[2],choosen_card[3]);
		    printf("secilen kart: %d  kordinatlari: %d, %d\n", cards[choosen_card[2]][choosen_card[3]], choosen_card[2]+1, choosen_card[3]+1);
			printf("benzer kart bulamadiniz sira rakiba gecti\n");
		}		
		
		printf("\nasagidaki kisim sadece gosterme amacli normal oyunda gozukmeyecek!!!\n");
		printf("computer memory\n");
		for(i=0;i<mem_count;++i){
			printf("i=%d\tj=%d\tcard=%d\n",memory_arr[i][1],memory_arr[i][2],memory_arr[i][0]);
		}
		
		turn = (turn+1)%2;
		sifirla(choosen_card);
		devam = control(board_p,n,score[0], score[1]);
		printf("\ndevam etmek icin herhangi bir tusa basiniz...\n");
		getch();
	}

    	

	if(score[0]>score[1]){
  		printf("tebrikler oyun bitti ve siz kazandiniz\t tahmin sayisi:%d\n", player_counter);	
	}else if(score[0]<score[1]){
		printf("bilgisayar kazandi tekrar deneyabilisiniz\t tahmin sayisi:%d\n", com_counter);
	}else{
		printf("oyun birabere bitti\n");
	}
	printf("player score: %d \t computer score %d", score[0], score[1]);
  	
    

    return 0;
}

void player_turn(int cards[8][8], char board[8][8], int score[2], int n, int *i1, int *j1, int *i2, int *j2){
	int index[4];
	int stop = 0;
	
//	index = (int*) calloc(4,sizeof(int));
	
    while(stop==0){
		stop = 1;
		sifirla(index);
		printf("birinci kart seciniz\n");
		printf("satir:");
		scanf("%d", &index[0]);
		--index[0];
		printf("sutun:");
		scanf("%d", &index[1]);
		--index[1];
		if(index[0]>=n || index[0]<0 || index[1]>=n || index[1]<0 ){
			printf("gerdigniz sayi ya kordinat disinda!!!\n");
			printf("bir daha secim yapiniz\n");
			stop = 0;
		}
		else if(board[index[0]][index[1]] == '-'){
			printf("girdigniz kart daha once acilmis!!!\n");
			printf("bir daha secim yapiniz\n");
			stop = 0;
		}
	}

	cizdir(cards,board,n,score[0],score[1],index[0],index[1],index[2],index[3]);
	printf("secilen kart: %d  kordinatlari: %d, %d\n", cards[index[0]][index[1]], index[0]+1, index[1]+1);
	stop = 0;
	while(stop==0){
		stop = 1;
		printf("ikinci kart seciniz\n");
		printf("satir:");
		scanf("%d", &index[2]);
		--index[2];
		printf("sutun:");
		scanf("%d", &index[3]);
		--index[3];
	
		if(index[2]>=n || index[2]<0 || index[3]>=n || index[3]<0 ){
			printf("gerdigniz sayi ya kordinat disinda!!!\n");
			printf("bir daha secim yapiniz\n");
			stop = 0;
		}else if(board[index[2]][index[3]] == '-' || (index[0] == index[2] && index[1]==index[3])){
			printf("gerdigniz kart daha once acilmis!!!\n");
			printf("bir daha secim yapiniz\n");
			stop = 0;
		}
	}
	*i1 = index[0];
	*j1 = index[1];
	*i2 = index[2];
	*j2 = index[3];
	
//	return index;
	
}

void sifirla(int arr[4]){
	int i;
	for(i=0;i<4;++i){
		arr[i] = -1;
	}
}

void com_turn(int cards[8][8], char board[8][8], int memory[16][3], int n, int count, int *i1, int *j1, int *i2, int *j2){
	int i , j, k;
	int mod;
//	int i1, j1, i2, j2;
//	int *tmp;
	int stop = 0;
	
//	tmp = (int*) calloc(4,sizeof(int));
	
	for(i=0;i<count-1;++i){
		for(j=i+1;j<count;++j){
			if(memory[i][0] == memory[j][0] && (memory[i][1] != memory[j][1] || memory[i][2] != memory[j][2])){
//				tmp[0] = memory[i][1];
//				tmp[1] = memory[i][2];
//				tmp[2] = memory[j][1];
//				tmp[3] = memory[j][2];
				*i1 = memory[i][1];
				*j1 = memory[i][2];
				*i2 = memory[j][1];
				*j2 = memory[j][2];
				
				return ;
			}
		}
	}
	
	do{
		stop=0;
		*i1 = rand() % n;
		*j1 = rand() % n;
 		
 	// bu kisim bilgisayar hamlesi yaparken kendi hafizasindan kart almasin diye 
 		i=0;
		while(i<count && (*i1 != memory[i][1] || *j1 != memory[i][2])){
			++i;
		}
		if(i==count){
			stop = 1;
		}
		
	}while(board[*i1][*j1] == '-' || stop==0);
	
	i=0;	
	while(i<count && cards[*i1][*j1] != memory[i][0]){
		i++;
	}
		
	if(i==count){
		do{
			stop = 0;
			*i2 = rand() % n;
			*j2 = rand() % n;
			
 		// bu kisim bilgisayar hamlesi yaparken kendi hafizasindan kart almasin diye 
			i=0;
			while(i<count && (*i2 != memory[i][1] || *j2 != memory[i][2])){
				++i;
			}
			if(i==count){
				stop = 1;
			}
		}while(board[*i2][*j2] == '-' || stop == 0 || ( *i2 == *i1 || *j2 == *j1));

	}else{
		*i2 = memory[i][1];
		*j2 = memory[i][2];
	}

//	tmp[0] = i1;
//	tmp[1] = j1;
//	tmp[2] = i2;
//	tmp[3] = j2;
//	return tmp;
			
}

void kaydet(int memory[16][3], int card, int ik, int jk, int n){
	int i;
	for(i=n-2;i>=0;--i){
		memory[i+1][0] = memory[i][0]; 
		memory[i+1][1] = memory[i][1]; 
		memory[i+1][2] = memory[i][2]; 
	}
	memory[0][0] = card;
	memory[0][1] = ik;
	memory[0][2] = jk;
}

void sil(int memory[16][3], int card, int ik, int jk, int n){
	int k, j = 0;
	
	for(j=0;j<n;++j){
		if(memory[j][0] == card && memory[j][1] == ik && memory[j][2] == jk){
			for(k=j;k<n-1;++k){
				memory[k][0] = memory[k+1][0];
				memory[k][1] = memory[k+1][1];
				memory[k][2] = memory[k+1][2];
			}
			memory[k][0] = -1;
			memory[k][1] = -1;
			memory[k][2] = -1;
		}
	}
	
	return;
	
}

int control(char board[8][8], int n, int s1, int s2){
	int i=0, j=0;
	if(s1>(n*n/4) || s2>(n*n)/4){
		return 0;
	}
	while(i<n && board[i][j] == '-'){
		j++;
		if(j==n){
			j=0;
			i++;
		}
	}
	if(i==n){
		return 0;
	}
	return 1;
}

void cizdir(int board[8][8], char board_c[8][8],int n, int s1, int s2, int x1, int y1, int x2, int y2){
    int i, j;
	
	printf("    ");
	for(j=0;j<n;++j){
        printf(" ___%d__ ", j+1);
    }
    printf("\n");
    for(i=0;i<n;++i){
    	printf(" %d  ", i+1);
        for(j=0;j<n;++j){
        	if( (i==x1 && j==y1) || (i==x2 && j==y2) ){
            	printf("|%4d  |", board[i][j]);        		
			}else{
            	printf("|%4c  |", board_c[i][j]);     		
			}
        }
        printf("\n    ");
        for(j=0;j<n;++j){
            printf("--------");
        }
        printf("\n");
    }
    printf("player score: %d \t computer score: %d\n", s1,s2);
}

void acik_cizdir(int board[8][8],int n){
    int i, j;
	
	printf("    ");
	for(j=0;j<n;++j){
        printf(" ___%d__ ", j+1);
    }
    printf("\n");
    for(i=0;i<n;++i){
    	printf(" %d  ", i+1);
        for(j=0;j<n;++j){
            printf("|%4d  |", board[i][j]);        		
        }
        printf("\n    ");
        for(j=0;j<n;++j){
            printf("--------");
        }
        printf("\n");
    }
}
