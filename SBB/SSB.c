#include "SSB.h"

void IniciarArvore(ApontadorNo *raiz){

    *raiz = NULL;
}


void EsquerdaEsquerda(ApontadorNo *no){

    ApontadorNo pApontaEAuxilia;

    /// Tá recebendo o nó que vai virar raiz, mas no momento é filho direito da raiz
    pApontaEAuxilia = (*no)->filhoEsq;
    /// Tá repassando a guarda, filho direito virou esquerdo
    (*no)->filhoEsq = pApontaEAuxilia->filhoDir;
    (*no)->bitE = Vertical;

    /// Nó que vai virar raiz agora é pai da ex-raiz
    pApontaEAuxilia->filhoDir = (*no);
    pApontaEAuxilia->bitE = Vertical;


    /// Tomou posse como raiz
    *no = pApontaEAuxilia;
}

void EsquerdaDireita(ApontadorNo *no){

    ApontadorNo pAuxilia, pFuturaRaiz;
    /// o indivíduo a esquerda da futura raiz
    pAuxilia = (*no)->filhoEsq;
    /// Apontador recebe a futura raiz
    pFuturaRaiz = pAuxilia->filhoDir;
    /// Acertar as inclinações
    (*no)->bitE = Vertical;
    pAuxilia->bitD = Vertical;
    /// Futura raiz distribui filhos
    (*no)->filhoEsq = pFuturaRaiz->filhoDir;
    pAuxilia->filhoDir = pFuturaRaiz->filhoEsq;
    /// Futura raiz adota vizinhos
    pFuturaRaiz->filhoEsq = pAuxilia;
    pFuturaRaiz->filhoDir = *no;
    /// Coroação
    *no = pFuturaRaiz;
}

void DireitaDireita(ApontadorNo *no){
    ApontadorNo pApontaEAuxilia;

    pApontaEAuxilia = (*no)->filhoDir;
    /// Repassando o filho
    (*no)->filhoDir = pApontaEAuxilia->filhoEsq;
    (*no)->bitD = Vertical;


    /// Futura raiz recebendo o filho
    pApontaEAuxilia->filhoEsq = *no;
    pApontaEAuxilia->bitD = Vertical;
    /// Virou raiz
    *no = pApontaEAuxilia;

}

void DireitaEsquerda(ApontadorNo *no){

    ApontadorNo pAuxilia, pFuturaRaiz;
    /// Conehcendo todo mundo
    pAuxilia = (*no)->filhoDir;
    pFuturaRaiz = pAuxilia->filhoEsq;
    /// Transferindo a guarda da futura para os vizinhos
    (*no)->filhoDir = pFuturaRaiz->filhoEsq;
    pAuxilia->filhoEsq = pFuturaRaiz->filhoDir;
    /// Acertando as inclinações
    (*no)->bitD = Vertical;
    pAuxilia->bitE = Vertical;
    /// Futura raiz adotando
    pFuturaRaiz->filhoEsq = *no;
    pFuturaRaiz->filhoDir = pAuxilia;
    /// Coroação
    *no = pFuturaRaiz;
}

void Insere(ApontadorNo *tree, int valor){

    short FIM;
    TipoInclinacao AP;

    InsereTrabalhadora(tree, &AP, valor, &FIM);
}

void InsereTrabalhadora(ApontadorNo *tree, TipoInclinacao *Ap, int valor, short *FIM){

    if (*tree == NULL){

        *tree = (ApontadorNo) malloc(sizeof(tipoNo));
        (*tree)->chave = valor;
        /// Quando nao for a raiz, vai definir a inclinação de como o pai olha para o no inserido
        *Ap = Horizontal;
        ///
        IniciarArvore(&(*tree)->filhoEsq);
        IniciarArvore(&(*tree)->filhoDir);
        /// Define as inclinações para o no criado
        (*tree)->bitE = Vertical;
        (*tree)->bitD = Vertical;
        /// Flag(?)
        *FIM = 0;
        return;
    }

    if ((*tree)->chave > valor){

        InsereTrabalhadora(&(*tree)->filhoEsq, &(*tree)->bitE, valor, FIM);
        /// Irá verificar se tem dois Horizontais seguidos
        if (*FIM)
            return;
        if ((*tree)->bitE != Horizontal){
            *FIM = 1;
            return;
        }
        if ((*tree)->filhoEsq->bitE == Horizontal){
            EsquerdaEsquerda(tree);
            *Ap = Horizontal;
            return;
        }
        if ((*tree)->filhoEsq->bitD == Horizontal){
            EsquerdaDireita(tree);
            *Ap = Horizontal;
        }
        return;
    }


    InsereTrabalhadora(&(*tree)->filhoDir, &(*tree)->bitD, valor, FIM);
    /// Irá verificar se tem dois Horizontais seguidos
        if (*FIM)
            return;
        if ((*tree)->bitD != Horizontal){
            *FIM = 1;
            return;
        }
        if ((*tree)->filhoDir->bitD == Horizontal){
            DireitaDireita(tree);
            *Ap = Horizontal;
            return;
        }
        if ((*tree)->filhoDir->bitE == Horizontal){
            DireitaEsquerda(tree);
            *Ap = Horizontal;
        }
}

void Ordem(ApontadorNo *tree){

    if (*tree != NULL){

        Ordem(&(*tree)->filhoEsq);
        printf("%d ", (*tree)->chave);
        Ordem(&(*tree)->filhoDir);
    }
}

void EsquerdaCurto(ApontadorNo *tree, short *Fim) { // Folha esquerda retirada => arvore curta na altura esquerda
  ApontadorNo pAuxiliar;

  if ((*tree)->bitE == Horizontal) {

    (*tree)->bitE = Vertical;
     *Fim = 1;
     return;
  }
  if ((*tree)->bitD == Horizontal) {

    pAuxiliar = (*tree)->filhoDir;
    (*tree)->filhoDir = pAuxiliar->filhoEsq;
    pAuxiliar->filhoEsq = *tree;
    *tree = pAuxiliar;

    if ((*tree)->filhoEsq->filhoDir->bitE == Horizontal) {

         DireitaEsquerda(&(*tree)->filhoEsq);
        (*tree)->bitE = Horizontal;

    } else if ((*tree)->filhoEsq->filhoDir->bitD == Horizontal){

        DireitaDireita(&(*tree)->filhoEsq);
        (*tree)->bitE = Horizontal;
    }

    *Fim = 1;
    return;
  }

  (*tree)->bitD = Horizontal;

  if ((*tree)->filhoDir->bitE == Horizontal) {

    DireitaEsquerda(tree);
    *Fim = 1;
    return;
  }
  if ((*tree)->filhoDir->bitD == Horizontal) {

    DireitaDireita(tree);
    *Fim = 1;
  }
}

void DireitaCurto(ApontadorNo *tree, short *Fim) { // Folha direita retirada => arvore curta na altura direita /
  ApontadorNo pAuxiliar;

  if ((*tree)->bitD == Horizontal) {

    (*tree)->bitD = Vertical;
     *Fim = 1;
     return;
  }
  if ((*tree)->bitE == Horizontal) {

    pAuxiliar = (*tree)->filhoEsq;
    (*tree)->filhoEsq = pAuxiliar->filhoDir;
    pAuxiliar->filhoDir = *tree;
    *tree = pAuxiliar;

    if ((*tree)->filhoDir->filhoEsq->bitD == Horizontal) {

         EsquerdaDireita(&(*tree)->filhoDir);
        (*tree)->bitD = Horizontal;

    } else if ((*tree)->filhoDir->filhoEsq->bitE == Horizontal){

        EsquerdaEsquerda(&(*tree)->filhoDir);
        (*tree)->bitD = Horizontal;
    }

    *Fim = 1;
    return;
  }

  (*tree)->bitE = Horizontal;

  if ((*tree)->filhoEsq->bitD == Horizontal) {

    EsquerdaDireita(tree);
    *Fim = 1;
    return;
  }
  if ((*tree)->filhoEsq->bitE == Horizontal) {

    EsquerdaEsquerda(tree);
    *Fim = 1;
  }
}



void Antecessor(ApontadorNo noAtual, ApontadorNo *noFilho, short *Fim){

    if ((*noFilho)->filhoDir != NULL){

        Antecessor(noAtual, &(*noFilho)->filhoDir, Fim);
        if (!*Fim){

            DireitaCurto(noFilho, Fim);
        }
        return;
    }

  noAtual->chave = (*noFilho)->chave;
  noAtual = *noFilho;
  *noFilho = (*noFilho)->filhoEsq;
  free(noAtual);
  if (*noFilho != NULL)
    *Fim = 1;
}


void IRetira(ApontadorNo *tree, int valor, short *Fim){

    ApontadorNo pAjudante; // tipoNo *aux

    if (*tree == NULL) {
        printf("Chave nao esta na arvore\n");
        *Fim = 1;
        return;
    }

    if (valor < (*tree)->chave) {
        IRetira(&(*tree)->filhoEsq, valor, Fim);

        if (!*Fim){

            EsquerdaCurto(tree, Fim);
        }
        return;
    }

    if (valor > (*tree)->chave){
        IRetira(&(*tree)->filhoDir, valor, Fim);

        if (!*Fim){

            DireitaCurto(tree, Fim);
        }
        return;
    }

    /// Encontrou
    *Fim = 0;
    pAjudante = *tree;

    if (pAjudante->filhoDir == NULL){
        *tree = pAjudante->filhoEsq;
        free(pAjudante);

        if (*tree != NULL){

            *Fim = 1;
        }
        return;
    }

    if (pAjudante->filhoEsq == NULL){
        *tree = pAjudante->filhoDir;
        free(pAjudante);

        if (*tree != NULL){
            *Fim = 1;
        }
        return;
    }
    Antecessor(pAjudante, &pAjudante->filhoEsq, Fim);

    if (!*Fim){

        EsquerdaCurto(tree, Fim); /* Encontrou chave */
    }
}

void Retira(ApontadorNo *tree, int valor){

    short Fim;
    IRetira(tree, valor, &Fim);
}





















