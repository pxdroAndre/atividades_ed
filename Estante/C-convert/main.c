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
    Estante *estantes;
    int num_estantes;
} Biblioteca;

int adicionar_livro(Prateleira *prateleira, Livro livro) 
{
    if (prateleira->volume_maximo + livro.volume <= prateleira->volume_maximo) 
    {
        prateleira->livros[prateleira->num_livros] = livro;
        prateleira->volume_usado += livro.volume;
        prateleira->num_livros++;
        return 1;
    }
    return 0;
}

void inicializar_prateleira(Prateleira *prateleira, int volume_maximo) {
    prateleira->volume_maximo = volume_maximo;
    prateleira->volume_usado = 0;
    prateleira->num_livros = 0;
}

void inicializar_estante(Estante *estante) {
    estante->num_prateleiras = MAX_PRATELEIRAS;
    for (int i = 0; i < MAX_PRATELEIRAS; i++) {
        inicializar_prateleira(&estante->prateleiras[i], VOLUME_MAXIMO);
    }
}

int adicionar_livro_estante(Estante *estante, Livro livro) {
    for (int i = 0; i < estante->num_prateleiras; i++) {
        if (adicionar_livro(&estante->prateleiras[i], livro)) {
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

void inicializar_biblioteca(Biblioteca *biblioteca) 
{
    biblioteca->num_estantes = 1;  // Inicia com uma estante
    biblioteca->estantes = malloc((MAX_LIVROS / MAX_PRATELEIRAS) * sizeof(Estante));
    if (!biblioteca->estantes) {
        printf("Erro ao alocar memória para estantes\n");
        exit(1);
    }
    inicializar_estante(&biblioteca->estantes[0]);  // Inicializa a primeira estante
}


void ler_livros_arquivo(const char *arquivo_path, Livro livros[]) 
{
    FILE *arquivo = fopen(arquivo_path, "r");
    if (!arquivo) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char linha[100];
    int indice = 1;
    while (fgets(linha, sizeof(linha), arquivo)) 
    {
        char titulo[100], autor[100];
        // Debug: Imprimindo a linha lida
        // printf("Lendo linha: %s\n", livros[indice-1]);
        
        if (sscanf(linha, "titulo=%99[^,],autor=%99[^,],largura=%d,altura=%d, profundidade=%d", 
                   titulo, autor, &livros[indice-1].largura, &livros[indice-1].altura, &livros[indice-1].profundidade) == 5) 
        {
            // Copiar os valores lidos para a estrutura livro
            strncpy(livros[indice-1].titulo, titulo, sizeof(livros[indice-1].titulo));
            strncpy(livros[indice-1].autor, autor, sizeof(livros[indice-1].autor));
            livros[indice-1].volume = livros[indice-1].largura * livros[indice-1].altura * livros[indice-1].profundidade;
            livros[indice-1].indice = indice;
        } else 
        {
            printf("Linha inválida: %s", linha);
        }
        indice++;
    }
    fclose(arquivo);
}

void ordenar_livros_por_volume(Livro livros[], int num_livros) 
{
    for (int i = 0; i < num_livros - 1; i++) 
    {
        for (int j = 0; j < num_livros - i - 1; j++) 
        {
            if (livros[j].volume > livros[j + 1].volume) 
            {
                // Trocar os livros de posição
                Livro temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

void pegar_maior_menor (Livro livros[], Biblioteca *biblioteca)
{

}

void encadeada_circular (Livro livros[])
{

}

// Função para criar um novo nó da lista
No* criar_no(Livro livro) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    novo_no->livro = livro;
    novo_no->anterior = novo_no->proximo = NULL;
    return novo_no;
}

// Função para transformar a array em uma lista duplamente encadeada circular
No* array_para_lista(Livro livros[], int num_livros) 
{
    if (num_livros == 0) return NULL;

    // Cria o primeiro nó e configura como a cabeça
    No* head = criar_no(livros[0]);
    No* atual = head;

    // Adiciona os demais livros à lista
    for (int i = 1; i < num_livros; i++) 
    {
        No* novo_no = criar_no(livros[i]);
        atual->proximo = novo_no;
        novo_no->anterior = atual;
        atual = novo_no;
    }

    // Torna a lista circular
    atual->proximo = head;
    head->anterior = atual;

    return head;
}

// Função para imprimir a lista circular
void imprimir_lista(No* head) {
    if (!head) return;

    No* atual = head;
    do {
        printf("Titulo: %s, Volume: %d\n", atual->livro.titulo, atual->livro.volume);
        atual = atual->proximo;
    } while (atual != head);
}

// Liberar a memória da lista
void liberar_lista(No* head) {
    if (!head) return;

    No* atual = head;
    do {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    } while (atual != head);
}


int main()
{
    
    //ler os livros
    Livro livros [MAX_LIVROS];

    // gurada os livros nnuma array de livros
    ler_livros_arquivo("entrada2.txt", livros);

    //calcula o tamanho da array
    int num_livros = sizeof(livros) / sizeof(livros[0]);    
    //ordena por volumes
    ordenar_livros_por_volume(livros, 30);
    //inicializa a biblioteca  
    Biblioteca biblioteca;
    inicializar_biblioteca(&biblioteca);
    
    No* livrosEncadeados = array_para_lista(livros, 30);
    printf("%d", livrosEncadeados->anterior->livro.volume);

    

    // atual anterior
    // atual -> proximo
    // anterior -> anterior -> anteior

    // pegar_maior_menor(livros, &biblioteca);

    return 0;
}
