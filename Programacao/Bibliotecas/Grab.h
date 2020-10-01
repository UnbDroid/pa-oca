#ifndef GRAB_H
#define GRAB_H

#include <Servo.h>

class Grab
{
public:
    Grab(int pinRead);
    ~Grab();

    void grabOpen(int ang);
    void grabClose(int ang);

    Servo *grab;


private:

    int pinRead;
        
};


#endif