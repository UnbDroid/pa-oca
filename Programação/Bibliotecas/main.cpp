
/*Código de teste da biblioteca nos motores.*/

/*
#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrasonic.h>
#include <Ultrassom.h>
#include <SensorColor.h>



//Criando os objetos dos motores.
MotorDC motorLeft (49, 31, 3, 18); //pinos
MotorDC motorRight (48, 46, 13, 19); //pinos

void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}


//Criando os objetos dos LDR's.
Ldr ldrLeft (A6, 600); //Porta e margem leitura - acima de 700 é preto
Ldr ldrRight (A3, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrBehind (A4, 600); //Porta e margem leitura - acima de 600 é preto


//Criando objetos de teste para o ultrassom
Ultrassom ultraFront (3, 4); //Ultrassom da parte frontal 

/*
//Criando os objetos do sensor de cor
SensorColor colorSensor (38, 70, 34, 32, 36);

*/
/*
void setup() {

  //pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(18), inc, RISING);
  attachInterrupt(digitalPinToInterrupt(19), incR, RISING);

  Serial.begin(9600);

}

void loop() {

  
  /*
  //------- Teste do Motores ---------
  
  //Motor anda para frente por 1 segundo.
  motorLeft.fwd(potBase);
  motorRight.fwd(33);
  delay(1000);

	Serial.print(motorLeft.getCount());
	Serial.print(' ');
	Serial.println(motorRight.getCount());
	delay(100);

  //Motor anda para trás por 1 segundo.
  motorLeft.rev(potBase);
  motorRight.rev(potBase);
  delay(1000);

  //Motores param por 1 segundo.
  motorRight.stop();
  motorLeft.stop();
  delay(1000);
  */
 
  
  //------- Teste do LDR's ---------

   //int leitura = ldrLeft.filter(10);
   //Serial.println(leitura);

  //if (ldrLeft.read(10)){
  //  digitalWrite(LED_BUILTIN, HIGH);
  //}else{
  //  digitalWrite(LED_BUILTIN, LOW);
  //}

  // Acima de 600 = preto! 

   /*
  //------- Teste do Ultrassom ---------
  

  //Teste o ultrassom com o Led Builtin
  //int ultrassom = usa.acende();

  //Teste do Ultrassom 
  int ultrassom = ultraFront.filter(10);
  Serial.print(ultrassom);
  Serial.println("cm");
  delay(100);
  


	/*
  //------- Teste do Sensor de Cor ---------

  //int leitura = colorSensor.color();
  //Serial.println(leitura);

  int filtragem = colorSensor.filter(10);
  Serial.println(filtragem);

  

  motorLeft.rev(potBase);
  Serial.println(motorLeft.getCount());
  delay(100);

  
}

*/


#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>
#include <Ultrassom.h>
#include <Move.h>

#define potBase 38
#define viradaLogDir 1
#define viradaLogEsq 0
#define escolhaVira 0

int esquerdo; //LDR esquerdo
int direito; //LDR direito
int atras; //LDR atrás
int flag;
int flag2 = 1;
bool searchWall = false;
int frente; //Ultra frente
//int lado; //Ultra lado
unsigned long timeBegin;
unsigned long timeUpdate;
unsigned long timeBegin2;
unsigned long timeUpdate2;

bool obstacle();

MotorDC motorLeft (49, 51, 3, 18); //pinos
MotorDC motorRight (48, 46, 13, 19); //pinos
Ldr ldrLeft (A6, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrRight (A3, 600); //Porta e margem leitura - acima de 600 é preto
Ldr ldrBehind (A4, 450); //Porta e margem leitura - acima de 600 é preto
Ultrassom ultraFront (5, 4); //Ultrassom da parte frontal
//Ultrassom ultraSide (3, 4);

void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}

void followLine() {
	esquerdo = ldrLeft.read(3);
	direito = ldrRight.read(3);
	atras = ldrBehind.read(3);
	bool j;
	moveAll(potBase, &motorLeft, &motorRight);

	Serial.println(esquerdo);
	Serial.println(direito);
	Serial.println(atras);
	
	timeBegin = millis();
	while(esquerdo == 1 && direito == 1) {
		timeUpdate = millis();
		
		Serial.println(motorLeft.getCount());
		Serial.println("Direito 1 esquerdo 1");
		//Serial.println(ldrLeft.filter(3));
		//Serial.println(ldrRight.filter(3));
		if(atras == 0 && flag == 0) {
			moveAll(potBase, &motorLeft, &motorRight);
			flag = 1;
		}
		else if (atras == 1) {
			flag = 0;
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
				Serial.println("Dentro do atras branco");
				Serial.println(ldrLeft.filter(3));
				Serial.println(ldrRight.filter(3));
				timeUpdate = millis();
				if(timeUpdate2 - timeBegin2 > 4000) {
					timeBegin = millis();
					while(ldrLeft.read(3) == 1 && ldrRight.read(3) == 1 && ldrBehind.read(3) == 1) {
						timeUpdate = millis();
						if((timeUpdate - timeBegin) > 500) {
							turnAnticlockwise(potBase, &motorLeft, &motorRight);
							if((timeUpdate - timeBegin) > 1000) {
								timeBegin = millis();
							}
						} 
						else {
							turnClockwise(potBase, &motorLeft, &motorRight);
							flag = 1;
						}
					}
				}
			}
			Serial.println(esquerdo);
			Serial.println(direito);
			Serial.println(atras);
		}
		if(timeUpdate - timeBegin > 120) {
			break;
		}
		j = obstacle();
		
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
			if((timeUpdate - timeBegin) > 120) {
				turnClockwise(potBase, &motorLeft, &motorRight);
				timeBegin = millis();
			}
			Serial.println("Direito 0 esquerdo 1");
			Serial.println(ldrRight.filter(3));
			direito = ldrRight.read(3);
		}
		moveAll(potBase, &motorLeft, &motorRight);
	}

	else if(direito == 1 && esquerdo == 0) {
	//girar sentido anti horario ate achar o preto
		timeBegin = millis();
		Serial.println("aqui");
		turnAnticlockwise(potBase, &motorLeft, &motorRight);
		while(esquerdo == 0) {
			timeUpdate = millis();
			if((timeUpdate - timeBegin) > 120) {
				turnAnticlockwise(potBase, &motorLeft, &motorRight);
				timeBegin = millis();
			}
			Serial.println("Direito 1 esquerdo 0");
			Serial.println(ldrLeft.filter(3));
			esquerdo = ldrLeft.read(3);
		}
		moveAll(potBase, &motorLeft, &motorRight);
	}

	else if(direito == 0 && esquerdo == 0) {
		moveRevAll(30, &motorLeft, &motorRight);
	}

	else {
	//erro
	}

}

bool obstacle() {
	int contador;
	frente = ultraFront.filter(3);
	int lado = 0;
	//lado = ultraSide.filter(3);
	Serial.println("Obstaculou");
	if(frente < 23 && frente != 0) { //distancia em centimetros
		if(escolhaVira == viradaLogDir) {
			turnDegrees(potBase,70,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,8, &motorLeft, &motorRight);
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,21, &motorLeft, &motorRight);
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,8, &motorLeft, &motorRight);
			turnDegrees(potBase,70,HORARIO, &motorLeft, &motorRight);
		} else {
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,8, &motorLeft, &motorRight);
			turnDegrees(potBase,70,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,21, &motorLeft, &motorRight);
			turnDegrees(potBase,70,HORARIO, &motorLeft, &motorRight);
			FowardCm(potBase+10,8, &motorLeft, &motorRight);
			turnDegrees(potBase,70,ANTIHORARIO, &motorLeft, &motorRight);
		}

	}
	else if(frente > 3 && lado > 10 && searchWall == true) {
		int countLeft = 0;
		int c = DIAMETER*PI;
	  int andado = 0;

		while(lado > 10) {
			countLeft = motorLeft.getCount(); //contagem do enconder
			Serial.println("WHY");
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
/*	while(true) {
		Serial.println(ultraFront.filter(5));
		//Serial.println(ldrRight.filter(3));
		//Serial.println(ldrBehind.filter(3));
		Serial.println("New");
		delay(600);
	}*/
	if (flag2 == 1) {
		flag2 = 0;
		moveAll(120, &motorLeft, &motorRight);
	}

	delay(80);
	followLine();
	Serial.println("Resetou");
}

