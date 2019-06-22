#include "Tabuleiro.h"
#include <string.h>

tabuleiro *inicializa()
{
    tabuleiro *t = (tabuleiro *)malloc(sizeof(tabuleiro));
    t->tab = NULL;

    return t;
}

void inicializa2(tabuleiro *t)
{
    //tabuleiro *t = (tabuleiro *)malloc(sizeof(tabuleiro));
    t->tab = NULL;
}

nodo *criaNodo(int indice, int linha)
{
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    int parInd = indice % 2;
    int parLn = linha % 2;
    if (linha <= 2) //as linhas preenchidas com peças brancas
    {
        novo->posicaoLinha = linha;
        if (indice < 4)
            novo->posicaoColuna = indice % 4;
        else
            novo->posicaoColuna = (indice % 4) + 4;

        if (parLn == 0)
        {
            if (parInd == 0) //insere as peças brancas
                novo->dado = 1;
            else //insere os zeros das 3 primeiras lihas
                novo->dado = 0;
        }
        else
        {
            if (parInd == 0) //insere as peças brancas
                novo->dado = 0;
            else //insere os zeros das 3 primeiras lihas
                novo->dado = 1;
        }
    }
    else if (linha > 2 && linha < 5) //linhas que ficam vazias na posição inicial
    {
        novo->posicaoLinha = linha;
        novo->dado = 0;

        if (indice < 4)
            novo->posicaoColuna = indice % 4;
        else
            novo->posicaoColuna = (indice % 4) + 4;
    }
    else //insere as peças pretas
    {
        novo->posicaoLinha = linha;
        if (indice < 4)
            novo->posicaoColuna = indice % 4;
        else
            novo->posicaoColuna = (indice % 4) + 4;

        if (parLn == 0)
        {
            if (parInd == 0) //insere as peças pretas
                novo->dado = 2;
            else //insere os zeros das 3 ultimas lihas
                novo->dado = 0;
        }
        else
        {
            if (parInd == 0) //insere as peças pretas
                novo->dado = 0;
            else //insere os zeros das 3 ultimas lihas
                novo->dado = 2;
        }
    }

    novo->prox = NULL;

    return novo;
}

nodo *inicioTabuleiro(nodo *lista, int indice, int linha)
{
    if (lista == NULL)
        return criaNodo(indice, linha);

    lista->prox = inicioTabuleiro(lista->prox, indice, linha);

    return lista;
}

void imprimeTabuleiro(nodo *lista)
{
    if (lista != NULL)
    {
        printf("Linha: %d Coluna: %d Peça: %d\n", lista->posicaoLinha, lista->posicaoColuna, lista->dado);
        imprimeTabuleiro(lista->prox);
    }
}

void ImprimePeca(nodo *lista, int flag)
{
    if (lista != NULL)
    {
        if (lista->dado == flag)
            printf("Linha: %d Coluna: %d \n", lista->posicaoLinha, lista->posicaoColuna);

        ImprimePeca(lista->prox, flag);
    }
}

nodo *copiaLista(nodo *ptrOrigem)
{
    if (ptrOrigem == NULL)
        return NULL;

    nodo *novo = (nodo *)malloc(sizeof(nodo));

    novo->posicaoColuna = ptrOrigem->posicaoColuna;
    novo->posicaoLinha = ptrOrigem->posicaoLinha;
    novo->dado = ptrOrigem->dado;
    novo->prox = copiaLista(ptrOrigem->prox);

    return novo;
}

tabuleiro *copiaTabuleiro(tabuleiro *ptrOrg)
{
    if (ptrOrg == NULL)
        return NULL;

    tabuleiro *novo = inicializa();

    novo->tab = copiaLista(ptrOrg->tab);

    return novo;
}

int buscaLista(nodo *ptrLista, int linha, int coluna)
{
    nodo *aux = ptrLista;
    while (aux != NULL)
    {
        if (aux->posicaoColuna == coluna && aux->posicaoLinha == linha)
        {
            return aux->dado;
        }
        else
        {
            aux = aux->prox;
        }
    }
    return -1;
}

nodo *retornaPonteiro(nodo *ptrLista, int linha, int coluna)
{
    nodo *aux = ptrLista;
    while (aux != NULL)
    {
        if (aux->posicaoColuna == coluna && aux->posicaoLinha == linha)
        {
            return aux;
        }
        else
        {
            aux = aux->prox;
        }
    }
    return NULL;
}