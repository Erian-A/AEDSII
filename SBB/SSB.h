#include <stdio.h>
#include <stdlib.h>

typedef enum {

    Vertical, Horizontal /// Aparentemente nao tem ;
} TipoInclinacao;


typedef struct tipoNo* ApontadorNo;
typedef struct tipoNo {

    int chave;
    ApontadorNo filhoEsq, filhoDir;
    TipoInclinacao bitE, bitD;

} tipoNo;

void IniciarArvore(ApontadorNo *raiz);

void EsquerdaEsquerda(ApontadorNo *no);

void EsquerdaDireita(ApontadorNo *no);

void DireitaDireita(ApontadorNo *no);

void DireitaEsquerda(ApontadorNo *no);

void Insere(ApontadorNo *tree, int valor);

void InsereTrabalhadora(ApontadorNo *tree, TipoInclinacao *Ap, int valor, short *FIM);

void Ordem(ApontadorNo *tree);

void EsquerdaCurto(ApontadorNo *tree, short *Fim);

void DireitaCurto(ApontadorNo *tree, short *Fim);

void Antecessor(ApontadorNo noAtual, ApontadorNo *noFilho, short *Fim);

void IRetira(ApontadorNo *tree, int valor, short *Fim);

void Retira(ApontadorNo *tree, int valor);

