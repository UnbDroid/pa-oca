# Equipe Pa-Oca - Robô
Equipe 1 da competição interna da Droid

## Padronização de código
Para melhor organização e modularização, regras definidas em reunião.
Usar como padrão o inglês

### Nomeação de variáveis:
  Para variáveis globais, usar letras em caixa alta
  ```
  int PIN_20;
  bool STEP;
  ```
  Outras variáveis seguem formatação normal, com a primeira letra sempre minúscula
  
  ```
  int position;
  int motorPower;
  char displayPortLetter;
  ```
  A mesma formatação é usada para funções.

### Nomeação de funções:
  Quando chamadas em uma função, utilizar nomes de variáveis correspondentes:
  
  ```
  changeSide(position, motorPower)
  ...
  void changeSide(var_position, var_motorPower) {
  ```
  
  Se a função for usada com vários tipos de variáveis, usar o mais coerente.
  ```
  checkLDR(left)
  checkLDR(right)
  ...
  int checkLDR(var_side) {
  ```
### Modularização
  Se uma seção do código foi copiado e colado em algum momento, é bem provável que seria melhor fazer uma nova função com isso.
  
  Ainda que não tenha sido, se vai deixar mais legível também é melhor fazer uma nova função.
  
  Se possível, utilizar mais de um arquivo quando estiver lidando com seções completamente separadas do código, tendo um Header para uni-los.
  ```
  Arquivo movement.c
  -> Função de aceleração
  -> Função de direção
  -> Função de média de potência dos motores
  ...
  Arquivo sensors.c
  -> Função de leitura dos LDRs
  -> Função de leitura de cor
  -> Função de leitura de proximidade
  ```
  
  
