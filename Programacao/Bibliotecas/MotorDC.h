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
        - pinPwn: Pino analógico de potência mandada para o motor (0 a 255).
        - pinEnc: Pino digital interrupt de sinal do encoder.
    */
    MotorDC(int pinA, int pinB, int pinPwn, int pinEnc);


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


    /* stop
      Descricao: Desliga o motor.
    */
    void stop();


    /* encSignal
      Descricao: Ao detectar um sinal do encoder, atualiza o contador do mesmo, de acordo com o sentido de rotação do motor.
    */
    void encSignal();


    /* stop
      Descricao: retorna o valor do contador de pulsos do encoder.
    */
    long unsigned int getCount();



    private:

    int pinA;
    int pinB;
    int pinPwm;
    int pinEnc;
    int dir;
    long unsigned int encCount;


};


#endif