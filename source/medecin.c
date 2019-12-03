#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "headers/commun.h"
#include "headers/structure.h"


char key;
void optionMedecin(int value)
{
    if (value == 1)
    {
        printf("De quel medecin voulez-vous voir les patients ?\n");
    }
}

void listeMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    int i;
    printf("Num |         Nom          |      Specialite      |\n");
    printf("----|----------------------|----------------------|\n");
    Mcurant = Mdeb;
    for (i = 1; i <= nbMed; i++)
    {
        printf(" %02d | %-21s| %-21s|\n", i, Mcurant->nom, Mcurant->specialite);
        Mcurant = Mcurant->suivant;
    }
    printf("\n");
}

void PrendRendVous(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();

    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Numero du medecin pour prendre le rendez-vous?");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed+1));
    disableRawMode();
    if (atoi(&key) == nbMed +1) return ;
}