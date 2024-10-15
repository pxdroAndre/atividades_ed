#include "pilha.h"
#include "funcoes.h"

int main()
{
  // TESTE PARA SOMA DE BINARIOS
  char entrada[114] = {'\0'}; //6 operandos de 19 bits + 5 ops + 1 \0
  scanf("%s", entrada);
  int tamanho = strlen(entrada);

//criando pilhas
  PilhaString pilha_num;
  pilha_num.topo = -1;
  PilhaChar pilha_op;
  pilha_op.topo = -1;
  
  empilhar_num(entrada, &pilha_num, &pilha_op, 0, 0, 0);
  // printf("b1: %s op:%c b2: %s \n", pilha_num.strings[0], pilha_op.characters[pilha_op.topo], pilha_num.strings[1]);
  // imprimir_bins(pilha_num);
  // imprimir_ops(pilha_op);
  for (int i = pilha_op.topo; pilha_op.topo != -1; i--)
  {
    // printf("i:%d\n", i);
    desempilha_e_opera(&pilha_num, &pilha_op);
  }
  printf("Resultado: %s\n", pilha_num.strings[pilha_num.topo]);

  return 0;
}
