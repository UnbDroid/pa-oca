#include <Arduino.h>
#include <SensorColor.h>
#include <math.h>

SensorColor::SensorColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut)
{
    this->pinOut = pinOut;
    this->pinS0 = pinS0;
    this->pinS1 = pinS1;
    this->pinS2 = pinS2;
    this->pinS3 = pinS3;

    pinMode(pinOut, INPUT);
    pinMode(pinS0, OUTPUT);
    pinMode(pinS1, OUTPUT);
    pinMode(pinS2, OUTPUT);
    pinMode(pinS3, OUTPUT);

    digitalWrite(pinS0, HIGH);
    digitalWrite(pinS1, LOW);
    
}

SensorColor::~SensorColor()
{
}

//Método que detecta a color lida.
int SensorColor::color(){

  //Variaveis cores
  int red = 0;
  int green = 0;
  int blue = 0;


  //Rotina que le o valor das cores
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);

  //count OUT, pred, red
  red = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  digitalWrite(pinS3, HIGH);
  //count OUT, pblue, blue
  blue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  digitalWrite(pinS2, HIGH);
  //count OUT, pgreen, green
  green = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Verifica se a cor vermelha foi detectada
  if (red < blue && red < green && red < 100)
  {
    return COLOR_RED;
  }
 
  //Verifica se a cor azul foi detectada
  else if (blue < red && blue < green && red > 30)
  {
    return COLOR_BLUE;
  }
 
  //Verifica se a cor verde foi detectada
  else if (green < red && blue < red && red < 30)
  {
    return COLOR_GREEN;
  } else{
    return 0; //Caso não detecte nada, retorna-se zero.
  }
}

  //Método de filtragem
  int SensorColor::filter(int count){

    int v[4] = {0};

    //Salva as leituras e decide quem repetiu mais vezes
    for (int i = 0; i<=count; i++){
      v[color()] += 1;
    }

    //Faz a comparação e diz quantas vezes um desses vetores foi mais incrementado.
    int n = fmax(fmax(v[0], v[1]), fmax(v[2], v[3]));

    //Diz o índice do vetor que foi mais incrementado.
    for (int i = 0; i<=3; i++){
      if(n == v[i]){
        return i;
      }
    }

    return -1;
  }


 


