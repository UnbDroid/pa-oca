#ifndef MOTORDC_H
#define MOTORDC_H

class MotorDC
{
    public:

    /* Motor DC
      Descricao: Construtor da Classe.
      Parâmetros:
        - pinA: Pino digital de indicação de direção.
        - pinB: Pino digital de indicação de direção.
        - pinPwn: Pino analógico de potência mandada para o motor (0 a 255)
    */

    MotorDC(int pinA, int pinB, int pinPwn);

    //Destrutor da Classe MotorDC

    ~MotorDC();

    /* fwd
      Descricao: Anda para frente.
      Parâmetros:
        - pot: Potência desejada.
    */

    void fwd(int pot);

    /* rev
      Descricao: Anda para trás.
      Parâmetros:
        - pot: Potência desejada.
    */

    void rev(int pot);

    /* rev
      Descricao: Desliga o motor.
    */

    void stop();

    private:

    int pinA;
    int pinB;
    int pinPwm;


};


#endif
