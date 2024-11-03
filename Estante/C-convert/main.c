#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 1000
#define MAX_PRATELEIRAS 6
#define LARGURA_MAXIMA 96
#define VOLUME_MAXIMO 96256

//struct de livro
typedef struct {
    char titulo[100];
    char autor[100];
    int largura;
    int altura;
    int profundidade;
    int volume;
    int indice;
} Livro;

//struct de no
typedef struct no{
 Livro livro;
 struct no *anterior, *proximo;
}No;

//struct de listaduplamenteencadeada
typedef struct
{
 No *inicio;
 No *fim;
}ListaDuplamenteEncadeada;

//struct de prateleira
typedef struct {
    int volume_maximo;
    int volume_usado;
    int num_livros;
    ListaDuplamenteEncadeada *lista_livros;
} Prateleira;

//struct de estante
typedef struct {
    Prateleira prateleiras[MAX_PRATELEIRAS];
    int num_prateleiras;
} Estante;

//struct da biblioteca
typedef struct {
    Estante *estantes;
    int num_estantes;
} Biblioteca;

int verificar_vazia(ListaDuplamenteEncadeada *lista)
{
    if (lista->inicio == NULL) return 1;
    return 0;
}

// Função para criar um novo nó e inserir no inicio da lista
void criar_no_e_insere_inicio(Livro livro, ListaDuplamenteEncadeada *prateleira) {
    printf("2222\n");
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    //passo1
    novo_no->livro = livro;
    //p2
    novo_no->proximo = prateleira->inicio;
    //P3  
    novo_no->anterior = NULL;
    //se a lista nao tiver vazia
    if((verificar_vazia(prateleira)) == 0) 
    {
        //P4
        prateleira->inicio->anterior = novo_no;
    }
    else
    {
        prateleira->fim = novo_no;
    }
    //p5  
    prateleira->inicio = novo_no;
    
    return;
}

// Função para criar um novo nó e inserir no fim da lista
void criar_no_e_insere_fim(Livro livro, ListaDuplamenteEncadeada *lista) {
    printf("5555\n");
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    //passo1
    novo_no->livro = livro;
    //p2
    novo_no->proximo = NULL;
    //P3  
    lista->fim->proximo = novo_no;
    //P4
    novo_no->anterior = lista->fim;
    //p5  
    lista->fim = novo_no;
    return;
}

//remover inicio da lista sem backup
int RemoveInicio(ListaDuplamenteEncadeada *lista)
{ 
    No *atual;  
    if (verificar_vazia(lista) == 1) return 0; 
    // backup do elemento do inicio da lista pra dar free
    atual = lista->inicio; 
    // backup do valor do elemento do inicio dalista q sera removido
 

    if (lista->inicio == lista->fim) // se só tiver um elemento na lista
        lista->inicio = lista->fim = NULL; 
    else
    { 
        // inicio da lista receba o item 2 metaforicamente   
        lista->inicio = atual->proximo; 
        // setando o item 2 como inicio da lista   
        lista->inicio->anterior = NULL;  
    }  
    // libera a memoria do nó removido  
    free(atual); 
    return 1; 
} 

int RemoveFim(ListaDuplamenteEncadeada *lista){ 
    No *atual;  
    
    // pega o livro que sera removido
    atual = lista->fim; 
    // ve se é o unico item da lista
    if (lista->inicio == lista->fim)  
        lista->inicio = lista->fim = NULL; 
    else
    {  
        // fazendo o penultimo apontar pro inicio se tornando o ultimo
        atual->anterior->proximo = atual->anterior;
        // atualiza o inicio-proximo pra apontar pro fim da lista
        atual->anterior->proximo = atual->proximo;
        // fim da lista aponta pro penultimo 
        lista->fim = atual->anterior; 
    }       
    free(atual); 
    
    return 1; 
} 

 
int RemoveMeio(No *livro_inicio, int indice)
{
    if (livro_inicio->livro.indice == indice)
    {
        No *atual;  
        atual = livro_inicio;
        // faz o 14-anterior apontar pro 12 metaforicamente
        livro_inicio->proximo->anterior = livro_inicio->anterior;
        // faz o 12-proximo apontar pro 14 metaforicament
        livro_inicio->anterior->proximo = livro_inicio->proximo;
        free (atual);
    } 
    else
    {
        // recursa ate achar o no q foi adicionado
        return RemoveMeio(livro_inicio->proximo, indice);
    }
    return 1; 
} 

//função para inicializar lista
void inicializar_lista (ListaDuplamenteEncadeada *lista_livros)
{
    printf("HHHH\n");
    //inicializar lista de livros com null
    lista_livros->inicio = NULL;
    lista_livros->fim = NULL;
}

//função para inicializar pratileira
void inicializar_prateleira(Prateleira *prateleira, int volume_maximo)
{
    printf("GGGG\n");

    prateleira->volume_maximo = volume_maximo; //volume máximo da pratileira irá receber 96256
    prateleira->volume_usado = 0; //volume usado começa com 0
    prateleira->num_livros = 0; //numero de livros na estante começa com 0
    prateleira->lista_livros = malloc(sizeof(ListaDuplamenteEncadeada));
    if (!prateleira->lista_livros) {
        printf("Erro ao alocar memória para lista de livros\n");
        exit(1);
    }
    inicializar_lista(prateleira->lista_livros); //função para inicializar lista de livros
}

//função para inicializar estante
void inicializar_estante(Estante *estante) {
    printf("DDDD\n");
    estante->num_prateleiras = MAX_PRATELEIRAS; //número de prateleiras da estante recebe o máximo = 6
    for (int i = 0; i < MAX_PRATELEIRAS; i++) {
        printf("era pra ter farios g\n");
        inicializar_prateleira(&estante->prateleiras[i], VOLUME_MAXIMO); //receber volume máximo de prateleiras em cada estante
    }
}

//função para retirar livro par
void retirar_livro_par(ListaDuplamenteEncadeada *livros)
{
    printf("33333\n");
    // utili pra liberar memoria do ponteiro
    No *temp = livros->inicio;
    //Faz o 6-proximo apontar pro 2 metaforicamente
    livros->fim->proximo = livros->inicio->proximo;
    // Faz o 2-anterior apontar pro 6 metaforicamente
    livros->inicio->proximo->anterior = livros->inicio->anterior;
    // Faz o inicio apontar pro 6 metaforicamente
    livros->inicio = livros->fim;
    // Faz o fim apontar pro 2 metaforicamente
    livros->fim = livros->inicio->proximo;
    free (temp);
}

//função para retirar livro impar
void retirar_livro_impar(ListaDuplamenteEncadeada *livros)
{
    printf("66666\n");
    //Faz o 2-anterior apontar pro 5 metaforicamente
    livros->fim->anterior = livros->inicio->anterior;
    // Faz o 5-proximo apontar pro 2 metaforicamente
    livros->inicio->anterior->proximo = livros->inicio->proximo;
    // Faz o inicio apontar pro 2 metaforicamente
    livros->inicio = livros->fim;
    // Faz o fim apontar pro 5 metaforicamente
    livros->fim = livros->inicio->anterior;
}

//função para criar lista
int achar_maior_possivel_e_adicionar_prateleira(Prateleira *prateleira, No *livros, int volume_restante)
{
    printf("99999\n");

    // se couber na estante ele adiciona
    if (volume_restante <= livros->livro.volume)
    {
        criar_no_e_insere_fim(livros->livro, prateleira->lista_livros);
        prateleira->volume_usado += livros->livro.volume;
        prateleira->num_livros++;
        return livros->livro.indice;
    }
    return achar_maior_possivel_e_adicionar_prateleira (prateleira, livros->anterior, volume_restante);
}

//função para adicionar livro
int adicionar_livro(Prateleira *prateleira, ListaDuplamenteEncadeada *livros)
{
    printf("EEEEE\n");
    printf("%d\n", prateleira->num_livros);
    if(prateleira->num_livros == 0) //caso seja primeiro livro na prateleira
    {
        printf("111\n");
        criar_no_e_insere_inicio(livros->inicio->livro, prateleira->lista_livros);
        prateleira->volume_usado += prateleira->lista_livros->inicio->livro.volume; //volume usado é acrescentado com volume de livro
        prateleira->num_livros++; //numero de livros da prateleira é aumentado
        // printf("livro: %d, vol: %d", prateleira->num_livros,prateleira->volume_usado);
        retirar_livro_par(livros); // remove livro da lista de livros
        return 1;
    }
    //se caso volume usado seja menor que volume máximo, inserir livro
    if (
        ((prateleira->volume_usado + livros->inicio->livro.volume) <= prateleira->volume_maximo) && // condicao 1: se oo volume cabe na estante
        // condicao 2: se a metade do livro mais recente eh maior do que o livro que quero colocar
        (((prateleira->lista_livros->fim->livro.altura / 2) < livros->inicio->livro.altura) || 
        // se metade da altura do livro que quero colocar eh menor do que o livro atual
        ((livros->inicio->livro.altura/2) < prateleira->lista_livros->fim->livro.altura)) 
        )
    {
        printf("44444\n");
        // inserir no fim da lista da prateleira
        criar_no_e_insere_fim(livros->inicio->livro, prateleira->lista_livros);
        prateleira->volume_usado += livros->inicio->livro.volume;
        if ((prateleira->num_livros % 2) == 0) //verificar se numero de livros é par ou impar para criar nó
        {
            retirar_livro_par(livros);
        }
        else
        {
            retirar_livro_impar(livros);
        }
        prateleira->num_livros++; //aumentar numero de lirvos na prateleria
        return 1;
    }
    else 
    {
        printf(".5\n");
        int volume_restante = prateleira->volume_maximo - prateleira->volume_usado;
        if ((prateleira->num_livros % 2) == 0)
        {
            printf("77777\n");
            // se o numero de livros for par a lista esta no livro menor
            // verifica o volume do livro menor da lista 
            // ISSO PROVAVELMENTE NAO VAI SER USADO 
            if (volume_restante >= livros->inicio->livro.volume);
            {
                printf("8888\n");
                //encontrar livro de maior volume possível para inserir na prateleira e retorna o indice do livor
                int indice_usado = achar_maior_possivel_e_adicionar_prateleira(prateleira, livros->fim, volume_restante); 
                if (indice_usado == livros->inicio->livro.indice) RemoveInicio(livros);
                else if (indice_usado == livros->fim->livro.indice) RemoveFim(livros);
                else RemoveMeio(livros->inicio, indice_usado);
            }
        }
        else
        {
            // se o numero de livros for impar a lista esta no livro maior
            // verifica o volume do livro menor da lista 
            if (volume_restante >= livros->inicio->proximo->livro.volume)
            {
                printf("888888\n");
                //encontrar livro de maior volume possível para inserir na prateleira e retorna o indice do livor
                int indice_usado = achar_maior_possivel_e_adicionar_prateleira(prateleira, livros->inicio, volume_restante); 
                if (indice_usado == livros->fim->livro.indice) RemoveFim(livros);
                else RemoveMeio(livros->inicio, indice_usado);
            }
        }
    }
    return 0;
}

//função para adicionar livro na estante
int adicionar_livro_estante(Estante *estante, ListaDuplamenteEncadeada *livros) {
    printf("FFF\n");
    for (int i = 0; i < estante->num_prateleiras; i++) {
        if (adicionar_livro(&estante->prateleiras[i], livros)) 
        {
            return 1;
        }
    }
    return 0;
}

//função para adicionar livro na biblioteca
int adicionar_livro_biblioteca(Biblioteca *biblioteca, ListaDuplamenteEncadeada *livros) 
{
    printf("bbb\n");
    printf("b: %d\n", biblioteca->num_estantes);
    if (biblioteca->num_estantes == 1 || !adicionar_livro_estante(&biblioteca->estantes[biblioteca->num_estantes - 1], livros)) {
        printf("CCC\n");
        Estante nova_estante;
        inicializar_estante(&nova_estante); //chamar iniciar estante
        if (adicionar_livro_estante(&nova_estante, livros)) { //chamar para adicionar o livro na estante
            biblioteca->estantes[biblioteca->num_estantes] = nova_estante;
            biblioteca->num_estantes++;
            return 1;
        }
    }
    return 0;
}

//função para inicializar biblioteca
void inicializar_biblioteca(Biblioteca *biblioteca)
{
    biblioteca->num_estantes = 1; // Inicia com uma estante
    biblioteca->estantes = malloc(sizeof(Estante)); //alocando memoria para estante
    if (!biblioteca->estantes) {
        printf("Erro ao alocar memória para estantes\n");
        exit(1);
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
    // Torna a listacircular
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
    ler_livros_arquivo("entrada_menor.txt", livros);
    //ordena por volumes
    ordenar_livros_por_volume(livros, 30);
    //inicializa a biblioteca
    Biblioteca biblioteca;
    inicializar_biblioteca(&biblioteca);
    //fazendo listas de livros
    ListaDuplamenteEncadeada livrosEncadeados;
    livrosEncadeados.inicio = array_para_lista(livros, 30);
    livrosEncadeados.fim = livrosEncadeados.inicio->anterior;
    // printf("%d, %d\n", livrosEncadeados.inicio->livro.volume, livrosEncadeados.fim->livro.volume);
    adicionar_livro_biblioteca(&biblioteca, &livrosEncadeados);
    // printf("nome:%s, vol:%d\n", biblioteca.estantes->prateleiras->lista_livros->inicio->livro.autor, biblioteca.estantes->prateleiras->lista_livros->inicio->livro.volume);
    return 0;
}
