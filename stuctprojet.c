#include <stdio.h>

typedef struct{
    int heure                    ;
    int minute                   ;
    int seconde                  ;
} Temps;

typedef struct{    
    Dentiste  dentiste           ; // on peut augmenter au bout d'un montant
    Temps     temps_debut_partie ;   
    Patient   patient            ;
    int       nb_client          ; // depuis le debut de la parti
    float     argent_cabinet     ; // ensemble argent gagné
    int       humeur             ; //nb patient mecontent, content et furieux
} Jeu;

typedef struct{
    int** position              ; // du dentiste sur plateau
    int   gants                 ; // mis = 1 pas mis = 0
    int   ustensile_en_main      ; // num ustensile
    int   main                  ; // pleine = 1 pas pleine = 0   
} Dentiste

typedef struct{
    int*   plateau              ; // tableau avec num ustensiles
    int    ustensile            ; // 1 ustensile = 1 nombre
    int    pathologie           ; // 1 pathologie = 1 nombre
    float  montant_a_payer      ; // diminue si qualité mauvaise
    int    humeur               ; // jauge
    int    fauteuil             ; //vide ou non
    Temps  heure_arrive         ; // a partir du moment où il est dans le  fauteuil
} Patient;
