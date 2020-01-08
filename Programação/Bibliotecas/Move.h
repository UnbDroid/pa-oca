#ifndef MOVE_H
#define MOVE_H

#define HORARIO 0
#define ANTIHORARIO 1

/* Move All
  Descricao: Liga os dois motores.
  Parâmetros:
    - potencia: Potência desejada.
*/

void moveAll(int potencia);

/* Stop All
  Descricao: Desliga os dois motores.
*/

void stopAll();

/* Turn Clockwise
  Descricao: Gira no sentido horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnClockwise(int potencia);

/* Turn Anti Clockwise
  Descricao: Gira no sentido anti horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnAnticlockwise(int potencia);

/* Turn Degrees
  Descricao: Gira em uma determinada direção, determinada quantidade de graus.
  Parâmetros:
    - potencia: Potência desejada.
    - graus: Quantidade de graus que se deseja girar.
    - direcao: Direção desejada HORARIO OU ANTIHORARIO
*/

void turnDegrees(int potencia, int graus, int direcao);

/* Foward Cm
  Descricao: Anda para frente uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void FowardCm(int potencia, int distance);

/* Rev Cm
  Descricao: Anda para trás uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void RevCm(int potencia, int distance);

#endif
