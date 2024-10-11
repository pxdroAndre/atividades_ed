#include <stdio.h>
#include <string.h>

//TA FUNCIONANDO  A = BINARIO 1  B = BINARIO 2  C = RESULTADO
void soma(char a[], char b[], char c[]){
    int extra = 0;
    printf("somando %s e %s\n", a, b);
    for(int i = 10; i > 0; i--){
        if((a[i] == '1' && b[i] == '0'  && extra == 0) || (a[i] == '0' && b[i] == '1' && extra == 0)){
            c[i] = '1';
        }
        else if(a[i] == '1' && b[i] == '1' && extra == 0){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 0){
            c[i] = '0';
        }
        else if((a[i] == '1' && b[i] == '0'  && extra == 1) || (a[i] == '0' && b[i] == '1' && extra == 1)){
            c[i] = '0';
            extra = 1;
        }
        else if(a[i] == '1' && b[i] == '1'  && extra == 1){
            c[i] = '1';
            extra = 1;
        }
        else if(a[i] == '0' && b[i] == '0' && extra == 1){
            c[i] = '1';
            extra = 0;
        }
        printf("c[%d] = %c\n", i,c[i]);
    }
    printf("resultado = %s \n", c);
    return;
}

void sub(char a[], char b[], char c[]){
        for(int i = 10; i > 0; i--){
            if(b[i] == '0'){
                b[i] = '1';
            }
            else{
                b[i] = '0';
            }
        }
        printf("b depois da inversão = %s\n", b);
        char aux[12] = {'0','0','0','0','0','0','0','0','0','0','1','\0'};
        soma(b,aux,c);
        printf("voltei da primeira soma\n");

        for(int i = 11; i > 0; i--){
            b[i] = c[i];
        }
        soma(a, b, c);
}

void mult(char a[], char b[], char c[])
{
    char resultado[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'}; //Inicializa o resultado como zero
    for(int i = 10; i >= 1; i--) //Loop para cada bit de 'b'
    {
        if(b[i] == '1')
        {
            char temp[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'}; //Cria um valor intermediário deslocado baseado na posição do bit de 'b'
            for(int j = 10, k = i; j >= 1 && k >= 1; j--, k--) //Copia 'a' deslocado para a direita
            {
                temp[k] = a[j];
            }
            char aux[12];
            soma(resultado, temp, aux); //Soma o valor intermediário ao resultado
            strcpy(resultado, aux);
        }
    }
    strcpy(c, resultado); //Copia o resultado final para 'c'
}

//pra ver se é soma subtração esses caralho mas ta incompleto so funciona de soma
void operacao(char a[], char b[], char c[], char sinal){
    switch(sinal){
        case '+': soma(a, b, c); break;
        case '-': sub(a, b, c); break;
        case '*': mult(a, b, c); break;
        default: printf("Sinal inválido\n"); break;
    }
}

int main(){
    char a[12] = {'\0'};
    char b[12] = {'\0'};
    char c[12] = {'\0'};
    char sinal;

    //pra pegar os numeros mas a gente vai fazer de string
    printf("Digite o primeiro binário(11 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%11s", a);

    printf("Digite o segundo binário(11 dígitos) com o primeiro sendo o sinal (0 = + // 1 = -): \n");
    scanf("%11s", b);

    printf("Digite o sinal: \n");
    scanf(" %c", &sinal);
    
    printf("a = %s \n", a);
    printf("b = %s \n", b);


    //pra ver os sinais
    if(b[0] != a[0]){
        for(int i = 1; i < 11; i++){
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
            else if(i == 10 && a[i] == b[i]){
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
