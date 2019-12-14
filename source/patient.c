#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/commun.h"
#include "headers/patient.h"

/*
Méthode qui va chercher le medecin voulut est passé son nom dans une 
méthode qui affichera tout les patients de ce medecin
*/
void patient_de_medecin(int nbPat, patient *Pdeb, patient *Pcurant, 
                        int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();
    char key[3], nomMedecin[21];
    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Choisiser un medecin : ");
    fflush(stdout);
    while (read(STDIN_FILENO, key, 1) == 1 && (atoi(key) < 1 || atoi(key) > nbMed + 1))
        ;

    if (atoi(key) == nbMed + 1)
        return;

    Mcurant = Mdeb;
    for (int i = 1; i < atoi(key); i++)
    {
        Mcurant = Mcurant->suivant;
    }
    strcpy(nomMedecin, Mcurant->nom);
    system("clear");
    char valeur;
    listepatient(nomMedecin, nbPat, Pdeb, Pcurant);

    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);
    while (read(STDIN_FILENO, &valeur, 1) == 1 && valeur != 10)
        ;

    disableRawMode();
}

/*
Méthode qui affiche tout les patients d'un medecin voulu
elle affiche le nom et prenom du patient.
*/
void listepatient(const char *nomMedecin,int nbPat ,patient *Pdeb, patient *Pcurant)
{
    Pcurant = Pdeb;

    printf("Liste des patients du medecin : %-s\n\n", nomMedecin);
    printf("   Nom patient    | Prenom patient | ID registre |\n");
    printf("------------------|----------------|-------------|\n");

    for (int i = 1; i <= nbPat; i++)
    {
        if (strcmp(Pcurant->nomMedecin, nomMedecin) == 0)
        {
            printf("%-18s|%-16s|%-13s|\n", Pcurant->nom, Pcurant->prenom, Pcurant->idRegistre);
        }
        Pcurant = Pcurant->suivant;
    }
}

bool estPatient(const char *nomMedecin, const char *idRegistre, int nbPat, patient *Pdeb, patient *Pcurant)
{
    Pcurant = Pdeb;
    for (int i = 1; i <= nbPat; i++)
    {
        if (strcmp(Pcurant->nomMedecin, nomMedecin) == 0 && (strcmp(Pcurant->idRegistre, idRegistre) == 0))
        {
            return 1;
        }
        Pcurant = Pcurant->suivant;
    }
    return 0;
}