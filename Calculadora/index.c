#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./pilha.h"
#include "./funcoes.h"

// NOTA: NAS MINHAS FUNÇÕES DE PILHA É NECESSÁRIO INICIAR O TOPO COM -1

int main()
{
  // TESTE PARA SOMA DE BINARIOS
  char entrada[120] = {'\0'};
  scanf("%s", entrada);
  tamanho = strlen(entrada);
  

  
  PilhaString numerosString;

  numerosString.topo = -1;

  pushString(&numerosString, "1010");
  pushString(&numerosString, "1101");

  char* bin1 = popString(&numerosString);
  char* bin2 = popString(&numerosString);
  printf("%s + %s\n", bin1, bin2);

  char* soma = somarBinarios(bin1, bin2);

  printf("%s", soma);


  return 0;
}
