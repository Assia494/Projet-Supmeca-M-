#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_string_settings_SIZE 3000

////////////-------------------------------------------------------------------------------

typedef struct{//pour les données dans chaque case
	int value;
	int visible;
}_tile;

typedef struct{
	int size_x ;
	int size_y ;
	//value et visibility doit être de la même longueur
	char value_tab[max_string_settings_SIZE]	 ;	
	//char visbility_tab[max_string_settings_SIZE] ;
}_grid_settings;


/////////////////////////pour la couleur des texts du terminal
void color(unsigned char r, unsigned char g, unsigned char b){
	printf("\x1B[38;2;%d;%d;%dm", r, g, b);
}
////////////-------------------------------------------------------------------------------
void reset_color(){
	printf("\x1B[0m");
}
////////////-------------------------------------------------------------------------------
int rand_int(int a ,int b){
	int NB;
	NB = rand()%(b+1 -a) +a;
	return NB;
}
////////////-------------------------------------------------------------------------------
_tile cree_tile(){
	_tile tile;
	//mettre les données qui sont par default
	tile.value 	 = 0;
	tile.visible = 1;
	
	return tile;
}
////////////-------------------------------------------------------------------------------

_tile** creer_grid(int size_x ,int size_y){
	//creation d'un tableau 2D
	_tile** grid = NULL;  
	grid = malloc(size_y * sizeof(_tile*));
	if(grid == NULL){//verifie si l'allocation est réussi
		exit(0);
	}
	for(int dy=0;dy<size_y;dy++){
		grid[dy] = malloc(size_x * sizeof(_tile*));
		if(grid == NULL){//verifie si l'allocation est réussi
			exit(1);
		}
		
		//crée les case et le met dans la grille
		for(int dx=0;dx<size_x;dx++){
			grid[dy][dx] = cree_tile();
		}
	} 
	return grid;
}

////////////-------------------------------------------------------------------------------

_tile** get_grid_settings(int* size_x ,int* size_y){

	_grid_settings settings;
	_tile** grid;
	FILE* file = NULL;
	
	//grille A
	if(1){
		settings.size_x = 10;
		settings.size_y = 10;
		file = fopen("mapdata.txt","r+");
	}
	//crée la grid
	grid = creer_grid(settings.size_x ,settings.size_y);

	int ind_string_set =0;
	char caractere ;
	
	*size_x = settings.size_x = 10;
	*size_y = settings.size_y = 10;
	//mettre les informations appropié
	
	if(file == NULL){
		exit(1);
	}
	for(int dy = 0 ;dy<settings.size_y ;dy++){
		for(int dx = 0 ;dx<settings.size_x ;dx++){
			caractere = getc(file);
			if(caractere == '\n'){
				printf("-\n");
				getc(file); //ind_string_set++;
				//aller à la prochaine ligne
				dx = 0;
				dy++;
			}
			
			//mettre les valueurs
			if(ind_string_set <= settings.size_y*(settings.size_x +1)){
				printf(".%c ",caractere);
				grid[dy][dx].value   = caractere;
			}
			
			ind_string_set++;
			
		}
	}
	return grid;
}
////////////-------------------------------------------------------------------------------

void element_print(char value){//affich un element selon une valeur
	if(1){
		printf("%d",value);
	}
	else{
		switch(value){
			case 0:
				printf("-");
				break;
			case 1:
				printf("\xE2\x97\xBC");
				break;
			default:
				printf("_");
				break;

		
		//\xF0\x9F\x9A\xAA : porte
		//\xE2\x97\xBC: bloc noir
			
			
			
			
			
		}
	}
}

////////////-------------------------------------------------------------------------------


void affiche_grid(_tile** grid ,int grid_size_x ,int grid_size_y){//affiche la grille
	printf("\n\n");
	for(int dy=0;dy<grid_size_y;dy++){
		printf("		");
		for(int dx=0;dx<grid_size_x;dx++){
			element_print(grid[dy][dx].value);
			printf(" ");
		}
		printf("\n");
	} 
	printf("\n\n");
}

////////////-------------------------------------------------------------------------------

void main(){
	_tile** grid=NULL;
	int size_x = 10;
	int size_y = 10;
	//grid = creer_grid(size_x, size_y);
	grid = get_grid_settings(&size_x ,&size_x);
	affiche_grid(grid ,size_x, size_y);




























}


































































