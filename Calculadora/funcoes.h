#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void empilhar_num (char *entrada, PilhaString *pilha_num, PilhaChar *pilha_op, int index_Op, int index_num)
{
    // printf("index_num: %d index_Op: %d\n", index_num, index_Op);
    // printf("%d\n", strlen(entrada));
    if (index_num == (strlen (entrada)-1))
    {
        // printf("fim\n");
        return;
    }
    if (index_num == 100000100)
    {
        printf ("Erro no operador\n");
        return;
    }
    if ((index_Op!=0) && (index_num == ((index_Op * 18) + (index_Op-1))))
    {
        // printf("op: %c\n", entrada[index_num]);
        if ((entrada[index_num]!= '+') && (entrada[index_num]!= '-') && (entrada[index_num]!= '*') && (entrada[index_num]!= '/') && (entrada[index_num]!= '+') && (entrada[index_num]!= '*')) {
            return empilhar_num (entrada, pilha_num, pilha_op, index_Op, 100000100);
        }
        // printf("op: %c\n", entrada[index_num]);
        pushChar (pilha_op, entrada[index_num]);
        return empilhar_num (entrada, pilha_num, pilha_op, index_Op, index_num+1);
    }
    char binario[19];
    // printf("a\n");
    for (int i = 0; i<19 && index_num < strlen(entrada); i++)
    {
        // printf("index_num: %d i: %d\n", index_num, i);
        binario[i] = entrada[index_num];
        index_num++;
    }
    binario[18] = '\0';
    // printf("binario: %s\n", binario);
    pushString (pilha_num, binario);
    empilhar_num(entrada, pilha_num, pilha_op, index_Op+1, index_num-1);
}

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
