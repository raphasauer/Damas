//#ifndef
#include <stdio.h>
#include <stdlib.h>
#define n 12    //quantidade de filhos = total de peças


typedef struct NoArv
{
    int ptrDado;
    struct NoArv *SubArvores[n];
}NoArv;

typedef struct Arvore
{
    NoArv *ptrRaiz;
}Arvore;

void criaArvore(Arvore *ptrArvore);
int Insere_Pai(Arvore *ptrArvore, int chavePai, int lado, int ptrElemento);
int consulta(Arvore *ptrArvore, int chave);
void Destroi(Arvore *ptrArvore);
void Caminha_Pre_Fixado(Arvore *ptrArvore);

//#endif