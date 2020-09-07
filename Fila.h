#include "BST.h"


typedef Apontador ApontadorArvore;

typedef struct Celula* ApontadorCelula;
typedef struct Celula{

    ApontadorArvore mangueira;
    ApontadorCelula pProx;

} Celula;

typedef struct{

    ApontadorCelula pFrente;
    ApontadorCelula pTras;

} Fila;



void Inicializar(ApontadorArvore *Tree);

void Inserir(ApontadorArvore *Tree, int valor);

void Ordem(ApontadorArvore *Tree);

void PosOrdem(ApontadorArvore *Tree);

void PreOrdem(ApontadorArvore *Tree);

int Altura(ApontadorArvore *Tree);

int PesquisarNaArvore(ApontadorArvore *Tree, int valor);


void IniciarFila(Fila *fila);
int VerificarFilaVazia(Fila *fila);
int Enfileirar(Fila *fila, ApontadorArvore *tree);
int Desenfileirar(Fila *fila, ApontadorArvore *no);
void ImprimirFila(Fila *fila);
int PercursoDasDificuldades(Fila *fila, ApontadorArvore *Tree);
