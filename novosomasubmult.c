#include <stdio.h>
#include <string.h>

// Função para soma de dois binários com sinal
void soma(char a[], char b[], char c[]){
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

// Função para subtração
void sub(char a[], char b[], char c[]){
    for(int i = 17; i >= 0; i--){
        b[i] = (b[i] == '0') ? '1' : '0'; // Complemento de 1
    }
    printf("b depois da inversão = %s\n", b);
    char aux[19] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\0'};
    soma(b, aux, b); // Complemento de 2
    printf("Voltei da primeira soma\n");

    soma(a, b, c); // Soma com o número original
}

// Função para multiplicação
void mult(char a[], char b[], char c[]){
    char resultado[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0','\0'};
    for(int i = 17; i >= 1; i--){ // Loop para cada bit de 'b'
        if(b[i] == '1'){
            char temp[19] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0','\0'};
            for(int j = 17, k = i; j >= 1 && k >= 1; j--, k--){
                temp[k] = a[j];
            }
            char aux[19];
            soma(resultado, temp, aux); // Soma o valor intermediário ao resultado
            strcpy(resultado, aux);
        }
    }
    strcpy(c, resultado); // Copia o resultado final para 'c'
}

// Função principal que realiza a operação
void operacao(char a[], char b[], char c[], char sinal){
    switch(sinal){
        case '+': soma(a, b, c); break;
        case '-': sub(a, b, c); break;
        case '*': mult(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}

int main(){
    char a[19] = {'\0'};
    char b[19] = {'\0'};
    char c[19] = {'\0'};
    char sinal;

    printf("Digite o primeiro binário (18 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%18s", a);

    printf("Digite o segundo binário (18 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%18s", b);

    printf("Digite o sinal: \n");
    scanf(" %c", &sinal);
    
    printf("a = %s \n", a);
    printf("b = %s \n", b);

    if(b[0] != a[0]){
        for(int i = 1; i < 18; i++){
            if(a[i] > b[i]){
                c[0] = a[0];
                operacao(a, b, c, sinal);
                break;
            }
            else if(a[i] < b[i]){
                c[0] = b[0];
                operacao(b, a, c, sinal);
                break;
            }
            else if(i == 17 && a[i] == b[i]){
                printf("Resultado = 000000000000000000\n");
                return 0;
            }
        }
    }
    else{
        c[0] = a[0];
        operacao(a, b, c, sinal);
    }

    printf("Resultado final: %s\n", c);
    return 0;
}
