#ifndef MOTORDC_H
#define MOTORDC_H

class MotorDC
{
    public:
    //Construtor e Destrutor da Classe  
    MotorDC(int pinA, int pinB, int pinPwn);
    ~MotorDC();

    //Funções de ir para frente e para trás
    void fwd(int pot);
    void rev(int pot);

    //Função de parada
    void stop();

    private:

    int pinA;
    int pinB;
    int pinPwm;
    

};


#endif