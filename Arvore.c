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
        while(i<n)
        {
            ptrNo->SubArvores[i] = NULL;
            i++;
        }
    }
    return ptrNo;
}

int ComparaTabuleiro(NoArv *Raiz, tabuleiro chave)
{
    NoArv *aux = (NoArv *) malloc(sizeof(NoArv));
    aux = chave.tab;
    int i=0;
    for(i=0; i<tam; i++)
    {
        if(Raiz->jogo->tab->posicaoColuna == aux->jogo->tab->posicaoColuna && 
            Raiz->jogo->tab->posicaoLinha == aux->jogo->tab->posicaoLinha && 
            Raiz->jogo->tab->dado == aux->jogo->tab->dado)
            return 1;
        else
            aux->jogo->tab->prox;
    }
    return 0;
}
NoArv* ConsultaLivre(NoArv *Raiz, tabuleiro chave, int lado)
{
    if(!Raiz)
        return NULL;

    //if(Raiz->jogo == chave && Raiz->SubArvores[lado] == NULL)
        //return Raiz;
    if(ComparaTabuleiro(Raiz, chave) == 1 && Raiz->SubArvores[lado] == NULL)
        return Raiz;

    for(int i=0; i<n;i++)
    {
        NoArv *ptrNo = ConsultaLivre(Raiz->SubArvores[i],chave,lado);
        if(ptrNo)
            return ptrNo;
    }
}

/*NoArv* ConsultaLocal(NoArv *ptrNo, int ptrChave)
{
    int i =0;
    if(! ptrNo) //arvore vazia
        return NULL; 
    
    if(ptrNo->ptrDado == ptrChave) //se encontrou
        return ptrNo;

    for(i=0; i< n; i++)
    {
        NoArv *ptrNo2 = ConsultaLocal(ptrNo->SubArvores[i], ptrChave);
        if ( ptrNo2 )
        return ptrNo2;
    }
    printf("finl \n");
 
}
int consulta(Arvore *ptrArvore, int chave)
{
    NoArv *ptrNo = ConsultaLocal(ptrArvore->ptrRaiz, chave);
    if (!ptrNo)
        return 0;
    printf("encontreiiiiii \n");
    return 1;
}*/
int Insere_Pai(Arvore *ptrArvore, tabuleiro chavePai, int lado, tabuleiro *ptrElemento)
{
    NoArv *ptrPai = ConsultaLivre(ptrArvore->ptrRaiz,chavePai, lado);

    NoArv *ptrNo = CriaNo(ptrElemento);
    if ( !ptrNo )
        return -1;

    if(!ptrArvore->ptrRaiz) //se rvore for vazia
    {
        ptrArvore->ptrRaiz = ptrNo;
        return 1;
    }

    if ( !ptrPai )  // elemento pai nao encontrado
    {
        free( ptrNo );
        return -2;
    }

    ptrNo->SubArvores[lado] = ptrPai->SubArvores[lado];
    ptrPai->SubArvores[lado] = ptrNo;

    return 1;
}

void CaminhaPreFixadoLocal(NoArv *ptrNo)
{
    if(ptrNo != NULL)
    {
        imprimeTabuleiro(ptrNo->jogo->tab);
        //printf("%d  ",ptrNo->jogo->tab);
        for(int i=0; i<n; i++)
        {
            CaminhaPreFixadoLocal(ptrNo->SubArvores[i]);
        }
       printf("******* \n");
    }
}
void Caminha_Pre_Fixado(Arvore *ptrArvore)
{
    CaminhaPreFixadoLocal(ptrArvore->ptrRaiz);
}