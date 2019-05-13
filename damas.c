#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

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

tabuleiro *inicializa()
{
    tabuleiro *t = (tabuleiro *)malloc(sizeof(tabuleiro));
    t->tab=NULL;

    return t;
}

nodo *criaNodo(int indice, int linha)
{
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    int parInd = indice%2;
    int parLn = linha%2;
    if(linha <=2) //as linhas preenchidas com peças brancas
    {
        novo->posicaoLinha = linha;
        if(indice < 4)
            novo->posicaoColuna = indice%4;
        else
            novo->posicaoColuna = (indice%4) + 4;

        if(parLn == 0)
        {
            if (parInd == 0)   //insere as peças brancas
                novo->dado = 1;
            else //insere os zeros das 3 primeiras lihas
                novo->dado = 0; 
        }else
        {
            if (parInd == 0)   //insere as peças brancas
                novo->dado = 0;
            else //insere os zeros das 3 primeiras lihas
                novo->dado = 1; 
        }
        
         
        
    }else if(linha > 2 &&linha < 5) //linhas que ficam vazias na posição inicial
    {
        novo->posicaoLinha = linha;
        novo->dado = 0;

        if(indice < 4)
            novo->posicaoColuna = indice%4;
        else
            novo->posicaoColuna = (indice%4) + 4;
    }else   //insere as peças pretas
    {
        novo->posicaoLinha = linha;
        if(indice < 4)
            novo->posicaoColuna = indice%4;
        else
            novo->posicaoColuna = (indice%4) + 4;

        if(parLn == 0)
        {
            if (parInd == 0)   //insere as peças pretas
                novo->dado = 2;
            else //insere os zeros das 3 ultimas lihas
                novo->dado = 0; 
        }else
        {
            if (parInd == 0)   //insere as peças pretas
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
    if(lista == NULL)
        return criaNodo(indice, linha);

    lista->prox = inicioTabuleiro(lista->prox, indice, linha);

    return lista;
}

void imprimeTabuleiro(nodo *lista)
{
    if(lista != NULL)
    {
        printf("Linha: %d Coluna: %d Peça: %d\n",lista->posicaoLinha, lista->posicaoColuna, lista->dado);
        imprimeTabuleiro(lista->prox);
    }
}

/*void ImprimePeca(nodo *lista, int flag)
{
    if(lista != NULL)
    {
        if(lista->dado == flag)
            printf("Linha: %d Coluna: %d \n",lista->posicaoLinha, lista->posicaoColuna);

        ImprimePeca(lista->prox);
    }
}*/

int main()
{
    int i;
    //inicia o tabuleiro com nulos
    tabuleiro *t = inicializa();

    //se for brancas flag=0 (são os Maximos).... pretas flag =1
    int linha = 0;
    while(linha < 8)
    {
        for(i = 0; i < 8; i++)
        {
            t->tab = inicioTabuleiro(t->tab, i,linha);
        }
        linha ++;
    }
    
        
    printf("-------------todas-----------\n");
    imprimeTabuleiro(t->tab);
    printf("\n\n-------------pretas-----------");
    //imprime(t->pretas);

    /*Arvore arv;
    criaArvore(&arv);

    Insere_Pai(&arv, 0, 0, 50);
    Insere_Pai(&arv, 50, 0, 20);
    Insere_Pai(&arv, 20, 0, 100);
    Insere_Pai(&arv, 50, 1, 10);
    Insere_Pai(&arv, 20, 1, 11);
    Insere_Pai(&arv, 50, 2, 30);

    Caminha_Pre_Fixado(&arv);  
    printf("Teste!\n");
    //int res = 0;
    consulta(&arv, 11);
    if(res == 1)
        printf("Elemento encontrado\n");
    else
        printf("Valor não encontrado");*/
    return 0;
}
