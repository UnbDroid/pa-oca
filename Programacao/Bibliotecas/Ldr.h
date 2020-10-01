#ifndef LDR_H
#define LDR_H

/*Esse arquivo ".h" é criado apenas para a declaração dos métodos e dos atributos*/

class Ldr
{
    
public:

    /* Ldr
      Descricao: Construtor da Classe.
      Parâmetros:
        - pinRead: Pino digital que o Ldr está conectado.
        - threshold: Variável de comparação/precisão
    */
    Ldr(int pinRead, int threshold);


    //Destrutor da Classe.
    ~Ldr();


    /* filter
      Descricao: Função que retorna um valor de filtragem.
      Parâmetros:
        - count: Quantidade de valores da amostra que será filtrado.
        
    */
    int filter(int count);


    /* read
      Descricao:Função que identifica se o LDR está lendo preto e branco
      Parâmetros:
        - count: Quantidade de valores da amostra que será filtrado.
        
    */
    bool read(int count);
    

private:
    //Declaração dos atributos
    int pinRead;
    int threshold;
};

#endif