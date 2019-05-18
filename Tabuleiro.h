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
nodo *criaNodo(int indice, int linha);
nodo *inicioTabuleiro(nodo *lista, int indice, int linha);
void imprimeTabuleiro(nodo *lista);