#define M1A 7
#define M1B 6
#define M1 5
#define M2A 12
#define M2B 11
#define M2 10

void setup() {
  //Seta todos os pinos dos motores como output
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2, OUTPUT);

  
}

void loop() {
  //Manda motor 1 girar pra frente
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  analogWrite(M1, 180);

  
  //Manda motor 2 girar pra frente
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  analogWrite(M2, 180);

  //Fica 1 segundo (1000 milissegundos) nessa bagaça
  delay(1000);

  //Manda os dois motores pararem
  digitalWrite(M2A, LOW);
  digitalWrite(M1A, LOW);

  //Espera 1 segundo nessa bagaça
  delay(1000);

  //Manda motor 1 girar pra trás
    //Não precisa setar o pwm dele, é o mesmo valor já determinado no começo do loop
  digitalWrite(M1B, HIGH);
  digitalWrite(M1A, LOW);

  
  //Manda motor 2 girar pra trás
    //Não precisa setar o pwm dele, é o mesmo valor já determinado no começo do loop
  digitalWrite(M2B, HIGH);
  digitalWrite(M2A, LOW);

  //Fica 1 segundo nessa bagaça
  delay(1000);

  //Para os dois motores
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, LOW);

  //e fica 1 segundo assim
  delay(1000);
}
