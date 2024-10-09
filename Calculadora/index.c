#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "funcoes.h"

// NOTA: NAS MINHAS FUNÇÕES DE PILHA É NECESSÁRIO INICIAR O TOPO COM -1
int main()
{
  // TESTE PARA SOMA DE BINARIOS
  char entrada[120] = {'\0'}; //6 operandos de 19 bits + 5 ops + 1 \0
  scanf("%s", entrada);
  int tamanho = strlen(entrada);

//criando pilhas
  PilhaString pilha_num;
  pilha_num.topo = -1;
  PilhaChar pilha_op;
  pilha_op.topo = -1;
  
  empilhar_num(entrada, &pilha_num, &pilha_op, 0, 0);
//   printf("b1: %s op: %c b2: %s\n op: %c b3; %s", pilha_num.strings[pilha_num.topo], pilha_op.characters[0], pilha_num.strings[pilha_num.topo], pilha_op.characters[1], pilha_num.strings[pilha_num.topo]);
//   pushString(&numerosString, "1010");
//   pushString(&numerosString, "1101");

//   char* bin1 = popString(&numerosString);
//   char* bin2 = popString(&numerosString);
//   printf("%s + %s\n", bin1, bin2);

//   char* soma = somarBinarios(bin1, bin2);

//   printf("%s", soma);


  return 0;
}
