#include <Ultrasonic.h>

#define ECHO 24
#define TRIG 22


Ultrasonic ultrassom(TRIG,ECHO);

long dist;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  dist = ultrassom.Ranging(CM); // Vai retornar o valor em centimetros
  
  Serial.print(dist);
  Serial.println("cm");
  delay(100);
}

