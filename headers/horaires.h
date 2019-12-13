#pragma once

void optionHoraire(int, int, struct medecin *, struct medecin *, int, struct rendezvous *, struct rendezvous *,int);
void listeRendezvous(int, struct medecin *, struct medecin *, int, rendezvous *Rdeb, rendezvous *Rcurant);
void horaireSemaine(int, struct medecin *, struct medecin *, int);
void horairePropreMedecin(int, struct medecin *, struct medecin *, int, int);
bool EncodageDate(int *, int *, int *);
int DerterminationJour(int, int, int);
const char *listJourSemaine[7];
bool check_date(int, int, int);
