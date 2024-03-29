#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/commun.h"
#include "headers/horaires.h"
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

/*
Méthode qui veriffie si le patient appartient bien au medecin 
*/
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

void annulation_par_patient(int nbMed, medecin *Mdeb, medecin *Mcurant, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    enableRawMode();
    listeMedecin(nbMed, Mdeb, Mcurant);
    char key[3];
    printf("Choisiser un medecin : \n");
    fflush(stdout);
    while (read(STDIN_FILENO, key, 1) == 1 && (atoi(key) < 1 || atoi(key) > nbMed + 1));

    disableRawMode();
    system("clear");
    listeAnnulationrendezvous(atoi(key),Mdeb, Mcurant, nbRed,Rdeb, Rcurant);

    int heure, min, jour, mois , annee;
    char  heureChar[10], minChar[10], nomPat[20], prenomPat[20];
    bool date = false;

    while (true)
    {
        do
        {
            date = EncodageDate(&jour, &mois, &annee);
        } while (date == false || check_date(jour, mois, annee) == false);
        
        printf("Choississez un des rendez-vous :  \n\n ");

        do
        {
            printf("Entrer l'heure du rendez-vous (x ou xx) /!\\Pas les minutes :");
            fgets(heureChar, 10, stdin);
        } while (atoi(heureChar) == 0 || strlen(heureChar) > 3);
        heure = atoi(heureChar);

        printf("\nEntrer les minutes du rendez-vous (x ou xx) :");

        do
        {
            fgets(minChar, 10, stdin);
            if (strlen(minChar) == 2 && (!(minChar[0] >= 'a') || !(minChar[0] <= 'z')) &&
                (!(minChar[0] >= 'A') || !(minChar[0] <= 'Z')))
                break;
        } while (atoi(minChar) == 0 || strlen(minChar) > 3 || atoi(minChar) != 30);
        min = atoi(minChar);

        printf("vous avez choisis l'heure suivante : %02d:%02d \n\n", heure, min);
        Mcurant = Mdeb;

        printf("Entrer le nom du patient : ");
        fgets(nomPat, 22, stdin);
        remove_jumpLine(nomPat, 22);
        remove_space(nomPat);

        printf("Entrer le prenom du patient : ");
        fgets(prenomPat, 22, stdin);
        remove_jumpLine(prenomPat, 22);
        remove_space(prenomPat);
        if (!rendezVous_for_annulation(nomPat, prenomPat, jour, mois, annee, heure, min, nbRed, Rdeb, Rcurant))
        {
            printf("Pas de rendez-vous pour cette date et cette heure.\n");
            continue;
        }

        validationRemoveRendezVous(nomPat, prenomPat, jour, mois, annee, heure, min, nbRed, Rdeb, Rcurant);
        break;
    }
}

bool rendezVous_for_annulation(const char *nomPat, const char *prenomPat, int jour, int mois,
                                int annee, int heure, int min, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    Rcurant = Rdeb;
    for (int i = 1 ; i<= nbRed; i++)
    {
        if (strcmp(nomPat, Rcurant->nomPatient) ==0 && strcmp(prenomPat, Rcurant->prenomPatient) == 0 &&
            jour == Rcurant->jour && Rcurant->mois == mois && Rcurant->annee == annee && Rcurant->heure == heure &&
            Rcurant->minutes == min)
        {
            return true;
        }
        Rcurant = Rcurant->suivant;
    }
    return false;
}

void validationRemoveRendezVous(const char *nomPat, const char *prenomPat, int jour, int mois,
                                int annee, int heure, int min, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{

    Rcurant = Rdeb;
    int numRendezvous;
    for ( int i = 1 ; i < nbRed ;i++)
    {
        if (strcmp(nomPat, Rcurant->nomPatient) == 0 && strcmp(prenomPat, Rcurant->prenomPatient) == 0 &&
            jour == Rcurant->jour && Rcurant->mois == mois && Rcurant->annee == annee && Rcurant->heure == heure &&
            Rcurant->minutes == min)
        {
            numRendezvous = i;
            break;
        }
        Rcurant = Rcurant->suivant;
    }

    remove_to_list(numRendezvous, nbRed, Rdeb, Rcurant);

    enableRawMode();
    char key;
    printf("Rendez-vous supprimé\n");
    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && key != 10);
    disableRawMode();
}

void remove_to_list(int place, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    //Suppression de la liste
    rendezvous *intercal;
    int i;

    if (place == 1)
    {
        // intercal = Rdeb;
        Rdeb = Rdeb->suivant;
        // free(intercal);
    }
    else
    {
        Rcurant = Rdeb;
        for (i = 1; i < place - 1; i++)
        {
            Rcurant = Rcurant->suivant;
        }
        if (place != nbRed)
        {
            intercal = Rcurant->suivant;
            Rcurant->suivant = intercal->suivant;
            free(intercal);
        }
        else
        {
            intercal = Rcurant->suivant;
            Rcurant->suivant = NULL;
            free(intercal);
        }
    }

    // Enregistrement dans le fichier de rendez-vous
    FILE *fres;
    fres = fopen("Save/rendez_vous.res", "w");

    Rcurant = Rdeb;
    for (i = 1; i < nbRed; i++)
    {
        fprintf(fres, "%-20s%-20s%-20s%2d%2d%4d %02d%02d %-40s\n", Rcurant->nomMedecin, Rcurant->nomPatient, Rcurant->prenomPatient,
                Rcurant->jour, Rcurant->mois, Rcurant->annee, Rcurant->heure, Rcurant->minutes, Rcurant->note);
        Rcurant = Rcurant->suivant;
    }

    fclose(fres);

}