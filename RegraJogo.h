#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"
#define tam 64 //tamanho do tabuleiro


int CapturaDir(nodo *no, int vetor[]);

int CapturaEsq(nodo *no, int vetor[]);


//retorna em vetor quais são as colunas disponiveis para que o nó possa ir
void Possibilidades2(tabuleiro *_tab, nodo *no, int vetor[]);
void GeraArvoreBrancas(tabuleiro *t, Arvore *arv);