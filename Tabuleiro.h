#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int posicaoColuna, posicaoLinha;
    int dado;   //0 - vazio     1 - brancas     2-pretas
    struct nodo *prox;
}nodo;

typedef struct
{
    nodo *tab;
}tabuleiro;

tabuleiro *inicializa();
void inicializa2(tabuleiro *t);
nodo *criaNodo(int indice, int linha);
nodo *inicioTabuleiro(nodo *lista, int indice, int linha);
void ImprimePeca(nodo *lista, int flag);
void imprimeTabuleiro(nodo *lista);
nodo *copiaLista(nodo *ptrOrigem);