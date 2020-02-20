//Código utilizado para testar o correto funcionamento de todos os componentes do robô

//Para recuperar a informacao desejada, declare no define quais informacoes deseja obter (se necessario, utilize mais de um define)
//Opcoes disponiveis de define: ALL, SENSORES, SERVO, MOTORES, INFRA, US, COR, BUMPER


#define MOTORES 





#include <Servo.h>
#include "Ultrasonic.h"


//Declaração da posição onde as portas estão localizadas
#define INFRAe A6
#define INFRAd A3
#define INFRAt A4 
#define USf_t 32
#define USf_e 34
#define USd_t 40
#define USd_e 42
#define BumperE 38
#define BumperD 36
#define CorS0 6
#define CorS1 7
#define CorS2 9
#define CorS3 8
#define CorOut 11
#define MeA 51 //m1A
#define MeB 46 //m1B
#define MePwm 3 //m1pwm
#define MeEnc 19 
#define MeEnable 47 //m1En
#define MdA 48 //m2A
#define MdB 49 //m2B 
#define MdPwm 7//fio verde solto, m2pwm
#define MdEnc 18 
#define MdEnable 50 //m2En


#define serv 5



Ultrasonic usf(USf_t,USf_e);
Ultrasonic usd(USd_t,USd_e);
Servo servo;


//Funcoes usadas
int color();
void EncEsq();
void EncDir();


//Macros para determinar a cor lida
#define VERM 1
#define VERDE 2
#define AZUL 3

//Variaveis usadas pela função de cor
int RED=0;
int GREEN=0;
int BLUE=0;

//Variaveis usadas pelos encoders
int encE=0;
int encD=0;
int j, l;
int k = 1;
//Variavel para controle de tempo
//long int lastTimeServo = millis();
//long int lastTimeMotores = millis();


void setup(){
  
  //Definição de todos os pinos como input ou output.
  pinMode(INFRAe, INPUT);
  pinMode(INFRAd, INPUT);
  pinMode(INFRAt, INPUT);
  pinMode(BumperE, INPUT_PULLUP);
  pinMode(BumperD, INPUT_PULLUP);
  pinMode(CorS0, OUTPUT);
  pinMode(CorS1, OUTPUT);
  pinMode(CorS2, OUTPUT);
  pinMode(CorS3, OUTPUT);
  pinMode(CorOut, INPUT);
  pinMode(MeA, OUTPUT);
  pinMode(MeB, OUTPUT);
  pinMode(MePwm, OUTPUT);
  pinMode(MeEnc, INPUT);
  pinMode(MdA, OUTPUT);
  pinMode(MdB, OUTPUT);
  pinMode(MdPwm, OUTPUT);
  pinMode(MdEnc, INPUT);

  servo.attach(serv);

  //Definindo os pinos de interrupt (encoders)
  attachInterrupt(digitalPinToInterrupt(MeEnc), EncEsq, RISING);
  attachInterrupt(digitalPinToInterrupt(MdEnc), EncDir, RISING);
  
  Serial.begin(9600);
}

void loop(){
  
  //Leitura dos ldr.
  #if defined(ALL) || defined(SENSORES) || defined(INFRA)
    Serial.print("INFRAesq: ");
    Serial.print(analogRead(INFRAe));
    Serial.print("; INFRAdir: ");
    Serial.print(analogRead(INFRAd));
    Serial.print("; INFRAtras: ");
    Serial.print(analogRead(INFRAt));
    Serial.print("; ");
  #endif

  
  //Leitura do sensor de cor.
  #if defined(ALL) || defined(SENSORES) || defined(COR)
    Serial.print("Cor: ");
    Serial.print(color());
    Serial.print("; ");
  #endif

  
  //Leitura dos ultrassonicos
  #if defined(ALL) || defined(SENSORES) || defined(US)
    Serial.print("US_f: ");
    Serial.print(usf.Ranging(CM));
    Serial.print("; US_d: ");
    Serial.print(usd.Ranging(CM));
    Serial.print("; ");
  #endif


  //Leitura dos Bumpers
  #if defined(ALL) || defined(SENSORES) || defined(BUMPER)
    Serial.print("Bumper_e: ");
    Serial.print(digitalRead(BumperE));
    Serial.print("Bumper_d: ");
    Serial.print(digitalRead(BumperD));
    Serial.print("; ");
  #endif
  

  //Teste do servo
  #if defined(ALL) || defined(SERVO)
    /*servo.writeMicroseconds(1400);
    delay(1000);
    servo.writeMicroseconds(2000);
    delay(1000);
  */
    l = millis();
    while((j = millis())-l < 2000){       //Muda posicao a cada 2 segundos
      if(k == 0) {
        servo.write(90);
        k = 1;
        Serial.println("passei 1");
      }
    }
    l = millis();
    while((j = millis())-l < 2000){
      if(k == 1){
        servo.write(0);
        k = 0;
        Serial.println("passei 2");
      }
    }
  #endif


  //Teste dos motores
  #if defined(ALL) ||  defined(MOTORES)
    if(millis()%2000 < 1000){     //Muda de sentido de rotacao dos motores a cada 1 seg
      digitalWrite(MeA, HIGH);
      digitalWrite(MeB, LOW);
      analogWrite(MePwm, 80);
      
      digitalWrite(MdA, HIGH);
      digitalWrite(MdB, LOW);
      analogWrite(MdPwm, 80);
    }
    else{
      digitalWrite(MeA, LOW);
      digitalWrite(MeB, HIGH);
      analogWrite(MePwm, 80);
    
      digitalWrite(MdA, LOW);
      digitalWrite(MdB, HIGH);
      analogWrite(MdPwm, 80);
      delay(100);
    }
  
    Serial.print("Enc_e: ");
    Serial.print(encE);
    Serial.print("Enc_d: ");
    Serial.print(encD);
    Serial.print("; ");
  #endif
  
  Serial.println();
}

  





void EncEsq(){
  encE++;
}

void EncDir(){
  encD++;
}



int color()
{
  //Rotina que le o valor das cores
  digitalWrite(CorS0, HIGH);
  digitalWrite(CorS1, LOW);
  digitalWrite(CorS2, LOW);
  digitalWrite(CorS3, LOW);
  //count OUT, pRed, RED
  RED = pulseIn(CorOut, digitalRead(CorOut) == HIGH ? LOW : HIGH);
  digitalWrite(CorS3, HIGH);
  //count OUT, pBLUE, BLUE
  BLUE = pulseIn(CorOut, digitalRead(CorOut) == HIGH ? LOW : HIGH);
  digitalWrite(CorS2, HIGH);
  //count OUT, pGreen, GREEN
  GREEN = pulseIn(CorOut, digitalRead(CorOut) == HIGH ? LOW : HIGH);


  //Verifica se a cor vermelha foi detectada
  if (RED < BLUE && RED < GREEN && RED < 100)
  {
    return VERM;
  }
 
  //Verifica se a cor azul foi detectada
  else if (BLUE < RED && BLUE < GREEN && BLUE < 1000)
  {
    return VERDE;
  }
 
  //Verifica se a cor verde foi detectada
  else if (GREEN < RED && GREEN < BLUE)
  {
    return AZUL;
  }
}

