#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/menu.h"
#include "headers/horaires.h"
#include "headers/run.h"

bool run(void)
{
    // Déclaration des variables
    int option, nbMed = 0, i, j, value, nbPat = 0, nbRed = 0, jourHoraire = 7;

    // Ouverture des différents fichiers
    FILE *fMedecin, *fPatient, *fRendezVous, *fHoraire;
    fMedecin = fopen("Donnees/Medecin.dat", "a+");
    fPatient = fopen("Donnees/patient.dat", "a+");
    fRendezVous = fopen("Save/rendez_vous.res", "a+");
    fHoraire = fopen("Donnees/Horaires.dat", "a+");

    // ***************************************************************************************************
    /* Lecture du fichier Medecin
       Le fichier contient le nom du medecin, sa spécialité, son numéro Inami et num GSM */
    // ***************************************************************************************************

    // Déclaration des structures
    medecin *Mdeb, *Mcurant, *Msuivant;

    Mdeb = malloc(sizeof(medecin));
    Mcurant = Mdeb;
    fscanf(fMedecin, "%20s", Mcurant->nom);

    while (!feof(fMedecin))
    {
        fscanf(fMedecin, "%20s%10s%10s", Mcurant->specialite, Mcurant->numInami, Mcurant->numGSM);
        Msuivant = malloc(sizeof(medecin));
        Mcurant->suivant = Msuivant;
        nbMed++;
        Mcurant = Msuivant;
        fscanf(fMedecin, "%20s", Mcurant->nom);
    }

    // Mise à Null du dernier element
    Mcurant = Mdeb;
    for (i = 1; i < nbMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }
    Mcurant->suivant = NULL;
    free(Msuivant);

    // ***************************************************************************************************

    // **************************************************************************************************
    /* Lecture du fichier Patient
       Le fichier contient le nom du patient, son prenom, son numéro GSM, le nom de son medecin , 
       son num registre nationnal et son code postal  */
    // **************************************************************************************************

    // Déclaration des structures
    patient *Pdeb, *Pcurant, *Psuivant;

    Pdeb = malloc(sizeof(patient));
    Pcurant = Pdeb;
    fscanf(fPatient, "%20s", Pcurant->nom);

    while (!feof(fPatient))
    {
        Psuivant = malloc(sizeof(patient));
        fscanf(fPatient, "%20s%10s%20s%11s%4d", Pcurant->prenom, Pcurant->numGSM, Pcurant->nomMedecin,
               Pcurant->idRegistre, &Pcurant->codePostal);
        Pcurant->suivant = Psuivant;
        nbPat++;
        Pcurant = Pcurant->suivant;
        fscanf(fPatient, "%20s", Pcurant->nom);
    }
    
    // Mise à Null du dernier element
    Pcurant = Pdeb;
    for (i = 1; i < nbPat; i++)
    {
        Pcurant = Pcurant->suivant;
    }
    Pcurant->suivant = NULL;
    free(Psuivant);

    // ***************************************************************************************************

    // **************************************************************************************************
    /* Lecture du fichier RendezVous
       Le fichier contient le nom du medecin, le nom du patient, son prenom, la date de la consultation,
       et l'heure du rendez-vous */
    // **************************************************************************************************

    // Déclaration des structures
    rendezvous *Rdeb, *Rcurant, *Rsuivant;

    Rdeb = malloc(sizeof(rendezvous));
    Rcurant = Rdeb;

    fscanf(fRendezVous, "%20s", Rcurant->nomMedecin);

    while (!feof(fRendezVous))
    {
        fscanf(fRendezVous, "%20s%20s%2d%2d%4d%2d%2d", Rcurant->nomPatient, Rcurant->prenomPatient,
               &Rcurant->jour, &Rcurant->mois, &Rcurant->annee, &Rcurant->heure, &Rcurant->minutes);
        Rsuivant = malloc(sizeof(rendezvous));
        Rcurant->suivant = Rsuivant;
        nbRed++;
        Rcurant = Rsuivant;
        fscanf(fRendezVous, "%20s", Rcurant->nomMedecin);
    }

    // Mise à Null du dernier element
    Rcurant = Rdeb;
    for (i = 1; i < nbRed; i++)
    {
        Rcurant = Rcurant->suivant;
    }
    Rcurant->suivant = NULL;
    free(Rsuivant);

    // ***************************************************************************************************

    // ***************************************************************************************************
    /* Lecture du fichier Horaire
       Le fichier comprend le nom du medecin et 7 horaires pour chauque jour de la semaine */
    // ***************************************************************************************************

    char nomMedecin[21];
    Mcurant = Mdeb;
    for (i = 1; i <= nbMed; i++)
    {
        fscanf(fHoraire, "%20s", nomMedecin);
        for (j = 1; j <= jourHoraire; j++)
        {
            fscanf(fHoraire, "%2d%2d", &Mcurant->horaire.heureDeb[j], &Mcurant->horaire.heureFin[j]);
        }
        Mcurant = Mcurant->suivant;
    }

    // ***************************************************************************************************

    // Affichage du menu principal et Scan de l'option
    option = MenuPrincipal();

    switch (option)
    {
    case 1:
        PrendRendVous(nbMed, Mdeb, Mcurant);
        break;
    case 2:
        value = MenuHoraire();
        optionHoraire(value, nbMed, Mdeb, Mcurant, nbRed, Rdeb, Rcurant, jourHoraire);
        break;
    case 3:
        value = MenuMedecin();
        optionMedecin(value, nbPat, Pdeb, Pcurant, nbMed, Mdeb, Mcurant);
        break;
    case 4:
        //code
        break;
    case 5:
        break;
    case 6:
        free(Mdeb);
        free(Mcurant);
        free(Pdeb);
        free(Pcurant);
        free(Rdeb);
        free(Rcurant);

        fclose(fMedecin);
        fclose(fPatient);
        fclose(fHoraire);
        fclose(fRendezVous);
        return false;
    }

    free(Mdeb);
    free(Mcurant);
    free(Pdeb);
    free(Pcurant);
    free(Rdeb);
    free(Rcurant);

    fclose(fMedecin);
    fclose(fPatient);
    fclose(fHoraire);
    fclose(fRendezVous);
    return true;
}