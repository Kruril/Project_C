#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "headers/commun.h"
#include "headers/structure.h"
#include "headers/medecin.h"

char key;
int MenuPrincipal()
{
    enableRawMode();
    system("clear");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|                 1. Prendre rendez-vous | 2. Voir les horaires                   |\n");
    printf("|                 3. Liste medecin       | 4. Annulation d'un rendez-vous         |\n");
    printf("|                 5. Information logiciel| 6. Quitter le programme                |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Numero de l'option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 6));
    disableRawMode();
    system("clear");
    return atoi(&key);
}
int MenuMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();
    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|             1. Voir la liste des patients | 2. Ajouter un medecin               |\n");
    printf("|             3. Information sur le medecin |                                     |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 4));
    disableRawMode();
    system("clear");
    return atoi(&key);
}

int MenuHoraire()
{
    enableRawMode();
    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                 |\n");
    printf("|             1. Liste des rendez-vous      | 2. Horaire de la semaine            |\n");
    printf("|                                                                                 |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Choix d'une option : ");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 3));
    disableRawMode();
    system("clear");
    return atoi(&key);
}