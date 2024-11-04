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
    printf("BIBLIOTECA:\n");
    for (int i = 0; i < biblioteca->num_estantes; i++) {
        printf("  ---------------------Estante %d:--------------------------------------------\n", i + 1);
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            printf("    Prateleira %d: (Peso = %d gm/cm3)\n", j + 1, prateleira->volume_usado);
            printf("      Livros[%d]:\n", prateleira->num_livros);

            // Percorre a lista de livros na prateleira
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) {
                Livro livro = atual->livro;
                printf("        - Indice: %d, Titulo: %s, Autor: %s, Altura: %d, Largura: %d, profundidade: %d Volume: %d\n", 
                livro.indice, livro.titulo, livro.autor,livro.altura, livro.largura, livro.profundidade, livro.volume);
                atual = atual->proximo;
            }
            
            // Verifica se a prateleira está vazia
            if (prateleira->lista_livros->inicio == NULL) {
                printf("        (Prateleira vazia)\n");
            }
        }
        printf("-------------------------------------------------------------------------------\n");
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

void print_livro (Livro livro)
{
    printf("Indice: %d\nTitulo: %s\nAutor: %s\nAltura: %d\nLargura: %d\nProfundidade: %d\nVolume: %d\n",
    livro.indice, livro.titulo, livro.autor, livro.altura, livro.largura, livro.profundidade, livro.volume);
}

Livro busca_indice(Biblioteca *biblioteca)
{
    int indice;
    printf("Digite o indice: ");
    scanf("%d", &indice);
    for (int i = 0; i < biblioteca->num_estantes; i++) 
    {
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            // Percorre a lista de livros na prateleira
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) 
            {
                Livro livro = atual->livro;
                if (livro.indice == indice) 
                {
                    print_livro(livro);
                    return livro;
                }
                atual = atual->proximo;
            }
        }
    }
    printf("Livro nao encontrado\n");
}

Livro busca_titulo(Biblioteca *biblioteca)
{
    char titulo [100], livro_titulo [100];
    printf("Digite o titulo:");
    getchar();
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    for (int i = 0; i < biblioteca->num_estantes; i++) 
    {
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            // Percorre a lista de livros na prateleira
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) 
            {
                Livro livro = atual->livro;
                strcpy(livro_titulo, titulo);
                if (strcmp(livro.titulo, titulo) == 0)
                {
                    print_livro(livro);
                    return livro;
                }
                atual = atual->proximo;
            }
        }
    }
    printf("Livro nao encontrado\n");
}

Livro busca_autor(Biblioteca *biblioteca)
{
    char autor [100];
    printf("Digite o autor: ");
    getchar();
    fgets(autor, sizeof(autor), stdin);
    autor[strcspn(autor, "\n")] = '\0';
    for (int i = 0; i < biblioteca->num_estantes; i++) 
    {
        Estante *estante = &biblioteca->estantes[i];
        for (int j = 0; j < estante->num_prateleiras; j++) {
            Prateleira *prateleira = &estante->prateleiras[j];
            // Percorre a lista de livros na prateleira
            No *atual = prateleira->lista_livros->inicio;
            while (atual != NULL) 
            {
                Livro livro = atual->livro;
                if (strcmp(livro.autor, autor) == 0)
                {
                    print_livro(livro);
                    return livro;
                } 
                atual = atual->proximo;
            }
        }
    }
    printf("Livro nao encontrado\n");
}

Livro ler_livro(Livro livro, Biblioteca *biblioteca)
{
    printf("Digite o titulo:");
    getchar();
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
    printf("Digite o autor:");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';
    printf("Digite a altura:");
    scanf("%d", &livro.altura);
    printf("Digite o largura:");
    scanf("%d", &livro.largura);
    printf("Digite a profundidade:");
    scanf("%d", &livro.profundidade);
    livro.volume = livro.altura * livro.largura * livro.profundidade;
    printf("Volume: %d\n", livro.volume);
    if (livro.volume > VOLUME_MAXIMO) 
    {
        printf ("Volume acima do permitido\n");
        return ler_livro(livro, biblioteca);
    }
    return livro;
} 

Biblioteca inserir_livro (Biblioteca *biblioteca, Livro livros[], int *contador)
{
    Livro livro_inserido;
    Biblioteca nova_biblioteca;
    livro_inserido = ler_livro(livro_inserido, biblioteca);
    livro_inserido.indice = MAX_LIVROS + *contador;
    printf("indice: %d\n", livro_inserido.indice);
    livros[MAX_LIVROS + (*contador-1)] = livro_inserido;
    ordenar_livros_por_volume(livros, MAX_LIVROS+*contador);
    // Adicionar livros à biblioteca
    for (int i = 0, j = MAX_LIVROS; i < MAX_LIVROS; i++)
    {
        adicionaLivro(&nova_biblioteca, livros[i]);    
        if ((i >= j)) break;
        adicionaLivro(&nova_biblioteca, livros[j]);
        j--;
    }
    return nova_biblioteca;

}

void consulta(Biblioteca *biblioteca)
{
    printf("Escolha qual o criterio da consulta\n");
    printf("[1] Indice\n[2] Titulo\n[3] Autor\n");
    int resposta;
    scanf("%d", &resposta);
    switch (resposta)
    {
    case 1:
        busca_indice(biblioteca);
        break;
    case 2:
        busca_titulo(biblioteca);
        break;
    case 3:
        busca_autor(biblioteca);
        break;
    default:
        printf("Parametro invalido!\n");
        break;
    }
}

Biblioteca *remover_livro(int indice, Livro livros[])
{
    Biblioteca *biblioteca = inicializaBiblioteca();
    // Adicionar livros à biblioteca
    for (int i = 0, j = MAX_LIVROS; i < MAX_LIVROS; i++)
    {
        if ((livros[i].indice != indice) && (livros[j].indice != indice))
        {
            adicionaLivro(biblioteca, livros[i]);    
            if ((i >= j)) break;
            adicionaLivro(biblioteca, livros[j]);
            j--;
        }
    }
    return biblioteca;
}
Biblioteca *emprestimo(Biblioteca *biblioteca, Livro livros[])
{
    Livro livro;
    livro = busca_indice(biblioteca);
    biblioteca = remover_livro(livro.indice, livros);
    return biblioteca;
}
void hub (Biblioteca *biblioteca, Livro livros[], int *contador_inserir)
{
    system("clear");
    printf("Seus livros foram armazenados! Escolha uma das opções a seguir\n");
    printf("[1] Imprimir a Biblioteca \n[2] Consultar um livro \n[3] Pegar emprestado \n[4] Inserir livro \n[5] Remover livro \n[0] Sair\n");
    int acao;
    scanf("%d", &acao);
    switch (acao)
    {
    case 1:
        // Imprimir a biblioteca
        imprimeBiblioteca(biblioteca);
        int resposta;
        printf("[0] Fechar programa\n[1] Voltar ao menu\n");
        scanf("%d", &resposta);
        if (resposta == 0) return;
        if (resposta == 1) hub(biblioteca, livros, contador_inserir);
        break;
    case 2:
        {
            consulta(biblioteca);
            int resposta_2;
            printf("[0] Fechar programa\n[1] Voltar ao menu\n");
            scanf("%d", &resposta_2);
            if (resposta_2 == 0) return;
            if (resposta_2 == 1) hub(biblioteca, livros, contador_inserir);
            break;
        }
    case 3:
        // funcao emprestimo
        biblioteca = emprestimo(biblioteca, livros);
        printf("[0] Fechar programa\n[1] Voltar ao menu\n");
        scanf("%d", &resposta);
        if (resposta == 0) return;
        if (resposta == 1) hub(biblioteca, livros, contador_inserir);
        break;
    case 4: 
        {
            // funcao insercao
            (*contador_inserir)++;
            Livro novos_livros [MAX_LIVROS + *contador_inserir];
            int i;
            for (i = 0; i < MAX_LIVROS; i++)
            {
                novos_livros[i] = livros[i];
            }
            *biblioteca = inserir_livro(biblioteca, novos_livros, contador_inserir);
            printf("[0] Fechar programa\n[1] Voltar ao menu\n");
            scanf("%d", &resposta);
            if (resposta == 0) return;
            if (resposta == 1) hub(biblioteca, novos_livros, contador_inserir);
            break;
        }
    case 5: 
        // funcao remocao
        printf("Digite o indice do livro que sera removido:");
        int indice;
        scanf("%d", &indice);
        biblioteca = remover_livro(indice, livros);
        int resposta_2;
        printf("[0] Fechar programa\n[1] Voltar ao menu\n");
        scanf("%d", &resposta_2);
        if (resposta_2 == 0) return;
        if (resposta_2 == 1) hub(biblioteca, livros, contador_inserir);
        break;

    case 0: 
        return;

    default:
        printf("Resposta invalida\n");
        break;
    }
}
// Exemplo de uso
int main() {
    Biblioteca *biblioteca = inicializaBiblioteca();
    Livro livros [MAX_LIVROS];
    int contador_inserir;

    // Criar alguns livros de exemplo 
    ler_livros_arquivo("entrada.txt", livros);
    ordenar_livros_por_volume(livros, MAX_LIVROS);

    // Adicionar livros à biblioteca
    for (int i = 0, j = MAX_LIVROS; i < MAX_LIVROS; i++)
    {
        adicionaLivro(biblioteca, livros[i]);    
        if ((i >= j)) break;
        adicionaLivro(biblioteca, livros[j]);
        j--;
    }
    hub(biblioteca, livros, &contador_inserir);
    
    // Liberar a memória alocada
    liberaBiblioteca(biblioteca);

    return 0;
}
