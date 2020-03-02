#include <Arduino.h>
#include <Grab.h>


//Função Construtor
Grab::Grab(int pinRead, int ang)
{
    //Setando os atributos da classe com os valores passado pela função.
    this->pinRead = pinRead;
    this->ang = ang;

    //Setando os pinos com INPUT.
    //pinMode(pinRead, INPUT);
    this->grab = new Servo;

    grab->attach(pinRead);


}

//Função Destrutor
Grab::~Grab()
{
}

//Método para abrir as garras

void Grab::grabOpen(){

    int pos;

    for(pos = 0; pos < ang; pos += 1)    {  
    grab->write(pos);                       
    delay(15);                       
  } 

}

void Grab::grabClose(){

    int pos;

    for(pos = ang; pos>=1; pos-=1)    {  
    grab->write(pos);                       
    delay(15);                       
  } 

}