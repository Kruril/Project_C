#pragma once
#include <stdbool.h>

void patient_de_medecin(int, struct patient *, struct patient *, int, struct medecin *, struct medecin *);
void listepatient(const char *, int, struct patient *, struct patient *);
bool estPatient(const char *, const char *, int, struct patient *, struct patient *);
void annulation_par_patient(int, struct medecin *, struct medecin *, int, struct rendezvous *, struct rendezvous *);
bool rendezVous_for_annulation(const char *, const char *, int , int ,int , int , int , int, rendezvous *, rendezvous *);
void validationRemoveRendezVous(const char *, const char *, int, int, int, int, int, int, rendezvous *, rendezvous *);
void remove_to_list(int, int, rendezvous *, rendezvous *);