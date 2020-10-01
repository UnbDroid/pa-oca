#ifndef SENSORCOLOR_H
#define SENSORCOLOR_H
#define COLOR_RED 1
#define COLOR_BLUE 2
#define COLOR_GREEN 3

class SensorColor
{
public:

    //Construtor e Destrutor da classe SensorColor.
    SensorColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut);
    ~SensorColor();

    //Método que detecta a cor.
    int color();

    //Método de filtragem.
    int filter(int count);
    int pinOut;

private:

    int pinS0;
    int pinS1;
    int pinS2;
    int pinS3;

    

};











#endif
