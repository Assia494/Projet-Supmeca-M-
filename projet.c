#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE_X 20
#define GRID_SIZE_Y 10

#define NB_TOOLS 7
//-----------------------------------------------------------
typedef enum {UP=0,RIGHT=1,DOWN=2,LEFT=3} _movement;
//-----------------
typedef enum {TEST_DESEASE=0} _maladie;
//-----------------
typedef struct {
	int value;  //type de case
	int player; //presence de joueur
} _tile;
//-----------------
typedef struct {
	int x;
	int y;
} _coord;
//-----------------
typedef struct {
    int clean;
    int used;
    int type;
} _tool;
//-----------------
typedef struct {
	_coord pos;
	_tool tool;   //si outil alors player.glove.type = (int)    sinon player.tool.type = 0
	_tool glove;  //si gant alors player.glove.type = 'h'       sinon player.glove.type = 0
} _player;
//-----------------
typedef struct {
    int hummeur;
    _maladie maladie;
} _patient;
//-----------------
typedef struct {
    int tools[NB_TOOLS] ;     //{a,b,c,d,e,f,g}
    int used_tools[NB_TOOLS] ;
    _patient* patient;
    int id;
} _plateau;
/////////////////////////pour la couleur des texts du terminal
void color(unsigned char r, unsigned char g, unsigned char b){
	printf("\x1B[38;2;%d;%d;%dm", r, g, b);
}
////////////-------------------------------------------------------------------------------
void reset_color(){
	printf("\x1B[0m");
}
////////////-------------------------------------------------------------------------------
//-----------------------------------------------------------
int randint(int a,int b) {
	return rand()%(b-a+1) +a;
}
//-----------------------------------------------------------
int inter_check(int nb,int a,int b) {
	return (a<=nb)&&(nb<=b);
}
//-----------------------------------------------------------
void exit_if_null_pointer(void* pointer) {
	if(pointer == NULL) {
		printf(">>Got a NULL pointer\n");
		exit(1);
	}
}
//-----------------------------------------------------------
_tile cree_tile() {
	_tile new_tile;
	new_tile.value = 0;
	new_tile.player = 0;
	return new_tile;
}
//-----------------------------------------------------------
_tile** cree_grid(int size_x,int size_y) {

	_tile** new_grid = NULL;
	new_grid = malloc( size_y * sizeof(_tile*) );
	exit_if_null_pointer(new_grid);

	for(int dy=0 ; dy<size_y ; dy++) {
		new_grid[dy] = malloc( size_x * sizeof(_tile) );
		exit_if_null_pointer(new_grid[dy]);

		for(int dx=0 ; dx<size_x ; dx++) {
			new_grid[dy][dx] = cree_tile();
			new_grid[dy][dx].value = 0;
		}
	}
    /*
	for(int dy=0 ; dy<size_y ; dy++) {
		for(int dx=0 ; dx<size_x ; dx++) {
			if( (dx==0)||(dx==size_x-1)||(dy==0)||(dy==size_y-1) ) {
				new_grid[dy][dx].value = 1;
			}
			else {
				new_grid[dy][dx].value = 0;
			}
		}
	}
    */
	return new_grid;

}
//-----------------------------------------------------------
_coord get_player_pos_from_grid(_tile** grid,int size_x,int size_y) {
	_coord pos;
	pos.x = -1;
	pos.y = -1;
	exit_if_null_pointer(grid);
	for(int dy=0 ; dy<size_y ; dy++) {
		for(int dx=0 ; dx<size_x ; dx++) {
			if(grid[dy][dx].player == 1) {
				pos.x = dx;
				pos.y = dy;
				return pos;
			}
		}
	}
	return pos;
}
//-----------------------------------------------------------
_coord get_element_pos_from_grid(_tile** grid,int size_x,int size_y,int element) {
	_coord pos;
	pos.x = -1;
	pos.y = -1;
	exit_if_null_pointer(grid);
	for(int dy=0 ; dy<size_y ; dy++) {
		for(int dx=0 ; dx<size_x ; dx++) {
			if(grid[dy][dx].value == element) {
				pos.x = dx;
				pos.y = dy;
				return pos;
			}
		}
	}
	return pos;
}
//-----------------------------------------------------------
_tile get_tile_from_pos(_tile** grid,int size_x,int size_y,int x,int y) {
	exit_if_null_pointer(grid);

	if(!inter_check(x,0,size_x) + !inter_check(x,0,size_x)) {
		printf("Got incoherent value  size=(x=%d/y=%d) ,position=(x=%d/y=%d)",size_x,size_y,x,y);
		exit(1);
	}
	return grid[y][x];

}
//-----------------------------------------------------------
int can_move_at_pos(_tile** grid,int size_x,int size_y,int x,int y) {
	int tile_value = 0;
	_tile tile;

	tile = get_tile_from_pos(grid,size_x,size_y,x,y) ;
	tile_value = tile.value;
	if(inter_check(tile_value,'a','z')){
	    return 1;
	}
	switch(tile_value) {
	default:
		return 0;
	case 0:
		return 1;
	}
}
//-----------------------------------------------------------
void tile_print(_tile tile ,_plateau* plateau_tab ,int taille) {
	if(tile.player == 1) {
		printf("😷 ");
	}
	else {
	    if( inter_check(tile.value,'T','Z') ){
	        
	        char c;
	        c = tile.value -'T' +'t';
	        for(int i=0;i<taille;i++){
	            if(plateau_tab[i].id==c){
    	            if(plateau_tab[i].patient != NULL){
    	                printf("🤒 ");
    	            }
    	            else{
    	                printf("🪑 ");    
    	            }
    	            break;
	            }
	        }
	        
	    }        
	    else{
    		switch(tile.value) {
    		default:
    		    if( inter_check(tile.value,'t','z') ){
    		        printf(" %c",tile.value);
    		    }
    		    else{
    		        printf("  ");
    		    }
    			break;
    		case 0:
    			printf("  ");
    			break;
    		case 1:
    			printf("⬛ " );
    			break;
    		case 2:
    			printf("🧊 ");
    			break;
    		case 3:
    			printf("🚪️ ");
    			break;
    			
    		case 'A':
    			printf("🪛 ");
    			break;
    		case 'B':
    			printf("⚙️ ");
    			break;
    		case 'C':
    			printf("🔩 ");
    			break;
    		case 'D':
    			printf("🔬 ");
    			break;
    		case 'E':
    			printf("💉 ");
    			break;
    			
    		case 'F':
    			printf("🩹 ");
    			break;
    		case 'G':
    			printf("💭 ");
    			break;
    		case 'H':
    			printf("🧤 ");
    			break;
    			
    		case 'I':
    			printf("♻️ ");
    			break;
    		case 'J':
    			printf("☣️ ");
    			break;

    		}
	    }
    /*
    -----------
    .player = 1 :😷
    -------
    0 :
    1 :⬛
    2 :🧊️
    3 :️🚪
    -------
    A :🪛  
    B :⚙️
    C :🔩
    D :🔬
    E :💉
    
    
    F :🩹
    G :💭
    H :🧤
    ️
    I :♻️
    J :☣️
	*/
	}
}
//-----------------------------------------------------------
void print_grid(_tile** grid,int size_x,int size_y,_plateau* plateau_tab,int taille) {
	exit_if_null_pointer(grid);
	printf("\n\n");
	for(int dy=0 ; dy<size_y ; dy++) {
		printf("       ");
		for(int dx=0 ; dx<size_x ; dx++) {
			tile_print(grid[dy][dx] ,plateau_tab ,taille);
			//printf(" ");
			//printf("%d ",(grid[dy][dx]).value);
		}
		printf("\n");
	}
}
//-----------------------------------------------------------
void move_player(_tile** grid,int size_x,int size_y,_movement movement) {
	_coord initial_pos;
	_coord final_pos;

	initial_pos = get_player_pos_from_grid(grid,size_x,size_y);
	if((initial_pos.x<0)||(initial_pos.y<0)){
        printf("player can't be found\n");
        exit(2);
    }
    
	if (inter_check(initial_pos.x,0,size_x)&&inter_check(initial_pos.y,0,size_y)) {
		//printf("%d %d %d %d\n",movement==UP,movement==RIGHT,movement==DOWN,movement==LEFT);
		final_pos.x = initial_pos.x +(movement==RIGHT) -(movement==LEFT) ;
		final_pos.y = initial_pos.y -(movement==UP) +(movement==DOWN) ;
		//printf("(%d;%d) -> (%d;%d)\n",initial_pos.x,initial_pos.y,final_pos.x,final_pos.y);
		if (inter_check(final_pos.x,0,size_x)&&inter_check(final_pos.y,0,size_y)) {

			if (can_move_at_pos(grid,size_x,size_y,final_pos.x,final_pos.y)) {
				grid[initial_pos.y][initial_pos.x].player = 0;
				grid[final_pos.y][final_pos.x].player = 1;

			}
			else{
			    //printf("Couldn't move\n");
			}


		}
	}

}
//-----------------------------------------------------------
void cure_if_got_tools(_plateau* plateau ,int a, int b, int c, int d, int e, int f ,int g){
    _plateau plate;
    plate = *plateau;
    if( (plate.tools[0]>=a)&&(plate.tools[1]>=b)&&(plate.tools[2]>=c)&&(plate.tools[3]>=d)&&(plate.tools[4]>=e)&&(plate.tools[5]>=f)&&(plate.tools[6]>=g)   ){
        (*plateau).tools[0]-=a;
        (*plateau).tools[1]-=b;
        (*plateau).tools[2]-=c;
        (*plateau).tools[3]-=d;
        (*plateau).tools[4]-=e;
        (*plateau).tools[5]-=f;
        (*plateau).tools[6]-=g;
        free((*plateau).patient);
        (*plateau).patient = NULL;
    }
    
}
//-----------------------------------------------------------
void try_cure_patient(_plateau* plateau){//verifie si il y a les outils pour soigner
    switch(plateau->patient->maladie){
        default:
            break;
        case TEST_DESEASE:
            cure_if_got_tools(plateau,0,1,1,0,0,1,0);
            break;
    }
    
}
//-----------------------------------------------------------
char try_do_action(_tile** grid,int size_x,int size_y,_player* player ,_plateau* plateau_tab ,int taille){
    _tile current_tile;
    int tile_value;
    
    player->pos = get_player_pos_from_grid(grid ,size_x ,size_y);
    if((player->pos.x<0)||(player->pos.y<0)){
        printf("player can't be found\n");
        exit(2);
    }
    current_tile = get_tile_from_pos(grid ,size_x ,size_y ,player->pos.x ,player->pos.y);
    tile_value = current_tile.value;
    
    if((tile_value=='h')&&(player->glove.type==0)){
        //prendre des gants si le joueur n'a pas des gants
        player->glove.type = 'h';
        player->glove.clean = 0 ;
        player->glove.used = 0 ;    
    }
    if(inter_check(tile_value,'a','g')&&(player->tool.type==0)){
        //prendre un objet si le joueur n'a pas d'outil
        player->tool.type = tile_value;
        player->tool.clean = (player->glove.type=='h')&&(player->glove.used==0) ;
        player->tool.used = 0 ;
    }
    else if(tile_value=='i'){
        //mettre les outils dans la poubelle de recyclage
        if((player->tool.type!=0)&&(player->tool.used!=1)){
            player->tool.type = 0;    
        }
        //mettre les gants dans la poubelle de recyclage
        else if((player->glove.type=='h')&&(player->tool.used!=1)){
            player->glove.type = 0;     
        }
    }
    else if(tile_value=='j'){
        //mettre les outils dans la poubelle biologique
        if((player->tool.type!=0)&&(player->tool.used==1)){
            player->tool.type = 0;    
        }
        //mettre les gants dans la poubelle biologique
        else if((player->glove.type=='h')&&(player->tool.used==1)){
            player->glove.type = 0;     
        }
    }
    else if(inter_check(tile_value,'t','z')){
        //pour les plateaux
        //on cherche le plateau
        for(int i=0;i<taille;i++){
            if(plateau_tab[i].id==tile_value){
                //mettre l'outil non sale au plateau si possible
                if(     (player->tool.type!=0)&&(player->tool.clean==1)&&(  (plateau_tab[i].tools[(player->tool.type)-'a'] + plateau_tab[i].used_tools[(player->tool.type)-'a']) == 0)    ){
                    plateau_tab[i].tools[(player->tool.type)-'a'] = 1;
                    player->tool.type = 0;
                }
                //soigner le patient si possible
                else if(     (player->tool.type==0)&&(player->glove.type=='h')&&(plateau_tab[i].patient!=NULL)){
                    try_cure_patient(&(plateau_tab[i]));
                }
                break;
                //prendre un outil du plateau si possible
                /*
                else if(     (player->tool.type==0)&&(plateau_tab[i].tool[(player->tool.type)-'a'] == 1)   ){
                    plateau_tab[i].tool[(player->tool.type)-'a'] = 0;
                    player->tool.type = 
                    
                    
                }
                */
                
            }
        }
    }
} 
//-----------------------------------------------------------
void ask_to_do_player_action(_tile** grid,int size_x,int size_y,_player* player ,_plateau* plateau_tab,int taille) {
	char move ;
	int error = 0;
	printf("Veuillez saisir votre action-----\n\n");
	printf("- type de déplacement\n");
	printf(" |  z:vers le haut\n");
	printf(" |  q:vers la droite\n");
	printf(" |  s:vers le bas\n");
	printf(" |  d:vers la gauche\n");
	printf("- action\n");
	printf(" |  g:faire un action\n");
	do {
		error = scanf(" %c",&move);
		if(!error){
		    printf("input went wrong,flushing scanf()\n");
		    do{
		    }while(!scanf("%c"),&move);
		}
		if((move!='z')&&(move!='d')&&(move!='s')&&(move!='q')&&(move!='g')) {
			printf("L'action saisi est incorrect,veuillez recommencez\n");
		}
	} while((move!='z')&&(move!='d')&&(move!='s')&&(move!='q')&&(move!='g'));
	switch(move) {
	default:
		break;
	case 'z':
		move_player(grid,size_x,size_y,UP);
		//printf("moved up\n");
		break;
	case 'd':
		move_player(grid,size_x,size_y,RIGHT);
		//printf("moved right\n");
		break;
	case 's':
		move_player(grid,size_x,size_y,DOWN);
		//printf("moved down\n");
		break;
	case 'q':
		move_player(grid,size_x,size_y,LEFT);
		//printf("moved left\n");
		break;
	case 'g':
		try_do_action(grid,size_x,size_y,player,plateau_tab ,taille);
		break;
	}
}
//-----------------------------------------------------------
void print_player_status(_player player){
    printf("\n----------------Le joueur-------------------\n");
    
    printf("    |le joueur possède des gants?   :%d-----\n",player.glove.type=='h');
    if(player.glove.type=='h'){
        printf("        |des gants usées?       :%d\n",player.glove.used==1);
    }
    printf("    |le joueur possède des outils?  :%d-----\n",player.tool.type != 0 );
    if(player.tool.type!= 0 ){
        printf("        |type d'outils?         :%c\n",player.tool.type);
        printf("        |des outils propres?    :%d\n",player.tool.clean);
        printf("        |des outils usées?      :%d\n",player.tool.used);
    }
    printf("\n");
}
//-----------------------------------------------------------
//pour www.onlinegdb.com en raison de fscanf
_tile** make_grid_from_string(char string[] ,int max_size_x ,int max_size_y){
    _tile** new_grid = NULL;
    new_grid = cree_grid(max_size_x ,max_size_y);
    
    int string_ind = 0;
    char c ;
    char c2[2];
    c2[1] = '\0';
    for(int dy=0;dy<max_size_y;dy++){
        for(int dx=0 ;dx<1+max_size_x ;dx++){
            
            c = string[string_ind];
            if(c=='_'){
                dx = 0;
                dy ++;
                string_ind++;
            }
            
            c = string[string_ind];
            if(string_ind < max_size_y*(1+max_size_x)){
                if(c!='P'){
                    if(inter_check(c,'0','9')){
                        c2[0] = c;
                        new_grid[dy][dx].value = atoi(c2);
                    }
                    else{
                        new_grid[dy][dx].value = c;
                    }
                }
                else{
                    new_grid[dy][dx].value  = 0;   
                    new_grid[dy][dx].player = 1;    
                }
                
                
                
            }
            string_ind++;
            
    }
    
    return new_grid;
}
}
//-----------------------------------------------------------
_plateau cree_plateau(int new_id){
    _plateau new_plateau;
    for(int i=0;i<NB_TOOLS;i++){
        new_plateau.tools[i] = 0;
        new_plateau.used_tools[i] = 0;
    }
    new_plateau.patient = NULL;
    new_plateau.id = new_id;
    return new_plateau;
}
//-----------------------------------------------------------
_plateau* get_plateau_tab(_tile** grid,int size_x,int size_y,int* taille){
    //compter le nombre de plateau present dans la grille
    _coord plateau_pos;
    *taille = 0;
    for(int id='t';id<='z';id++){
        plateau_pos = get_element_pos_from_grid(grid ,size_x ,size_y ,id);
        if(inter_check(plateau_pos.x,0,size_x)&&inter_check(plateau_pos.y,0,size_y)){
            (*taille)++;    
        }
    }
    //allocation de la liste des plateau
    _plateau* plateau_tab = NULL;
    plateau_tab = malloc((*taille)*sizeof(_plateau));
    exit_if_null_pointer(plateau_tab);
    //creation des tableaux
    int index = 0;
    for(int id='t';id<='z';id++){
        plateau_pos = get_element_pos_from_grid(grid ,size_x ,size_y ,id);
        if(inter_check(plateau_pos.x,0,size_x)&&inter_check(plateau_pos.y,0,size_y)){
            plateau_tab[index] = cree_plateau(id);
            index++;
        }
    }
    return plateau_tab;
    
}
//-----------------------------------------------------------
void print_plateau(_plateau plateau){
    printf("-------plateau %c -----------\n",plateau.id);
    printf("    |tools :  ");
    for(int i=0;i<NB_TOOLS;i++)
        printf("%c:%d  ",i+'a',plateau.tools[i]);
    printf("\n");
    printf("    |has patient? : %d\n",plateau.patient!=NULL);
    
}    
//-----------------------------------------------------------
void print_plateau_tab(_plateau* plateau_tab ,int taille){
    for(int i=0;i<taille;i++){
        print_plateau(plateau_tab[i]);    
    }    
    printf("\n");
}
//-----------------------------------------------------------
_patient* cree_patient(){
    _patient* patient = NULL;
    patient = malloc(sizeof(_patient));
    exit_if_null_pointer(patient);
    
    patient->hummeur = 100;
    patient->maladie = TEST_DESEASE;
    return patient;
}
//-----------------------------------------------------------
int get_a_patient(_plateau* plateau_tab ,int taille ,int initial_hapiness){
    exit_if_null_pointer(plateau_tab);
    int more_patient = 0;
    for(int i=0;i<taille;i++){
        if(plateau_tab[randint(0,taille-1)].patient == NULL){
            more_patient = 1;
            break;
        }    
    }
    if(more_patient){
        int ind = 0; 
        do{
            ind = randint(0,taille-1);
        }while(plateau_tab[ind].patient != NULL);
        plateau_tab[ind].patient = cree_patient();
        plateau_tab[ind].patient->hummeur = initial_hapiness; 
        return 1;
    }
    return 0;
}
//-----------------------------------------------------------
void update_patients_hapiness(_plateau* plateau_tab ,int taille ,int* all_happy ,int* full){
    int full_var = 1;
    for(int i=0;i<taille;i++){
        if(plateau_tab[i].patient != NULL){
            plateau_tab[i].patient->hummeur--;
            if( (plateau_tab[i].patient->hummeur)<=0  ){
                free(plateau_tab[i].patient);
                plateau_tab[i].patient = NULL;
                *all_happy = 0;
            }
        }
        else{
            full_var = 0;
        }
    }
    *full = full_var;
}
//-----------------------------------------------------------
//pour l'arrivée des patients
//si un patient n'a pas de place il attendera avant d'entrer dans la salle(1 patient en attentes au maximum)
void patients_spawning_regulation(_plateau* plateau_tab ,int taille ,int min_spawn_time ,int spawn_time_range ,int* current_patient_spawning_time ,int initial_hapiness){

    if(     (*current_patient_spawning_time) <= 0   ){
        
		if(get_a_patient(plateau_tab ,taille ,initial_hapiness)){
		    (*current_patient_spawning_time) = min_spawn_time + randint(0 ,spawn_time_range);    
        }
        
	}
	else{
	    (*current_patient_spawning_time)--;
	}
}
//-----------------------------------------------------------
int update_patients(_plateau* plateau_tab ,int taille ,int min_spawn_time ,int spawn_time_range ,int* current_patient_spawning_time ,int initial_hapiness){
    int full = 0;
    int all_happy = 1;
    
    patients_spawning_regulation(plateau_tab ,taille ,min_spawn_time ,spawn_time_range ,current_patient_spawning_time ,initial_hapiness);
    update_patients_hapiness(plateau_tab ,taille ,&all_happy ,&full);
    
    if(full&(!all_happy)){
        //game Over
        return 0;
    }
    return 1;
    
}
//-----------------------------------------------------------
void main() {
    srand(time(NULL));
    
    float profit = 0.00f;//inutile pour le momment
    
    //initialisation du joueur
	_player player;
	player.tool.type = 0;
	player.glove.type = 0;
	
	//initialisation du lieu de jeu
	_tile** grid = NULL;
    char map_string[GRID_SIZE_Y*(GRID_SIZE_X +1)] = "11111111111331111111_10000000100000030001_10000011100111111101_100P00jJ100000uU0001_100000iI100000vV0001_11100111100000011101_10000000000000wW0001_10abcde0fgh000xX0001_11ABCDE1FGH111111101_11111111111111111111_";                                                                                                                           
    grid = make_grid_from_string(map_string,GRID_SIZE_X,GRID_SIZE_Y);
    //print_grid(grid,GRID_SIZE_X,GRID_SIZE_Y);
    
    //initialisation des plateaux
    int nb_plateau = 0;
    _plateau* plateau_tab = NULL;
    plateau_tab = get_plateau_tab(grid ,GRID_SIZE_X ,GRID_SIZE_Y ,&nb_plateau);
    
    //initialisation des paramètre des patients
    int patient_minimum_spawn_intervalle = 22;
    int patient_spawn_range = 7;
    int patient_spawning_hapiness = 90;
    int patient_hapiness_range = 10;
    int next_patient_time = next_patient_time = patient_minimum_spawn_intervalle + randint(0 ,patient_spawn_range);
    
    int nb_step = -1;
    int game_still_going = 1;
    while(game_still_going) {
        nb_step++;
		print_grid(grid,GRID_SIZE_X,GRID_SIZE_Y,plateau_tab,nb_plateau);
		print_plateau_tab(plateau_tab ,nb_plateau);
		print_player_status(player);
		ask_to_do_player_action(grid,GRID_SIZE_X,GRID_SIZE_Y,&player,plateau_tab,nb_plateau);
		
		game_still_going = update_patients(plateau_tab ,nb_plateau ,patient_minimum_spawn_intervalle ,patient_spawn_range ,&next_patient_time ,patient_spawning_hapiness+randint(0,patient_hapiness_range));
	
    }
printf("\n\nGAME OVER!! The game lasted for %d steps with a %.2f$ profit",nb_step ,profit);
}
