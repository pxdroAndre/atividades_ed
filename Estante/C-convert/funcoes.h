#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 1000
#define MAX_PRATELEIRAS 6
#define LARGURA_MAXIMA 96
#define VOLUME_MAXIMO 96.256

typedef struct {
    char titulo[100];
    char autor[100];
    int largura;
    int altura;
    int profundidade;
    int volume;
    int indice;
} Livro;

typedef struct no{ 
 Livro livro; 
 struct no *anterior, *proximo; 
}No; 

typedef struct { 
 No *inicio; 
 No *fim; 
}ListaDuplamenteEncadeada;

typedef struct {
    int volume_maximo;
    int volume_usado;
    Livro livros[MAX_LIVROS];
    int num_livros;
} Prateleira;

typedef struct {
    Prateleira prateleiras[MAX_PRATELEIRAS];
    int num_prateleiras;
} Estante;

typedef struct {
    Estante estantes[MAX_LIVROS / MAX_PRATELEIRAS];
    int num_estantes;
} Biblioteca;

void inicializar_estante(Estante *estante) 
{
    estante->num_prateleiras = MAX_PRATELEIRAS;
    for (int i = 0; i < MAX_PRATELEIRAS; i++) 
    {
        inicializar_prateleira(&estante->prateleiras[i], LARGURA_MAXIMA);
    }
}

void inicializar_biblioteca(Biblioteca *biblioteca) {
    biblioteca->num_estantes = 0;
}


int adicionar_livro(Prateleira *prateleira, Livro livro) {
    if (prateleira->largura_usada + livro.largura <= prateleira->largura_maxima) {
        prateleira->livros[prateleira->num_livros] = livro;
        prateleira->largura_usada += livro.largura;
        prateleira->num_livros++;
        return 1;
    }
    return 0;
}

int remover_livro(Prateleira *prateleira, int indice) {
    for (int i = 0; i < prateleira->num_livros; i++) {
        if (prateleira->livros[i].indice == indice) {
            prateleira->largura_usada -= prateleira->livros[i].largura;
            prateleira->livros[i] = prateleira->livros[--prateleira->num_livros];
            return 1;
        }
    }
    return 0;
}

int adicionar_livro_estante(Estante *estante, Livro livro) {
    for (int i = 0; i < estante->num_prateleiras; i++) {
        if (adicionar_livro(&estante->prateleiras[i], livro)) {
            return 1;
        }
    }
    return 0;
}

int remover_livro_estante(Estante *estante, int indice) {
    for (int i = 0; i < estante->num_prateleiras; i++) {
        if (remover_livro(&estante->prateleiras[i], indice)) {
            return 1;
        }
    }
    return 0;
}

int adicionar_livro_biblioteca(Biblioteca *biblioteca, Livro livro) {
    if (biblioteca->num_estantes == 0 || !adicionar_livro_estante(&biblioteca->estantes[biblioteca->num_estantes - 1], livro)) {
        Estante nova_estante;
        inicializar_estante(&nova_estante);
        if (adicionar_livro_estante(&nova_estante, livro)) {
            biblioteca->estantes[biblioteca->num_estantes] = nova_estante;
            biblioteca->num_estantes++;
            return 1;
        }
    }
    return 0;
}

// int remover_livro_biblioteca(Biblioteca *biblioteca, int indice) {
//     for (int i = 0; i < biblioteca->num_estantes; i++) {
//         if (remover_livro_estante(&biblioteca->estantes[i], indice)) {
//             return 1;
//         }
//     }
//     return 0;
// }

void imprimir_biblioteca(Biblioteca *biblioteca) {
    for (int i = 0; i < biblioteca->num_estantes; i++) {
        printf("-------------------ESTANTE %d:-------------------\n", i + 1);
        for (int j = 0; j < biblioteca->estantes[i].num_prateleiras; j++) {
            Prateleira *prateleira = &biblioteca->estantes[i].prateleiras[j];
            for (int k = 0; k < prateleira->num_livros; k++) {
                Livro *livro = &prateleira->livros[k];
                printf("Livro[%d]: %s Autor: %s (%dcm x %dcm x %dcm x %dcm3)\n", 
                       livro->indice, livro->titulo, livro->autor, 
                       livro->largura, livro->altura, livro->profundidade, livro->volume);
            }
        }
        printf("---------------------------------------------------------------\n");
    }
}
