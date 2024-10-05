#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// TODO : FUNÇÃO PARA EXTENDER BINARIO (DEIXAR ELES DO MESMO TAMANHO PARA FAZER O CALCULO)

// TODO : FUNÇÃO PARA CONVERTER DE BINARIO PARA GRAY

// TODO : FUNÇÃO PARA CONVERTER DE GRAY PARA BINARIO

void inverterString(char* binario)
{
  for (size_t i = 0; i < strlen(binario) / 2; i++)
  {
    int j = strlen(binario) - 1 - i;
    char temp = binario[i];
    binario[i] = binario[j];
    binario[j] = temp;
  }
}

char* somarBinarios(char* bin1, char* bin2)
{
  char* resultado = (char*) malloc(33 * sizeof(char));
  char valorSomaAnterior = '0';
  int j = 0;
  int tamanhoStrings = strlen(bin1);
  for (int i = tamanhoStrings - 1; i >= 0; i--)
  {
    // calculo 0 + 0 + somaAnterior
    if (bin1[i] == '0' && bin2[i] == '0')
    {
      if (valorSomaAnterior = '0')
      {
        resultado[j] = '0';
        valorSomaAnterior = '0';
      }
      else
      {
        resultado[j] = '1';
        valorSomaAnterior = '0';
      }
    }

    // calculo 1 + 0 + somaAnterior
    else if ((bin1[i] == '1' && bin2[i] == '0') || (bin1[i] == '0' && bin2[i] == '1'))
    {
      if (valorSomaAnterior == '0')
      {
        resultado[j] = '1';
        valorSomaAnterior = '0';
      }
      else
      {
        resultado[j] = '0';
        valorSomaAnterior = '1';
      }
    }

    // calculo 1 + 1 + somaAnterior
    else if (bin1[i] == '1' && bin2[i] == '1')
    {
      if (valorSomaAnterior == '0')
      {
        resultado[j] = '0';
        valorSomaAnterior = '1';
      }
      else
      {
        resultado[j] = '1';
        valorSomaAnterior = '1';
      }
    }

    

    j++;


    // verificando overflow
    if (valorSomaAnterior == '1' && i == 0)
    {
      printf("OVERFLOW\n");
      resultado[j] = '1';
    }

  }

  resultado[++j] = '\0';
  inverterString(resultado);

  return resultado;
}

// TODO : FUNÇÃO PARA SUBTRAIR BINARIOS

// TODO : FUNÇÃO PARA MULTIPLICAR BINARIOS

// TODO : FUNÇÃO PARA DIVIDIR BINARIOS