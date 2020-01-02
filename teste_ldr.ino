#define LED 42
#define ALTO 44
#define LDR A1
#define LED2 48
#define ALTO2 50
#define LDR2 A4

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(ALTO, OUTPUT);
  pinMode(LDR, INPUT);

  pinMode(LED2, OUTPUT);
  pinMode(ALTO2, OUTPUT);
  pinMode(LDR2, INPUT);

  Serial.begin(9600);

  digitalWrite(LED, HIGH);
  digitalWrite(ALTO, HIGH);

  digitalWrite(LED2, HIGH);
  digitalWrite(ALTO2, HIGH);
  
}

void loop() {
  Serial.print("LDR1 :");
  Serial.println(analogRead(LDR));
  delay(1000);
  Serial.print("LDR2 :");
  Serial.println(analogRead(LDR2));
}
