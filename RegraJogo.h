#include "Arvore.h"

typedef struct Mov
{
    int liEsq;
    int colEsq;
    int pontEsq;
    int liDir;
    int colDir;
    int pontDir;
}Mov;


int CapturaDir(nodo *no, Mov *dados);
int CapturaEsq(nodo *no, Mov *dados);
void Possibilidades(tabuleiro *_tab, nodo *no, Mov *dados);
void GeraArvoreBrancas(tabuleiro *t, Arvore *arv);
void GeraArvorePretas(tabuleiro *t, Arvore *arv);