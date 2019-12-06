#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/commun.h"
#include "headers/patient.h"

void patient_de_medecin(int nbPat, patient *Pdeb, patient *Pcurant, 
                        int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();
    char key[3], nomMedecin[21];
    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Choisiser un medecin : ");
    fflush(stdout);
    while (read(STDIN_FILENO, key, 1) == 1 && (atoi(key) < 1 || atoi(key) > nbMed + 1));

    if (atoi(key) == nbMed +1) return;

    Mcurant = Mdeb;
    for (int i = 1; i < atoi(key); i++)
    {
        Mcurant = Mcurant->suivant;
    }
    strcpy(nomMedecin, Mcurant->nom);
    listepatient(nomMedecin, nbPat, Pdeb, Pcurant);

    disableRawMode();
}

void listepatient(const char *nomMedecin,int nbPat ,patient *Pdeb, patient *Pcurant)
{
    system("clear");
    Pcurant = Pdeb;
    char valeur; 
    printf("Liste des patients du medecin : %-s\n\n", nomMedecin);
    printf("   Nom patient    | Prenom patient |\n");
    printf("------------------|----------------|\n");

    for(int i = 1; i <= nbPat; i++)
    {
        if (strcmp(Pcurant->nomMedecin , nomMedecin) == 0)
        {
            printf("%-18s|%-16s|\n", Pcurant->nom, Pcurant->prenom);
        }
        Pcurant = Pcurant->suivant;
    }

    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);
    while (read(STDIN_FILENO, &valeur, 1) == 1 && valeur != 10);
}