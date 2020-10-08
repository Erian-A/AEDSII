#include "Pat.h"

int main()
{

    Palavra palavraTeste, segundaPala, tercPala, quaPala;
    palavraTeste = EncapsulaVocabulo("pata");
    segundaPala = EncapsulaVocabulo("pato");
    tercPala = EncapsulaVocabulo("aviao");
    quaPala = EncapsulaVocabulo("pato");

    TipoArvore semente;

    Inicializar(&semente);

    semente = Insere(palavraTeste, &semente);

    semente = Insere(segundaPala, &semente);

    semente = Insere(tercPala, &semente);

    semente = Insere(quaPala, &semente);

    printf("%d\n", semente->No.NoInterno.numBitOndeDifere);






    /// Testes func basicas
    /*
    Palavra peleps;

    peleps = EncapsulaVocabulo("retangulo");

    printf("%s\n", peleps.vocabulo);

    for (int i = 0; i < 10; i++){
        printf("%d", peleps.codigoBinario[i]);
    }
    */

    printf("\nHello world!\n");
    return 0;
}
