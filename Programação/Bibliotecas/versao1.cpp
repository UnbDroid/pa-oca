#include <MotorDC.cpp>
#include <Ldr.cpp>
#include <Ultrassom.cpp>
#include <Move.cpp>

MotorDC motorLeft (12, 11, 10); //pinos
MotorDC motorRight (7, 6, 5); //pinos
Ldr ldrLeft (A0, 600); //porta e margem leitura - acima de 600 é preto
Ldr ldrRight (A1, 600); //porta e margem leitura - acima de 600 é preto
Ldr ldrBehind (A2, 600); //porta e margem leitura - acima de 600 é preto
Ultrassom ulltraFront (1, 2);
Ultrassom ultraSide (3, 4);

void followLine() {
  int esquerdo = ldrLeft.read(5);
  int direito = ldrRight.read(5);
  int atras = ldrBehind.read(5);
  moveAll(40);

  if(esquerdo == 1 && direito == 1) {
    if(atras == 0) {
      moveAll(40);
    }
    else {
      int tempo = 0;
      //gap
      while(atras == 1) {
        atras = ldrBehind.read(5);
        moveAll(40);
        tempo++;
        if(tempo>10) {
          //tem que se achar
        }
      }
      followLine();
    }
  }

  else if(esquerdo == 1 && direito == 0) {
    //girar sentido horario ate achar o preto
    while(direito == 0) {
      direito = ldrRight.read(5);
      turnClockwise();
    }
    moveAll(40);
  }

  else if(direito == 1 && esquerdo == 0) {
    //girar sentido anti horario ate achar o preto
    while(esquerdo == 0) {
      esquerdo = ldrLeft.read(5);
      turnAnticlockwise();
    }
    moveAll(40);
  }

  else if(direito == 0 && esquerdo == 0) {
    //encruzilhada
  }

  else {
    //erro
  }

}

bool obstacle() {
  int frente = ultraFront.filter(5);
  int lado = ultraSide.filter(5);
  if(frente < 5) { //distancia em centimetros
    turnDegrees(40,90,HORARIO);
    FowardCm(5);
    turnDegrees(40,90,ANTIHORARIO);
    FowardCm(8);
    turnDegrees(40,90,ANTIHORARIO);
    FowardCm(5);
  }
  else if(frente > 5 && lado > 10) {
    int contador = 0;
    while(lado>10) {
      //contador = contagemEnconder
      //calcular o tanto que andou
    }
    stopAll();
    RevCm(); //o tanto que andou
    turnDegrees(40,90,HORARIO);
    FowardCm(); //andar alguns cms para achar a linha e seguir o segue linha
    return true;  // ja passou para a segunda parte do desafio
  }
  else {
  return false; // não passou para a segunda parte ainda
  }
}

int decodColor() {

}



void setup () {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

}
