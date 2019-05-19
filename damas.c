#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"
//#include "Tabuleiro.h"
#define tam 64  //tamanho do tabuleiro


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

    return -1;
}
//retorna em vetor quais são as colunas disponiveis para que o no possa ir
void Possibilidades(tabuleiro _tab, nodo *no, int vetor[], int indice )
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));
    //aux = _tab->tab;
    aux = _tab.tab;
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
    //printf("possibilidade: %d$$$%d\n", vetor[0], vetor[1]);
}
void testeEsq (int esq, tabuleiro *inicio, nodo *ptrNo, Arvore *arv)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));  //local antigo
    nodo *auxMov = (nodo *) malloc(sizeof(nodo)); //novo local da peça


    //faz uma cópia do tabuleiro original
    tabuleiro *novoT = inicializa();
    novoT = inicio;
    aux = novoT->tab;
    int lado =0; //controla a posição do filho na arvore
    int i=0, j=0;
    for(i =0; i< tam; i++)
    {
        if(aux == ptrNo)
        {
            auxMov = aux;
                for(j=0; j< 7; j++){
                    auxMov = auxMov->prox;}   //caminha 9 vezes o tabuleiro o que faz com que chegue na posição disponivel pra movimentar
                
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                Insere_Pai(arv, inicio, lado, novoT);
                lado++;
            

        }
        aux = aux->prox;
    }
}

void testeDir (int dir, tabuleiro *inicio, nodo *ptrNo, Arvore *arv)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));  //local antigo
    nodo *auxMov = (nodo *) malloc(sizeof(nodo)); //novo local da peça
    aux = inicio->tab;

    //faz uma cópia do tabuleiro original
    tabuleiro *novoT = inicializa();
    novoT = inicio;

    int lado =0; //controla a posição do filho na arvore
    int i=0, j=0;
    for(i =0; i< tam; i++)
    {
        auxMov = aux;
        if(aux == ptrNo)
        {
            //printf("#%d$$%d\n", esq);
            
            
                for(j=0; j< 9; j++){
                    auxMov = auxMov->prox;}   //caminha 9 vezes o tabuleiro o que faz com que chegue na posição disponivel pra movimentar
                
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                Insere_Pai(arv, inicio, lado, novoT);
                lado++;
            

        }
        aux = aux->prox;
    }
}
void GeraArvoreBrancas(tabuleiro t, Arvore * arv)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));  //local antigo
    nodo *auxMov = (nodo *) malloc(sizeof(nodo)); //novo local da peça
    tabuleiro novoT;
    inicializa2(&novoT);
    novoT = t;
    aux = novoT.tab;
    for(int i=0; i<18;i++)
        aux= aux->prox;
    
    aux->dado = 4;

    imprimeTabuleiro(novoT.tab);
    printf("-----------------------------------------------------------------------\n");
    ImprimePeca(t.tab, 1);
/*
    int lado =0; //controla a posição do filho na arvore
    int vet[2], j;
    for(int i=0; i< 30; i++)
    {
        if(aux->dado != 0)
        {
            Possibilidades(t, aux,vet, i);
            printf("\n\nLi: %d coluna: %d vetor: #%d$$%d#\n", aux->posicaoLinha,aux->posicaoColuna,  vet[0], vet[1]);
            //ImprimePeca(t.tab, 1);
            if(vet[1] != -1)
            {
                auxMov = aux;
                for(j=0; j< 7; j++){
                    auxMov = auxMov->prox;}   //caminha 9 vezes o tabuleiro o que faz com que chegue na posição disponivel pra movimentar
                
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                //Insere_Pai(arv, inicio, lado, novoT);
                lado++;
            }
        
        }

        aux = aux->prox;
    }*/
}

int main()
{
    int i, res;
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
    
    tabuleiro cop;
    inicializa2(&cop);
    linha = 0;
    while(linha < 8)
    {
        for(i = 0; i < 8; i++)
        {
            cop.tab = inicioTabuleiro(cop.tab, i,linha);
        }
        linha ++;
    }
    imprimeTabuleiro(cop.tab);
    Arvore arv;
    //criaArvore(&arv);
    //res = Insere_Raiz(&arv, t); //insere o tabuleiro inicial
    GeraArvoreBrancas(cop, &arv);
    
    printf("TOTAL DE NOS: %d\n", ContaNos(&arv));
    //Caminha_Pre_Fixado(&arv);  
    printf("Teste!\n");
    return 0;
}
