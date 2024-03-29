#pragma once
#include <stdbool.h>

void optionMedecin(int, int, struct patient *, struct patient *, int, struct medecin *, struct medecin *, FILE *, FILE *);
void listeMedecin(int, struct medecin *, struct medecin *);
void PrendRendVous(int, struct medecin *, struct medecin *, int, struct rendezvous *, struct rendezvous *, int, struct patient *, struct patient *);
void infoMedecin(int, medecin *, medecin *);
void addMedecin(int, medecin *, medecin *, FILE *, FILE *);
bool check_Inami(const char *, int, medecin *, medecin *);
bool check_GSM(const char *);
void validationAddMedecin(const char *, const char *, const char *, const char *, horaire *, int , medecin *, medecin *, FILE *, FILE *);
void remove_jumpLine(char *, int);
void remove_space(char *);
void add_medecin_to_list(const char *, const char *, const char *, const char *, horaire *, int, medecin *, medecin *, FILE *, FILE *);
void rdvPrecis(int, struct medecin *, struct medecin *, int, struct rendezvous *, struct rendezvous *, int, int, int);
bool estLibre(struct medecin *, int, int, int, int, int, int, struct rendezvous *, struct rendezvous *);
void enregistrer(struct rendezvous *);
bool checkMed(const char *, int, struct medecin *, struct medecin *);
bool checkId(const char *, int, patient *, patient *, const char *);
void addPatient(int, patient *, patient *, int, medecin *, medecin *);
void validationAddPatient(const char *, const char *, const char *, const char *, const char *, int, int, patient *, patient *);
void add_patient_to_list(const char *, const char *, const char *, const char *, const char *, int, int, patient *, patient *);