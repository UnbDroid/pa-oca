#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrassom.h>
#include <Move.h>

MotorDC motorLeft (12, 11, 10); //pinos
MotorDC motorRight (7, 6, 5); //pinos
Ldr ldrLeft (A0, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrRight (A1, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrBehind (A2, 600); //Porta e margem leitura - acima de 600 é preto
Ultrassom ulltraFront (1, 2); //Ultrassom da parte frontal
//Ultrassom ultraSide (3, 4);

void followLine() {
	esquerdo = ldrLeft.read(5);
	direito = ldrRight.read(5);
	atras = ldrBehind.read(5);
	moveAll(40);

	while(esquerdo == 1 && direito == 1) {
		if(atras == 0 && flag == 0) {
			moveAll(40);
			flag = 1;
		}
		else if (atras == 1) {
			flag = 0;
			timeBegin = milis();
			//gap
			while(atras == 1) {
				if(esquerdo == 0 || direito == 0) {
					break;
				}
				esquerdo = ldrLeft.read(5);
				direito = ldrRight.read(5);
				atras = ldrBehind.read(5);
				timeUpdate = milis();
				if(timeUpdate - timeBegin > 2000) {
				//tem que se achar
				}
			}
		}
		else {
			obstacle();
		}
		esquerdo = ldrLeft.read(5);
		direito = ldrRight.read(5);
		atras = ldrBehind.read(5);
	}

	if(esquerdo == 1 && direito == 0) {
	//girar sentido horario ate achar o preto
		turnClockwise(20);
		while(direito == 0) {
			direito = ldrRight.read(5);
		}
		moveAll(40);
	}

	else if(direito == 1 && esquerdo == 0) {
	//girar sentido anti horario ate achar o preto
		turnAnticlockwise(20);
		while(esquerdo == 0) {
			esquerdo = ldrLeft.read(5);
		}
		moveAll(40);
	}

	else if(direito == 0 && esquerdo == 0) {
	//encruzilhada
		while(direito == 0 && esquerdo == 0) {
			esquerdo = ldrLeft.read(5);
			direito = ldrRight.read(5);
			atras = ldrBehind.read(5);
			if(atras == 1) {
				break;
			}
		}
	}

	else {
	//erro
	}

}

bool obstacle() {
	int contador;
	frente = ultraFront.filter(5);
	//lado = ultraSide.filter(5);
	if(frente < 5) { //distancia em centimetros
		turnDegrees(40,90,HORARIO);
		FowardCm(5);
		turnDegrees(40,90,ANTIHORARIO);
		FowardCm(8);
		turnDegrees(40,90,ANTIHORARIO);
		FowardCm(5);
	}
	else if(frente > 5 && lado > 10 && searchWall == true) {
		int countLeft = 0;
		int c = DIAMETER*PI;
	  int andado = 0;

		while(lado > 10) {
			countLeft = motorLeft.getencCount(); //contagem do enconder																		//calcular o tanto que andou
		}

		andado = (countLeft*c)/GIRO;

		stopAll();
		RevCm(andado); //andar de ré o tanto que andou
		turnDegrees(40,90,HORARIO);
		FowardCm(10); //andar alguns cms para achar a linha e seguir o segue linha
		return true;	// ja passou para a segunda parte do desafio
	}
	else if (lado < 10) {
		searchWall = true;
	}
	return false; // não passou para a segunda parte ainda
}

int decodColor() {

}



void setup () {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	int esquerdo; //LDR esquerdo
	int direito; //LDR direito
	int atras; //LDR atrás
	int flag;
	bool searchWall = false;
	int frente; //Ultra frente
	//int lado; //Ultra lado
	unsigned long timeBegin;
	unsigned long timeUpdate;
}

void loop() {
	followLine();

}
