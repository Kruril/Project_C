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
    int option, nbMed, i, value;

    // Ouverture des différents fichiers
    FILE *fMedecin /*, *fPatient*/;
    fMedecin = fopen("Donnees/Medecin.dat", "r+");
    // fPatient = fopen("Save/patient.res", "a+");

    /* Lecture du fichier Medecin
       Le fichier contient le nom du medecin, sa spécialité et son numéro Inami */
    fscanf(fMedecin, "%2d", &nbMed);
    // Déclaration des structures
    medecin med[nbMed];

    for (i = 0; i < nbMed; i++)
    {
        fscanf(fMedecin, "%20s%20s%10s", med[i].nom, med[i].specialite, med[i].numInami);
    }
    // Affichage du menu principal et Scan de l'option
    do
    {
        option = MenuPrincipal();
    } while (option < 0 || option > 4);

    if (option == 1)
    {
        // code
    }
    else if (option == 2)
    {
        //code
    }
    else if (option == 3)
    {
        do
        {
            value = VuMedecin(nbMed, med);
        } while (value < 0 || value > 4);
        choixOption(value);
    }
    else if (option == 4)
    {
        /* code */
    }
    else if (option == 0)
    {
        return false;
    }
    return true;
}