#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"
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
void Possibilidades(tabuleiro *_tab, nodo *no, int vetor[], int indice )
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));
    //aux = _tab->tab;
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
    /*for(i=0; i <indice; i++)
        aux= aux->prox;*/

    //printf("----------testando----------");
    //printf("li: %d col: %d dado: %d\n", aux->posicaoLinha, aux->posicaoColuna, aux->dado);
        
    //if(no->dado == 1)
    //{
        for(i=0; i< tam; i++)
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
}



void GeraArvoreBrancas(tabuleiro *t, Arvore * arv)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));  //local antigo
    nodo *auxMov = (nodo *) malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa();
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado =0; //controla a posição do filho na arvore
    int vet[2], j, res;
    for(int i=0; i< tam; i++)
    {
        if(aux->dado == 1)
        {
            Possibilidades(t, aux,vet, i);
            printf("\n\nLi: %d coluna: %d vetor: #%d$$%d#\n", aux->posicaoLinha,aux->posicaoColuna,  vet[0], vet[1]);
            //Movimento a esquerda peça branca
            if(vet[1] != -1)
            {
                auxMov = aux;
                for(j=0; j< 7; j++){
                    auxMov = auxMov->prox;}   //caminha 7 vezes o tabuleiro o que faz com que chegue na posição disponivel pra movimentar
                
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            }
            //movimento a direita peça branca
            if(vet[0] != -1 )
            {
                auxMov = aux;
                for(j=0; j< 9; j++){
                    auxMov = auxMov->prox;}   //caminha 9 vezes o tabuleiro o que faz com que chegue na posição disponivel pra movimentar
                
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            }
            //movimento pra direita
            if(vet[0] != -1 && aux->dado == 2)
            {
                int j=0;
                auxMov = novoT->tab;
                for(j=0; j < (i-9); j++){//printf("prox\n");
                    auxMov = auxMov->prox;}
                printf("***********-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            }       

            if(vet[1] != -1 && aux->dado == 2)
            {
                int j=0;
                auxMov = novoT->tab;
                for(j=0; j < (i-7); j++)
                    auxMov = auxMov->prox;
                printf("***********-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            } 
        }
        aux = aux->prox;
    }
    free(novoT);
    free(aux);
    free(auxMov);
}
void GeraArvorePretas(tabuleiro *t, Arvore * arv)
{
    nodo *aux = (nodo *) malloc(sizeof(nodo));  //local antigo
    nodo *auxMov = (nodo *) malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa();
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado =0; //controla a posição do filho na arvore
    int vet[2], j, res;
    for(int i=0; i< tam; i++)
    {
        if(aux->dado == 2)
        {
            Possibilidades(t, aux,vet, i);
            printf("\n\nLi: %d coluna: %d vetor: #%d$$%d#\n", aux->posicaoLinha,aux->posicaoColuna,  vet[0], vet[1]);
            //Movimento a esquerda peça branca
            
            //movimento pra direita
            if(vet[0] != -1)
            {
                int j=0;
                auxMov = novoT->tab;
                for(j=0; j < (i-9); j++){//printf("prox\n");
                    auxMov = auxMov->prox;}
                printf("***********-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            }       

            if(vet[1] != -1 )
            {
                int j=0;
                auxMov = novoT->tab;
                for(j=0; j < (i-7); j++)
                    auxMov = auxMov->prox;
                printf("***********-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //move a peça
                auxMov->dado = aux->dado;
                aux->dado = 0;
                printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                //ImprimePeca(t.tab, 1);
                res = Insere_Pai(arv, t, lado, novoT);
                lado++;
                //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                aux->dado = auxMov->dado;
                auxMov->dado = 0;
            } 
        }
        aux = aux->prox;
    }
    free(novoT);
    free(aux);
    free(auxMov);
}
int main()
{
    int i, res;

    //inicia o tabuleiro com nulos
    tabuleiro *t = inicializa();
    //tabuleiro *cop = inicializa();

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
    Arvore arv;
    criaArvore(&arv);
    res = Insere_Raiz(&arv, t); //insere o tabuleiro inicial
    GeraArvoreBrancas(t, &arv); 
    
    //printf("TOTAL DE NOS: %d\n", ContaNos(&arv));
    //Caminha_Pre_Fixado(&arv);  
    printf("Teste!\n");
    system("pause");
    return 0;
}
