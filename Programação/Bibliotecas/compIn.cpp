#include <Arduino.h>
#include <compIn.h>


char state[32] = "segue_linha"; //Máquina de estados


void followLine(){

	int front = ultraFront.filter(3);

	if(front < 29 && front != 0) {

		/*Função obstáculo*/
		sprintf(state, "obstaculo");

	} else {
		/*Função segue linha*/
	}
}


 void obstacle(){

		 int side = ultraSide.filter(3);

	 	/*Robô stop para fazer movimentação de desvio do obstáculo*/
	 	stopAll(&motorLeft, &motorRight);

		/*Movimentação de desvio do obstáculo*/ 
		turnDegrees(_power,65,HORARIO, &motorLeft, &motorRight);
		FowardCm(_power,4, &motorLeft, &motorRight);
		turnDegrees(_power,70,ANTIHORARIO, &motorLeft, &motorRight);
		FowardCm(_power,19, &motorLeft, &motorRight);
		turnDegrees(_power,70,ANTIHORARIO, &motorLeft, &motorRight);
		FowardCm(_power,4, &motorLeft, &motorRight);
		turnDegrees(_power,65,HORARIO, &motorLeft, &motorRight);

		/*Começar a verificar se tem vão ou não*/
		if (side > 10 /*mais alguma coisa*/ ){
			followLine(); //Conferir se quando ele estiver virando e olhar para a parede será menor que 29.
		}else{
			sprintf(state, "lacuna");
		}

 }


 void vain(){

	 /*Função para passar pelo vão utilizando os bumpers*/
	 /*Quando achar os blocos, ou seja, o ultrassom da frente os ver mudar de state para GRAB*/

 }




void grab() {

	/*São três blocos, depois de pegar o terceito bloco (saber a quantidade colocando em um vetor) muda de state para visão*/
	/*Função de abrir a garra e levar para os locais adequados*/

}





void vision(){

	/*Não faço ideia, mas é isto!*/
}