#include "Arvore.h"


void criaArvore(Arvore *ptrArvore)
{
    ptrArvore->ptrRaiz == NULL;
}

NoArv* CriaNo(int Dado)
{
    NoArv *ptrNo = (NoArv *) malloc(sizeof(NoArv));
    int i =0;
    if(ptrNo)
    {
        ptrNo->ptrDado = Dado;
        while(i<n)
        {
            ptrNo->SubArvores[i] = NULL;
            i++;
        }
    }
    return ptrNo;
}

NoArv* ConsultaLocal(NoArv *Raiz, int chave, int lado)
{
    if(!Raiz)
        return NULL;

    if(Raiz->ptrDado == chave && Raiz->SubArvores[lado] == NULL)
        return Raiz;

    for(int i=0; i<n;i++)
    {
        NoArv *ptrNo = ConsultaLocal(Raiz->SubArvores[i],chave,lado);
        if(ptrNo)
            return ptrNo;
    }
}
int Insere_Pai(Arvore *ptrArvore, int chavePai, int lado, int ptrElemento)
{
    NoArv *ptrPai = ConsultaLocal(ptrArvore->ptrRaiz,chavePai, lado);

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
        printf("%d  ",ptrNo->ptrDado);
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