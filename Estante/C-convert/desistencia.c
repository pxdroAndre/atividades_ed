#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 1000
#define MAX_PRATELEIRAS 6
#define LARGURA_MAXIMA 96
#define VOLUME_MAXIMO 96256

// struct de livro
typedef struct {
    char titulo[100];
    char autor[100];
    int largura;
    int altura;
    int profundidade;
    int volume;
    int indice;
} Livro;

// struct de no
typedef struct no {
    Livro livro;
    struct no *anterior, *proximo;
} No;

// struct de listaduplamenteencadeada
typedef struct {
    No *inicio;
    No *fim;
} ListaDuplamenteEncadeada;

// struct de prateleira
typedef struct {
    int volume_maximo;
    int volume_usado;
    int num_livros;
    ListaDuplamenteEncadeada *lista_livros;
} Prateleira;

// struct de estante
typedef struct {
    Prateleira prateleiras[MAX_PRATELEIRAS];
    int num_prateleiras;
} Estante;

// struct da biblioteca
typedef struct {
    Estante *estantes;
    int num_estantes;
} Biblioteca;

// Função para inicializar uma lista duplamente encadeada
ListaDuplamenteEncadeada *inicializaLista() {
    ListaDuplamenteEncadeada *lista = (ListaDuplamenteEncadeada *)malloc(sizeof(ListaDuplamenteEncadeada));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

// Função para inicializar uma prateleira
Prateleira inicializaPrateleira() {
    Prateleira prateleira;
    prateleira.volume_maximo = VOLUME_MAXIMO;
    prateleira.volume_usado = 0;
    prateleira.num_livros = 0;
    prateleira.lista_livros = inicializaLista();
    return prateleira;
}

// Função para inicializar uma estante
Estante inicializaEstante() {
    Estante estante;
    estante.num_prateleiras = MAX_PRATELEIRAS;
    for (int i = 0; i < MAX_PRATELEIRAS; i++) {
        estante.prateleiras[i] = inicializaPrateleira();
    }
    return estante;
}

// Função para inicializar a biblioteca
Biblioteca *inicializaBiblioteca() {
    Biblioteca *biblioteca = (Biblioteca *)malloc(sizeof(Biblioteca));
    biblioteca->estantes = NULL;
    biblioteca->num_estantes = 0;
    return biblioteca;
}

// Função para adicionar uma nova estante à biblioteca
void adicionaEstante(Biblioteca *biblioteca) {
    biblioteca->num_estantes++;
    biblioteca->estantes = (Estante *)realloc(biblioteca->estantes, biblioteca->num_estantes * sizeof(Estante));
    biblioteca->estantes[biblioteca->num_estantes - 1] = inicializaEstante();
}

// Função para adicionar um livro a uma lista duplamente encadeada
void adicionaLivroNaLista(ListaDuplamenteEncadeada *lista, Livro livro) {
    No *novo_no = (No *)malloc(sizeof(No));
    novo_no->livro = livro;
    novo_no->anterior = lista->fim;
    novo_no->proximo = NULL;
    if (lista->fim != NULL) {
        lista->fim->proximo = novo_no;
    } else {
        lista->inicio = novo_no;
    }
    lista->fim = novo_no;
}

// Função para adicionar um livro à biblioteca
void adicionaLivro(Biblioteca *biblioteca, Livro livro) {
    // Verificar se precisamos adicionar uma estante
    if (biblioteca->num_estantes == 0) {
        adicionaEstante(biblioteca);
    }
    
    // Iterar pelas estantes para encontrar espaço
    for (int i = 0; i < biblioteca->num_estantes; i++) {
        Estante *estante = &biblioteca->estantes[i];
        
        // Tentar adicionar o livro em uma das prateleiras
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            
            // Verificar se a prateleira tem espaço suficiente
            if (prateleira->volume_usado + livro.volume <= prateleira->volume_maximo) {
                adicionaLivroNaLista(prateleira->lista_livros, livro);
                prateleira->volume_usado += livro.volume;
                prateleira->num_livros++;
                return; // Livro adicionado com sucesso
            }
        }
    }

    // Se todas as prateleiras em todas as estantes estiverem cheias, adicionar nova estante
    adicionaEstante(biblioteca);
    adicionaLivro(biblioteca, livro); // Tentar adicionar o livro novamente
}

// Função para liberar a memória da biblioteca
void liberaBiblioteca(Biblioteca *biblioteca) {
    for (int i = 0; i < biblioteca->num_estantes; i++) {
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) {
                No *prox = atual->proximo;
                free(atual);
                atual = prox;
            }
            free(prateleira->lista_livros);
        }
    }
    free(biblioteca->estantes);
    free(biblioteca);
}

// Função para imprimir a biblioteca
void imprimeBiblioteca(Biblioteca *biblioteca) {
    printf("Biblioteca:\n");
    for (int i = 0; i < biblioteca->num_estantes; i++) {
        printf("  Estante %d:\n", i + 1);
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            printf("    Prateleira %d: (Peso = %d gm/cm3)\n", j + 1, prateleira->volume_usado);
            printf("      Livros:\n");

            // Percorre a lista de livros na prateleira
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) {
                Livro livro = atual->livro;
                printf("        - Indice: %d, Titulo: %s, Autor: %s, Volume: %d\n", livro.indice, livro.titulo, livro.autor, livro.volume);
                atual = atual->proximo;
            }
            
            // Verifica se a prateleira está vazia
            if (prateleira->lista_livros->inicio == NULL) {
                printf("        (Prateleira vazia)\n");
            }
        }
    }
}


//função para ler arquivo e inserir os dados do livro
void ler_livros_arquivo(const char *arquivo_path, Livro livros[])
{
    FILE *arquivo = fopen(arquivo_path, "r"); //abrir arquivo
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

//função para ordernar livros de acordo com volume do menor para maior
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


// Exemplo de uso
int main() {
    Biblioteca *biblioteca = inicializaBiblioteca();
    Livro livros [MAX_LIVROS];

    // Criar alguns livros de exemplo 
    ler_livros_arquivo("entrada.txt", livros);
    ordenar_livros_por_volume(livros, MAX_LIVROS);

    // Adicionar livros à biblioteca
    for (int i = 0; i < MAX_LIVROS; i++)
    {
        adicionaLivro(biblioteca, livros[i]);    
    }
    // Imprimir a biblioteca
    imprimeBiblioteca(biblioteca);
    // Liberar a memória alocada
    liberaBiblioteca(biblioteca);

    return 0;
}
