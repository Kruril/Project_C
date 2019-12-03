#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers/commun.h"
#include "headers/structure.h"
#include "headers/medecin.h"

void listeRendezvous(int, struct medecin *, struct medecin *, int, rendezvous *Rdeb, rendezvous *Rcurant);
void horaireSemaine(int, struct medecin *, struct medecin *, int);

char key;
void optionHoraire(int option, int nbMed, medecin *Mdeb, medecin *Mcurant, int nbRed,
                   rendezvous *Rdeb, rendezvous *Rcurant, int jourHoraire)
{
    if (option == 3)
        return;

    enableRawMode();


        listeMedecin(nbMed, Mdeb, Mcurant);
        printf("Choisiser un medecin : ");
        fflush(stdout);

        while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed));
        disableRawMode();
        system("clear");

    switch (option)
    {
    case 1:
        listeRendezvous(atoi(&key), Mdeb, Mcurant, nbRed, Rdeb, Rcurant);
        break;
    case 2:
        horaireSemaine(atoi(&key), Mdeb, Mcurant, jourHoraire);
        break;
    }
}

char key;
void listeRendezvous(int numMed, medecin *Mdeb, medecin *Mcurant, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    enableRawMode();
    int i;
    // Recherche du medecin
    Mcurant = Mdeb;
    for (i = 1; i < numMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }

    printf("Rendez du medecin %-s : \n\n", Mcurant->nom);
    printf("   Date    | Heure |        Patient        |\n");
    printf("-----------|-------|-----------------------|\n");
    Rcurant = Rdeb;
    for (i = 1; i <= nbRed; i++)
    {
        if (strcmp(Mcurant->nom, Rcurant->nomMedecin) == 0)
        {
            printf("%02d/%02d/%4d | %02d:%02d | %-10s %-10s |\n", Rcurant->jour, Rcurant->mois, Rcurant->annee,
                   Rcurant->heure, Rcurant->minutes, Rcurant->nomPatient, Rcurant->prenomPatient);
        }
        Rcurant = Rcurant->suivant;
    }
    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && key != 10);
    disableRawMode();
    
}
const char *listJourSemaine[] = {
    "Lundi",
    "Mardi",
    "Mercredi",
    "Jeudi",
    "Vendredi",
    "Samedi",
    "Dimanche",
};

void horaireSemaine(int numMed, medecin *Mdeb, medecin *Mcurant, int jourHoraire)
{
    enableRawMode();
    int i;
    // Recherche du medecin
    Mcurant = Mdeb;
    for (i = 1; i < numMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }

    printf("Horaire du medecin %-s\n\n", Mcurant->nom);
    printf("   Jour   | Heure debut | Heure fin |\n");
    printf("----------|-------------|-----------|\n");

    for (i = 1; i <= jourHoraire; i++)
    {
        printf(" %-9s|    %02d:00    |   %02d:00   |\n", listJourSemaine[i - 1], Mcurant->horaire.heureDeb[i],
               Mcurant->horaire.heureFin[i]);
    }
    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && key != 10);
    disableRawMode();
}