#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int posicaoColuna, posicaoLinha;
    int dado;   //0 - vazio     1 - brancas     2-pretas -> 3 - Dama branca     4 - Dama preta
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
tabuleiro *copiaTabuleiro(tabuleiro *ptrOrg);
//Retorna 1 ou 2 se existe uma peça na linha e coluna indicados, 1 para peças brancas, 2 para peças pretas e 0 se a posição está livre. -1 caso a posição seja inválida
int buscaLista(nodo *ptrLista, int linha, int coluna);
//Retorna o ponteiro da posição na lista da linha e coluna fornecidas
nodo *retornaPonteiro(nodo* ptrLista, int linha, int coluna);
