#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};

Node *creeaza_nod(char grila[MAXN][MAXN + 1]) {
    Node *nod = malloc(sizeof(Node));
    for (int i = 0; i < N; i++)
        strcpy(nod->grila[i], grila[i]);
    nod->stanga = NULL;
    nod->dreapta = NULL;
    return nod;
}

void regula_B(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int vecini = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && sursa[ni][nj] == 'X')
                    vecini++;
            }
            if (sursa[i][j] == 'X') {
                rezultat[i][j] = 'X';
            } else {
                rezultat[i][j] = (vecini == 2) ? 'X' : '+';
            }
        }
        rezultat[i][M] = '\0';
    }
}

void regula_clasica(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cnt = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && sursa[ni][nj] == 'X')
                    cnt++;
            }
            if (sursa[i][j] == 'X')
                rezultat[i][j] = (cnt == 2 || cnt == 3) ? 'X' : '+';
            else
                rezultat[i][j] = (cnt == 3) ? 'X' : '+';
        }
        rezultat[i][M] = '\0';
    }
}

void genereaza_generatii(Node *rad, int k) {
    if (k == 0) return;

    char stg[MAXN][MAXN + 1], drp[MAXN][MAXN + 1];
    regula_B(stg, rad->grila);
    regula_clasica(drp, rad->grila);

    rad->stanga = creeaza_nod(stg);
    rad->dreapta = creeaza_nod(drp);

    genereaza_generatii(rad->stanga, k - 1);
    genereaza_generatii(rad->dreapta, k - 1);
}

void afiseaza_generatii(Node *nod, FILE *fout) {
    if (!nod) return;

    for (int i = 0; i < N; i++)
        fprintf(fout, "%s\n", nod->grila[i]);
    fprintf(fout, "\n");

    afiseaza_generatii(nod->stanga, fout);
    afiseaza_generatii(nod->dreapta, fout);
}

void elibereaza_arbore(Node *nod) {
    if (!nod) return;
    elibereaza_arbore(nod->stanga);
    elibereaza_arbore(nod->dreapta);
    free(nod);
}