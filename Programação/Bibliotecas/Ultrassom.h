#ifndef ULTRASSONIC_H
#define ULTRASSONIC_H
#include <Ultrasonic.h>

/*Esse arquivo ".h" ele é criado apenas para a declaração dos métodos e dos atributos*/

/* Classe Teste criado para utilizar o Led BUILTIN como teste do sinal */
class Teste
{
public:
    Teste();
    ~Teste();
    //Função em que o Led acender
    void acende();
};


/* Classe da Biblioteca Ultrassom.h */

class Ultrassom
{

public:

  /* Ultrassom
    Descricao: Construtor da Classe.
    Parâmetros:
      - pinEcho: Pino digital em que o ultrassom recebe a onda.
      - pinTrig: Pino digital em que o ultrassom manda a onda.
  */

    Ultrassom( int pinEcho, int pinTrig);

    //Destrutor da Classe Ultrassom
    ~Ultrassom();

    /* Filter
      Descricao: Função de filtragem das leituras do ultrassom.
      Parâmetros:
        - count: Quantidade de leituras.
    */

    int filter (int count);

    //Função utilizada para testar no Led Builtin.

    void acende();


private:

    int pinEcho;
    int pinTrig;

    Ultrasonic *ultra;

    Teste *teste;

};




#endif
