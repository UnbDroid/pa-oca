#include <Arduino.h>
#include <compIn.h>


char state[32] = "segue_linha"; //Máquina de estados


void followLine(int potencia, MotorDC *motorLeft, MotorDC *motorRight, Ultrassom *ultraFront) {

	int front = ultraFront->filter(3);

	if(front < 29 && front != 0) {

		/*Função obstáculo*/
		sprintf(state, "obstaculo");

	} else {
		/*Função segue linha*/
	}
}


void obstacle(int _power, MotorDC *_motorLeft, MotorDC *_motorRight, Ultrassom *_ultraFront){
	/*Robô stop para fazer movimentação de desvio do obstáculo*/
	stopAll(_motorLeft, _motorRight);

	/*Movimentação de desvio do obstáculo*/ 
	turnDegrees(_power,65,HORARIO, _motorLeft, _motorRight);
	FowardCm(_power,4, _motorLeft, _motorRight);
	turnDegrees(_power,70,ANTIHORARIO, _motorLeft, _motorRight);
	FowardCm(_power,19, _motorLeft, _motorRight);
	turnDegrees(_power,70,ANTIHORARIO, _motorLeft, _motorRight);
	FowardCm(_power,4, _motorLeft, _motorRight);
	turnDegrees(_power,65,HORARIO, _motorLeft, _motorRight);
}


void vain(Ultrassom _ultraSide, MotorDC *_motorRight, MotorDC *_motorLeft, bool *_foundWall, Ldr _infraLeft, Ldr _infraRight, int _bumperD, int _bumperE){
	/*Função para passar pelo vão utilizando os bumpers*/
	int sideDis = _ultraSide.filter(4);

	if(sideDis < 250 && (*_foundWall) == false) {
		*_foundWall = true;
	} 
	if(*_foundWall and sideDis > 400) {
		FowardCm(37, 5, _motorLeft, _motorRight);
		turnDegrees(37, 90, HORARIO, _motorLeft, _motorRight);
		moveAll(37, _motorLeft, _motorRight);
		while(_infraLeft.read(4) || _infraRight.read(4)) {
			if(digitalRead(_bumperD) == LOW){
				//Substituir as referências do bumper por nomes, funções e classes reais.
				turnDegrees(37, 15, HORARIO, _motorLeft, _motorRight);
				RevCm(37, 7, _motorLeft, _motorRight);
				turnDegrees(37, 15, ANTIHORARIO, _motorLeft, _motorRight);
				moveAll(37, _motorLeft, _motorRight);
			}
			if(digitalRead(_bumperE) == LOW){
				//Substituir as referências do bumper por nomes, funções e classes reais.
				turnDegrees(37, 15, ANTIHORARIO, _motorLeft, _motorRight);
				RevCm(37, 7, _motorLeft, _motorRight);
				turnDegrees(37, 15, HORARIO, _motorLeft, _motorRight);
				moveAll(37, _motorLeft, _motorRight);
			}
		}
		stopAll(_motorLeft, _motorRight);
		//Passar para segunda parte do desafio
	}
}




void grab() {

	/*São três blocos, depois de pegar o terceito bloco (saber a quantidade colocando em um vetor) muda de state para visão*/
	/*Função de abrir a garra e levar para os locais adequados*/

}





void vision(){

	/*Não faço ideia, mas é isto!*/
}