#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "headers/commun.h"
#include "headers/structure.h"
#include "headers/medecin.h"
#include "headers/patient.h"
#include "headers/menu.h"

//key est une variable global permetant de choisir le numéro souhaité
char key;

/*
Méthode affichant le menu principal du programme elle retourne le 
numéro de l'option choisi par l'utilisateur
*/
int MenuPrincipal()
{
    enableRawMode();
    system("clear");
    printf("┌---------------------------------------------------------------------------------┐\n");
    printf("|                                                                                 |\n");
    printf("|                 1. Prendre rendez-vous | 2. Voir les horaires                   |\n");
    printf("|                 3. Personnel           | 4. Annulation d'un rendez-vous         |\n");
    printf("|                 5. Information logiciel| 6. Quitter le programme                |\n");
    printf("|                                                                                 |\n");
    printf("└---------------------------------------------------------------------------------┘\n");
    printf("Numero de l'option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 6));
    disableRawMode();
    system("clear");
    return atoi(&key);
}

/*
Méthode affichant le menu de l'option 3 du menu principal
elle retourne l'option choisi par l'utilisateur
*/
int MenuMedecin(void)
{
    enableRawMode();
    printf("┌---------------------------------------------------------------------------------┐\n");
    printf("|                                                                                 |\n");
    printf("|             1. Voir la liste des patients | 2. Ajouter un medecin               |\n");
    printf("|             3. Information sur le medecin |                                     |\n");
    printf("|                                                                                 |\n");
    printf("└---------------------------------------------------------------------------------┘\n");
    printf("Choix d'une option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 4));
    disableRawMode();
    system("clear");
    return atoi(&key);
}

/*
Méthode affichant le menu de l'option 2 du menu principal
elle retourne l'option choisi par l'utilisateur
*/
int MenuHoraire()
{
    enableRawMode();
    printf("┌---------------------------------------------------------------------------------┐\n");
    printf("|                                                                                 |\n");
    printf("|             1. Liste des rendez-vous      | 2. Horaire de la semaine            |\n");
    printf("|                                                                                 |\n");
    printf("└---------------------------------------------------------------------------------┘\n");
    printf("Choix d'une option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 3));
    disableRawMode();
    system("clear");
    return atoi(&key);
}

/*
Méthode affichant le menu de l'option 4 du menu principal
*/
void MenuAnnulation(int nbMed, medecin *Mdeb, medecin *Mcurant, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    enableRawMode();
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|                  1. Annulation par date, heure et Patient                       |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 2));
    disableRawMode();
    system("clear");

    switch (atoi(&key))
    {
    case 1:
        annulation_par_patient(nbMed,Mdeb, Mcurant,nbRed, Rdeb, Rcurant);
        break;
    }
}