#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// serve para tirar a parte decimal que passa de 99
void corrigir_decimal(char* binario)
{
    char um[11] = {"0000000001"};
    char sinal = binario[0];
    char* parteInteira = (char*) malloc((11) * sizeof(char));
    char* parteDecimal = (char*) malloc((9) * sizeof(char));

    strncpy(parteInteira, binario + 1, 10);
    strncpy(parteDecimal, binario + 11, 7);
    parteInteira[10] = '\0';
    parteDecimal[7] = '\0';

    if (comparar_binarios(parteDecimal, "1100011"))
    {
        strcpy(parteDecimal, sub(parteDecimal, "1100011"));
        strcpy(parteInteira, somarBinarios(parteInteira, um));
        strcpy(binario, parteInteira);
        strcat(binario, parteDecimal);
        binario[0] = sinal;
    }
    free(parteInteira);
    free(parteDecimal);

}

void extender_binario(char* binario, int tamanhobin2) 
{
    int len = tamanhobin2 - 0;
    int tamanhobin = 0;

    while (binario[tamanhobin] != '\0') 
    {
        tamanhobin++;
    }

    len = tamanhobin2 - tamanhobin;
    if (len <= 0) 
    {
        return;
    }

    for (int i = tamanhobin + len; i >= 0; i--) 
    {
        binario[i] = binario[i - len];
    }

    for (int i = 0; i < len; i++) 
    {
        binario[i] = '0';
    }

    binario[tamanhobin + len] = '\0'; 
}

int comparar_binarios(char* bin1, char* bin2) 
{
    int tam1 = strlen(bin1);
    int tam2 = strlen(bin2);

    if (tam1 < tam2) 
    {
        extender_binario(bin1, tam2);
    } 
    else if (tam2 < tam1) 
    {
        extender_binario(bin2, tam1);
    }

    return strcmp(bin1, bin2);
}

void remover_zeros_esquerda(char* binario) 
{
    int i = 0;
    
    while (binario[i] == '0') 
    {
        i++;
    }
    if (i > 0) 
    {
        memmove(binario, binario + i, strlen(binario) - i + 1);
    }
}

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

char* sub(char* a, char* b)
{
    int tamanho = strlen(a);
    char* resultado = (char*) malloc((tamanho + 1) * sizeof(char));
    char* a_copia = (char*) malloc((tamanho + 1) * sizeof(char));
    strcpy(a_copia, a);
    int roubo = 0;
    int j = 0;

    for (int i = tamanho - 1; i >= 0; i--)
    {
        // Aplica o roubo se houver e ajusta o valor de a_copia
        if (roubo == 1 && a_copia[i] == '1')
        {
            a_copia[i] = '0';
            roubo = 0;
        }
        else if (roubo == 1 && a_copia[i] == '0')
        {
            a_copia[i] = '1'; // Precisa continuar com o roubo
        }
        
        // Realiza a subtração bit a bit
        if (a_copia[i] == '0' && b[i] == '0')
        {
            resultado[j] = '0';
        }
        else if (a_copia[i] == '1' && b[i] == '0')
        {
            resultado[j] = '1';
        }
        else if (a_copia[i] == '1' && b[i] == '1')
        {
            resultado[j] = '0';
        }
        else if (a_copia[i] == '0' && b[i] == '1')
        {
            resultado[j] = '1';
            roubo = 1; // Indica que precisamos roubar da próxima posição
        }
        j++;
    }

    resultado[j] = '\0';

    inverterString(resultado);
    free(a_copia);

    return resultado;
}

// TODO : FUNÇÃO PARA MULTIPLICAR BINARIOS

char* dividirBinarios(char* bin1, char* bin2)
{ 
    int tam_bin1 = strlen(bin1);

    char* resultado = (char*) malloc((tam_bin1 + 1) * sizeof(char));
    char* dividendo = (char*) calloc((50),  sizeof(char));
    resultado[0] = '\0';
    
    remover_zeros_esquerda(bin2);

    int i;
    int j = 0;
    int condicao = 0;

    for (i = 0; i <= tam_bin1 + 8; i++)
    {

        int compara = comparar_binarios(dividendo, bin2);
        if (compara >= 0)
        {
            condicao = 1;

            char* subtracao = (char*) calloc(strlen(dividendo) + 1, sizeof(char));
            strcpy(subtracao, sub(dividendo, bin2));
            strcpy(dividendo, subtracao);

            free(subtracao);

            int tamanho = strlen(dividendo);
            dividendo[tamanho] = bin1[i];
            resultado[j] = '1';
            j++; 
        }
        else if (condicao == 0)
        {
            strncpy(dividendo, bin1, i + 1);
        }
        else
        {
            
            int tamanho = strlen(dividendo);

            if (i > 18) dividendo[tamanho] = '0';
            else dividendo[tamanho] = bin1[i];

            if (i == 19) resultado[j] = '.';
            else resultado[j] = '0';

            j++;
        }
    }
    resultado[j] = '\0';

    free(dividendo);

    return resultado;
}
