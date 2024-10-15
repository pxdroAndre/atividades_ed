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
            soma(resultado, temp, aux); // Soma o valor intermediário ao resultado
            strcpy(resultado, aux);
        }
    }

    // Adiciona o sinal ao resultado
    resultado[0] = sinal; // Define o sinal no resultado
    strcpy(c, resultado); // Copia o resultado final para 'c'
}
