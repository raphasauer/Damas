#include "RegraJogo.h"

//retorna qual linha que a peça vai após o movimento
int Regra_MovimentaLinha(int lin_partida, int dado)
{
    if (dado == 1)
    {
        return lin_partida + 1;
    }
    else
        return lin_partida - 1;
}

//retorna qual coluna a peça fica indo para esquerda
int Regra_MovimentaColunaEsq(int col_partida, int dado)
{
    if (dado == 1 && col_partida != 0) //se não for a coluna 0
        return col_partida - 1;
    else if (dado == 1 && col_partida == 0)
        return -1; //não pode se mover pra esquerda
    else if (dado == 2 && col_partida != 7) //se não for a ultima coluna
        return col_partida + 1;
    else if (dado == 2 && col_partida == 7)
        return -1;

    return -1;
}

//retorna qual coluna a peça fica indo para direita
int Regra_MovimentaColunaDir(int col_partida, int dado)
{
    if (dado == 1 && col_partida != 7)
        return col_partida + 1;
    else if (dado == 1 && col_partida == 7)
        return -1; //não pode se mover pra direita
    else if (dado == 2 && col_partida != 0)
        return col_partida - 1;
    else if (dado == 2 && col_partida == 0)
        return -1;

    return -1;
}

int CapturaDir(nodo *no, int vetor[])
{
    nodo *captura = (nodo *)malloc(sizeof(nodo));
    captura = no;
    for (int k = 0; k < 9; k++) //caminha até chegar a direita da peça a ser capturada
        captura = captura->prox;

    if (captura->dado == 0)
    {
        vetor[0] = captura->posicaoColuna;
        vetor[1] = captura->posicaoLinha;
        vetor[2]++; //pq comeu 1 peça
    }else
        return 0;
    
    return 1;

}
int CapturaEsq(nodo *no, int vetor[])
{
    nodo *captura = (nodo *)malloc(sizeof(nodo));
    captura = no;
    for (int k = 0; k < 7; k++) //caminha até chegar a esquerda da peça a ser capturada
        captura = captura->prox;

    if (captura->dado == 0)
    {
        vetor[3] = captura->posicaoColuna;
        vetor[4] = captura->posicaoLinha;
        vetor[5]++; //soma 1 pq comeu 1 peça
    }else
        return 0;
    
    return 1;

}

//retorna em vetor quais são as colunas disponiveis para que o nó possa ir
void Possibilidades2(tabuleiro *_tab, nodo *no, int vetor[])
{
    nodo *aux = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel
    aux = _tab->tab;
    int r = 0, posL, colDir, colEsq,res;
    int i = 0;

    for (int j = 0; j < 6; j++)
        vetor[j] = -1;

    vetor[2] = 1; //pontos para arvore
    vetor[5] = 1;
    posL = Regra_MovimentaLinha(no->posicaoLinha, no->dado);
    colDir = Regra_MovimentaColunaDir(no->posicaoColuna, no->dado);
    colEsq = Regra_MovimentaColunaEsq(no->posicaoColuna, no->dado);

    for (i = 0; i < tam; i++)
    {
        if (colDir != -1)
        {
            if (aux->posicaoLinha == posL && aux->posicaoColuna == colDir)
            {
                if (aux->dado == 0) //não tem peça para capturar
                {
                    vetor[0] = colDir;
                    vetor[1] = posL;
                    //vetor[2]  não altera o valor pq não comeu nenhuma peça
                }
                else if (aux->dado != no->dado) //se for peça do oponente
                {
                    CapturaDir(aux, vetor); 
                }
            }
        }

        if (colEsq != -1)
        {
            if (aux->posicaoLinha == posL && aux->posicaoColuna == colEsq)
            {
                if(aux->dado == 0) //não tem peça para capturar
                {
                    vetor[3] = colEsq;
                    vetor[4] = posL;
                    //vetor[2]  não altera o valor pq não comeu nenhuma peça
                }else if(aux->dado != no->dado) //se for peça do oponente
                {
                    res = CapturaEsq(aux, vetor);
                }
            }
        }
        aux = aux->prox;
    }
}
void GeraArvoreBrancas(tabuleiro *t, Arvore *arv)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo));    //local antigo
    nodo *auxMov = (nodo *)malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa();
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado = 0; //controla a posição do filho na arvore
    int vet[6], j, res, guarda;
    for (int i = 0; i < tam; i++)
    {
        if (aux->dado == 1)
        {
            Possibilidades2(t, aux, vet);
            printf("\n\nLi: %d coluna: %d vetor: #%d$$%d#\n", aux->posicaoLinha, aux->posicaoColuna, vet[0], vet[3]);
            nodo *temp = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel
            //Movimento a esquerda peça branca
            /*if (vet[3] != -1)
            {
                temp->posicaoLinha = vet[4];
                temp->posicaoColuna = vet[3];
                temp->dado = 0;
                auxMov = aux;
                for (j = i; j < tam; j++)
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
                        printf("-------------tabuleiro esquerda-------\n");
                        imprimeTabuleiro(novoT->tab);
                        lado++;
                        //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                        aux->dado = auxMov->dado;
                        auxMov->dado = 0;
                        temp->dado = guarda;
                        break; //pra não comparar os outro nós (desnecessario)
                    }
                    auxMov = auxMov->prox;
                }
            }*/
            //movimento a direita peça branca
            if (vet[0] != -1)
            {
                
                temp->posicaoLinha = vet[1];
                temp->posicaoColuna = vet[0];
                temp->dado = 0;
                auxMov = aux;
                for (j = i; auxMov != NULL; j++)
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
                        printf("-------------tabuleiro direita-------\n");
                        imprimeTabuleiro(novoT->tab);
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
}