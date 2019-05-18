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
        printf("no criado: ");
        //imprimeTabuleiro(ptrNo->jogo->tab);
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
    printf("entrei comparaTabuleiro \n");
    nodo *Noaux = (nodo *) malloc(sizeof(nodo));
    if(!Noaux)
        printf("Erro ao alocar NoAux (Arvore.c 32)\n");
    nodo *NoRaiz = (nodo *) malloc(sizeof(nodo));
    if(!NoRaiz)
        printf("Erro ao alocar NoAux (Arvore.c 32)\n");

    printf("cheguei 36\n");
    Noaux = chave->tab;
    printf("cheguei 38, %d\n",Raiz->jogo->tab->dado);
    NoRaiz = Raiz->jogo->tab;
    printf("cheguei 40\n");
    int i=0;
    printf("pré for::: \n");
    for(i=0; i<tam; i++)
    {
        printf("comparação for::: \n");
        if(NoRaiz->posicaoLinha == Noaux->posicaoLinha && NoRaiz->posicaoColuna == Noaux->posicaoColuna &&
            NoRaiz->dado == Noaux->dado)
        {
            NoRaiz->prox;
            Noaux->prox;
            printf("igaul\n");
        }
        else
            return 0;

    }
    return 0;
}
NoArv* ConsultaLivre(NoArv *Raiz, tabuleiro *chave, int lado)
{
    printf("entrei consulta livre\n");
    if(Raiz == NULL)
        return NULL;

    printf("54res::: \n");
    int res= ComparaTabuleiro(Raiz,chave);
    printf("res::: %d", res);
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
    
    return 1;
}
int Insere_Pai(Arvore *ptrArvore, tabuleiro *chavePai, int lado, tabuleiro *ptrElemento)
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

void CaminhaPreFixadoLocal(NoArv *ptrNo)
{
    if(ptrNo != NULL)
    {
        imprimeTabuleiro(ptrNo->jogo->tab);
        //printf("%d  ",ptrNo->jogo->tab);
        /*printf("-------------------\n");
        for(int i=0; i<n; i++)
        {
            CaminhaPreFixadoLocal(ptrNo->SubArvores[i]);
        }*/
       printf("******* \n");
    }
}
void Caminha_Pre_Fixado(Arvore *ptrArvore)
{
    CaminhaPreFixadoLocal(ptrArvore->ptrRaiz);
}