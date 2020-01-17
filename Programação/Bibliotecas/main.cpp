
/*Código de teste da biblioteca nos motores.*/

/*
#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrasonic.h>
#include <Ultrassom.h>
#include <SensorColor.h>



//Criando os objetos dos motores.
MotorDC motorLeft (12, 11, 10, 20);
//MotorDC motorRight (7, 6, 5);

void inc (){

  motorLeft.encSignal();
  
}

//Criando os objetos dos LDR's.
Ldr ldrLeft (A0, 600);

//Criando objetos de teste para o ultrassom
Ultrassom usa (51, 50); 

//Ultrasonic usa(50, 51);

//Criando os objetos do sensor de cor
SensorColor colorSensor (38, 40, 34, 32, 36);



void setup() {

  //pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(20), inc, RISING);

  Serial.begin(9600);

}

void loop() {

  /* 
  
  ------- Teste do Motores ---------
  
  //Motor anda para frente por 1 segundo.
  motorLeft.fwd(40);
  motorRight.fwd(40);
  delay(1000);

  //Motor anda para trás por 1 segundo.
  motorLeft.rev(40);
  motorRight.rev(40);
  delay(1000);

  //Motores param por 1 segundo.
  motorRight.stop();
  motorLeft.stop();
  delay(1000);

  
  ------- Teste do LDR's ---------

  // int leitura = ldrLeft.filter(10);
  // Serial.println(leitura);

  if (ldrLeft.read(10)){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Acima de 600 = preto! 

   
  ------- Teste do Ultrassom ---------
  

  //Teste o ultrassom com o Led Builtin
  //int ultrassom = usa.acende();

  //Teste do Ultrassom 
  int ultrassom = usa.filter(10);
  Serial.print(ultrassom);
  Serial.println("cm");
  delay(100);



  ------- Teste do Sensor de Cor ---------

  //int leitura = colorSensor.color();
  //Serial.println(leitura);

  int filtragem = colorSensor.filter(10);
  Serial.println(filtragem);

  

  motorLeft.rev(40);
  Serial.println(motorLeft.getCount());
  delay(100);
}
*/

#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrassom.h>
#include <Move.h>

int esquerdo; //LDR esquerdo
int direito; //LDR direito
int atras; //LDR atrás
int flag;
bool searchWall = false;
int frente; //Ultra frente
//int lado; //Ultra lado
unsigned long timeBegin;
unsigned long timeUpdate;

bool obstacle();

MotorDC motorLeft (51, 49, 3, 18); //pinos
MotorDC motorRight (48, 46, 2, 19); //pinos
Ldr ldrLeft (A6, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrRight (A3, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrBehind (A4, 600); //Porta e margem leitura - acima de 600 é preto
Ultrassom ultraFront (5, 4); //Ultrassom da parte frontal
//Ultrassom ultraSide (3, 4);

void followLine() {
	esquerdo = ldrLeft.read(5);
	direito = ldrRight.read(5);
	atras = ldrBehind.read(5);
	bool j;
	moveAll(40, motorLeft, motorRight);

	while(esquerdo == 1 && direito == 1) {
		if(atras == 0 && flag == 0) {
			moveAll(40, motorLeft, motorRight);
			flag = 1;
		}
		else if (atras == 1) {
			flag = 0;
			timeBegin = millis();
			//gap
			while(atras == 1) {
				if(esquerdo == 0 || direito == 0) {
					break;
				}
				esquerdo = ldrLeft.read(5);
				direito = ldrRight.read(5);
				atras = ldrBehind.read(5);
				timeUpdate = millis();
				if(timeUpdate - timeBegin > 2000) {
				//tem que se achar
				}
			}
		}
		else {
			j = obstacle();
		}
		esquerdo = ldrLeft.read(5);
		direito = ldrRight.read(5);
		atras = ldrBehind.read(5);
	}

	if(esquerdo == 1 && direito == 0) {
	//girar sentido horario ate achar o preto
		turnClockwise(20, motorLeft, motorRight);
		while(direito == 0) {
			direito = ldrRight.read(5);
		}
		moveAll(40, motorLeft, motorRight);
	}

	else if(direito == 1 && esquerdo == 0) {
	//girar sentido anti horario ate achar o preto
		turnAnticlockwise(20, motorLeft, motorRight);
		while(esquerdo == 0) {
			esquerdo = ldrLeft.read(5);
		}
		moveAll(40, motorLeft, motorRight);
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
	int lado = 0;
	//lado = ultraSide.filter(5);
	if(frente < 5) { //distancia em centimetros
		turnDegrees(40,90,HORARIO, motorLeft, motorRight);
		FowardCm(180,5, motorLeft, motorRight);
		turnDegrees(40,90,ANTIHORARIO, motorLeft, motorRight);
		FowardCm(180,8, motorLeft, motorRight);
		turnDegrees(40,90,ANTIHORARIO, motorLeft, motorRight);
		FowardCm(180,5, motorLeft, motorRight);
	}
	else if(frente > 5 && lado > 10 && searchWall == true) {
		int countLeft = 0;
		int c = DIAMETER*PI;
	  int andado = 0;

		while(lado > 10) {
			countLeft = motorLeft.getCount(); //contagem do enconder																		//calcular o tanto que andou
		}

		andado = (countLeft*c)/GIRO;

		stopAll(motorLeft, motorRight);
		RevCm(180, andado, motorLeft, motorRight); //andar de ré o tanto que andou
		turnDegrees(40,90,HORARIO, motorLeft, motorRight);
		FowardCm(180,10, motorLeft, motorRight); //andar alguns cms para achar a linha e seguir o segue linha
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
