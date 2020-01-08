#ifndef LDR_H
#define LDR_H

class Ldr
{

public:
  /* Ldr
    Descricao: Construtor da Classe.
    Parâmetros:
      - pinRead: Pino analógico de leitura do ldr.
      - threshold: Limite entre a leitura das cores branca e preta.
  */

    Ldr(int pinRead, int threshold);

    //Destrutor da Classe MotorDC
    ~Ldr();

    /* Read
      Descricao: Função que identifica preto e branco.
      Parâmetros:
        - count: Quantidade de leituras.
      Retorno:
        - True: Branco.
        - False: Preto.

    */
    bool read(int count);

    /* Read
      Descricao: Função que retorna um valor de filtragem.
      Parâmetros:
        - count: Quantidade de leituras.
      Retorno: Valor filtrado da leitura do ldr.

    */
    int filter(int count);

private:

    int pinRead;
    int threshold;
};



#endif
