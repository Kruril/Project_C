#pragma once

typedef struct horaire
{
    int heureDeb[8], heureFin[8];
} horaire;

typedef struct medecin
{
    char nom[21], specialite[21], numInami[11], numGSM[11];
    struct horaire horaire;
    struct medecin *suivant;

} medecin;

typedef struct patient
{
    char nom[21], prenom[21], numGSM[11], nomMedecin[21], idRegistre[12];
    int codePostal;
    struct patient *suivant;
} patient;

typedef struct rendezvous
{
    int jour, mois, annee, heure, minutes;
    char nomPatient[21], prenomPatient[21], nomMedecin[21], note[40];
    struct rendezvous *suivant;
} rendezvous;
