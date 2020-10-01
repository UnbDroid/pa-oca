#include <Arduino.h>
#include <Ldr.h>

//Função Construtor
Ldr::Ldr(int pinRead, int threshold)
{
    //Setando os atributos da classe com os valores passado pela função.
    this->pinRead = pinRead;
    this->threshold = threshold;

    //Setando os pinos com INPUT.
    pinMode(pinRead, INPUT);
}

//Função Destrutor
Ldr::~Ldr()
{
}

//Função que retorna um valor de filtragem.
int Ldr::filter(int count){

    int soma = 0;

    //Pegando n números de leituras e salvando em uma variável.
    for (int i = 0; i<=count; i++){
        soma += analogRead(pinRead);
    }

    //Calculando a média e a retornando.
    return (soma)/count;
}

//Função que identifica preto e branco
bool Ldr::read(int count){

    //Variável que irá conter o valor filtrado.
    int f = filter(count);

    //Comparação se é preto ou branco de acordo com a precisão.
    if (f <= threshold){
        //Caso a leitura seja menor que a precisão estará lendo branco: true (1).
        return true;
    }else{
        //Caso a leitura seja menor que a precisão estará lendo preto: false (0).
        return false;
    }

}

