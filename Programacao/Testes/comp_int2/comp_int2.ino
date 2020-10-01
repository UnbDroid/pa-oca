/*
#define LED 42
#define ALTO 44
#define LDR A1

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(ALTO, OUTPUT);
  pinMode(LDR, INPUT);

  Serial.begin(9600);

  digitalWrite(LED, HIGH);
  digitalWrite(ALTO, HIGH);
}

void loop() {
  Serial.println(analogRead(LDR));
}

*/



#define M1A 7
#define M1B 6
#define M1 5
#define M2A 12
#define M2B 11
#define M2 10
#define LED 42
#define ALTO 44
#define LDR A1
#define LED2 48
#define ALTO2 50
#define LDR2 A4
#define pot 180


void moveMotorLeft(int potencia) {
  if (potencia != 0) {
    if (potencia < 0) {
      digitalWrite(M1A, LOW);
      digitalWrite(M1B, HIGH);
    } else {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
    }
    analogWrite(M1, abs(potencia));
  } else {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
  }
}

void moveMotorRight(int potencia) {
  if (potencia != 0) {
    if (potencia < 0) {
    digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
    } else {
      digitalWrite(M2A, LOW);
      digitalWrite(M2B, HIGH);
    }
    analogWrite(M2, abs(potencia));
  } else {
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
  }
}

//int leitura1 =  analogRead(LDR);

//Branco menor que 200;
//Preto maior que 200;

void LEDLeft(int leitura1, int potencia) {
 
    if (leitura1 > 300) {
      moveMotorRight(potencia);
      moveMotorLeft(0);
    } else {
      moveMotorRight(potencia);
      moveMotorLeft(potencia);
    }
}


void LEDRight(int leitura2, int potencia) {
 
    if (leitura2 > 300) {
      moveMotorLeft(potencia);
      //delay(1);
      //moveMotorLeft((potencia)/4);
      moveMotorRight(0);
    } else {
      moveMotorRight(potencia);
      moveMotorLeft(potencia);
    }
}
     
    


void setup() {
  //Seta todos os pinos dos motores como output
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(LED, OUTPUT);
  pinMode(ALTO, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(ALTO2, OUTPUT);
  pinMode(LDR2, INPUT);

  digitalWrite(LED, HIGH);
  digitalWrite(ALTO, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(ALTO2, HIGH);

  Serial.begin(9600);


  
  
/*
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  analogWrite(M2, abs(pot));
  
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  analogWrite(M1, abs(pot));

  delay(1000);

  */



}

void loop() { 
  

  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  analogWrite(M2, 180);
  delay(1000);
  
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  analogWrite(M1, 180);
  delay(1000);

  /*
  Serial.print("LDR1 :");
  Serial.println(analogRead(LDR));
  delay(1000);
  Serial.print("LDR2 :");
  Serial.println(analogRead(LDR2));
  */
  
  LEDLeft(analogRead(LDR), 180);
  delay(1000);
  LEDRight(analogRead(LDR2), 180);
  delay(1000);
  
  
}
  
