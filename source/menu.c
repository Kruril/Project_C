#include <stdio.h>
#include <stdlib.h>

int MenuPrincipal()
{
    int option;
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                 1. Prendre rendez-vous | 2. Voir les horaires                   |\n");
    printf("|                 3. Liste medecin       | 4. Annulation d'un rendez-vous         |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Numero de l'option : ");
    scanf("%2d",&option);
    system("clear");
    return option;
}

void VuMedecin()
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("|             1. Voir la liste des patients | 2. Ajouter un medecin               |\n");
    printf("|             3. Information sur le medecin | 4. retour au menu principal         |\n");
    printf("-----------------------------------------------------------------------------------\n");
}