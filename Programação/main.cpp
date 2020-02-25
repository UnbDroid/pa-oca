#include <Arduino.h>
#include <compIn.h>

#define COLOR_RED 1
#define COLOR_BLUE 2
#define COLOR_GREEN 3


#define STATE_FWD 0 //pid FRENTE
#define STATE_TURN_RIGHT 1 // VIRANDO
#define STATE_TURN_LEFT 2
#define STATE_REV 3 //RÉ
#define potBase 40

#define BumperE 38
#define BumperD 36


int left; //Infra esquerdo
int right; //Infra direito
int behind; //Infra atrás

//Declarando os objetos dos motores.
MotorDC motorRight (46, 51, 3, 19); 
MotorDC motorLeft (48, 49, 7, 18);
Servo myservo;

//Declarando os obejtos do infravermelho
Ldr infraLeft (A6, 600); //Porta e margem leitura - acima de 600 é preto
Ldr infraRight (A3, 600); //Porta e margem leitura - acima de 600 é preto
Ldr infraBehind (A4, 600); //Porta e margem leitura - acima de 600 é preto


//Declarando o objeto do sensor de cor
SensorColor colorSensor(8, 9, 11, 10, 13);
//SensorColor colorSensor(6, 7, 9, 8, 11);


//Declaração de variáveis que serão parâmetros na função moveAllpid.
float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;

//Máquina de estado (Flag)
char state = STATE_FWD; 

//Torre de Hanoi
int encruzilhada = 0;
int hanoi = 0;


int red = 0;

void followLine();
void decodColor();
void towerHanoi();


void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}

void setup () {

	pinMode(A6,INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(BumperD, INPUT_PULLUP);
	pinMode(BumperE, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(19), inc, RISING);
	attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
	Serial.begin(9600);
	myservo.attach(5);
	error[0] = 0;
	error[1] = millis();

	pinMode(colorSensor.pinOut, INPUT);
}

void loop () {

  //int filtragem = colorSensor.filter(10);
  //Serial.println(filtragem);
  //delay(1000);

  //Serial.println(infraLeft.filter(5));

	followLine();
	decodColor();
}



void decodColor() {
  int fitas = 0;
  int filtragem = colorSensor.filter(5);
  //int leitura = colorSensor.color();
  int esquerdo = infraLeft.read(3);
  int direito = infraRight.read(3);
  int encodIni, encodUpd, flag;

if(filtragem != 0) {
  encodIni = motorLeft.getCount();
  encodUpd = motorLeft.getCount();
  flag = 0;
    while((encodUpd - encodIni) < 200) { //leitura das fitas para saber qual decisão tomar
      if(flag == 1 && (encodUpd - encodIni) > 40) {
        encodIni = motorLeft.getCount();
        flag = 0;
        fitas++;
      } 
      else if(flag == 1) {
        flag = 0;
        encodIni = motorLeft.getCount();
      }
      encodUpd = motorLeft.getCount();
      //Serial.println(encodUpd - encodIni);
      filtragem = colorSensor.filter(5);
      while(filtragem != 0) {
        encodUpd = motorLeft.getCount();
        //Serial.println("PORQUE");
        filtragem = colorSensor.filter(5);
        flag = 1;
      }
    }
  }
  //Serial.println("Aqui agora");
  //Serial.println(fitas);

  esquerdo = infraLeft.read(3);
  direito = infraRight.read(3);

  //followLine();
  if(fitas != 0 && (esquerdo == 0 && direito == 0)) { // se há uma leitura de fitas e os dois ldrs da frente são pretos, decide pra qual lado da encruzilhada ir
	if (encruzilhada == 1) { //verifica se ja passou pela encruzilhada
	  towerHanoi();
	}
	if(fitas == 1) {
	  //vira p direita
	  stopAll(&motorLeft, &motorRight);
	  turnDegrees(potBase,100,HORARIO,&motorLeft, &motorRight);
	  encruzilhada = 1;
	  fitas = 0;
	  //followLine();
	}
	else if(fitas == 2){
	  //vira p esquerda
	  stopAll(&motorLeft, &motorRight);
	  turnDegrees(potBase,90,HORARIO,&motorLeft, &motorRight);
	  encruzilhada = 1;
	  fitas = 0;
	  //followLine();
	}
	else if(fitas == 3) {
	  //segue em frente
	  stopAll(&motorLeft, &motorRight);
	  FowardCm(potBase,5,&motorLeft, &motorRight);
	  encruzilhada = 1;
	  fitas = 0;
	  //followLine();
	} else {
	  //error
	  Serial.println(fitas);
	  Serial.println("Não é pra entrar aqui");
	  fitas = 0;
	  encruzilhada = 0;
	  stopAll(&motorLeft, &motorRight);
	}
  }
}


void followLine(){

	   
		left = infraLeft.read(3);
		right = infraRight.read(3);
		behind = infraBehind.read(3);
	 
	 //Vendo os dois preto
		if (analogRead(A6) > 700 && analogRead(A3) > 700){
      /*
      Serial.println("SADASA");

			if(state != STATE_REV){
				state = STATE_REV;
				mL = motorLeft.getCount();
				mR = motorRight.getCount();
				giro = mL - mR;
				soma = 0;
				//Serial.print("mL: ");
				//Serial.print(mL);
				//Serial.print("mR: ");
				//Serial.print(mR);

			}			
			moveAllpid(-37, &motorLeft, &motorRight, &soma, error, giro);
      */
    } 
		else{
			if(analogRead(A6) > 700) {

				if(state != STATE_TURN_LEFT){
					motorLeft.rev(37);
					motorRight.fwd(37);
					state = STATE_TURN_LEFT;
				}
			} 
			else if (analogRead(A3) > 700){
				if(state != STATE_TURN_RIGHT){
					motorLeft.fwd(37);
					motorRight.rev(37);
					state = STATE_TURN_RIGHT;
				}
				
			}
			else {

				if(state != STATE_FWD){				
					state= STATE_FWD;
					mL = motorLeft.getCount();
					mR = motorRight.getCount();
					giro = mL - mR;
					soma = 0;
					//Serial.print("mL: ");
					//Serial.print(mL);
					//Serial.print("mR: ");
					//Serial.print(mR);
				}

				moveAllpid(37, &motorLeft, &motorRight, &soma, error, giro);
				
			} 
		}
	   
	}

void towerHanoi(){
	//nois
}




