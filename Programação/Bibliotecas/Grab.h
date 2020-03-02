#ifndef GRAB_H
#define GRAB_H

#include <Servo.h>

class Grab
{
public:
    Grab(int pinRead, int ang);
    ~Grab();

    void grabOpen();
    void grabClose();

    Servo *grab;


private:

    int pinRead;
    int ang;
    
};


#endif