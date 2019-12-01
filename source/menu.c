#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/structure.h"
#include "headers/medecin.h"

int MenuPrincipal()
{
    char option[20];
    system("clear");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|                 1. Prendre rendez-vous | 2. Voir les horaires                   |\n");
    printf("|                 3. Liste medecin       | 4. Annulation d'un rendez-vous         |\n");
    printf("|                 5. Information logiciel| 6. Quitter le programme                |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Numero de l'option : ");
    scanf("%s",option);
    system("clear");
    return atoi(option);
}

char value[20];
int MenuMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|             1. Voir la liste des patients | 2. Ajouter un medecin               |\n");
    printf("|             3. Information sur le medecin |                                     |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option : ");
    scanf("%s", value);
    system("clear");
    return atoi(value);
}

int MenuHoraire()
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|             1. Liste des rendez-vous      | 2. Horaire de la semaine            |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option : ");
    scanf("%s", value);
    system("clear");
    return atoi(value);
}