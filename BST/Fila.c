#include "Fila.h"

void Inicializar(ApontadorArvore *Tree){

    *Tree = NULL;

}

void Inserir(ApontadorArvore *Tree, int valor){

    if (*Tree == NULL){

        *Tree = (ApontadorArvore) malloc(sizeof(noDaArvore));
        (*Tree)->chave = valor;
        Inicializar(&(*Tree)->filhoEsq);
        Inicializar(&(*Tree)->filhoDir);

    } else {

        if (valor <= (*Tree)->chave){

            Inserir(&(*Tree)->filhoEsq, valor);
        }
        if (valor > (*Tree)->chave){

            Inserir(&(*Tree)->filhoDir, valor);
        }
    }
}

void Ordem(ApontadorArvore *Tree){

    if (*Tree != NULL){

        Ordem(&(*Tree)->filhoEsq);
        printf("%d ", (*Tree)->chave);
        Ordem(&(*Tree)->filhoDir);
    }
}

void PreOrdem(ApontadorArvore *Tree){

    if (*Tree != NULL){

        printf("%d ", (*Tree)->chave);
        PreOrdem(&((*Tree)->filhoEsq));
        PreOrdem(&((*Tree)->filhoDir));
    }
}

void PosOrdem(ApontadorArvore *Tree){

    if (*Tree != NULL){

        PosOrdem(&((*Tree)->filhoEsq));
        PosOrdem(&((*Tree)->filhoDir));
        printf("%d ", (*Tree)->chave);
    }
}

int PesquisarNaArvore(ApontadorArvore *Tree, int valor){

    if (*Tree == NULL){
        return 0;
    }

    if ((*Tree)->chave > valor){

      return PesquisarNaArvore(&(*Tree)->filhoEsq, valor);
    }
    if ((*Tree)->chave < valor){

      return PesquisarNaArvore(&(*Tree)->filhoDir, valor);
    }
    
    int conta = PesquisarNaArvore(&(*Tree)->filhoEsq, valor);

    return conta + 1;
}

void Antecessor(ApontadorArvore noAtual, ApontadorArvore *noFilho){
    ApontadorArvore pAjudante;

    if ((*noFilho)->filhoDir != NULL){

        Antecessor(noAtual, &(*noFilho)->filhoDir);
        return;
    }
    noAtual->chave = (*noFilho)->chave;
    pAjudante = *noFilho;
    *noFilho = (*noFilho)->filhoEsq;
    free(pAjudante);
}

void RemoverNo(ApontadorArvore *Tree, int valor){

    ApontadorArvore pHelp;

    if (*Tree == NULL){

        printf("Arvore invalida ou valor nao presente\n");
        return;
    }

    if ((*Tree)->chave == valor){

        if ((*Tree)->filhoDir == NULL && (*Tree)->filhoEsq != NULL){
            pHelp = *Tree;
            *Tree = (*Tree)->filhoEsq;
            free(pHelp);
            return;
        }
        if ((*Tree)->filhoDir != NULL && (*Tree)->filhoEsq != NULL){
            Antecessor(*Tree, &(*Tree)->filhoEsq);
            return;

        }
        if ((*Tree)->filhoDir != NULL && (*Tree)->filhoEsq == NULL){
            pHelp = *Tree;
            *Tree = (*Tree)->filhoDir;
            free(pHelp);
            return;
        }
        *Tree = NULL;
        pHelp = *Tree;
        free(pHelp);

    } else {

        if ((*Tree)->chave > valor){

            RemoverNo(&(*Tree)->filhoEsq, valor);
        }
        if ((*Tree)->chave < valor){

            RemoverNo(&(*Tree)->filhoDir, valor);
        }
    }
}

int Altura(ApontadorArvore *Tree){

    if (*Tree == NULL){

        return -1;
    }

    int alturaEsquerda = Altura(&(*Tree)->filhoEsq);
    int alturaDireita = Altura(&(*Tree)->filhoDir);

    if (alturaDireita > alturaEsquerda){

        return alturaDireita + 1;
    }
     return alturaEsquerda + 1;
}


/// Fila
void IniciarFila(Fila *fila){

   fila->pFrente = (ApontadorCelula) malloc(sizeof(Celula));
   fila->pTras = fila->pFrente;
   fila->pFrente->pProx = NULL;

}

int VerificarFilaVazia(Fila *fila){

    return (fila->pFrente == fila->pTras);

}

int Enfileirar(Fila *fila, ApontadorArvore *tree){

    ApontadorCelula pAjuda;

    pAjuda = (ApontadorCelula) malloc(sizeof(Celula));
    if (pAjuda == NULL){

        return 0;
    }
    fila->pTras->pProx = pAjuda;
    pAjuda->mangueira = *tree;
    pAjuda->pProx = NULL;

    fila->pTras = pAjuda;
    return 1;
}

int Desenfileirar(Fila *fila, ApontadorArvore *no){

    if (VerificarFilaVazia(fila)){

        return 0;

    }

    ApontadorCelula pLibera;

    pLibera = fila->pFrente;
    fila->pFrente = fila->pFrente->pProx;
    //printf("ponto\n");
    *no = pLibera->pProx->mangueira;
    //printf("fim\n");
    free(pLibera);
    return 1;

}

void ImprimirFila(Fila *fila){

    ApontadorCelula pPercorre;
    pPercorre = fila->pFrente->pProx;

    while(pPercorre != NULL){
        printf("%d ", pPercorre->mangueira->chave);
        pPercorre = pPercorre->pProx;
    }
    printf("FimImprimi\n");
}

int PercursoDasDificuldades(Fila *fila, ApontadorArvore *Tree){

   if (*Tree == NULL)
        return 0;

    ApontadorArvore pAjuda = NULL;

    Enfileirar(fila, &(*Tree));

    while (VerificarFilaVazia(fila) != 1){

        Desenfileirar(fila, &pAjuda);
        //printf("aqui\n");
        printf("%d ", pAjuda->chave);

        if (pAjuda->filhoEsq != NULL){

            Enfileirar(fila, &(pAjuda->filhoEsq));

        }
        if (pAjuda->filhoDir != NULL){

            Enfileirar(fila, &(pAjuda->filhoDir));

        }
    }
    printf("\n");
    return 1;
}
