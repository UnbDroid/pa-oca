#ifndef SENSORCOLOR_H
#define SENSORCOLOR_H
#define COLOR_RED 1
#define COLOR_BLUE 2
#define COLOR_GREEN 3

class SensorColor
{
public:

     /* SensorColor
      Descricao: Construtor da Classe.
      Parâmetros:
        - pinS0, pinS1, pinS2, pinS3, pinOut: Pinos digitais que o sensor de cor está conectado. 
    */
    SensorColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut);

    // Desconstrutor
    ~SensorColor();

    
     /* color
      Descricao: Método que detecta a cor que o sensor está vendo.
      Parâmetros:
        - pinS0, pinS1, pinS2, pinS3, pinOut: Pinos digitais que o sensor de cor está conectado. 
    */
    int color();

    /* filter
      Descricao: Função que retorna um valor de filtragem.
      Parâmetros:
        - count: Quantidade de valores da amostra que será filtrado.
        
    */
    int filter(int count);
    

private:

// Declaração de variáveis
    int pinS0;
    int pinS1;
    int pinS2;
    int pinS3;
    int pinOut;   

};

#endif
