#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

#include "headers/commun.h"
#include "headers/structure.h"
#include "headers/horaires.h"
#include "headers/patient.h"
#include "headers/medecin.h"

//key est une variable global permetant de choisir le numéro souhaité
char key;

/*
Méthode qui va regarder quelle option a été choisi précedement et 
transmetre les différente valeur utile pour soit voir les patients 
d'un médecin soit ajouter un médecin soit voir les informations
personnelles d'un medecin
*/
void optionMedecin(int value, int nbPat, patient *Pdeb, patient *Pcurant, int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    switch (value)
    {
    case 1:
        patient_de_medecin(nbPat, Pdeb, Pcurant, nbMed, Mdeb, Mcurant);
        break;

    case 2:
        break;
    case 3:
        infoMedecin(nbMed, Mdeb, Mcurant);
        break;
    }
}

/*
Méthode qui permet d'afficher la liste des medecins présent 
dans le cabinet. La méthode affiche le numéro du médecin 
(qui permetra par la suite de selectionne le medecin), son 
nom et sa spécialité.
*/
void listeMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    int i;
    printf("Num |         Nom          |      Specialite      |\n");
    printf("----|----------------------|----------------------|\n");
    Mcurant = Mdeb;
    for (i = 1; i <= nbMed; i++)
    {
        printf(" %02d | %-21s| %-21s|\n", i, Mcurant->nom, Mcurant->specialite);
        Mcurant = Mcurant->suivant;
    }
    printf("\n");
}

/*
Méthode qui va prendre les rendez-vous. elle fait appel a diéfferente 
méthode comme la listeMedecin, horaireSemaine, ...
*/
void PrendRendVous(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();
    int jour, mois, annee, jourSemaine;
    bool date = false;

    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Numero du medecin pour prendre le rendez-vous?");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed+1));
    disableRawMode();
    if (atoi(&key) == nbMed + 1)
        return;
    system("clear");
    horaireSemaine(atoi(&key), Mdeb, Mcurant, 7);

    do
    {
        date = EncodageDate(&jour, &mois, &annee);
    } while (date == false || check_date(jour, mois, annee) == false);

    jourSemaine = DerterminationJour(jour, mois, annee);

    printf("Horaire disponible pour le %s %02d/%02d/%4d : \n", listJourSemaine[jourSemaine-1], jour, mois, annee);


}

/*
Méthode affichant les informations personnelles du médecin 
*/
void infoMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    enableRawMode();

    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Choisiser un medecin : ");
    fflush(stdout);
    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed + 1));
    Mcurant = Mdeb;
    for (int i = 1; i < atoi(&key); i++)
    {
        Mcurant = Mcurant->suivant;
    }
    
    system("clear");

    printf("Fiche technique de medecin : %-s\n\n", Mcurant->nom);
    printf("|-----------------------------------------------|\n");
    printf("|Domaine de la medecine : %-15s       |\n",Mcurant->specialite);
    printf("|-----------------------------------------------|\n");
    printf("|Num. pour le remboursement mutuel : %-s |\n",Mcurant->numInami);
    printf("|-----------------------------------------------|\n");
    printf("|Numéro de contact : %-16s           |\n", Mcurant->numGSM);
    printf("|-----------------------------------------------|\n\n");
    disableRawMode();
    horairePropreMedecin(atoi(&key),Mdeb,Mcurant,7);

}