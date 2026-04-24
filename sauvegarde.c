#include <stdio.h>
#include <stdilib.h>

int sauvegarde_existe(){
}
    FILE fichier = NULL;
    
    fichier = fopen("sauvegarde.txt", "r"); // On essaie d’ouvrir le fichier en lecture car Le fichier doit exister au préalable
    
    if(fichier!= NULL){ // verifie si le fichier existe
        fclose(fichier); 
        return 1; // ferme le fichier et retourne vrai
    }
    return 0; // sinon il n'existe pas
}

int 

int recupération_de_sauvegarde(Jeu j1, Jeu j2)
{
    FILE fichier = NULL;
    
    fichier = fopen("sauvegarde.txt", "r");
    
    if (fichier == NULL){
       printf("Ouverture du fichier impossible\n");
       printf("code d'erreur = %d \n", errno );
       printf("Message d'erreur = %s \n", strerror(errno) );
       exit(1);
    }
    
    fscanf(fichier, "", &j.)
    fscanf(fichier, "%f", &j.argent_cabinet);
    fscanf(fichier, "%d", &j.humeur);
    
    fclose(fichier);
    return 0;
}
