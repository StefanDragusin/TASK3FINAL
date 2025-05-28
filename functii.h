#ifndef FUNCTII_H
#define FUNCTII_H

#define MAXN 100

extern int N, M, T, K;

typedef struct Node {
    char grila[MAXN][MAXN + 1];
    struct Node *stanga, *dreapta;
} Node;

Node *creeaza_nod(char grila[MAXN][MAXN + 1]);
void regula_B(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]);
void regula_clasica(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]);
void genereaza_generatii(Node *rad, int k);
void afiseaza_generatii(Node *nod, FILE *fout);
void elibereaza_arbore(Node *nod);

#endif