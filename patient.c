#include <stdio.h>
#include <stdbool.h>


int convertir_en_secondes(Temps t)
{
    int duree = t.heure * 3600 + t.minute * 60 + t.seconde;
    return duree;
}


void mettre_a_jour_humeur_patient(Patient *p, Temps temps_actuel)
{
    int temps_actuel_sec;
    int temps_arrivee_sec;
    int attente;

    temps_actuel_sec = convertir_en_secondes(temps_actuel);

    temps_arrivee_sec = convertir_en_secondes(p->heure_arrive);

    attente = temps_actuel_sec - temps_arrivee_sec;

    if (attente>=300){
        p->humeur = ROUGE; 
    }

    else if(attente >=180 && attente <= 300){
        p->humeur = ORANGE; 
    }

    else{
        p->humeur =VERT; 
    }
}

float calculer_montant_patient(Patient *p){
     if (p->humeur == ROUGE){
         return p->montant_a_payer / 2 ;  //pr ne pas modif 
     }
     
     else{
         return p->montant_a_payer;
     }
}

void verifier_gants(Dentiste *d, Patient *p){
     if(d->gants == 0){
         p->humeur = ROUGE; 
         p->fauteuil = 0; 
     }
}

void verifier_proprete_ustensile(Dentiste *d, Patient *p){
    if(d->proprete_ustensile == false){
        p->humeur = ROUGE;
        p->fauteuil = 0;
    }
}

void gerer_patient(Patient *p, Dentiste *d, Temps temps_actuel){  //initialiser
    if (p->fauteuil == 0){
        return; 
    }

    mettre_a_jour_humeur_patient(p, temps_actuel);

    verifier_gants(d,p); 

       if(p->fauteuil ==0){
          return; 
       }

    verifier_proprete_ustensile(d,p); 

}
