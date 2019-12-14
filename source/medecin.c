#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

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
void optionMedecin(int value, int nbPat, patient *Pdeb, patient *Pcurant, int nbMed, medecin *Mdeb, medecin *Mcurant, FILE *fMedecin,
                   FILE *fHoraire)
{
    switch (value)
    {
    case 1:
        patient_de_medecin(nbPat, Pdeb, Pcurant, nbMed, Mdeb, Mcurant);
        break;

    case 2:
        addMedecin(nbMed, Mdeb, Mcurant, fMedecin, fHoraire);
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
void PrendRendVous(int nbMed, medecin *Mdeb, medecin *Mcurant, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant, int nbPat, patient *Pdeb, patient *Pcurant)
{
    enableRawMode();
    int jour, mois, annee, jourSemaine;
    bool date = false;
    rendezvous *rdv;

    listeMedecin(nbMed, Mdeb, Mcurant);
    printf("Numero du medecin pour prendre le rendez-vous?");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed + 1))
        ;
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

    printf("Horaire disponible pour le %s %02d/%02d/%4d : \n", listJourSemaine[jourSemaine - 1], jour, mois, annee);

    rdvPrecis(atoi(&key), Mdeb, Mcurant, nbRed, Rdeb, Rcurant, jour, mois, annee);

    int heure, min, heuredeb, heurefin, i;
    char idRegistre[20], heureChar[10], minChar[10];

    Mcurant = Mdeb;
    for (i = 1; i < atoi(&key); i++)
    {
        Mcurant = Mcurant->suivant;
    }

    heuredeb = Mcurant->horaire.heureDeb[jourSemaine];
    heurefin = Mcurant->horaire.heureFin[jourSemaine];
    while (true)
    {
        printf("%02dh - %02dh  choisissez un heure comprise entre les deux heures proposé ulterieurement \n\n ", heuredeb, heurefin);

        do
        {
            fgets(heureChar, 10, stdin);
        } while (atoi(heureChar) == 0 || strlen(heureChar) > 3);
        heure = atoi(heureChar);
        fflush(stdin);

        if (heure < heuredeb || heure > heurefin)
        {
            printf("heure invalide\n");
            continue;
        }
        printf("attention vueillez prendre un rendez-vous les heures pile (0) ou les demi heure(30) \n\n");

        do
        {
            fgets(minChar, 10, stdin);
            if (strlen(minChar) == 2 && (!(minChar[0] >= 'a') || !(minChar[0] <= 'z')) &&
                (!(minChar[0] >= 'A') || !(minChar[0] <= 'Z')))
                break;

            if (atoi(minChar) != 30)
            {
                printf("choisissez les heures pile (0) ou les demi heure(30)\n");
            }
        } while (atoi(minChar) == 0 || strlen(minChar) > 3 || atoi(minChar) != 30);
        min = atoi(minChar);
        fflush(stdin);

        printf("vous avez choisis l'heure suivante : %02d h %02d \n\n", heure, min);
        Mcurant = Mdeb;
        for (i = 1; i < atoi(&key); i++)
        {
            Mcurant = Mcurant->suivant;
        }
        if (!estLibre(Mcurant, annee, mois, jour, heure, min, nbRed, Rdeb, Rcurant))
        {
            printf("cette heure est déjà occupée \n");
            continue;
        }
        listepatient(Mcurant->nom, nbPat, Pdeb, Pcurant);

        printf("entrez l'id du patient \n");

        do
        {
            fgets(idRegistre, 20, stdin);

            idRegistre[11] = '\0';
            if (!estPatient(Mcurant->nom, idRegistre, nbPat, Pdeb, Pcurant))
            {
                printf("patient incorrect \n");
            }

        } while (!estPatient(Mcurant->nom, idRegistre, nbPat, Pdeb, Pcurant));

        Pcurant = Pdeb;
        for (i = 1; i < nbPat; i++)
        {
            Pcurant = Pcurant->suivant;
            if (strcmp(Pcurant->idRegistre, idRegistre) == 0)
            {
                break;
            }
        }
        rdv = malloc(sizeof(rendezvous));
        strcpy(rdv->nomPatient, Pcurant->nom);
        strcpy(rdv->prenomPatient, Pcurant->prenom);
        strcpy(rdv->nomMedecin, Mcurant->nom);
        rdv->jour = jour;
        rdv->mois = mois;
        rdv->annee = annee;
        rdv->heure = heure;
        rdv->minutes = min;
        printf(" décrivez la raison de la visite en bref \n");
        fgets(rdv->note, 42, stdin);
        rdv->suivant = NULL;
        i = 0;
        while (rdv->note[i] != '\n')
        {
            i++;
        }
        rdv->note[i] = '\0';

        break;
    }
    Rcurant = Rdeb;
    for (i = 1; i < nbRed; i++)
    {
        Rcurant = Rcurant->suivant;
    }
    Rcurant->suivant = rdv;
    enregistrer(rdv);

    printf("\nAppuyer sur entrer pour revenir au menu principal");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && key != 10)
        ;
    disableRawMode();
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
    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > nbMed + 1))
        ;
    Mcurant = Mdeb;
    for (int i = 1; i < atoi(&key); i++)
    {
        Mcurant = Mcurant->suivant;
    }

    system("clear");

    printf("Fiche technique de medecin : %-s\n\n", Mcurant->nom);
    printf("|-----------------------------------------------|\n");
    printf("|Domaine de la medecine : %-15s       |\n", Mcurant->specialite);
    printf("|-----------------------------------------------|\n");
    printf("|Num. pour le remboursement mutuel : %-s |\n", Mcurant->numInami);
    printf("|-----------------------------------------------|\n");
    printf("|Numéro de contact : %-16s           |\n", Mcurant->numGSM);
    printf("|-----------------------------------------------|\n\n");
    disableRawMode();
    horairePropreMedecin(atoi(&key), Mdeb, Mcurant, 7, nbMed);
}

/*
Méthode qui va demander les informations d'un medecin pour pouvoir
l'ajouter au medecin du cabinet. Il est tout de fois impossible d'ajouter
plus de 8 medecin. Si on essaie de rajouter un medecin de plus un 
message d'erreur nous dira que le nombre de medecin que peut acceuillir 
le batiment est complet. 
*/
void addMedecin(int nbMed, medecin *Mdeb, medecin *Mcurant, FILE *fMedecin, FILE *fHoraire)
{
    char nom[21], specialite[21], numInami[11], numGSM[11];
    horaire horaire;

    if (nbMed >= 8)
    {
        printf("Impossible de rajouter un medecin le batiment est plein\n");
    }
    else
    {
        // Nom du medecin
        printf("Entrer le nom du medecin : ");
        fgets(nom, 22, stdin);
        remove_jumpLine(nom, 22);
        //Specialite
        printf("\nEntrer son domaine : ");
        fgets(specialite, 22, stdin);
        remove_jumpLine(specialite, 22);

        do
        {
            printf("\nEntrer le numero inami (xxxx-xxxxx): ");
            fgets(numInami, 12, stdin);
            numInami[10] = '\0';
        } while (check_Inami(numInami, nbMed, Mdeb, Mcurant) == false);

        do
        {
            printf("\nEntrer le numero de GSM (04xxxxxxxx): ");
            fgets(numGSM, 12, stdin);
            numGSM[10] = '\0';
        } while (check_GSM(numGSM) == false);

        printf(" \n/!\\ L'HEURE DE DEBUT ET DE FIN SONT DES HEURES PILE /!\\");

        char heureDeb[10], heureFin[10];

        for (int i = 1; i <= 7; i++)
        {
            do
            {
                printf("\nEntrer l'heure du début (x ou xx) pour %s : ", listJourSemaine[i - 1]);
                scanf("%s", heureDeb);
            } while (atoi(heureDeb) == 0 || strlen(heureDeb) > 2);
            horaire.heureDeb[i] = atoi(heureDeb);

            do
            {
                printf("\nEntrer l'heure du Fin (x ou xx) pour %s : ", listJourSemaine[i - 1]);
                scanf("%s", heureFin);
            } while (atoi(heureFin) == 0 || strlen(heureFin) > 2);
            horaire.heureFin[i] = atoi(heureFin);
        }

        validationAddMedecin(nom, specialite, numInami, numGSM, &horaire, nbMed, Mdeb, Mcurant, fMedecin, fHoraire);
    }
}

/*
Méthode qui vérifie que le num Inami encoder lors de l'ajout d'un medecin
n'est pas déjà encoder dans la base de données
*/
bool check_Inami(const char *numInami, int nbMed, medecin *Mdeb, medecin *Mcurant)
{
    Mcurant = Mdeb;
    if (numInami[4] != '-')
        return false;
    for (int i = 1; i < nbMed; i++)
    {
        if (strcmp(numInami, Mcurant->numInami) == 0)
        {
            return false;
        }
        Mcurant = Mcurant->suivant;
    }
    return true;
}

/*
Transforme le numero en chiffre si il contient des lettres la valeur 
sera de 0 la méthode renvoie alors false sinon c'est qu'il a que des 
chiffres alors il renvoie true
*/
bool check_GSM(const char *numGSM)
{
    if (numGSM[0] != '0' || numGSM[1] != '4')
        return false;
    if (atoi(numGSM) == 0)
        return false;
    return true;
}

/*
Méthode qui affiche toutes les inforamtions du nouveau medecin et demande 
à l'utilisateur si oui ou non il veut enregistrer les informations. SI oui 
le nouveau medecin sera ajouter à la liste des medecin du cabinet
*/
void validationAddMedecin(const char *nom, const char *specialite, const char *numInami, const char *numGSM,
                          horaire *horaire, int nbMed, medecin *Mdeb, medecin *Mcurant, FILE *fMedecin, FILE *fHoraire)
{
    system("clear");
    printf("|-----------------------------------------------|\n");
    printf("|------Information sur le nouveau medecin-------|\n");
    printf("|-----------------------------------------------|\n");
    printf("|Nom du nouveau medecin :  %-21s|\n", nom);
    printf("|-----------------------------------------------|\n");
    printf("|Domaine du nouveau medecin : %-11s       |\n", specialite);
    printf("|-----------------------------------------------|\n");
    printf("|Num. pour le remboursement mutuel : %-s |\n", numInami);
    printf("|-----------------------------------------------|\n");
    printf("|Numéro de contact : %-16s           |\n", numGSM);
    printf("|-----------------------------------------------|\n");

    printf("|       Jour      |  Heure debut  |  Heure fin  |\n");
    printf("|-----------------|---------------|-------------|\n");

    for (int i = 1; i <= 7; i++)
    {
        printf("|      %-9s  |     %02d:00     |    %02d:00    |\n", listJourSemaine[i - 1], horaire->heureDeb[i],
               horaire->heureFin[i]);
    }
    printf("|-----------------------------------------------|\n\n");

    enableRawMode();
    printf("Voulez-vous valider l'ajout du medecin ? \n 1. OUI\n 2. NON");
    fflush(stdout);

    while (read(STDIN_FILENO, &key, 1) == 1 && (atoi(&key) < 1 || atoi(&key) > 2))
        ;
    disableRawMode();

    if (atoi(&key) == 1)
        add_medecin_to_list(nom, specialite, numInami, numGSM, horaire, nbMed, Mdeb, Mcurant, fMedecin, fHoraire);
}

/*
Méthode qui supprime le saut de lignes à la fin d'une chaine de caractere
lu via un fgets
*/
void remove_jumpLine(char *valeur, int tailleMax)
{
    for (int i = 0; i < tailleMax; i++)
    {
        if (valeur[i] == '\n')
        {
            valeur[i] = '\0';
            break;
        }
    }
}

/*
Méthode qui ajoute à la fin de la liste chainée le nouveau medecin 
*/
void add_medecin_to_list(const char *nom, const char *specialite, const char *numInami, const char *numGSM,
                         horaire *horaire, int nbMed, medecin *Mdeb, medecin *Mcurant, FILE *fMedecin, FILE *fHoraire)
{
    medecin *MNouveau;
    // Aller au dernier medecin
    Mcurant = Mdeb;
    for (int i = 1; i < nbMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }

    //Ajout à la liste chainée du programme actuel
    MNouveau = malloc(sizeof(medecin));
    Mcurant->suivant = MNouveau;
    Mcurant = MNouveau;
    Mcurant->suivant = NULL;
    strcpy(Mcurant->nom, nom);
    strcpy(Mcurant->specialite, specialite);
    strcpy(Mcurant->numInami, numInami);
    strcpy(Mcurant->numGSM, numGSM);
    Mcurant->horaire = *horaire;

    //Ajout dans le fichier de données fMedecin
    fprintf(fMedecin, "%-20s%-20s%10s %10s\n", Mcurant->nom, Mcurant->specialite, Mcurant->numInami, Mcurant->numGSM);

    //Ajout dans le fichier de données fHoraire
    fprintf(fHoraire, "%s\n", Mcurant->nom);
    for (int i = 1; i <= 7; i++)
    {
        fprintf(fHoraire, "%02d%02d\n", Mcurant->horaire.heureDeb[i], Mcurant->horaire.heureFin[i]);
    }
}

void enregistrer(rendezvous *rdv)
{
    FILE *fres;
    fres = fopen("Save/rendez_vous.res", "a+");

    fprintf(fres, "%-20s%-20s%-20s%2d%2d%4d %02d%02d %-40s\n", rdv->nomMedecin, rdv->nomPatient, rdv->prenomPatient, rdv->jour,
            rdv->mois, rdv->annee, rdv->heure, rdv->minutes, rdv->note);

    fclose(fres);
}
bool estLibre(medecin *medecin, int annee, int mois, int jour, int heure, int min, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant)
{
    int i;

    Rcurant = Rdeb;
    for (i = 1; i <= nbRed; i++)
    {

        if (strcmp(medecin->nom, Rcurant->nomMedecin) == 0)
        {

            if ((Rcurant->annee == annee) && (Rcurant->mois == mois) && (Rcurant->jour == jour) && (Rcurant->heure == heure) && (Rcurant->minutes == min))
            {
                return false;
            }
        }
        Rcurant = Rcurant->suivant;
    }

    return true;
}

void rdvPrecis(int numMed, medecin *Mdeb, medecin *Mcurant, int nbRed, rendezvous *Rdeb, rendezvous *Rcurant, int jour, int mois, int annee)
{

    int i;
    Mcurant = Mdeb;
    for (i = 1; i < numMed; i++)
    {
        Mcurant = Mcurant->suivant;
    }

    printf("Rendez du medecin %-s : \n\n", Mcurant->nom);
    printf("   Date    | Heure |             Patient             |                  Note                  |\n");
    printf("-----------|-------|---------------------------------|----------------------------------------|\n");
    Rcurant = Rdeb;
    for (i = 1; i <= nbRed; i++)
    {
        if (strcmp(Mcurant->nom, Rcurant->nomMedecin) == 0)
        {
            if ((Rcurant->annee == annee) && (Rcurant->mois == mois) && (Rcurant->jour == jour))
            {
                printf("%02d/%02d/%4d | %02d:%02d |   %-13s %-13s   |%40s|\n", Rcurant->jour, Rcurant->mois, Rcurant->annee,
                       Rcurant->heure, Rcurant->minutes, Rcurant->nomPatient, Rcurant->prenomPatient, Rcurant->note);
            }
        }
        Rcurant = Rcurant->suivant;
    }
    printf("\n");
}