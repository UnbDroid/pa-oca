#include <Arduino.h>
#include <Grab.h>

/* Classe criada para controlar a garra da qual
iremos utilizar uma biblioteca pronta do Servo <Servo.h> que está declarada
no Grab.h para controlar os movimentos */


//Função Construtor
Grab::Grab(int pinRead)
{
    //Setando os atributos da classe com os valores passado pela função.
    this->pinRead = pinRead;    

    //Instanciando/inicializando o objeto grab que da classe Servo.
    this->grab = new Servo;

    //Diz em qual pino do arduino o Servo está.
    grab->attach(pinRead);

}

//Função Destrutor
Grab::~Grab()
{
}

/*Para a garra abrir ou fechar de modo não brusco, ou seja, que a garra 
  faça o movimento gradativamente, optamos em fazer o servo ir do 
  angulo 0 até o angulo desejado de um em um com um delay 
  de 15 milisegundos entre cada acréscimo.*/


//Método para abrir as garras
void Grab::grabOpen(int ang){  
      
    int pos;

    for(pos = 0; pos < ang; pos += 1)    {  
    //Vai setando o angulo para o Servo
    grab->write(pos);                       
    delay(15);                       
  } 

}

//Método para fechar as garras
void Grab::grabClose(int ang){

    int pos;

    for(pos = ang; pos>=1; pos-=1)    {  
    grab->write(pos);                       
    delay(15);                       
    } 

}