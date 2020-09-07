#include "Fila.h"


int main()
{
    Fila line;

    ApontadorArvore raiz;
    ApontadorArvore vc;
    IniciarFila(&line);


    /// Funciona

    Inicializar(&raiz);
    Inserir(&raiz, 15);
    Inserir(&raiz, 7);
    Inserir(&raiz, 8);

    Inserir(&raiz, 3);
    Inserir(&raiz, 2);

    PesquisarNaArvore(&raiz, 3);
    /*
    Inserir(&raiz, 20);
    Inserir(&raiz, 16);
    Inserir(&raiz, 22);
    */
    //Ordem(&raiz);
    printf("Altura: %d\n", Altura(&raiz));
    //PercursoDasDificuldades(&line, &raiz);

}
