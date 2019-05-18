#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"
#define tam 64

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

int Regra_MovimentaLinha(int lin_partida, int dado)
{
    if(dado == 1 )
    {
        return lin_partida+1;
    }else 
        return lin_partida-1;
}
int Regra_MovimentaColunaEsq(int col_partida, int dado)
{
    if(dado == 1 && col_partida != 0)
        return col_partida-1;
    else if(dado == 1 && col_partida == 0)
        return -1;      //não pode se mover pra esquerda
    else if(dado == 2 && col_partida != 7)
        return col_partida+1;
    else if(dado == 2 && col_partida == 7)
        return -1;
}
int Regra_MovimentaColunaDir(int col_partida, int dado)
{
    if(dado == 1 && col_partida != 7)
        return col_partida+1;
    else if(dado == 1 && col_partida == 7)
        return -1;      //não pode se mover pra esquerda
    else if(dado == 2 && col_partida != 0)
        return col_partida-1;
    else if(dado == 2 && col_partida == 0)
        return -1;
}
//retorna em vetor quais são as colunas disponiveis para que o no possa ir
void Possibilidades(tabuleiro *_tab, nodo *no, int vetor[], int indice )
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));
    aux = _tab->tab;
    vetor[0] = -1;
    vetor[1] = -1;
    int r = 0, posL, colDir, colEsq;
    //printf("170-linha aux %d-%d-%d---%d\n", aux->posicaoLinha, aux->posicaoColuna, aux->dado, aux->prox->dado);
    int i= 0;
    posL = Regra_MovimentaLinha(no->posicaoLinha, no->dado);
    //printf("linha seguinte: %d\n", posL);
    colDir = Regra_MovimentaColunaDir(no->posicaoColuna, no->dado);
    //printf("ColDir: %d\n", colDir);
    colEsq = Regra_MovimentaColunaEsq(no->posicaoColuna, no->dado);
    //printf("ColEsq: %d\n", colEsq);

    //referencia ao mesmo nó da função geraArvore
    for(i=0; i <indice; i++)
        aux= aux->prox;

    //printf("----------testando----------");
    //printf("li: %d col: %d dado: %d\n", aux->posicaoLinha, aux->posicaoColuna, aux->dado);
        
    for(i=indice; i< tam; i++)
    {
        if(colDir != -1)
        {
            //printf("auxDir---- lin: %d col: %d dado:%d\n", aux->posicaoLinha, aux->posicaoColuna, aux->dado);
            if(aux->posicaoLinha == posL && aux->posicaoColuna == colDir && aux->dado == 0)
            {
                vetor[0] = colDir;
                //printf("coluna direira %d\n", colDir);
            }
        }

        if(colEsq != -1)
        {
            //printf("entre2\n");
            if(aux->posicaoLinha == posL && aux->posicaoColuna == colEsq && aux->dado == 0)
            {
                vetor[1] = colEsq;
                //printf("coluna esquerda %d\n", colEsq);
            }
        }
        aux = aux->prox;
            //printf("foi prox\n"); 
    }
    //printf("-------------------vetor-------------\n");
    //printf("%d$$$%d\n", vetor[0], vetor[1]);
}
void GeraArvoreBrancas(tabuleiro *t)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));
    nodo *auxMov = (nodo *) malloc(sizeof(nodo));
    aux = t->tab;
    int vet[2], j;
    for(int i=0; i< 20; i++)
    {
        if(aux->dado != 0)
        {
            Possibilidades(t, aux,vet, i);
            printf("Li: %d coluna: %d vetor: #%d$$%d#\n\n", aux->posicaoLinha,aux->posicaoColuna,  vet[0], vet[1]);
        }
        auxMov->dado = aux;
        if(vet[0] != -1 && aux->dado ==1)
        {
            for(j=0; j< 9; j++)
                auxMov->prox;
            //move a peça
            auxMov->dado = aux->dado;
            aux->dado = 0;
        }
        aux = aux->prox;
    }
}
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
    
        
    //printf("-------------todas-----------\n ");
    //imprimeTabuleiro(t->tab);
    //printf("\n\n-------------pretas-----------\n%d", sizeof(t));

    tabuleiro *cop = inicializa();
    cop = t;
    GeraArvoreBrancas(cop);
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
