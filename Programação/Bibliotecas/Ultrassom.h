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

    //Construtor e Destrutor da classe Ultrassom.
    Ultrassom( int pinEcho, int pinTrig);
    ~Ultrassom();
    //Função de filtragem das leituras do ultrassom.
    int filter (int count);
    //Função utilizada para testar no Led Builtin.
    void acende();
    

private:
    //Atributos da classe ultrassom
    int pinEcho;
    int pinTrig;

    //
    Ultrasonic *ultra;

    //Usa-se para fazer teste com o Led Builtin
    Teste *teste;

};




#endif
