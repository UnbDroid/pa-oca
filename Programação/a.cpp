
/*Código da competição interna segue linha.*/


#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrasonic.h>
#include <Ultrassom.h>
#include <SensorColor.h>
#include <Servo.h>
#include <Move.h>
#include <stdio.h>

//Pino do servo é 5.


#define _power 45 
//#define viradaLogDir 1
//#define viradaLogEsq 0
//#define escolhaVira 1


int left; //Infravermelho esquerdo
int right; //Infravermelho direito
int behind; //Infravermelho atrás

char state[32] = "segue_linha"; //Máquina de estados

int flag;
int flag2 = 1;
bool searchWall = false;
int frente; //Ultra frente
//int lado; //Ultra lado
unsigned long timeBegin;
unsigned long timeUpdate;
unsigned long timeBegin2;
unsigned long timeUpdate2;



//Criando os objetos dos motores.
MotorDC motorLeft (51, 49, 3, 18); 
MotorDC motorRight (46, 48, 7, 19);


void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}


//Criando os objetos dos LDR's.
Ldr infraLeft (A6, 80); //Porta e margem leitura - acima de 80 é preto
Ldr infraRight (A3, 80); //Porta e margem leitura - acima de 80 é preto
Ldr infraBehind (A4, 80); //Porta e margem leitura - acima de 80 é preto


//Criando objetos de teste para o ultrassom
Ultrassom ultraFront (34, 32); //Ultrassom da parte frontal ( Echo, Trigger )
Ultrassom ultraSide (42, 40); //Ultrassom da parte lateral ( Echo, Trigger )


//Criando os objetos do sensor de cor
SensorColor colorSensor (8, 9, 11, 10, 12);



void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(18), inc, RISING);
  attachInterrupt(digitalPinToInterrupt(19), incR, RISING);

  Serial.begin(9600);


}

void loop() {
	
	if (strcmp(state, "segue_linha") == 1){
		followLine();
	} 	

	if (strcmp(state, "obstaculo") == 1){
		obstacle();
		sprintf(state, "lacuna");
		}
	
	if(strcmp(state, "lacuna") == 1){
		vain();
		sprintf(state, "pegar_bloco");
	}

	if(strcmp(state, "pegar_bloco") == 1){
		grab();
		sprintf(state, "pegar_bloco");
	}

	if(strcmp(state, "visao") == 1){
		vision();
	} 
  
  
  
}





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









/*

void followLine() {

	esquerdo = infraLeft.read(3);
	direito = infraRight.read(3);
	atras = infraBehind.read(3);
	bool j;
	moveAll(potBase, &motorLeft, &motorRight);

	////Serial.println(esquerdo);
	////Serial.println(direito);
	////Serial.println(atras);
	
	timeBegin = millis();
	while(esquerdo == 1 && direito == 1) {
		timeUpdate = millis();
		
		////Serial.println(motorLeft.getCount());
		////Serial.println("Direito 1 esquerdo 1");
		//////Serial.println(ldrLeft.filter(3));
		//////Serial.println(ldrRight.filter(3));
		
		if (atras == 1) {
			timeBegin2 = millis();
			//gap
			while(atras == 1) {
				if(esquerdo == 0 || direito == 0 || (ultraFront.filter(3) <= 20)) {
					break;
				}
				timeUpdate = millis();
				timeUpdate2 = millis();
				if((timeUpdate - timeBegin) > 80) {
					moveAll(potBase, &motorLeft, &motorRight);
					timeBegin = millis();
				}
				esquerdo = ldrLeft.read(3);
				direito = ldrRight.read(3);
				atras = ldrBehind.read(3);
				//Serial.println("Dentro do atras branco");
				////Serial.println(ldrLeft.filter(3));
				////Serial.println(ldrRight.filter(3));
				timeUpdate = millis();
				if(timeUpdate2 - timeBegin2 > 5000) {
					timeBegin = millis();
					while(ldrLeft.read(3) == 1 && ldrRight.read(3) == 1 && ldrBehind.read(3) == 1) {
						timeUpdate = millis();
						if((timeUpdate - timeBegin) > 500) {
							turnAnticlockwise(potBase-10, &motorLeft, &motorRight);
							if((timeUpdate - timeBegin) > 1000) {
								timeBegin = millis();
							}
						} 
						else {
							turnClockwise(potBase-10, &motorLeft, &motorRight);
							flag = 1;
						}
					}
				}
			}
			////Serial.println(esquerdo);
			////Serial.println(direito);
			////Serial.println(atras);
		}
		if(timeUpdate - timeBegin > 100) {
			moveAll(potBase, &motorLeft, &motorRight);
		}
		
		obstacle();
		
		esquerdo = ldrLeft.read(3);
		direito = ldrRight.read(3);
		atras = ldrBehind.read(3);
	}

	if(esquerdo == 1 && direito == 0) {
	//girar sentido horario ate achar o preto
		timeBegin = millis();
		turnClockwise(potBase, &motorLeft, &motorRight);
		while(direito == 0) {
			timeUpdate = millis();
			if((timeUpdate - timeBegin) > 140) {
				turnClockwise(potBase, &motorLeft, &motorRight);
				timeBegin = millis();
			}
			//Serial.println("Direito 0 esquerdo 1");
			//Serial.println(ldrRight.filter(3));
			direito = ldrRight.read(3);
		}
		moveAll(potBase, &motorLeft, &motorRight);
	}

	else if(direito == 1 && esquerdo == 0) {
	//girar sentido anti horario ate achar o preto
		timeBegin = millis();
		////Serial.println("aqui");
		turnAnticlockwise(potBase, &motorLeft, &motorRight);
		while(esquerdo == 0) {
			timeUpdate = millis();
			if((timeUpdate - timeBegin) > 140) {
				turnAnticlockwise(potBase, &motorLeft, &motorRight);
				timeBegin = millis();
			}
			//Serial.println("Direito 1 esquerdo 0");
			//Serial.println(ldrLeft.filter(3));
			esquerdo = ldrLeft.read(3);
		}
		moveAll(potBase, &motorLeft, &motorRight);
	}

	else if(direito == 0 && esquerdo == 0) {
		moveRevAll(30, &motorLeft, &motorRight);
		//Serial.println("Ambos");
		//Serial.println(ldrLeft.filter(3));
		//Serial.println(ldrRight.filter(3));
	}

	else {
	//erro
	}

}

bool obstacle() {
	int count;
	int front = ultraFront.filter(3);
	int side = 0;
	//lado = ultraSide.filter(3);
	////Serial.println("Obstaculou");
	if(front < 29 && front != 0) { //distancia em centimetros
		if(escolhaVira == viradaLogDir) {
			turnDegrees(potBase,65,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,4, &motorLeft, &motorRight);
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,19, &motorLeft, &motorRight);
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,4, &motorLeft, &motorRight);
			turnDegrees(potBase,65,HORARIO, &motorLeft, &motorRight);
		} else {
			turnDegrees(potBase,65,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,4, &motorLeft, &motorRight);
			turnDegrees(potBase,65,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,18, &motorLeft, &motorRight);
			turnDegrees(potBase,65,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,4, &motorLeft, &motorRight);
			turnDegrees(potBase,65,ANTIHORARIO, &motorLeft, &motorRight);
		}

	}
	else if(frente > 3 && lado > 10 && searchWall == true) {
		int countLeft = 0;
		int c = DIAMETER*PI;
	  int andado = 0;

		while(lado > 10) {
			countLeft = motorLeft.getCount(); //contagem do enconder
			////Serial.println("WHY");
		}

		andado = (countLeft*c)/GIRO;

		stopAll(&motorLeft, &motorRight);
		RevCm(170, andado, &motorLeft, &motorRight); //andar de ré o tanto que andou
		turnDegrees(potBase,90,HORARIO, &motorLeft, &motorRight);
		FowardCm(170,10, &motorLeft, &motorRight); //andar alguns cms para achar a linha e seguir o segue linha
		return true;	// ja passou para a segunda parte do desafio
	}
	else if (lado < 10) {
		searchWall = true;
	}
	return false; // não passou para a segunda parte ainda
}

int decodColor() {
	return 2;
}



void setup () {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(18), inc, RISING);
	attachInterrupt(digitalPinToInterrupt(19), incR, RISING);
}

void loop() {
	//while(true) {
		//Serial.println(ldrLeft.filter(5));
		//Serial.println(ldrRight.filter(3));
		//Serial.println(ldrBehind.filter(3));
		//Serial.println("New");
		//delay(600);
	//}
	if (flag2 == 1) {
		flag2 = 0;
		moveAll(120, &motorLeft, &motorRight);
	}

	delay(80);
	followLine();
	////Serial.println("Resetou");
}

*/