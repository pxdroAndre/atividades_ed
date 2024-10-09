#include <stdio.h>

//TA FUNCIONANDO  A = BINARIO 1  B = BINARIO 2  C = RESULTADO
void soma(int a[], int b[], int c[]){
    int extra;
    for(int i = 4; i > 0; i--){
        printf("i = %d\n", i);
        if(a[i] == 1 && b[i] == 0  && extra == 0 || a[i] == 0 && b[i] == 1 && extra == 0){
            c[i] = 1;
            printf("a\n");
        }
        else if(a[i] == 1 && b[i] == 1 && extra == 0){
            c[i] = 0;
            extra = 1;
            printf("b\n");
        }
        else if(a[i] == 0 && b[i] == 0 && extra == 0){
            c[i] = 0;
            printf("c\n");
        }
        else if(a[i] == 1 && b[i] == 0  && extra == 1 || a[i] == 0 && b[i] == 1 && extra == 1){
            c[i] = 0;
            extra = 1;
            printf("d\n");
        }
        else if(a[i] == 1 && b[i] == 1  && extra == 1){
            c[i] = 1;
            extra = 1;
            printf("e\n");
        }
        else if(a[i] == 0 && b[i] == 0 && extra == 1){
            c[i] = 1;
            extra = 0;
            printf("f\n");
        }
        else{
            printf("pqp\n");
        }
    }
    printf("Resultado = ");
    for(int i = 0; i < 5; i++){
        printf("%d", c[i]);
    }
    return;
}

//TA FALTANDO
void sub(int a[], int b[], int c[]){
    
}

//pra ver se é soma subtração esses caralho mas ta incompleto so funciona de soma
void operacao(int a[], int b[], int c[], char sinal){
    switch(sinal){
        case '+': soma(a, b, c); break;
        case '-': sub(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}

int main(){
    int a[5];
    int b[5];
    int c[5] = {0};
    char sinal;

    //pra pegar os numeros mas a gente vai fazer de string
    printf("Digite o sinal do primeiro binário (0 = + // 1 = -): \n");
    scanf("%d", &a[0]);
    printf("Digite o primeiro binário: \n");
    for(int i = 1; i < 5; i++){
        scanf("%d", &a[i]);
    }

    printf("Digite o sinal do segundo binário (0 = + // 1 = -): \n");
    scanf("%d", &b[0]);
    printf("Digite o segundo binário: \n");
    for(int i = 1; i < 5; i++){
        scanf("%d", &b[i]);
    }

    printf("Digite o sinal: \n");
    scanf(" %c", &sinal);
    
    for(int i = 0; i < 5; i++){
        printf("%d", a[i]);
    }
    printf("\n");
    for(int i = 0; i < 5; i++){
        printf("%d", b[i]);
    }
    printf("\n");

    //pra ver os sinais
    if(b[0] != a[0]){
        for(int i = 1; i < 5; i++){
            //isso aqui ve quem é maior
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
            else if(i == 4 && a[i] == b[i]){
                printf("Resultado = 00000\n");
                return 0;
            }
        }
    }
    else{
        c[0] = a[0];
        operacao(a, b, c, sinal);
    }

    return 0;
}