#ifndef GRAB_H
#define GRAB_H
#include <Servo.h>

/*Esse arquivo ".h" é criado apenas para a declaração dos métodos e dos atributos*/

class Grab
{
public:

    //Declaração do construtor e desconstrutor
    Grab(int pinRead);
    ~Grab();

    //Declaração do métodos abrir e fechar garra
    void grabOpen(int ang);
    void grabClose(int ang);

    //Declaração do objeto servo.
    Servo *grab;

private:

    //Declaração do pino do arduino
    int pinRead;
        
};

#endif
