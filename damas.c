#include <stdio.h>
#include <stdlib.h>
#include "RegraJogo.h"
#define tam 64 //tamanho do tabuleiro


int main()
{
    int i;

    //inicia o tabuleiro com nulos
    tabuleiro *t = inicializa();
    tabuleiro *e = inicializa();

    //se for brancas flag=0 (são os Maximos).... pretas flag =1
    int linha = 0;
    while (linha < 8)
    {
        for (i = 0; i < 8; i++)
        {
            t->tab = inicioTabuleiro(t->tab, i, linha);
        }
        linha++;
    }
    
    Arvore *arv = (Arvore *) malloc(sizeof(Arvore));
    criaArvore(arv);
    Insere_Raiz(arv, t); //insere o tabuleiro inicial
    GeraArvoreBrancas(t, arv);
    //GeraArvorePretas(t, arv);

    //Caminha_Pre_Fixado(arv);

    //--------------------------------------------------------------------------
    //tabuleiro ficticio para testar captura de peças
    /*nodo *a = (nodo *)malloc(sizeof(nodo));
    e->tab = copiaLista(t->tab);
    a = e->tab;
    int o;
    for (o = 0; i < 35; i++)
        a = a->prox;

    printf("li: %d col: %d\n", a->posicaoLinha, a->posicaoColuna);
    a->dado = 2;
    //imprimeTabuleiro(e->tab);
    Arvore *arv2 = (Arvore *) malloc(sizeof(Arvore));
    criaArvore(arv2);
    Insere_Raiz(arv2, e);
    
    GeraArvoreBrancas(e, arv2);*/
    //-----------------------------------------------------------------------------
    printf("Teste!\n");
    //system("pause");
    return 0;
}
