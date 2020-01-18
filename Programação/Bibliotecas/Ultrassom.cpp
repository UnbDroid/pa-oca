#include <Arduino.h>
#include <Ultrassom.h>
#include <Ultrasonic.h>


/* Nessa classe será utilizada outra classe já exitente chamada Ultrassonic, pois nesta teremos os métodos
usados para medir a distância que o ultrassom lê.*/

//Método Construtor da classe Ultrassom.
Ultrassom::Ultrassom(int pinEcho, int pinTrig)
{   
    //Setando os atributos da classe com os valores passado pela método.
    this->pinEcho = pinEcho;
    this->pinTrig = pinTrig;

    //Gravando no atributo de ponteiro ultra o construtor do objeto da método Ultrassonic.
    this->ultra = new Ultrasonic(pinTrig, pinEcho);

    /*Gravando no atributo de ponteiro teste o construtor do objeto da método Teste da qual
    está sendo utilizada para testar com o Led Builtin.*/
    this->teste = new Teste();

    //Setando os pinos com INPUT e OUTPUT.
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);

}

//Método Destrutor da classe Ultrassom.
Ultrassom::~Ultrassom()
{
}

//Método que pega uma quantidade de leituras e faz a média deles para filtragem.
int Ultrassom::filter(int count){

    int soma = 0;
    int valor = 0;

    //Pegando n números de leituras e salvando em uma variável.
    for (int i = 0; i<=count; i++){
        valor = ultra->Ranging(CM);
        if(valor != 0) {
            soma += valor;
        } else {
            count--;
        }
    } 

    //Calculando a média e a retornando.
    return (soma)/count;

}


/*Teste do Ultrassom com o Led Builtin */

//Método Construtor da classe Teste.
Teste::Teste()
{
    //Setando o pino com OUTPUT
    pinMode(LED_BUILTIN, OUTPUT);
}

//Método Destrutor da classe Teste.
Teste::~Teste()
{
}

//Método que pertence a classe Teste que acende o Led na placa do Arduino.
void Teste::acende(){

    //Método que manda o sinal para o Led do arduino.
    digitalWrite(LED_BUILTIN, HIGH);

}

/*Método da classe Ultrassom que chama um método da classe Teste, visto que o objeto inicializado
de "tipo" Teste está na parte privada da classe ultrassom.*/
void Ultrassom::acende(){

    //Chama o método que pertence ao ponteiro teste construído no construtor da classe ultrassom
    teste->acende();
    delay(1000);
    //Método que desliga o led.
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
