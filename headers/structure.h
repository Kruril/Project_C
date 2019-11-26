#pragma once

typedef struct medecin
{
    char nom[21],specialite[21],numInami[11];
    struct horaire *horaireRend;
    struct patient *patient;

}medecin;

typedef struct patient
{
    char nom[21],numGSM[11];
    long idRegistre;
    int codePostal;
    struct patient *suivant;
}patient;

typedef struct horaire
{
    /*heure prise de rendez-vous toutes les 30 minutes*/
    char date[11], heure[6];
    struct horaire *suivant;
}horaire;
