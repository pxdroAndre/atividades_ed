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
    printf("Somando somasubsoma %s e %s\n", a, b);
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
        printf("c[%d] = %c\n", i, c[i]);
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    printf("Resultado soma = %s\n", c);
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
        printf("b depois da inversão = %s\n", b);
        char aux[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1','\0'};
        somasubsoma(b,aux,c);
        printf("voltei da primeira soma\n");

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
    printf("Somando %s e %s\n", a, b);
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
        printf("c[%d] = %c\n", i, c[i]);
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    printf("Resultado soma = %s\n", c);
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
        printf("b depois da inversão = %s\n", b);
        char aux[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1','\0'};
        somasubsoma(b,aux,c);
        printf("voltei da primeira soma\n");

        for(int i = 18; i > 0; i--){
            b[i] = c[i];
        }
        somasubsoma(a, b, c);
}

void somamult(char a[], char b[], char c[]){
    int extra = 0;
    printf("Somando %s e %s\n", a, b);
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
        printf("c[%d] = %c\n", i, c[i]);
    }
    c[18] = '\0'; // Certifique-se de que o último caractere seja o terminador de string
    printf("Resultado = %s\n", c);
    return;
}

void mult(char a[], char b[], char c[]) {
    // Inicializa o resultado com zeros
    char resultado[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
    
    // Determina o sinal do resultado
    char sinal = '0'; // Inicializa como positivo
    if (a[0] != b[0]) { // Se os sinais forem diferentes
        sinal = '1'; // O resultado será negativo
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
    resultado[0] = sinal; // Define o sinal no resultado
    strcpy(c, resultado); // Copia o resultado final para 'c'
}


void dividirBinarios(char* bin1, char* bin2, char* res)
{ 
    char sinal;
    if (bin1[0] == '1' && bin2[0] == '1')
    {
        sinal = '0';
    }
    else if ((bin1[0] == '0' && bin2[0] == '1') || (bin1[0] == '1' && bin2[0] == '0'))
    {
        sinal = '1';
    }
    else
    {
        sinal = '0';
    }
    

    int tam_bin1 = strlen(bin1);

    char* resultado = (char*) malloc((tam_bin1 + 1) * sizeof(char));
    char* dividendo = (char*) calloc((50),  sizeof(char));
    resultado[0] = '\0';

    strncpy(bin2, bin2 + 1, strlen(bin2));
    
    remover_zeros_esquerda(bin2);

    int i;
    int j = 0;
    int condicao = 0;

    for (i = 1; i <= tam_bin1 + 8; i++)
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

            resultado[j] = '0';

            j++;
        }
    }

    resultado[j] = '\0';

    free(dividendo);
    extender_binario(resultado, 18);
    resultado[0] = sinal;
    strcpy(res, resultado);
    free(resultado);
}


void exp_binaria(char base[], char exp[], char resultado[]){
    // Inicializa o resultado como 1 binário (000000000000000001)
    char temp[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '\0'};
    strcpy(resultado, temp);
    
    // Enquanto o expoente for maior que 0
    char zero[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
    char exp_copy[19];
    strcpy(exp_copy, exp);
    
    while(strcmp(exp_copy, zero) != 0) {
        // Se o bit menos significativo do expoente for 1, multiplica o resultado pela base
        if (exp_copy[17] == '1') {
            char aux[19];
            mult(resultado, base, aux);
            strcpy(resultado, aux);
        }
        // Multiplica a base por ela mesma (base = base * base)
        char base_aux[19];
        char base_temp[19];
        strcpy(base_temp, base);
        mult(base_temp, base_temp, base_aux);
        strcpy(base, base_aux);
        
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
        case '/': dividirBinarios(a, b, c); break;
        case '*': exp_b(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}


void desempilha_e_opera(PilhaString *pilha_num, PilhaChar *pilha_op)
{
  char a[19] = {'\0'};
  char b[19] = {'\0'};
  char c[19];
  c[18] = '\0';
  char op;

  strcpy(a, popString(pilha_num));
  strcpy(b, popString(pilha_num));
//   printf("op: %c top: %d\n", op, pilha_op->topo);
  op = popChar(pilha_op);
//   printf("op: %c top: %d\n", op, pilha_op->topo);
  operacao(a,b,c,op);
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
    if ((entrada[index_num]!= '+') && (entrada[index_num]!= '-') && (entrada[index_num]!= '*') && (entrada[index_num]!= '/') && (entrada[index_num]!= '+') && (entrada[index_num]!= '*')) 
    {
      printf("i: %d op: %c\n", index_num,entrada[index_num]);
      return empilhar_num (entrada, pilha_num, pilha_op, index_Op, 100000100, preferencia);
    }
    // printf("op: %c\n", entrada[index_num+1]);
    calcula_preferencia(entrada[index_num], &preferencia);
    calcula_preferencia(entrada[index_num], &preferencia_atual);
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
