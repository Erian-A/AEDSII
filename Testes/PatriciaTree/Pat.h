#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Tamanho 10

typedef unsigned char TipoChave; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef struct Palavra{

    char *vocabulo;
    int codigoBinario[Tamanho];
} Palavra;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct PatriciaNo* TipoArvore;
typedef struct PatriciaNo {

  TipoNo idEstruturalNo;

  union {
    struct {

      char numBitOndeDifere;
      TipoArvore Esq, Dir;

    } NoInterno ;

    Palavra Chave;

  } No;

} PatriciaNo;


int ValorDaPalavra(char *vocabulo);

void TraduzParaBinario(int valor, int *vet);

Palavra EncapsulaVocabulo(char *vocabulo);

void Inicializar(TipoArvore *tree);

int Bit(int numQueDifereNoInterno, Palavra palavra);

int VerificarNoExterno(TipoArvore tree);

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir);

TipoArvore CriaNoExterno(Palavra palavra);

TipoArvore InsereEntre(Palavra palavra, TipoArvore *tree, int i);

TipoArvore Insere(Palavra palavra, TipoArvore *tree);



