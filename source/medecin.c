#include <stdio.h>
#include <stdlib.h>
#include "headers/structure.h"


void choixOption( int value)
{
    if (value == 1)
    {
        printf("De quel medecin voulez-vous voir les patients ?\n");
    }
}

void listeMedecin(int nbMed, medecin med[])
{
    int i;
    for (i = 0; i < nbMed; i++)
    {
        printf("%02d %-21s\n", (i + 1), med[i].nom);
    }
    printf("\n");
}

void PrendRendVous(int nbMed, medecin med[])
{
    int numMed;
    char nom[21];
    listeMedecin(nbMed, med);
    printf("Pour quel medecin prendre le rendez-vous?\n");
    do
    {
        scanf("%2d", &numMed);
        if (numMed < 0 || numMed > nbMed)
        {
            printf("Numéro du medecin invalide recommancer\n");
        }
        
    } while (numMed < 0 || numMed > nbMed);
   
    *nom = med[numMed-1].nom;
}