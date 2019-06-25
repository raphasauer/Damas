//#include "RegraJogo.h"
#include "tabuleiro.h"
#include "Arvore.h"
#include <time.h>
#include <stdlib.h>
#define RAND_MAX 12

//Função que determina a melhor jogada baseada na pontuação dos tabuleiros
tabuleiro *minimax(NoArv *ptrArv)
{
    int i, k, j = 10;           //nb - np + 10
    if (ptrArv->nivel % 2 == 0) //par, jogada de Max
    {
        for (i = 0; i < n; i++)
        {
            if (ptrArv->SubArvores[i]->pontuacao > j)
            {
                j = ptrArv->SubArvores[i]->pontuacao;
                k = i;
            }
        }
        ptrArv->pontuacao = j; 
        return ptrArv->SubArvores[k]->jogo;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (ptrArv->SubArvores[i]->pontuacao < j)
            {
                j = ptrArv->SubArvores[i]->pontuacao;
                k = i;
            }
        }
        ptrArv->pontuacao = j;
        return ptrArv->SubArvores[k]->jogo;
    }
}

for(i = 0; i < 12; i++)
{
    for(j = 0; j < 12; j++)
    {
        minimax(ptrArv->)
    }
}

//Algoritmo para teste da eficiência da IA
nodo *jogadaAleatoria(nodo *ptrNodo)
{
    //Varíaveis da função
    int i, captura, j, k, pecas = 0;
    captura = 0;
    j = 0;
    int posLinha[12];
    int posColuna[12];
    int andarLinha[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int andarColuna[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    nodo *aux = ptrNodo;
    nodo *ptrCapturada;
    nodo *ptrCapturador;
    nodo *ptrPosicaoFinal;

    //Número de controle: -1
    for (i = 0; i < 12; i++)
    {
        posLinha[i] = -1;
        posColuna[i] = -1;
    }

    //Quantas peças eu tenho? Onde elas estão?
    for (i = 0; i < 64; i++)
    {
        if (ptrNodo->dado == 2)
        {
            posLinha[pecas] = ptrNodo->posicaoLinha;
            posColuna[pecas] = ptrNodo->posicaoColuna;
            pecas++;
        }
        ptrNodo = ptrNodo->prox;
    }

    ptrNodo = aux;

    //Existe a possibilidade de capturar uma peça? Se sim, captura
    for (i = 0; i < pecas; i++)
    {
        if (buscaLista(ptrNodo, posLinha[i] - 1, posColuna[i] - 1) == 1)
        {
            printf("Tem alguem embaixo de mim\n");
            if (buscaLista(ptrNodo, posLinha[i] - 2, posColuna[i] - 2) == 0)
            {
                captura = 1;
                break;
            }
        }
        else if (buscaLista(ptrNodo, posLinha[i] - 1, posColuna[i] + 1) == 1)
        {
            if (buscaLista(ptrNodo, posLinha[i] - 2, posColuna[i] + 2) == 0)
            {
                captura = 2;
                break;
            }
        }
    }
    if (captura != 0)
    {

        if (captura == 1)
        {
            ptrCapturador = retornaPonteiro(ptrNodo, posLinha[i], posColuna[i]);
            ptrCapturada = retornaPonteiro(ptrNodo, posLinha[i] - 1, posColuna[i] - 1);
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, posLinha[i] - 2, posColuna[i] - 2);
        }
        else if (captura == 2)
        {
            ptrCapturador = retornaPonteiro(ptrNodo, posLinha[i], posColuna[i]);
            ptrCapturada = retornaPonteiro(ptrNodo, posLinha[i] - 1, posColuna[i] + 1);
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, posLinha[i] - 2, posColuna[i] + 2);
        }
        ptrCapturador->dado = 0;
        ptrCapturada->dado = 0;
        ptrPosicaoFinal->dado = 2;
        //printf("A peça andou de L %d C %d para L %d C %d\n", ptrCapturador->posicaoLinha, ptrCapturador->posicaoColuna, ptrPosicaoFinal->posicaoLinha, ptrPosicaoFinal->posicaoColuna);
        return ptrNodo;
    }
    //Quantas peças podem realizar movimentos
    for (i = 0; i < pecas; i++)
    {
        //Essas peças têm um vetor próprio
        if (buscaLista(ptrNodo, posLinha[i] - 1, posColuna[i] - 1) == 0 || (ptrNodo, posLinha[i] - 1, posColuna[i] + 1) == 0)
        {
            andarLinha[j] = posLinha[i];
            andarColuna[j++] = posColuna[i];
        }
    }
    if(j == 0)
        return ptrNodo;

    //Gera a jogada aleatória
    int r = rand() % j;
    k = rand() % 2;

    //Verifica se a posição em que a peça vai movimentar é válida, se não muda o lado e atualiza os ponteiros
    ptrCapturador = retornaPonteiro(ptrNodo, andarLinha[r], andarColuna[r]);

    if (k == 0)
    {
        if (buscaLista(ptrNodo, posLinha[r] - 1, posColuna[r] - 1) == 0)
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, andarLinha[r] - 1, andarColuna[r] - 1);
        else
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, andarLinha[r] - 1, andarColuna[r] + 1);
    }
    else
    {
        if (buscaLista(ptrNodo, posLinha[r] - 1, posColuna[r] + 1) == 0)
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, andarLinha[r] - 1, andarColuna[r] + 1);
        else
            ptrPosicaoFinal = retornaPonteiro(ptrNodo, andarLinha[r] - 1, andarColuna[r] - 1);
    }
    ptrCapturador->dado = 0;
    ptrPosicaoFinal->dado = 2;
    //printf("A peça andou de L %d C %d para L %d C %d\n", ptrCapturador->posicaoLinha, ptrCapturador->posicaoColuna, ptrPosicaoFinal->posicaoLinha, ptrPosicaoFinal->posicaoColuna);
    return ptrNodo;
}

//retorna em vetor quais são as colunas disponiveis para que o no possa ir
/*void Possibilidades(tabuleiro *_tab, nodo *no, int vetor[], int indice)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo));
    aux = _tab->tab;
    vetor[0] = -1;
    vetor[1] = -1;
    int r = 0, posL, colDir, colEsq;
    int i = 0;
    posL = Regra_MovimentaLinha(no->posicaoLinha, no->dado);
    colDir = Regra_MovimentaColunaDir(no->posicaoColuna, no->dado);
    colEsq = Regra_MovimentaColunaEsq(no->posicaoColuna, no->dado);

    for (i = 0; i < tam; i++)
    {
        if (colDir != -1)
        {
            if (aux->posicaoLinha == posL && aux->posicaoColuna == colDir && aux->dado == 0)
                vetor[0] = colDir;
        }

        if (colEsq != -1)
        {
            if (aux->posicaoLinha == posL && aux->posicaoColuna == colEsq && aux->dado == 0)
                vetor[1] = colEsq;
        }
        aux = aux->prox;
    }
}

void GeraArvorePretas(tabuleiro *t, Arvore *arv)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo));    //local antigo
    nodo *auxMov = (nodo *)malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa();
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado = 0; //controla a posição do filho na arvore
    int vet[5], j, res, guarda, i;
    for (i = 0; i < tam; i++)
    {
        if (aux->dado == 2)
        {
            Possibilidades2(t, aux, vet);
            printf("\n\nLi: %d coluna: %d vetor: #%d$$%d#\n", aux->posicaoLinha, aux->posicaoColuna, vet[0], vet[3]);
            nodo *temp = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel

            //movimento pra direita
            if (vet[0] != -1)
            {
                temp->posicaoLinha = vet[1];
                temp->posicaoColuna = vet[0];
                temp->dado = 0;
                auxMov = novoT->tab;
                for (j = 0; j < tam; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //cheguei na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (vet[2] == 2)
                        {
                            //caminha no tabuleiro até encontrar a peça a ser comida
                            temp = novoT->tab;
                            for (int p = 0; p < (j - 9); p++)
                                temp = temp->prox;
                            guarda = temp->dado;
                            temp->dado = 0; //"excluiu" a peça que foi capturada
                        }
                        printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                        //ImprimePeca(t.tab, 1);
                        res = Insere_Pai(arv, t, lado, novoT, vet[2]);
                        lado++;
                        //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                        aux->dado = auxMov->dado;
                        auxMov->dado = 0;
                        temp->dado = guarda;
                        break; //pra não comparar os outro nós (desnecessario)
                    }
                    auxMov = auxMov->prox;
                }
            }

            if (vet[3] != -1)
            {
                temp->posicaoLinha = vet[4];
                temp->posicaoColuna = vet[3];
                temp->dado = 0;
                auxMov = novoT->tab;
                for (j = 0; j < 64; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //cheguei na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (vet[5] == 2)
                        {
                            //caminha no tabuleiro até encontrar a peça a ser comida
                            temp = novoT->tab;
                            for (int p = 0; p < (j - 7); p++)
                                temp = temp->prox;
                            guarda = temp->dado;
                            temp->dado = 0; //"excluiu" a peça que foi capturada
                        }
                        printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                        //ImprimePeca(t.tab, 1);
                        res = Insere_Pai(arv, t, lado, novoT, vet[5]);
                        lado++;
                        //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                        aux->dado = auxMov->dado;
                        auxMov->dado = 0;
                        temp->dado = guarda;
                        break; //pra não comparar os outro nós (desnecessario)
                    }
                    auxMov = auxMov->prox;
                }
            }
            free(temp);
        }
        aux = aux->prox;
    }
    free(novoT);
    free(aux);
    free(auxMov);
}*/
int main()
{
    srand(time(NULL));

    int i, res;

    //inicia o tabuleiro com nulos
    tabuleiro *t = inicializa();
    tabuleiro *e = inicializa();
    tabuleiro *c = inicializa();

    //se for brancas flag=0 (são os Maximos).... pretas flag =1
    int linha = 0;
    while (linha < 8)
    {
        for (i = 0; i < 8; i++)
        {
            t->tab = inicioTabuleiro(t->tab, i, linha);
        }
        linha++;
    }
    //imprimeTabuleiro(t->tab);
    //printf("Teste de jogada aleatória\n");
    //t->tab = jogadaAleatoria(t->tab);
    if (t->tab == NULL)
        printf("Erro, tabuleiro nulo!\n");
    nodo *ptrAux = t->tab;
    for (i = 0; i < 64; i++)
    {
        t->tab->dado = 0;
        t->tab = t->tab->prox;
    }
    t->tab = ptrAux;
    ptrAux = retornaPonteiro(t->tab, 7, 2);
    ptrAux->dado = 2;
    ptrAux = retornaPonteiro(t->tab, 5, 0);
    ptrAux->dado = 2;
    ptrAux = retornaPonteiro(t->tab, 4, 1);
    ptrAux->dado = 1;
    ptrAux = retornaPonteiro(t->tab, 5, 4);
    ptrAux->dado = 1;
    ptrAux = retornaPonteiro(t->tab, 7, 7);
    ptrAux->dado = 2;
    //printf("%d\n", buscaLista(t->tab, 4, 1));
    //imprimeTabuleiro(t->tab);
    t->tab = jogadaAleatoria(t->tab);
    t->tab = jogadaAleatoria(t->tab);
    t->tab = jogadaAleatoria(t->tab);
    t->tab = jogadaAleatoria(t->tab);
    //imprimeTabuleiro(t->tab);
    /*Arvore arv;
    criaArvore(&arv);

    nodo *a = (nodo *)malloc(sizeof(nodo));
    e->tab = copiaLista(t->tab);
    a = e->tab;
    int o;
    for (o = 0; i < 35; i++)
        a = a->prox;

    printf("li: %d col: %d\n", a->posicaoLinha, a->posicaoColuna);
    a->dado = 2;
    //imprimeTabuleiro(e->tab);

    //res = Insere_Raiz(&arv, e); //insere o tabuleiro inicial
    //GeraArvoreBrancas(e, &arv);
    //Caminha_Pre_Fixado(&arv);
    //GeraArvorePretas(e, &arv );
    //imprimeTabuleiro(arv.ptrRaiz->SubArvores[0]->jogo->tab);
    //printf("************************");
    //imprimeTabuleiro(arv.ptrRaiz->SubArvores[0]->jogo->tab);
    //printf("TOTAL DE NOS: %d\n", ContaNos(&arv));
    //Caminha_Pre_Fixado(&arv);
    printf("Teste!\n");
    system("pause");*/
    return 0;
}
