//Programa: Sensor TCS3200 e led RGB
//Autor: FILIPEFLOP
 
//Pinos de conexao do modulo
const int S0_COLOR = 38;
const int S1_COLOR = 40;
const int S2_COLOR = 34;
const int S3_COLOR = 32;
const int OUT_COLOR = 36;
 
//Variaveis cores
int RED = 0;
int GREEN = 0;
int BLUE = 0;
 
void setup()
{
  pinMode(S0_COLOR, OUTPUT);
  pinMode(S1_COLOR, OUTPUT);
  pinMode(S2_COLOR, OUTPUT);
  pinMode(S3_COLOR, OUTPUT);
  pinMode(OUT_COLOR, INPUT);
  Serial.begin(9600);
  digitalWrite(S0_COLOR, HIGH);
  digitalWrite(S1_COLOR, LOW);
}
 
void loop()
{
  //Detecta a cor
  color();
  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(RED, DEC);
  Serial.print(" Verde : ");
  Serial.print(GREEN, DEC);
  Serial.print(" Azul : ");
  Serial.print(BLUE, DEC);
  Serial.println();
 
  //Verifica se a cor vermelha foi detectada
  if (RED < BLUE && RED < GREEN && RED < 100)
  {
    Serial.println("Vermelho");
  }
 
  //Verifica se a cor azul foi detectada
  else if (BLUE < RED && BLUE < GREEN && BLUE < 1000)
  {
    Serial.println("Azul");
  }
 
  //Verifica se a cor verde foi detectada
  else if (GREEN < RED && GREEN < BLUE)
  {
    Serial.println("Verde");
  }
  Serial.println();
 
  //Delay para apagar os leds e reiniciar o processo
  delay(600);
}
 
void color()
{
  //Rotina que le o valor das cores
  digitalWrite(S2_COLOR, LOW);
  digitalWrite(S3_COLOR, LOW);
  //count OUT, pRed, RED
  RED = pulseIn(OUT_COLOR, digitalRead(OUT_COLOR) == HIGH ? LOW : HIGH);
  digitalWrite(S3_COLOR, HIGH);
  //count OUT, pBLUE, BLUE
  BLUE = pulseIn(OUT_COLOR, digitalRead(OUT_COLOR) == HIGH ? LOW : HIGH);
  digitalWrite(S2_COLOR, HIGH);
  //count OUT, pGreen, GREEN
  GREEN = pulseIn(OUT_COLOR, digitalRead(OUT_COLOR) == HIGH ? LOW : HIGH);
}
