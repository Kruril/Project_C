#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/structure.h"


void choixOption( int value)
{
    if (value == 1)
    {
        printf("De quel medecin voulez-vous voir les patients ?\n");
    }
}

void listeMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    int i;
    printf("Num |         Nom          | Specialite\n");
    Mcurant = Mdeb;
    for (i = 1; i <= nbMed; i++)
    {
        printf(" %02d | %-21s| %-21s\n", i, Mcurant->nom
        , Mcurant->specialite);
        Mcurant = Mcurant->suivant;
    }
    printf("\n");
}

void PrendRendVous(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    char numMed[20];
    int num ;
    
    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Numero du medecin pour prendre le rendez-vous?\n");
    do
    {
        scanf("%s", numMed);
        num = atoi(numMed);
        if (num == nbMed + 1)
        {
            return;
        }
        if (num < 1 || num > nbMed )
        {
            printf("Numéro du medecin invalide recommancer\n");
        }
        

    } while (num < 1 || num > nbMed);

    
}