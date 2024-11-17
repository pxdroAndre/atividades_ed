// LEONARDO BEZERRA, LUCCA PAES, PEDRO ANDRÉ, YUCK ARTHUR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char *titulo;
    char *autor;
    char *descricao;
    char *palavras_chave;
    char *link;
} artigo;

typedef struct 
{
    char *titulo;
    char *autor;
    char *descricao;
    char *palavras_chave;
    char *link;
    int semelhantes;
} artigosEncontrados;

typedef struct listaArtigos
{
    artigo *artigos;
    struct listaArtigos *proximo;
    int tamanho;
} listaArtigos;

typedef struct listaArtigosEncontrados
{
    artigosEncontrados *artigos;
    struct listaArtigosEncontrados *proximo;
    int tamanho;
} listaArtigosEncontrados;

listaArtigosEncontrados *criarListaArtigosEncontrados()
{
    listaArtigosEncontrados *lista = (listaArtigosEncontrados *)malloc(sizeof(listaArtigosEncontrados));
    lista->artigos = NULL;
    lista->proximo = NULL;
    lista->tamanho = 0;
    return lista;
}

listaArtigos *criarListaArtigos()
{
    listaArtigos *lista = (listaArtigos *)malloc(sizeof(listaArtigos));
    if (!lista) {
        fprintf(stderr, "Erro ao alocar memória para lista de artigos.\n");
        exit(EXIT_FAILURE);
    }
    lista->artigos = NULL;
    lista->proximo = NULL;
    lista->tamanho = 0;
    return lista;
}

void adicionarArtigo(listaArtigos *lista, artigo *novoArtigo)
{
    artigo *temp = (artigo*)realloc(lista->artigos, (lista->tamanho + 1) * sizeof(artigo));
    if (!temp) {
        fprintf(stderr, "Erro ao alocar memória para novo artigo.\n");
        exit(EXIT_FAILURE);
    }
    lista->artigos = temp;
    lista->artigos[lista->tamanho] = *novoArtigo;
    lista->tamanho++;
}

void adicionarArtigoEncontrado(listaArtigosEncontrados *lista, artigosEncontrados *novoArtigo)
{
    artigosEncontrados *temp = (artigosEncontrados*)realloc(lista->artigos, (lista->tamanho + 1) * sizeof(artigosEncontrados));
    if (!temp) {
        fprintf(stderr, "Erro ao alocar memória para novo artigo.\n");
        exit(EXIT_FAILURE);
    }
    lista->artigos = temp;
    lista->artigos[lista->tamanho] = *novoArtigo;
    lista->tamanho++;
}

void lerArquivoEAdicionarArtigos(const char *caminhoTitulos, const char *caminhoDescricoes, const char *caminhoPalavrasChave, const char *caminhoLinks, listaArtigos *lista)
{
    FILE *arquivoTitulos = fopen(caminhoTitulos, "r");
    FILE *arquivoDescricoes = fopen(caminhoDescricoes, "r");
    FILE *arquivoPalavrasChave = fopen(caminhoPalavrasChave, "r");
    FILE *arquivoLinks = fopen(caminhoLinks, "r");

    if (!arquivoTitulos || !arquivoDescricoes || !arquivoPalavrasChave || !arquivoLinks) {
        fprintf(stderr, "Erro ao abrir um dos arquivos.\n");
        exit(EXIT_FAILURE);
    }

    char *linhaTitulo = NULL, *linhaDescricao = NULL, *linhaPalavrasChave = NULL, *linhaLink = NULL;
    size_t tamanhoTitulo = 0, tamanhoDescricao = 0, tamanhoPalavrasChave = 0, tamanhoLink = 0;

    while (getline(&linhaTitulo, &tamanhoTitulo, arquivoTitulos) != -1 &&
           getline(&linhaDescricao, &tamanhoDescricao, arquivoDescricoes) != -1 &&
           getline(&linhaPalavrasChave, &tamanhoPalavrasChave, arquivoPalavrasChave) != -1 &&
           getline(&linhaLink, &tamanhoLink, arquivoLinks) != -1) {
        
        artigo novoArtigo;
        char *titulo = strstr(linhaTitulo, "titulo: ");
        char *autor = strstr(linhaTitulo, "Autor: ");
        char *descricao = strstr(linhaDescricao, "descricao: ");
        char *palavrasChave = strstr(linhaPalavrasChave, "palavras-chave: ");
        char *link = strstr(linhaLink, "link: ");
        
        if (titulo && autor && descricao && palavrasChave && link) {
            titulo += strlen("titulo: ");
            autor += strlen("Autor: ");
            descricao += strlen("descricao: ");
            palavrasChave += strlen("palavras-chave: ");
            link += strlen("link: ");
            
            char *fimTitulo = strstr(titulo, " |");
            if (fimTitulo) {
                *fimTitulo = '\0';
            }
            
            novoArtigo.titulo = strdup(titulo);
            // printf("titulo: %s\n", novoArtigo.titulo);
            novoArtigo.autor = strdup(autor);
            novoArtigo.descricao = strdup(descricao);
            novoArtigo.link = strdup(link);

            if (strstr(palavrasChave, "Palavras-chave não encontradas") == NULL) {
                novoArtigo.palavras_chave = strdup(palavrasChave);
            } else {
                novoArtigo.palavras_chave = strdup(""); // Nenhuma palavra-chave encontrada
            }
            
            adicionarArtigo(lista, &novoArtigo);
        }
    }

    free(linhaTitulo);
    free(linhaDescricao);
    free(linhaPalavrasChave);
    free(linhaLink);

    fclose(arquivoTitulos);
    fclose(arquivoDescricoes);
    fclose(arquivoPalavrasChave);
    fclose(arquivoLinks);
}

void remover_preposicoes(const char *pergunta, char *pergunta_sem_preposicoes, const char *preposicoes) {
    // Inicializa a string de saída
    pergunta_sem_preposicoes[0] = '\0';

    // Faça uma cópia da string pergunta
    char *pergunta_copia = strdup(pergunta);
    if (!pergunta_copia) {
        fprintf(stderr, "Erro ao alocar memória para a cópia da pergunta.\n");
        return;
    }

    char *token = strtok(pergunta_copia, " ");
    while (token != NULL) {
        if (strstr(preposicoes, token) == NULL) 
        {
            // printf("token: %s\n", token);
            strcat(pergunta_sem_preposicoes, token);
            strcat(pergunta_sem_preposicoes, " "); // Adiciona um espaço entre as palavras
        }
        token = strtok(NULL, " ");
    }

    free(pergunta_copia); // Libera a memória alocada para a cópia
}

void print_string_details(const char *string, const char *str) 
{
    printf("%s: %s\n", str, string);
    printf("ASCII: ");
    for (int i = 0; string[i] != '\0'; i++) {
        printf("%d ", string[i]);
    }
    printf("\n");
}

listaArtigosEncontrados *buscarArtigos(listaArtigos *lista, const char *pergunta) 
{
    listaArtigosEncontrados *artigos_correspondentes = criarListaArtigosEncontrados();
    char *pergunta_copia = strdup(pergunta);
    if (!pergunta_copia) {
        fprintf(stderr, "Erro ao alocar memória para a cópia da pergunta.\n");
        return NULL;
    }

    char *saveptr_pergunta;
    char *token_pergunta = strtok_r(pergunta_copia, " ", &saveptr_pergunta);
    // printf("token_pergunta: %s\n", token_pergunta);
    while (token_pergunta != NULL) {
        token_pergunta[strcspn(token_pergunta, "\n")] = '\0';
        for (int i = 0; i < lista->tamanho; i++) {
            int encontrou = 0;

            // Verifica no título
            char *titulo_copia = strdup(lista->artigos[i].titulo);
            char *saveptr_titulo;
            char *token_titulo = strtok_r(titulo_copia, " ", &saveptr_titulo);
            while (token_titulo != NULL) {
                if (strcmp(token_titulo, token_pergunta) == 0) {
                    encontrou++;
                }
                token_titulo = strtok_r(NULL, " ", &saveptr_titulo);
            }
            free(titulo_copia);

            // Verifica nas palavras-chave
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

            // Verifica na descrição
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

            if (encontrou) 
            {
                artigosEncontrados artigo_encontrado;
                artigo_encontrado.titulo = lista->artigos[i].titulo;
                artigo_encontrado.autor = lista->artigos[i].autor;
                artigo_encontrado.descricao = lista->artigos[i].descricao;
                artigo_encontrado.palavras_chave = lista->artigos[i].palavras_chave;
                artigo_encontrado.link = lista->artigos[i].link;
                artigo_encontrado.semelhantes = encontrou;
                int titulo_ja_existe = 0;
                for (int k = 0; k < artigos_correspondentes->tamanho; k++) {
                    if (strcmp(artigos_correspondentes->artigos[k].titulo, artigo_encontrado.titulo) == 0) {
                        titulo_ja_existe = 1;
                        break;
                    }
                }

                if (!titulo_ja_existe) {
                    adicionarArtigoEncontrado(artigos_correspondentes, &artigo_encontrado);
                }
                // Não interrompe o loop, continua verificando outras palavras da pergunta
            }
        }
        token_pergunta = strtok_r(NULL, " ", &saveptr_pergunta);// Avança para o próximo token da pergunta
        // printf("token_pergunta: %s\n", token_pergunta); 
    }

    free(pergunta_copia); // Libera a memória alocada para a cópia
    return artigos_correspondentes;
}

void ordenarArtigosEncontrados(listaArtigosEncontrados *lista)
{
    for (int i = 0; i < lista->tamanho - 1; i++) {
        for (int j = 0; j < lista->tamanho - i - 1; j++) {
            if (lista->artigos[j].semelhantes < lista->artigos[j + 1].semelhantes) {
                artigosEncontrados temp = lista->artigos[j];
                lista->artigos[j] = lista->artigos[j + 1];
                lista->artigos[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    listaArtigos *lista = criarListaArtigos();
    lerArquivoEAdicionarArtigos("artigos/site1/titulos.txt", "artigos/site1/descricoes.txt", "artigos/site1/palavras_chave.txt", "artigos/site1/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site2/titulos.txt", "artigos/site2/descricoes.txt", "artigos/site2/palavras_chave.txt", "artigos/site2/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site3/titulos.txt", "artigos/site3/descricoes.txt", "artigos/site3/palavras_chave.txt", "artigos/site3/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site4/titulos.txt", "artigos/site4/descricoes.txt", "artigos/site4/palavras_chave.txt", "artigos/site4/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site5/titulos.txt", "artigos/site5/descricoes.txt", "artigos/site5/palavras_chave.txt", "artigos/site5/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site6/titulos.txt", "artigos/site6/descricoes.txt", "artigos/site6/palavras_chave.txt", "artigos/site6/links.txt", lista);
    lerArquivoEAdicionarArtigos("artigos/site7/titulos.txt", "artigos/site7/descricoes.txt", "artigos/site7/palavras_chave.txt", "artigos/site7/links.txt", lista);

    // Exemplo de como acessar os artigos
    // for (int i = 0; i < lista->tamanho; i++) {
    //     printf("Título: %s\n", lista->artigos[i].titulo);
    //     printf("Autor: %s", lista->artigos[i].autor);
    //     printf("Descrição: %s", lista->artigos[i].descricao);
    //     printf("Palavras-chave: %s\n", lista->artigos[i].palavras_chave);
    //     printf("Link: %s\n", lista->artigos[i].link);
    //     printf("\n");
    // }
    // printf("tamanho: %d\n", lista->tamanho);
    char *pergunta = NULL;
    size_t tamanho = 0;
    ssize_t caracteresLidos;

    printf("Digite sua pergunta: ");
    caracteresLidos = getline(&pergunta, &tamanho, stdin);
    printf("pergunta: %s\n", pergunta);
    char preposicoes[] = "de da do das dos que o as the and a of for in at to with as at na no nas nos";
    char pergunta_sem_preposicoes[100];
    remover_preposicoes(pergunta, pergunta_sem_preposicoes, preposicoes);
    printf("Pergunta sem preposições: %s\n", pergunta_sem_preposicoes);
    listaArtigosEncontrados *artigos_correspondentes = buscarArtigos(lista, pergunta_sem_preposicoes);
    ordenarArtigosEncontrados(artigos_correspondentes);
    printf("Há %d artigos relevantes para sua pergunta.\n", artigos_correspondentes->tamanho);
    printf("\n");
    
    for (int i = 0; i < artigos_correspondentes->tamanho; i++) {
        printf("Título: %s\n", artigos_correspondentes->artigos[i].titulo);
        printf("Autor: %s", artigos_correspondentes->artigos[i].autor);
        printf("Descrição: %s", artigos_correspondentes->artigos[i].descricao);
        printf("Palavras-chave: %s", artigos_correspondentes->artigos[i].palavras_chave);
        printf("Link: %s", artigos_correspondentes->artigos[i].link);
        printf("Semelhantes: %d\n", artigos_correspondentes->artigos[i].semelhantes);
        printf("\n");
    }

    free(pergunta); // Libera a memória alocada

    // Liberação de memória
    free(lista->artigos);
    free(lista);

    return 0;
}

