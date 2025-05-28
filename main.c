#include <stdio.h>
#include <stdlib.h>
#include "functii.h"

int N, M, T, K;
char grila[MAXN][MAXN + 1];

void salveaza_generatie(const char *nume, char grila[MAXN][MAXN + 1]) {
    FILE *f = fopen(nume, "w");
    if (!f) return;
    for (int i = 0; i < N; i++)
        fprintf(f, "%s\n", grila[i]);
    fclose(f);
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Eroare la deschiderea input.txt");
        return 1;
    }

    fscanf(fin, "%d", &T);
    fscanf(fin, "%d %d", &N, &M);
    fscanf(fin, "%d", &K);

    for (int i = 0; i < N; i++)
        fscanf(fin, "%s", grila[i]);
    fclose(fin);

    Node *rad = creeaza_nod(grila);
    genereaza_generatii(rad, K);

    FILE *fout = fopen("output.txt", "w");
    if (!fout) {
        perror("Eroare la deschiderea output.txt");
        return 1;
    }

    afiseaza_generatii(rad, fout);
    elibereaza_arbore(rad);

    fclose(fout);
    return 0;
}