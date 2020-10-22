#include <Arduino.h>
#include <SensorColor.h>
#include <math.h>

SensorColor::SensorColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut)
{
		//Setando os atributos da classe com os valores passado pela função.
		this->pinOut = pinOut;
		this->pinS0 = pinS0;
		this->pinS1 = pinS1;
		this->pinS2 = pinS2;
		this->pinS3 = pinS3;

		pinMode(pinS0, OUTPUT);
		pinMode(pinS1, OUTPUT);
		pinMode(pinS2, OUTPUT);
		pinMode(pinS3, OUTPUT);
		//pinMode(pinOut, INPUT);

		digitalWrite(pinS0, HIGH);
		digitalWrite(pinS1, LOW);

}

SensorColor::~SensorColor()
{
}

//Método que detecta a color lida.
int SensorColor::color(){

	//Variaveis cores
	int red = 0;
	int green = 0;
	int blue = 0;

	//Rotina que le o valor das cores

	//Ler Vermelho:
	digitalWrite(pinS2, LOW);
	digitalWrite(pinS3, LOW);
	//count OUT, pred, red
	red = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
	// Serial.print("vermelho: ");
	// Serial.println(red);

	//Ler Azul:
	digitalWrite(pinS3, HIGH);
	//count OUT, pblue, blue
	blue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
	//Serial.println(blue);

	//Ler Verde:
	digitalWrite(pinS2, HIGH);
	//count OUT, pgreen, green
	green = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
	// Serial.print("verde: ");
	// Serial.println(green);

	int dif = red - green;
  	dif = abs(dif);

	// Serial.print("diferença: ");
	// Serial.println(dif);

	if(dif > 10) {
		return 1; //colorido
	}
	else {
		return 0; //não é colorido
	}

}

	//Método de filtragem
	int SensorColor::filter(int count){

		int v[4] = {0};

		//Salva as leituras e decide quem repetiu mais vezes
		for (int i = 0; i<=count; i++){
			v[color()] += 1;
		}

		//Faz a comparação e diz quantas vezes um desses vetores foi mais incrementado.
		int n = fmax(fmax(v[0], v[1]), fmax(v[2], v[3]));

		//Diz o índice do vetor que foi mais incrementado.
		for (int i = 0; i<=3; i++){
			if(n == v[i]){
				return i;
			}
		}

		return -1;
	}
