#ifndef LDR_H
#define LDR_H

class Ldr
{
    
public:
    Ldr(int pinRead, int threshold);
    ~Ldr();
    bool read(int count);
    int filter(int count);

private:

    int pinRead;
    int threshold;
};



#endif