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

int CapturaDir(nodo *no, Mov *dados)
{
    nodo *captura = (nodo *)malloc(sizeof(nodo));
    captura = no;   //aponta para o mesmo lugar que tem o nó desejado

    for (int k = 0; k < 9; k++) //caminha até chegar a direita da peça a ser capturada
        captura = captura->prox;

    if (captura->dado == 0) //peça pra capturar
    {
        dados->colDir = captura->posicaoColuna;
        dados->liDir = captura->posicaoLinha;
        dados->pontDir = dados->pontDir + 1 ; //pq comeu 1 peça
    }else
        return 0;
    
    free(captura);
    return 1;

}
int CapturaEsq(nodo *no, Mov *dados)
{
    nodo *captura = (nodo *)malloc(sizeof(nodo));
    captura = no;
    for (int k = 0; k < 7; k++) //caminha até chegar a esquerda da peça a ser capturada
        captura = captura->prox;

    if (captura->dado == 0)
    {
        dados->colEsq = captura->posicaoColuna;
        dados->liEsq = captura->posicaoLinha;
        dados->pontEsq = dados->pontEsq + 1 ; //soma 1 pq comeu 1 peça
    }else
        return 0;
    
    free(captura);
    return 1;

}

//retorna em vetor quais são as colunas disponiveis para que o nó possa ir
void Possibilidades(tabuleiro *_tab, nodo *no, Mov *dados)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel
    aux = _tab->tab;
    int r = 0, posL, colDir, colEsq,res;
    int i = 0;

    dados->colDir = -1;
    dados->liDir = -1;
    dados->pontDir = 1;
    dados->colEsq = -1;
    dados->liEsq = -1;
    dados->pontEsq = 1;

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
                    dados->colDir = colDir;
                    dados->liDir = posL;
                    //dados->pontDir  não altera o valor pq não comeu nenhuma peça
                }
                else if (aux->dado != no->dado) //se for peça do oponente
                {
                    CapturaDir(aux, dados); 
                }
            }
        }

        if (colEsq != -1)
        {
            if (aux->posicaoLinha == posL && aux->posicaoColuna == colEsq)
            {
                if(aux->dado == 0) //não tem peça para capturar
                {
                    dados->colEsq = colEsq;
                    dados->liEsq = posL;
                    //dados->pontEsq não altera o valor pq não comeu nenhuma peça
                }else if(aux->dado != no->dado) //se for peça do oponente
                {
                    res = CapturaEsq(aux, dados);
                }
            }
        }
        aux = aux->prox;
    }

    free(aux);
}
void GeraArvoreBrancas(tabuleiro *t, Arvore *arv)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo));    //local antigo
    nodo *auxMov = (nodo *)malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa(); //tabuleiro que sera feito as modificações
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado = 0; //controla a posição do filho na arvore
    Mov *nvDados= (Mov *) malloc(sizeof(Mov));
    nvDados->colDir = -1;
    nvDados->liDir = -1;
    nvDados->pontDir = 1;
    nvDados->colEsq = -1;
    nvDados->liEsq = -1;
    nvDados->pontEsq = 1;

    int  j, res, guarda;
    for (int i = 0; i < tam; i++)
    {
        if (aux->dado == 1)
        {
            Possibilidades(t, aux, nvDados);
            printf("\n\nLi: %d coluna: %d struct: #%d$$%d#\n", aux->posicaoLinha, aux->posicaoColuna, nvDados->colEsq, nvDados->colDir);
            nodo *temp = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel
            //Movimento a esquerda peça branca
            if (nvDados->colEsq != -1)
            {
                temp->posicaoLinha = nvDados->liEsq;
                temp->posicaoColuna = nvDados->colEsq;
                temp->dado = 0;
                auxMov = aux; 
                for (j = i; j < tam; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //chegou na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (nvDados->pontEsq == 2) //se pode comer a peça
                        {
                            //caminha no tabuleiro até encontrar a peça a ser comida
                            temp = novoT->tab;
                            for (int p = 0; p < (j - 7); p++)
                                temp = temp->prox;
                            guarda = temp->dado;
                            temp->dado = 0; //"excluiu" a peça que foi capturada
                        }
                        printf("novoPosEsq-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                        res = Insere_Pai(arv, t, lado, novoT, nvDados->pontEsq);
                        lado++;
                        //desfaz a troca após inserir na arvore para que não troque essa mesma peça novamente
                        aux->dado = auxMov->dado;
                        auxMov->dado = 0;
                        temp->dado = guarda;
                        //novoT->tab = copiaLista(t->tab);
                        break; //pra não comparar os outro nós (desnecessario)
                    }
                    auxMov = auxMov->prox;
                }
            }
            //movimento a direita peça branca
            if (nvDados->colDir != -1)
            {
                
                temp->posicaoLinha = nvDados->liDir;
                temp->posicaoColuna = nvDados->colDir;
                temp->dado = 0;
                auxMov = aux;
                for (j = i; j<tam; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //cheguei na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (nvDados->pontDir == 2)
                        {
                            //caminha no tabuleiro até encontrar a peça a ser comida
                            temp = novoT->tab;
                            for (int p = 0; p < (j - 9); p++)
                                temp = temp->prox;
                            guarda = temp->dado;
                            temp->dado = 0; //"excluiu" a peça que foi capturada
                        }
                        printf("novoPosDir-> lin: %d col: %d dado: %d\n", auxMov->posicaoLinha, auxMov->posicaoColuna, auxMov->dado);
                        res = Insere_Pai(arv, t, lado, novoT, nvDados->pontDir);
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
    free(aux);
    free(auxMov);
}


void GeraArvorePretas(tabuleiro *t, Arvore *arv)
{
    nodo *aux = (nodo *)malloc(sizeof(nodo));    //local antigo
    nodo *auxMov = (nodo *)malloc(sizeof(nodo)); //novo local da peça
    tabuleiro *novoT = inicializa();
    novoT->tab = copiaLista(t->tab);
    aux = novoT->tab;

    int lado = 0; //controla a posição do filho na arvore
    Mov *nvDados= (Mov *) malloc(sizeof(Mov));
    nvDados->colDir = -1;
    nvDados->liDir = -1;
    nvDados->pontDir = 1;
    nvDados->colEsq = -1;
    nvDados->liEsq = -1;
    nvDados->pontEsq = 1;

    int  j, res, guarda, i;
    for (i = 0; i < tam; i++)
    {
        if (aux->dado == 2)
        {
            Possibilidades(t, aux, nvDados);
            printf("\n\nLi: %d coluna: %d struct: #%d$$%d#\n", aux->posicaoLinha, aux->posicaoColuna, nvDados->colEsq, nvDados->colDir);
            nodo *temp = (nodo *)malloc(sizeof(nodo)); //nova posição disponivel

            //movimento pra direita
            if (nvDados->colDir != -1)
            {
                temp->posicaoLinha = nvDados->liDir;
                temp->posicaoColuna = nvDados->colDir;
                temp->dado = 0;
                auxMov = novoT->tab;
                for (j = 0; j < tam; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //cheguei na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (nvDados->pontDir == 2)
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
                        res = Insere_Pai(arv, t, lado, novoT, nvDados->pontDir);
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
            //movimentos para esquerda
            if (nvDados->colEsq != -1)
            {
                temp->posicaoLinha = nvDados->liEsq;
                temp->posicaoColuna = nvDados->colEsq;
                temp->dado = 0;
                auxMov = novoT->tab;
                for (j = 0; j < tam; j++)
                {
                    if (auxMov->posicaoColuna == temp->posicaoColuna && auxMov->posicaoLinha == temp->posicaoLinha && auxMov->dado == temp->dado) //cheguei na nova posição
                    {
                        //move a peça
                        auxMov->dado = aux->dado;
                        aux->dado = 0;
                        if (nvDados->pontEsq == 2)
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
                        res = Insere_Pai(arv, t, lado, novoT, nvDados->pontEsq);
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
    free(aux);
    free(auxMov);
}