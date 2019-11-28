#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headers/structure.h"
#include "headers/menu.h"
#include "headers/medecin.h"

bool run()
{
    // Déclaration des variables
    int option, nbMed = 0, i, value, nbPat=0;

    // Ouverture des différents fichiers
    FILE *fMedecin , *fPatient, *fRendezVous;
    fMedecin = fopen("Donnees/Medecin.dat", "a+");
    fPatient = fopen("Donnees/patient.dat", "a+");
    fRendezVous = fopen("Save/rendez_vous.res", "a+");

    //A SUPPRIMER PAR LA SUITE
    fprintf(fRendezVous, "blabla");

    // ***************************************************************************************************
    /* Lecture du fichier Medecin
       Le fichier contient le nom du medecin, sa spécialité, son numéro Inami et num GSM */
    // ***************************************************************************************************


    // Déclaration des structures
    medecin *Mdeb, *Mcurant, *Msuivant;
    
    Mdeb = malloc(sizeof(medecin));
    Mcurant = Mdeb;
    fscanf(fMedecin,"%20s",Mcurant->nom);

    while (!feof(fMedecin))
    {
        fscanf(fMedecin, "%20s%10s%10s", Mcurant->specialite,Mcurant->numInami,Mcurant->numGSM);
        Msuivant = malloc(sizeof(medecin));
        Mcurant->suivant = Msuivant;
        nbMed++;
        Mcurant = Msuivant;
        fscanf(fMedecin, "%20s", Mcurant->nom);
    }

    // Mise à Null du dernier element
    Mcurant = Mdeb;
    for ( i = 1; i < nbMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }
    Mcurant->suivant = NULL;
    free(Msuivant);

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
        fscanf(fPatient, "%20s%10s%20s%11s%4d",Pcurant->prenom,Pcurant->numGSM,Pcurant->nomMedecin,
        Pcurant->idRegistre,&Pcurant->codePostal);
        Psuivant = malloc(sizeof(patient));
        Pcurant->suivant = Psuivant;
        nbPat++;
        Pcurant = Psuivant;
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

    // Affichage du menu principal et Scan de l'option
    do
    {
        option = MenuPrincipal();
    } while (option < 0 || option > 5);

    if (option == 1)
    {
        PrendRendVous(nbMed, Mdeb, Mcurant);
    }
    else if (option == 2)
    {
        //code
    }
    else if (option == 3)
    {
        do
        {
            value = VuMedecin(nbMed, Mdeb, Mcurant);
        } while (value < 0 || value > 4);
        choixOption(value);
    }
    else if (option == 4)
    {
        /* code */
    }
    else if (option == 5)
    {
        free(Mdeb);
        free(Pdeb);
        return false;
    }
    free(Mdeb);
    free(Pdeb);
    return true;
}