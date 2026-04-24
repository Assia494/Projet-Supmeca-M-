#include <stdio.h>
#include <stdbool.h>



int convertir_en_secondes(Temps t){

    int duree = t.heure * 3600 + t.minute * 60 + t.seconde;
    return duree;
}




void mettre_a_jour_humeur_patient(Patient *p, Temps temps_actuel){

    int temps_actuel_sec;
    int temps_arrivee_sec;
    int attente;

    temps_actuel_sec = convertir_en_secondes(temps_actuel);
    temps_arrivee_sec = convertir_en_secondes(p->heure_arrive);
    attente = temps_actuel_sec - temps_arrivee_sec;

    if (attente >= 300){
        p->humeur = ROUGE;
    }
    else if (attente >= 180){
        p->humeur = ORANGE;
    }
    else{
        p->humeur = VERT;
    }

    
    if (attente >= 600){     // 10min pr s en aller
        p->etat = FURIEUX;
        p->fauteuil = 0;
    }
}



float calculer_montant_patient(Patient *p){

    if (p->etat == FURIEUX){
        return 0;
    }
    else if (p->etat == MECONTENT){
        return p->montant_a_payer / 2;
    }
    else{
        return p->montant_a_payer;
    }
}




void verifier_gants(Dentiste *d, Patient *p){

    if (d->gants == 0){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
    }
}



void verifier_proprete_ustensile(Dentiste *d, Patient *p){

    if (d->proprete_ustensile == false){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
    }
}


void verifier_ustensile_pathologie(Dentiste *d, Patient *p){    //mauvais ustensile -> s en va
   

    if (p->pathologie == 1 && d->ustensile_en_main != 1){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 2 && d->ustensile_en_main != 2){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 3 && d->ustensile_en_main != 3){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 4 && d->ustensile_en_main != 4){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 5 && d->ustensile_en_main != 5){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 6 && d->ustensile_en_main != 6){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 7 && d->ustensile_en_main != 7){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }

    if (p->pathologie == 8 && d->ustensile_en_main != 8){
        p->humeur = ROUGE;
        p->etat = FURIEUX;
        p->fauteuil = 0;
        return;
    }
}

void gerer_patient(Patient *p, Dentiste *d, Temps temps_actuel){

    if (p->fauteuil == 0){ 
        return;
    }

    mettre_a_jour_humeur_patient(p, temps_actuel);
    if (p->fauteuil == 0){
        return;
    }

    verifier_gants(d, p);
    if (p->fauteuil == 0){
        return;
    }

    verifier_proprete_ustensile(d, p);
    if (p->fauteuil == 0){
        return;
    }

    verifier_ustensile_pathologie(d, p);
    if (p->fauteuil == 0){
        return;
    }

    
    if (p->humeur == ROUGE){   //verif etat pr payement
        p->etat = MECONTENT;
    }
    else{
        p->etat = SATISFAIT;
    }
}

void encaisser_patient(Jeu *j, Patient *p){

    j->argent_cabinet = j->argent_cabinet + calculer_montant_patient(p);
}
