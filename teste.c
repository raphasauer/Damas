#include <stdio.h>
#include <stdlib.h>

//Estrutura do nó e do tabuleiro
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


//Função de cópia do nodo - NÃO FUNCIONA (SHALLOW COPY)
nodo *copiaLista(nodo *ptrOrigem)
{
    if(ptrOrigem == NULL)
        return NULL;

    nodo *novo = (nodo*)malloc(sizeof(nodo));

    novo->posicaoColuna = ptrOrigem->posicaoColuna;
    novo->posicaoLinha = ptrOrigem->posicaoLinha;
    novo->dado = ptrOrigem->dado;
    novo->prox = copiaLista(ptrOrigem->prox);

    return novo;
}

//Inicializa o tabuleiro
tabuleiro *inicializa()
{
    tabuleiro *t = (tabuleiro *)malloc(sizeof(tabuleiro));
    t->tab=NULL;

    return t;
}

//Cria os nodos com a linha e a peça especificadas
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

int main()
{
    int i, res;

    //inicia o tabuleiro com nulos
    tabuleiro *t = inicializa();
    tabuleiro *cop = inicializa();

    //se for brancas flag=0 (são os Maximos).... pretas flag =1
    int linha = 0;
    while(linha < 8)
    {
        for(i = 0; i < 8; i++)
        {
            t->tab = inicioTabuleiro(t->tab, i, linha);
        }
        linha ++;
    }



    cop->tab = copiaLista(t->tab);

    //Altera um dado na variável de destino
    cop->tab->prox->dado = 4;

    //Variável de origem também é afetada
    printf("Dado modificado: %d, Dado original %d\n", cop->tab->prox->dado, t->tab->prox->dado);

    system("pause");
    return 0;
}
