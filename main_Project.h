#pragma once

// Déclaration des différentes fonctions
void MenuPrincipal();

// Déclaration des différentes structures
typedef struct medecin
{
    char nom[21],specialite[21],numInami[11];
    struct patient *patient;

}medecin;
typedef struct patient
{
    char nom[21];
    long idRegistre;
    struct patient *suivant;
}patient;