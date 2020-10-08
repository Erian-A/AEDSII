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

}
