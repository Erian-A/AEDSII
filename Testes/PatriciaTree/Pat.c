#include "Pat.h"



int ValorDaPalavra(char *vocabulo){

    if (*(vocabulo + 1) == '\0'){

        return *(vocabulo);
    }

    return ValorDaPalavra((vocabulo + 1)) + *(vocabulo);
}

void TraduzParaBinario(int valor, int *vet){

    int i = Tamanho - 1;

    while (i >= 0) {

        vet[i] = valor % 2;
        valor = valor / 2;
        i--;
    }
    /*
    for (i = 0; i < 10; i++){
        printf("%d", vet[i]);
    }
    */
}

Palavra EncapsulaVocabulo(char *vocabulo){

    Palavra palavraPronta;
    int ValorVocabulo;

    ValorVocabulo = ValorDaPalavra(vocabulo);

    printf("Soma: %d\n", ValorVocabulo);
    TraduzParaBinario(ValorVocabulo, palavraPronta.codigoBinario);


    palavraPronta.vocabulo = (char*) malloc(strlen(vocabulo) * sizeof(char));

    strcpy((palavraPronta.vocabulo), (vocabulo));

    return palavraPronta;
}

void Inicializar(TipoArvore *tree){

    *tree = NULL;
}

int Bit(int numQueDifereNoInterno, Palavra palavra){  /// Função Bit

    return palavra.codigoBinario[numQueDifereNoInterno -1];
}

int VerificarNoExterno(TipoArvore tree){

    return (tree->idEstruturalNo == Externo);
}

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir){ /// i -> quantidade que difere enre pontos

    TipoArvore pAjudante;

    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Interno;
    pAjudante->No.NoInterno.Esq = *Esq;
    pAjudante->No.NoInterno.Dir = *Dir;

    pAjudante->No.NoInterno.numBitOndeDifere = i;

    return pAjudante;

}


TipoArvore CriaNoExterno(Palavra palavra){

    int j;
    TipoArvore pAjudante;

    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Externo;

    pAjudante->No.Chave.vocabulo = (char*) malloc (strlen(palavra.vocabulo) * sizeof(char));
    strcpy(pAjudante->No.Chave.vocabulo, palavra.vocabulo);
    /// PRECISA ARRUMAR OS BITS NO NÓ
    ///strcpy(pAjudante->No.Chave.codigoBinario, palavra.codigoBinario);

    for (j = 0; j < 10; j++){

        pAjudante->No.Chave.codigoBinario[j] = palavra.codigoBinario[j];
    }
    return pAjudante;
}

TipoArvore InsereEntre(Palavra palavra, TipoArvore *tree, int i){

    TipoArvore pAjudante;

    if (VerificarNoExterno(*tree) || i < (*tree)->No.NoInterno.numBitOndeDifere){

        pAjudante = CriaNoExterno(palavra);

        if (Bit(i, palavra) == 1) {

            return CriaNoInterno(i, tree, &pAjudante);

        } else {

            return CriaNoInterno(i, &pAjudante, tree);
        }

    } else {

        if (Bit((*tree)->No.NoInterno.numBitOndeDifere, palavra) == 1){

            (*tree)->No.NoInterno.Dir = InsereEntre(palavra, &(*tree)->No.NoInterno.Dir, i);
        } else {

            (*tree)->No.NoInterno.Esq = InsereEntre(palavra, &(*tree)->No.NoInterno.Esq, i);
        }

        return (*tree);
    }
}

TipoArvore Insere(Palavra palavra, TipoArvore *tree){

    TipoArvore pAjudante;
    int i;

    if (*tree == NULL){

        return CriaNoExterno(palavra);

    } else {

        pAjudante = *tree;

        while (!VerificarNoExterno(pAjudante)){

            if (Bit(pAjudante->No.NoInterno.numBitOndeDifere, palavra) == 1){

                pAjudante = pAjudante->No.NoInterno.Dir;

            } else {

                pAjudante = pAjudante->No.NoInterno.Esq;
            }
        }

        /// Atencao, esta acessando o vetor a partir do indice 1
        i = 1;

        while ((i <= Tamanho) && (Bit(i, palavra) == Bit(i, pAjudante->No.Chave))){

            i++;
        }

        if (i > Tamanho){

            printf("Necessario trabalhar aqui. i > tamanho\n");
            return (*tree);
        } else {

            return InsereEntre(palavra, tree, i);
        }
    }
}
