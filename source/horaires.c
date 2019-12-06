#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "headers/commun.h"
#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/horaires.h"

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
        horairePropreMedecin(atoi(&key), Mdeb, Mcurant, jourHoraire);
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
}

void horairePropreMedecin(int numMed, medecin *Mdeb, medecin *Mcurant, int jourHoraire)
{
    enableRawMode();

    horaireSemaine(numMed, Mdeb, Mcurant, jourHoraire);

    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && key != 10);
    disableRawMode();
}

bool EncodageDate(int *jour, int *mois, int *an)
{
    char date[12], jourChar[3], moisChar[3], anChar[5];
    int depMois = 0, depAn = 0, i = 0;
    printf("Entrer date (DD/MM/YYYY): ");
    // fflush(stdout);
    fgets(date, 15, stdin);

    if (date[2] == '/' && date[5] == '/' && date[10] == '\n')
    {
        while (date[i] != '/')
        {
            jourChar[i] = date[i];
            i++;
        }
        jourChar[i] = '\0';
        i++;
        while (date[i] != '/')
        {
            moisChar[depMois] = date[i];
            i++;
            depMois++;
        }
        moisChar[depMois] = '\0';
        i++;
        while (date[i] != '\n')
        {
            anChar[depAn] = date[i];
            i++;
            depAn++;
        }
        anChar[depAn] = '\0';

        *jour = atoi(jourChar);
        *mois = atoi(moisChar);
        *an = atoi(anChar);
    }
    else
    {
        *jour = 0;
        *mois = 0;
        *an = 0;
    }

    //check année
    if (*an >= 1900 && *an <= 9999)
    {
        //check mois
        if (*mois >= 1 && *mois <= 12)
        {
            //check jours
            if ((*jour >= 1 && *jour <= 31) && (*mois == 1 || *mois == 3 || *mois == 5 || *mois == 7 || *mois == 8 || *mois == 10 || *mois == 12))
                return true;
            else if ((*jour >= 1 && *jour <= 30) && (*mois == 4 || *mois == 6 || *mois == 9 || *mois == 11))
                return true;
            else if ((*jour >= 1 && *jour <= 28) && (*mois == 2))
                return true;
            else if (*jour == 29 && *mois == 2 && (*an % 400 == 0 || (*an % 4 == 0 && *an % 100 != 0)))
                return true;
            else
            {
                printf("Date mal encodé.\n");
                return false;
            }
        }
        else
        {
            printf("Date mal encodé.\n");
            return false;
        }
    }
    else
    {
        printf("Date mal encodée.\n");
        return false;
    }
}

int DerterminationJour(int jour, int mois, int an)
{
    struct tm t;
    int jours[7] = {7, 1, 2, 3, 4, 5, 6};
    t.tm_year = an + 100;
    t.tm_mon = mois - 1;
    t.tm_mday = jour;
    t.tm_hour = t.tm_min = t.tm_sec = 0;
    if (mktime(&t) == -1)
    {
        printf("Erreur, le format de la date n'est pas correcte\n");
        return 0;
    }
    return jours[t.tm_wday];
}