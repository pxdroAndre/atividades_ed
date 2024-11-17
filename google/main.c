// LEONARDO BEZERRA, LUCCA PAES, PEDRO ANDRÉ, YUCK ARTHUR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações de um artigo
typedef struct 
{
    char *titulo;          // Título do artigo
    char *autor;           // Autor do artigo
    char *descricao;       // Descrição do artigo
    char *palavras_chave;  // Palavras-chave associadas ao artigo
    char *link;            // Link para o artigo
} artigo;

// Estrutura para armazenar informações de um artigo encontrado, incluindo a contagem de semelhanças
typedef struct 
{
    char *titulo;
    char *autor;
    char *descricao;
    char *palavras_chave;
    char *link;
    int semelhantes;       // Número de palavras semelhantes encontradas
} artigosEncontrados;

// Estrutura para uma lista encadeada de artigos
typedef struct listaArtigos
{
    artigo *artigos;               // Array de artigos
    struct listaArtigos *proximo;  // Ponteiro para o próximo nó da lista
    int tamanho;                   // Número de artigos na lista
} listaArtigos;

// Estrutura para uma lista encadeada de artigos encontrados
typedef struct listaArtigosEncontrados
{
    artigosEncontrados *artigos;   // Array de artigos encontrados
    struct listaArtigosEncontrados *proximo; // Ponteiro para o próximo nó da lista
    int tamanho;                   // Número de artigos encontrados na lista
} listaArtigosEncontrados;

// Função para criar uma nova lista de artigos encontrados
listaArtigosEncontrados *criarListaArtigosEncontrados()
{
    listaArtigosEncontrados *lista = (listaArtigosEncontrados *)malloc(sizeof(listaArtigosEncontrados));
    lista->artigos = NULL;  // Inicializa o array de artigos como NULL
    lista->proximo = NULL;  // Inicializa o ponteiro para o próximo nó como NULL
    lista->tamanho = 0;     // Inicializa o tamanho da lista como 0
    return lista;
}

// Função para criar uma nova lista de artigos
listaArtigos *criarListaArtigos()
{
    listaArtigos *lista = (listaArtigos *)malloc(sizeof(listaArtigos));
    lista->artigos = NULL;  // Inicializa o array de artigos como NULL
    lista->proximo = NULL;  // Inicializa o ponteiro para o próximo nó como NULL
    lista->tamanho = 0;     // Inicializa o tamanho da lista como 0
    return lista;
}

// Função para adicionar um novo artigo à lista de artigos
void adicionarArtigo(listaArtigos *lista, artigo *novoArtigo)
{
    // Realoca memória para o array de artigos para acomodar o novo artigo
    artigo *temp = (artigo*)realloc(lista->artigos, (lista->tamanho + 1) * sizeof(artigo));
    lista->artigos = temp;
    lista->artigos[lista->tamanho] = *novoArtigo;  // Adiciona o novo artigo ao final do array
    lista->tamanho++;  // Incrementa o tamanho da lista
}

// Função para adicionar um novo artigo encontrado à lista de artigos encontrados
void adicionarArtigoEncontrado(listaArtigosEncontrados *lista, artigosEncontrados *novoArtigo)
{
    // Realoca memória para o array de artigos encontrados para acomodar o novo artigo
    artigosEncontrados *temp = (artigosEncontrados*)realloc(lista->artigos, (lista->tamanho + 1) * sizeof(artigosEncontrados));
    if (!temp) {
        fprintf(stderr, "Erro ao alocar memória para novo artigo.\n");
        exit(EXIT_FAILURE);
    }
    lista->artigos = temp;
    lista->artigos[lista->tamanho] = *novoArtigo;  // Adiciona o novo artigo ao final do array
    lista->tamanho++;  // Incrementa o tamanho da lista
}

// Função para ler arquivos e adicionar artigos à lista
void lerArquivoEAdicionarArtigos(const char *caminhoTitulos, const char *caminhoDescricoes, const char *caminhoPalavrasChave, const char *caminhoLinks, listaArtigos *lista)
{
    // Abre os arquivos para leitura
    FILE *arquivoTitulos = fopen(caminhoTitulos, "r");
    FILE *arquivoDescricoes = fopen(caminhoDescricoes, "r");
    FILE *arquivoPalavrasChave = fopen(caminhoPalavrasChave, "r");
    FILE *arquivoLinks = fopen(caminhoLinks, "r");

    // Verifica se todos os arquivos foram abertos corretamente
    if (!arquivoTitulos || !arquivoDescricoes || !arquivoPalavrasChave || !arquivoLinks) {
        fprintf(stderr, "Erro ao abrir um dos arquivos.\n");
        exit(EXIT_FAILURE);
    }

    // Alocação de memória para as linhas lidas dos arquivos
    char *linhaTitulo = NULL, *linhaDescricao = NULL, *linhaPalavrasChave = NULL, *linhaLink = NULL;
    size_t tamanhoTitulo = 0, tamanhoDescricao = 0, tamanhoPalavrasChave = 0, tamanhoLink = 0;

    // Leitura das linhas dos arquivos
    while (getline(&linhaTitulo, &tamanhoTitulo, arquivoTitulos) != -1 &&
           getline(&linhaDescricao, &tamanhoDescricao, arquivoDescricoes) != -1 &&
           getline(&linhaPalavrasChave, &tamanhoPalavrasChave, arquivoPalavrasChave) != -1 &&
           getline(&linhaLink, &tamanhoLink, arquivoLinks) != -1) {
        
        artigo novoArtigo;  // Cria um novo artigo
        // Procura por palavras-chave específicas nas linhas lidas
        char *titulo = strstr(linhaTitulo, "titulo: ");
        char *autor = strstr(linhaTitulo, "Autor: ");
        char *descricao = strstr(linhaDescricao, "descricao: ");
        char *palavrasChave = strstr(linhaPalavrasChave, "palavras-chave: ");
        char *link = strstr(linhaLink, "link: ");
        
        // Verifica se todas as palavras-chave foram encontradas
        if (titulo && autor && descricao && palavrasChave && link) {
            // Avança para o início da string após a palavra-chave
            titulo += strlen("titulo: ");
            autor += strlen("Autor: ");
            descricao += strlen("descricao: ");
            palavrasChave += strlen("palavras-chave: ");
            link += strlen("link: ");
            
            // Remove o sufixo " |" do título, se existir
            char *fimTitulo = strstr(titulo, " |");
            if (fimTitulo) {
                *fimTitulo = '\0';
            }
            
            // Copia os valores para o artigo
            novoArtigo.titulo = strdup(titulo);
            novoArtigo.autor = strdup(autor);
            novoArtigo.descricao = strdup(descricao);
            novoArtigo.link = strdup(link);

            // Verifica se há palavras-chave válidas
            if (strstr(palavrasChave, "Palavras-chave não encontradas") == NULL) {
                novoArtigo.palavras_chave = strdup(palavrasChave);
            } else {
                novoArtigo.palavras_chave = strdup(""); // Nenhuma palavra-chave encontrada
            }
            
            // Adiciona o novo artigo à lista
            adicionarArtigo(lista, &novoArtigo);
        }
    }

    // Libera a memória alocada para as linhas
    free(linhaTitulo);
    free(linhaDescricao);
    free(linhaPalavrasChave);
    free(linhaLink);

    // Fecha os arquivos
    fclose(arquivoTitulos);
    fclose(arquivoDescricoes);
    fclose(arquivoPalavrasChave);
    fclose(arquivoLinks);
}

// Função para remover preposições de uma pergunta
void remover_preposicoes(const char *pergunta, char *pergunta_sem_preposicoes, const char *preposicoes) {
    // Inicializa a string de saída
    pergunta_sem_preposicoes[0] = '\0';

    // Faça uma cópia da string pergunta
    char *pergunta_copia = strdup(pergunta);
    if (!pergunta_copia) {
        fprintf(stderr, "Erro ao alocar memória para a cópia da pergunta.\n");
        return;
    }

    // Tokeniza a pergunta em palavras
    char *token = strtok(pergunta_copia, " ");
    while (token != NULL) {
        // Verifica se a palavra não é uma preposição
        if (strstr(preposicoes, token) == NULL) 
        {
            strcat(pergunta_sem_preposicoes, token);  // Adiciona a palavra à string de saída
            strcat(pergunta_sem_preposicoes, " ");    // Adiciona um espaço entre as palavras
        }
        token = strtok(NULL, " ");  // Avança para o próximo token
    }

    free(pergunta_copia); // Libera a memória alocada para a cópia
}

// Função para imprimir detalhes de uma string
void print_string_details(const char *string, const char *str) 
{
    printf("%s: %s\n", str, string);  // Imprime a string
    printf("ASCII: ");
    // Imprime os valores ASCII de cada caractere na string
    for (int i = 0; string[i] != '\0'; i++) {
        printf("%d ", string[i]);
    }
    printf("\n");
}

// Função para buscar artigos que correspondem a uma pergunta
listaArtigosEncontrados *buscarArtigos(listaArtigos *lista, const char *pergunta) 
{
    listaArtigosEncontrados *artigos_correspondentes = criarListaArtigosEncontrados();  // Cria uma nova lista de artigos encontrados
    char *pergunta_copia = strdup(pergunta);  // Faz uma cópia da pergunta
    if (!pergunta_copia) {
        fprintf(stderr, "Erro ao alocar memória para a cópia da pergunta.\n");
        return NULL;
    }

    // Tokeniza a pergunta em palavras
    char *saveptr_pergunta;
    char *token_pergunta = strtok_r(pergunta_copia, " ", &saveptr_pergunta);
    while (token_pergunta != NULL) {
        token_pergunta[strcspn(token_pergunta, "\n")] = '\0';  // Remove o caractere de nova linha
        for (int i = 0; i < lista->tamanho; i++) {
            int encontrou = 0;  // Contador de palavras semelhantes encontradas

            // Verifica no título do artigo
            char *titulo_copia = strdup(lista->artigos[i].titulo);
            char *saveptr_titulo;
            char *token_titulo = strtok_r(titulo_copia, " ", &saveptr_titulo);
            while (token_titulo != NULL) {
                if (strcmp(token_titulo, token_pergunta) == 0) {
                    encontrou++;  // Incrementa se a palavra for encontrada
                }
                token_titulo = strtok_r(NULL, " ", &saveptr_titulo);
            }
            free(titulo_copia);

            // Verifica nas palavras-chave do artigo
            if (!encontrou) {
                char *palavras_chave_copia = strdup(lista->artigos[i].palavras_chave);
                char *saveptr_palavras_chave;
                char *token_palavras_chave = strtok_r(palavras_chave_copia, " ", &saveptr_palavras_chave);
                while (token_palavras_chave != NULL) {
                    if (strcmp(token_palavras_chave, token_pergunta) == 0) {
                        encontrou++;
                    }
                    token_palavras_chave = strtok_r(NULL, " ", &saveptr_palavras_chave);
                }
                free(palavras_chave_copia);
            }

            // Verifica na descrição do artigo
            if (!encontrou) {
                char *descricao_copia = strdup(lista->artigos[i].descricao);
                char *saveptr_descricao;
                char *token_descricao = strtok_r(descricao_copia, " ", &saveptr_descricao);
                while (token_descricao != NULL) {
                    if (strcmp(token_descricao, token_pergunta) == 0) {
                        encontrou++;
                    }
                    token_descricao = strtok_r(NULL, " ", &saveptr_descricao);
                }
                free(descricao_copia);
            }

            // Se encontrou palavras semelhantes, adiciona o artigo à lista de encontrados
            if (encontrou) 
            {
                artigosEncontrados artigo_encontrado;
                artigo_encontrado.titulo = lista->artigos[i].titulo;
                artigo_encontrado.autor = lista->artigos[i].autor;
                artigo_encontrado.descricao = lista->artigos[i].descricao;
                artigo_encontrado.palavras_chave = lista->artigos[i].palavras_chave;
                artigo_encontrado.link = lista->artigos[i].link;
                artigo_encontrado.semelhantes = encontrou;

                // Verifica se o título já existe na lista de encontrados
                int titulo_ja_existe = 0;
                for (int k = 0; k < artigos_correspondentes->tamanho; k++) {
                    if (strcmp(artigos_correspondentes->artigos[k].titulo, artigo_encontrado.titulo) == 0) {
                        titulo_ja_existe = 1;
                        break;
                    }
                }

                // Se o título não existe, adiciona o artigo encontrado à lista
                if (!titulo_ja_existe) {
                    adicionarArtigoEncontrado(artigos_correspondentes, &artigo_encontrado);
                }
            }
        }
        token_pergunta = strtok_r(NULL, " ", &saveptr_pergunta);  // Avança para o próximo token da pergunta
    }

    free(pergunta_copia); // Libera a memória alocada para a cópia
    return artigos_correspondentes;  // Retorna a lista de artigos encontrados
}

// Função para ordenar artigos encontrados com base no número de semelhanças
void ordenarArtigosEncontrados(listaArtigosEncontrados *lista)
{
    // Algoritmo de ordenação Bubble Sort
    for (int i = 0; i < lista->tamanho - 1; i++) {
        for (int j = 0; j < lista->tamanho - i - 1; j++) {
            if (lista->artigos[j].semelhantes < lista->artigos[j + 1].semelhantes) {
                // Troca os artigos se o atual tiver menos semelhanças que o próximo
                artigosEncontrados temp = lista->artigos[j];
                lista->artigos[j] = lista->artigos[j + 1];
                lista->artigos[j + 1] = temp;
            }
        }
    }
}

// Função principal
int main() 
{
    listaArtigos *lista = criarListaArtigos();  // Cria uma nova lista de artigos

    // Lê arquivos de diferentes sites e adiciona artigos à lista
    lerArquivoEAdicionarArtigos("artigos/site1/titulos.txt", "artigos/site1/descricoes.txt", "artigos/site1/palavras_chave.txt", "artigos/site1/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site2/titulos.txt", "artigos/site2/descricoes.txt", "artigos/site2/palavras_chave.txt", "artigos/site2/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site3/titulos.txt", "artigos/site3/descricoes.txt", "artigos/site3/palavras_chave.txt", "artigos/site3/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site4/titulos.txt", "artigos/site4/descricoes.txt", "artigos/site4/palavras_chave.txt", "artigos/site4/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site5/titulos.txt", "artigos/site5/descricoes.txt", "artigos/site5/palavras_chave.txt", "artigos/site5/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site6/titulos.txt", "artigos/site6/descricoes.txt", "artigos/site6/palavras_chave.txt", "artigos/site6/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site7/titulos.txt", "artigos/site7/descricoes.txt", "artigos/site7/palavras_chave.txt", "artigos/site7/links.txt", lista);

    // Solicita ao usuário que digite uma pergunta
    char *pergunta = NULL;
    size_t tamanho = 0;
    ssize_t caracteresLidos;

    printf("Digite sua pergunta: ");
    caracteresLidos = getline(&pergunta, &tamanho, stdin);  // Lê a pergunta do usuário
    printf("pergunta: %s\n", pergunta);

    // Define uma lista de preposições para remoção
    char preposicoes[] = "de da do das dos que o as the and a of for in at to with as at na no nas nos";
    char pergunta_sem_preposicoes[100];
    remover_preposicoes(pergunta, pergunta_sem_preposicoes, preposicoes);  // Remove preposições da pergunta
    printf("Pergunta sem preposições: %s\n", pergunta_sem_preposicoes);

    // Busca artigos que correspondem à pergunta sem preposições
    listaArtigosEncontrados *artigos_correspondentes = buscarArtigos(lista, pergunta_sem_preposicoes);
    ordenarArtigosEncontrados(artigos_correspondentes);  // Ordena os artigos encontrados

    // Imprime o número de artigos relevantes encontrados
    printf("Há %d artigos relevantes para sua pergunta.\n", artigos_correspondentes->tamanho);
    printf("\n");
    
    // Imprime detalhes dos artigos encontrados
    for (int i = 0; i < artigos_correspondentes->tamanho; i++) {
        printf("Título: %s\n", artigos_correspondentes->artigos[i].titulo);
        printf("Autor: %s", artigos_correspondentes->artigos[i].autor);
        printf("Descrição: %s", artigos_correspondentes->artigos[i].descricao);
        printf("Palavras-chave: %s", artigos_correspondentes->artigos[i].palavras_chave);
        printf("Link: %s", artigos_correspondentes->artigos[i].link);
        printf("Semelhantes: %d\n", artigos_correspondentes->artigos[i].semelhantes);
        printf("\n");
    }

    free(pergunta); // Libera a memória alocada para a pergunta

    // Liberação de memória para a lista de artigos
    free(lista->artigos);
    free(lista);

    return 0;  // Retorna 0 para indicar que o programa terminou com sucesso
}
