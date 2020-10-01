//*************************Classe*************************//
class abacaxi{
  public:
  abacaxi(){
    count = 0;
  }
  ~abacaxi(){}

  void up(){
    count++;
  }

  int count;
  private:
};
//*********************************************************//


//******Criando objeto que vai ter o metodo chamado********//
abacaxi pacoca;


//*************Funcao que chama metodo da classe***********//
void inc(){
  digitalWrite(LED_BUILTIN, HIGH);
  pacoca.up();
}



void setup(){
  pinMode(LED_BUILTIN, OUTPUT); //Led usado pra debugar o código
  pinMode(20, INPUT);     //Entrada do sinal do encoder
  Serial.begin(9600);     
  attachInterrupt(digitalPinToInterrupt(20), inc, RISING);    //O pino 20 é o utilizado como interrupt, sempre 
                                                              //que o sinal lido passar de LOW para HIGH. 
                                                              //Em caso desse evento, a função "inc" é chamada
}

void loop(){
  //A cada 0.1s, mostra no monitor serial o valor acumulado da contagem de pulsos do encoder
  Serial.println(pacoca.count);
  delay(100);
}

