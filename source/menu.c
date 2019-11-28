#include <stdio.h>
#include <stdlib.h>
#include "headers/structure.h"
#include "headers/medecin.h"

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

int VuMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    listeMedecin(nbMed, Mdeb, Mcurant);
    int value;
    printf("-----------------------------------------------------------------------------------\n");
    printf("|             1. Voir la liste des patients | 2. Ajouter un medecin               |\n");
    printf("|             3. Information sur le medecin |                                     |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option :\n");
    scanf("%2d", &value);
    system("clear");
    return value;
}