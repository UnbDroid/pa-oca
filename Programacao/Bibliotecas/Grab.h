#ifndef GRAB_H
#define GRAB_H
#include <Servo.h>

/*Esse arquivo ".h" é criado apenas para a declaração dos métodos e dos atributos*/

class Grab
{
public:

    /* Grab
      Descricao: Construtor da Classe.
      Parâmetros:
        - pinRead: Pino digital que o Servo está conectado. 
    */
    Grab(int pinRead);

    //Desconstrudor
    ~Grab();

    
    /* grabOpen
      Descricao: Abre a garra.
      Parâmetros:
        - ang: angulo de abertura desejado.
    */
    void grabOpen(int ang);

    /* grabClose
      Descricao: Fecha a garra.
      Parâmetros:
        - ang: angulo de fechamento desejado.
    */
    void grabClose(int ang);

    //Declaração do objeto servo.
    Servo *grab;

private:

    //Declaração do pino do arduino
    int pinRead;
        
};

#endif
