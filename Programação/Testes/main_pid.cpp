#include <Arduino.h>
#include <MotorDC.h>
#include <Ultrasonic.h>
#include <Ultrassom.h>
#include <SensorColor.h>
#include <Move.h>
#include <Servo.h>
#include <Ldr.h>

#define STATE_FWD 0 //pid FRENTE
#define STATE_TURN_RIGHT 1 // VIRANDO
#define STATE_TURN_LEFT 2
#define STATE_REV 3 //RÉ


int left; //Infra esquerdo
int right; //Infra direito
int behind; //Infra atrás

//Declarando os objetos dos motores.
MotorDC motorRight (46, 51, 3, 19); 
MotorDC motorLeft (48, 49, 7, 18);
Servo myservo;

//Declarando os obejtos do infravermelho
Ldr infraLeft (A6, 150); //Porta e margem leitura - acima de 80 é preto
Ldr infraRight (A3, 150); //Porta e margem leitura - acima de 80 é preto
Ldr infraBehind (A4, 150); //Porta e margem leitura - acima de 80 é preto


//Declaração de variáveis que serão parâmetros na função moveAllpid.
float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;

//Máquina de estado (Flag)
int state = STATE_FWD; 

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
    attachInterrupt(digitalPinToInterrupt(19), inc, RISING);
    attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
    Serial.begin(9600);
    myservo.attach(5);
    error[0] = 0;
    error[1] = millis();
}

void loop () {
    while(true){

        left = infraLeft.read(3);
        right = infraRight.read(3);
        behind = infraBehind.read(3);
        
        //Serial.print("Left: ");
        //Serial.print(infraLeft.filter(1));
        //Serial.print("; Right: ");
        //Serial.print(infraRight.filter(1));
        //Serial.print("; Behind: ");
        //Serial.println(infraBehind.filter(1));
        Serial.print("Giro:");
        Serial.println(giro);


        //Vendo os dois preto
        if (analogRead(A6) > 150 && analogRead(A3) > 150){

            if(state != STATE_REV){
                state = STATE_REV;
                mL = motorLeft.getCount();
                mR = motorRight.getCount();
                giro = mL - mR;
                soma = 0;
                Serial.print("mL: ");
                Serial.print(mL);
                Serial.print("mR: ");
                Serial.print(mR);

            }            
            moveAllpid(-45, &motorLeft, &motorRight, &soma, error, giro);
        } 
        else{
            if(analogRead(A6) > 150) {

                if(state != STATE_TURN_LEFT){
                    motorLeft.rev(45);
                    motorRight.fwd(45);
                    state = STATE_TURN_LEFT;
                }
            } 
            else if (analogRead(A3) > 150){
                if(state != STATE_TURN_RIGHT){
                    motorLeft.fwd(55);
                    motorRight.rev(45);
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
                    Serial.print("mL: ");
                    Serial.print(mL);
                    Serial.print("mR: ");
                    Serial.print(mR);
                }

                moveAllpid(45, &motorLeft, &motorRight, &soma, error, giro);
                
            } 
        }
        
    }

}