#ifndef MOVE_H
#define MOVE_H

#include <MotorDC.h>

#define HORARIO 0
#define ANTIHORARIO 1
#define DIAMETER 5.5 //roda tem 5,5cm de diametro
//#define PI 3.14159265359
#define GIRO 400 //o enconder conta 400 para dar 1 giro na roda
#define WDIST 27.6 //distancia entre as duas rodas em cm

/* Move All
  Descricao: Liga os dois motores.
  Parâmetros:
    - potencia: Potência desejada.
*/

void moveAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight);

/* Stop All
  Descricao: Desliga os dois motores.
*/

void moveRevAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight);

void stopAll(MotorDC *motorLeft, MotorDC *motorRight);

/* Turn Clockwise
  Descricao: Gira no sentido horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnClockwise(int potencia, MotorDC *motorLeft, MotorDC *motorRight);

/* Turn Anti Clockwise
  Descricao: Gira no sentido anti horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnAnticlockwise(int potencia, MotorDC *motorLeft, MotorDC *motorRight);

/* Turn Degrees
  Descricao: Gira em uma determinada direção, determinada quantidade de graus.
  Parâmetros:
    - potencia: Potência desejada.
    - graus: Quantidade de graus que se deseja girar.
    - direcao: Direção desejada HORARIO OU ANTIHORARIO
*/

void turnDegrees(int potencia, int graus, int direcao, MotorDC *motorLeft, MotorDC *motorRight);

/* Foward Cm
  Descricao: Anda para frente uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void FowardCm(int potencia, int distance, MotorDC *motorLeft, MotorDC *motorRight);

/* Rev Cm
  Descricao: Anda para trás uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void RevCm(int potencia, int distance, MotorDC *motorLeft, MotorDC *motorRight);

#endif
