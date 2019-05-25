//#ifndef
#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"
#define tam 64  //tamanho do tabuleiro
#define n 12    //quantidade de filhos = total de peças 


typedef struct NoArv
{
    tabuleiro *jogo;
    int pontuacao;
    struct NoArv *SubArvores[n];
}NoArv;

typedef struct Arvore
{
    NoArv *ptrRaiz;
}Arvore;

void criaArvore(Arvore *ptrArvore);
int Insere_Raiz(Arvore *ptrArvore, tabuleiro *ptrElemento);
int Insere_Pai(Arvore *ptrArvore, tabuleiro *chavePai, int lado, tabuleiro *ptrElemento);
int consulta(Arvore *ptrArvore, int chave);
void Destroi(Arvore *ptrArvore);
void Caminha_Pre_Fixado(Arvore *ptrArvore);
int ContaNos (Arvore *ptrArvore);

//#endif