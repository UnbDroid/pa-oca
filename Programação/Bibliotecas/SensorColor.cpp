#include <Arduino.h>
#include <SensorColor.h>
#include <math.h>

SensorColor::SensorColor(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut)
{
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
	//Serial.println(red);

	//Ler Azul:
	digitalWrite(pinS3, HIGH);
	//count OUT, pblue, blue
	blue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
	//Serial.println(blue);

	//Ler Verde:
	digitalWrite(pinS2, HIGH);
	//count OUT, pgreen, green
	green = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
	//Serial.println(green);

	//Verifica se a cor vermelha foi detectada
	if (red < blue && red < green && red < 160 && blue > 90)
	{
		return COLOR_RED;
	}

	//Verifica se a cor azul foi detectada
	else if (blue < red && blue < green && (green > 115 || green < 93) && red > 80 && blue < 100)
	{
		return COLOR_BLUE;
	}

	//Verifica se a cor verde foi detectada
	else if (green < red && blue < red && blue > 70)
	{
		return COLOR_GREEN;
	}
	else if (green < 40 && blue < 40 && red < 40 ) {
		return COLOR_WHITE;
	}
	else{
		return 0; //Caso não detecte nada, retorna-se zero.
	}


	// if(red < 85 && blue < 80 && green < 85) {
	// 	return 0;
	// }
	// else if((red < 120 and red > 80) and (blue < 100 and blue > 70) and (green < 120 and green > 83)) {
	// 	return 0;
	// } else {
	// 	return 1;
	// }

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
