#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_Project.h"

main()
{
    // Déclaration des variables
    int option, nbMed,i;

    // Ouverture des différents fichiers
    FILE *fMedecin;
    fMedecin = fopen("Donnees/Medecin.dat","a+");

    /* Lecture du fichier Medecin
       Le fichier contient le nom du medecin, sa spécialité et son numéro Inami */
    fscanf(fMedecin,"%2d",&nbMed);
    // Déclaration des structures
    medecin med[nbMed];
    printf("%2d\n",nbMed);
    for ( i = 0; i < nbMed; i++)
    {
        fscanf(fMedecin,"%20s%20s%10s",med[i].nom,med[i].specialite,med[i].numInami);
    }


    // Affichage du menu principal et Scan de l'option
    do
    {
        MenuPrincipal();
        printf("Numero de l'option : ");
        scanf("%2d",&option);
        system("cls");
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
        for ( i = 0; i < nbMed; i++)
        {
            printf("%02d %-21s\n",(i+1),med[i].nom);
        }
        
    }
    else if (option == 4)
    {
        /* code */
    }
    else if (option == 0)
    {
        /* code */
    }
    
    
    
    
    
    printf("Fin du Programme");
    
}

void MenuPrincipal()
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                 1. Prendre rendez-vous | 2. Voir les horaires                   |\n");
    printf("|                 3. Liste medecin       | 4. Annulation d'un rendez-vous         |\n");
    printf("-----------------------------------------------------------------------------------\n");
}