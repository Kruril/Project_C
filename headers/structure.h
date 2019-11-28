#pragma once

typedef struct medecin
{
    char nom[21], specialite[21], numInami[11], numGSM[11];
    struct horaire *horaireRend;
    struct medecin *suivant;

} medecin;

typedef struct patient
{
    char nom[21], prenom[21], numGSM[11], nomMedecin[21], idRegistre[12];
    int codePostal;
    struct patient *suivant;
} patient;

typedef struct horaire
{
    /*heure prise de rendez-vous toutes les 30 minutes*/
    // char date[11];
    // nbConsultation = 14 par default car 14 consultation par jour max 9h->12h
    // 13h-> 17h 
    int mois,annee, nbConsultation;
    struct jour jour[8];
    struct horaire *suivant;
} horaire;

typedef struct jour
{
    int heure[8], minutes[3];
};

