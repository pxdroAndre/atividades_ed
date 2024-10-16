#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



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


void somasubsoma(char a[], char b[], char c[]){
    int extra = 0;
    // printf("Somando somasubsoma %s e %s\n", a, b);
    for(int i = 17; i > 0; i--){ // Considera o bit de sinal
        if((a[i] == '1' && b[i] == '0' && extra == 0) || (a[i] == '0' && b[i] == '1' && extra == 0)){
            c[i] = '1';
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 0){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 0){
            c[i] = '0';
        }
        else if((a[i] == '1' && b[i] == '0' && extra == 1) || (a[i] == '0' && b[i] == '1' && extra == 1)){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 1){
            c[i] = '1';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 1){
            c[i] = '1';
            extra = 0;
        }
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    // printf("Resultado soma = %s\n", c);
    return;
}

void somasub(char a[], char b[], char c[]){
        for(int i = 17; i > 0; i--){
            if(b[i] == '0'){
                b[i] = '1';
            }
            else{
                b[i] = '0';
            }
        }

        char aux[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1','\0'};
        somasubsoma(b,aux,c);

        for(int i = 18; i > 0; i--){
            b[i] = c[i];
        }
        somasubsoma(a, b, c);
}

void soma(char a[], char b[], char c[]){
    if(a[0] != b[0]){
        somasub(a,b,c);
        return;
    }
    int extra = 0;
    // printf("Somando %s e %s\n", a, b);
    for(int i = 17; i > 0; i--){ // Considera o bit de sinal
        if((a[i] == '1' && b[i] == '0' && extra == 0) || (a[i] == '0' && b[i] == '1' && extra == 0)){
            c[i] = '1';
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 0){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 0){
            c[i] = '0';
        }
        else if((a[i] == '1' && b[i] == '0' && extra == 1) || (a[i] == '0' && b[i] == '1' && extra == 1)){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 1){
            c[i] = '1';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 1){
            c[i] = '1';
            extra = 0;
        }
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    // printf("Resultado soma = %s\n", c);
    return;
}
// Função para subtração
void sub(char a[], char b[], char c[], int maior){
    if(a[0] != b[0]){
        if(maior == 1){
            c[0] = b[0];
        }
        somasubsoma(a,b,c);
        return;
    }
        for(int i = 17; i > 0; i--){
            if(b[i] == '0'){
                b[i] = '1';
            }
            else{
                b[i] = '0';
            }
        }


        char aux[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0','0', '1','\0'};
        somasubsoma(b,aux,c);

        for(int i = 18; i > 0; i--){
            b[i] = c[i];
        }
        somasubsoma(a, b, c);
}

void somamult(char a[], char b[], char c[]){
    int extra = 0;
    // printf("Somando %s e %s\n", a, b);
    for(int i = 17; i >= 0; i--){ // Considera o bit de sinal
        if((a[i] == '1' && b[i] == '0' && extra == 0) || (a[i] == '0' && b[i] == '1' && extra == 0)){
            c[i] = '1';
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 0){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 0){
            c[i] = '0';
        }
        else if((a[i] == '1' && b[i] == '0' && extra == 1) || (a[i] == '0' && b[i] == '1' && extra == 1)){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 1){
            c[i] = '1';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 1){
            c[i] = '1';
            extra = 0;
        }
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    // printf("Resultado = %s\n", c);
    return;
}

void mult(char a[], char b[], char c[]) {
    // Inicializa o resultado com zeros
    char resultado[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
    
    // Determina o sinal do resultado
    if (a[0] != b[0]) { // Se os sinais forem diferentes
        c[0] = '1'; // O resultado será negativo
    }
    else
    {
        c[0] = '0';
    }

    for (int i = 17; i >= 1; i--) { // Loop para cada bit de 'b'
        if (b[i] == '1') {
            char temp[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
            for (int j = 17, k = i; j >= 1 && k >= 1; j--, k--) {
                temp[k] = a[j]; // Copia o bit de 'a' para 'temp'
            }
            char aux[19];
            somamult(resultado, temp, aux); // Soma o valor intermediário ao resultado
            strcpy(resultado, aux);
        }
    }

    // Adiciona o sinal ao resultado
    resultado[0] = c[0]; // Define o sinal no resultado
    strcpy(c, resultado); // Copia o resultado final para 'c'
}


void exp_b(char a[], char b[], char resultado[]){
    // Inicializa o resultado como 1 binário (000000000000000001)
    char temp[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '\0'};
    strcpy(resultado, temp);
    
    // Enquanto o expoente for maior que 0
    char zero[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
    char exp_copy[19];
    strcpy(exp_copy, b);
    
    while(strcmp(exp_copy, zero) != 0) {
        // Se o bit menos significativo do expoente for 1, multiplica o resultado pela a
        if (exp_copy[17] == '1') {
            char aux[19];
            if (a[0] == '1' && b[17] == '1') aux[0]='1';
            // printf("a: %c\nb: %c\naux: %c\n", a[0],b[17],aux[0]);
            mult(resultado, a, aux);
            strcpy(resultado, aux);
        }
        // Multiplica a a por ela mesma (a = a * a)
        char base_aux[19];
        char base_temp[19];
        strcpy(base_temp, a);
        mult(base_temp, base_temp, base_aux);
        strcpy(a, base_aux);
        
        // Divide o expoente por 2 (shift à direita)
        for (int i = 17; i > 0; i--) {
            exp_copy[i] = exp_copy[i-1];
        }
        exp_copy[0] = '0';
    }
}

// Função principal que realiza a operação
void operacao(char a[], char b[], char c[], char sinal, int maior){
    switch(sinal){
        case '+': soma(a, b, c); break;
        case '-': sub(a, b, c, maior); break;
        case '*': mult(a, b, c); break;
        case '^': exp_b(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}


void desempilha_e_opera(PilhaString *pilha_num, PilhaChar *pilha_op)
{
    printf("Operando\n");
  imprimir_bins(*pilha_num);
  imprimir_ops(*pilha_op);
  char a[19] = {'\0'};
  char b[19] = {'\0'};
  char c[19];
  c[18] = '\0';
  char op;

  strcpy(b, popString(pilha_num));
  strcpy(a, popString(pilha_num));
//   printf("op: %c top: %d\n", op, pilha_op->topo);
  op = popChar(pilha_op);
    int maior = 0;
    if(b[0] != a[0]){
        for(int i = 1; i < 18; i++){
            if(a[i] > b[i]){
                maior = 0;
                c[0] = a[0];
                operacao(a, b, c, op, maior);
                break;
            }
            else if(a[i] < b[i]){
                maior = 1;
                c[0] = b[0];
                if(op == '^'){
                    operacao(a, b, c, op, maior);
                    break;
                }
                operacao(b, a, c, op, maior);
                break;
            }
            else if(i == 17 && a[i] == b[i]){
                printf("Resultado = 000000000000000000\n");
            }
        }
    }
    else{
        c[0] = a[0];
        if(a[0] == '1' && b[0] == '1' && op == '-'){
            for(int i = 1; i < 18; i++){
                if(a[i] > b[i]){
                    maior = 0;
                    c[0] = a[0];
                    operacao(a, b, c, op, maior);
                    break;
                }
                else if(a[i] < b[i]){
                    maior = 1;
                    c[0] = '1';
                    operacao(b, a, c, op, maior);
                    break;
                }
            }
        }
        else{
            operacao(a, b, c, op,0);
        }
    }
//   printf("op: %c top: %d\n", op, pilha_op->topo);
  pushString(pilha_num, c);
}

int calcula_preferencia(char op, int *preferencia)
{
  if ((op == '+') || (op == '-')) *preferencia = 1;
  if ((op == '*') || (op == '/')) *preferencia = 2;
  if ((op == '^')) *preferencia = 3;
}

void empilhar_num (char *entrada, PilhaString *pilha_num, PilhaChar *pilha_op, int index_Op, int index_num, int preferencia)
{
  int preferencia_atual = 0;
  // printf("index_num: %d index_Op: %d\n", index_num, index_Op);
  int tamanho = strlen(entrada);
  // printf("strlen: %d\n", tamanho);
  if (index_num==tamanho)
  {
    //para no fim da string
    // printf("fim\n");
    return ;
  }
  if (index_num == 100000100)
  {
    //tratamento de erro
    printf ("Operador invalido\n");
    return;
  }
  if ((index_Op!=0) && (((index_num-18) % 19)== 0) || (index_num == 18))
  {
    // printf("op: %c\n", entrada[index_num]);
    if ((entrada[index_num]!= '+') && (entrada[index_num]!= '-') && (entrada[index_num]!= '*') && (entrada[index_num]!= '/') && (entrada[index_num]!= '^')) 
    {
    //   printf("i: %d op: %c\n", index_num,entrada[index_num]);
      return empilhar_num (entrada, pilha_num, pilha_op, index_Op, 100000100, preferencia);
    }
    // printf("op: %c\n", entrada[index_num+1]);
    if (preferencia==0) calcula_preferencia(entrada[index_num], &preferencia);
    calcula_preferencia(entrada[index_num], &preferencia_atual);
    // printf("a: %d %d\n", preferencia, preferencia_atual);
    if (preferencia_atual < preferencia)
    {
      desempilha_e_opera(pilha_num, pilha_op);
    } 
    preferencia = preferencia_atual;
    pushChar (pilha_op, entrada[index_num]);
    // printf("index_num: %d \n", index_num);
    // printf("i: %d op: %c\n", index_num,entrada[index_num]);
    return empilhar_num (entrada, pilha_num, pilha_op, index_Op, index_num+1, preferencia);
  }
  char binario[19];
  // printf("a\n");
  for (int i = 0; i<18 && index_num < strlen(entrada); i++)
  {
    // printf("index_num: %d i: %d\n", index_num, i);
    binario[i] = entrada[index_num];
    index_num++;
  }
  binario[18] = '\0';
//   printf("binario: %s\n", binario);
  pushString (pilha_num, binario);
  // printf("index_num: %d \n", index_num);
  empilhar_num(entrada, pilha_num, pilha_op, index_Op+1, index_num, preferencia);
}
