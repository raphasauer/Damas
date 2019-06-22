#include "Arvore.h"


void criaArvore(Arvore *ptrArvore)
{
    ptrArvore->ptrRaiz ==NULL;
}

NoArv* CriaNo(tabuleiro *Dado)
{
    NoArv *ptrNo = (NoArv *) malloc(sizeof(NoArv));
    int i =0;
    if(ptrNo)
    {
        ptrNo->jogo = Dado;
        ptrNo->pontuacao = 10;
        while(i<n)
        {
            ptrNo->SubArvores[i] = NULL;
            i++;
        }
    }
    return ptrNo;
}

int ComparaTabuleiro(NoArv *Raiz, tabuleiro *chave)
{
    nodo *Noaux = (nodo *) malloc(sizeof(nodo));
    if(!Noaux)
        printf("Erro ao alocar NoAux (Arvore.c 30)\n");
    nodo *NoRaiz = (nodo *) malloc(sizeof(nodo));
    if(!NoRaiz)
        printf("Erro ao alocar NoAux (Arvore.c 32)\n");

    Noaux = chave->tab;
    NoRaiz = Raiz->jogo->tab;
    int i=0;
    for(i=0; i<tam; i++)
    {
        if(NoRaiz->posicaoLinha == Noaux->posicaoLinha && NoRaiz->posicaoColuna == Noaux->posicaoColuna &&
            NoRaiz->dado == Noaux->dado)
        {
            NoRaiz->prox;
            Noaux->prox;
        }
        else
            return 0;

    }
    return 1;
}
NoArv* ConsultaLivre(NoArv *Raiz, tabuleiro *chave, int lado)
{
    if(Raiz == NULL)
        return NULL;

    int res= ComparaTabuleiro(Raiz,chave);
    if(res == 1 && Raiz->SubArvores[lado] == NULL)
        return Raiz;

    for(int i=0; i<n;i++)
    {
        NoArv *ptrNo = ConsultaLivre(Raiz->SubArvores[i],chave,lado);
        if(ptrNo)
            return ptrNo;
    }

    return NULL;
}
int Insere_Raiz(Arvore *ptrArvore, tabuleiro *ptrElemento)
{
    NoArv *ptrNo = CriaNo(ptrElemento);
    if ( !ptrNo )
        return -1;

    ptrArvore->ptrRaiz = ptrNo;
    printf("Tabuleiro Inicial inserido com Sucesso\n");
    return 1;
}
int Insere_Pai(Arvore *ptrArvore, tabuleiro *chavePai, int lado, tabuleiro *ptrElemento, int ponto)
{
    NoArv *ptrPai = ConsultaLivre(ptrArvore->ptrRaiz,chavePai, lado);

    NoArv *ptrNo = CriaNo(ptrElemento);
    if ( !ptrNo )
        return -1;

    if ( !ptrPai )  // elemento pai nao encontrado
    {
        free( ptrNo );
        printf("Filho %d falhou!!!\n", lado);
        return -2;
    }

    ptrNo->SubArvores[lado] = ptrPai->SubArvores[lado];
    ptrPai->SubArvores[lado] = ptrNo;
    ptrNo->pontuacao = ptrNo->pontuacao * ponto;
    printf("Filho %d inserido com Sucesso com pontuação = %d\n", lado, ptrNo->pontuacao);
    return 1;
}

void CaminhaPreFixadoLocal(NoArv *ptrNo)
{
    if(ptrNo != NULL)
    {
        imprimeTabuleiro(ptrNo->jogo->tab);
        for(int i=0; i<n; i++)
        {
            CaminhaPreFixadoLocal(ptrNo->SubArvores[i]);
        }
    }
}
void Caminha_Pre_Fixado(Arvore *ptrArvore)
{
    CaminhaPreFixadoLocal(ptrArvore->ptrRaiz);
}

int ContaNosLocal (NoArv *ptrRaiz)
{
    int i=0;
    if ( !ptrRaiz )
        return 0;

    for(i=0;  i<12;  i++)
        return 1 + ContaNosLocal(ptrRaiz->SubArvores[i]);
    
    return 0;   //so pra tirar o Warning mas nunca vai chegar aqui;
}

int ContaNos (Arvore *ptrArvore)
{
    return ContaNosLocal(ptrArvore->ptrRaiz);
}