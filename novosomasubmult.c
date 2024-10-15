#include <stdio.h>
#include <string.h>

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

// Função principal que realiza a operação
void operacao(char a[], char b[], char c[], char sinal, int maior){
    switch(sinal){
        case '+': soma(a, b, c); break;
        case '-': sub(a, b, c, maior); break;
        case '*': mult(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}

int main(){
    char a[19] = {0};
    char b[19] = {0};
    char c[19] = {0};
    a[18] = '\0';
    b[18] = '\0';
    c[18] = '\0';
    char sinal;

    printf("Digite o primeiro binário (18 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%18s", a);

    printf("Digite o segundo binário (18 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%18s", b);

    printf("Digite o sinal: \n");
    scanf(" %c", &sinal);
    
    printf("a = %s \n", a);
    printf("b = %s \n", b);
    
    int maior = 0;
    if(b[0] != a[0]){
        for(int i = 1; i < 18; i++){
            if(a[i] > b[i]){
                maior = 0;
                c[0] = a[0];
                operacao(a, b, c, sinal, maior);
                break;
            }
            else if(a[i] < b[i]){
                maior = 1;
                c[0] = b[0];
                operacao(b, a, c, sinal, maior);
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
        operacao(a, b, c, sinal,0);
    }

    printf("Resultado final: %s\n", c);
    return 0;
}
