#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int posicaoColuna, posicaoLinha;
    struct nodo *prox;
}nodo;

typedef struct
{
    nodo *brancas;
    nodo *pretas;
}tabuleiro;

tabuleiro *inicializa()
{
    tabuleiro *t = (tabuleiro *)malloc(sizeof(tabuleiro));
    t->brancas = t->pretas = NULL;

    return t;
}

nodo *criaNodo(int indice, int flag)
{
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    novo->posicaoColuna = indice%4; 
    flag ? (novo->posicaoLinha = 9 + indice / 4) : (novo->posicaoLinha = indice / 4);
    novo->prox = NULL;

    return novo;
}

nodo *preenche(nodo *lista, int indice, int flag)
{
    if(lista == NULL)
        return criaNodo(indice, flag);

    lista->prox = preenche(lista->prox, indice, flag);

    return lista;
}

void imprime(nodo *lista)
{
    if(lista != NULL)
    {
        printf("Coluna: %d Linha: %d\n",lista->posicaoColuna, lista->posicaoLinha);
        imprime(lista->prox);
    }
}

int main()
{
    int i;
    tabuleiro *t = inicializa();


    for(i = 0; i < 12; i++)
    {
        t->brancas = preenche(t->brancas, i, 0);
        t->pretas = preenche(t->pretas, i, 1);
    }
        

    imprime(t->brancas);
    imprime(t->pretas);

    

    printf("Teste!\n");
    return 0;
}
