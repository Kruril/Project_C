#pragma once
#include <stdbool.h>

void patient_de_medecin(int, struct patient *, struct patient *, int, struct medecin *, struct medecin *);
void listepatient(const char *, int, struct patient *, struct patient *);
bool estPatient(const char *, const char *, int, struct patient *, struct patient *);