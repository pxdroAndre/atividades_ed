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
void criar_no_e_insere_inicio(Livro livro, ListaDuplamenteEncadeada *prateleira) 
{
    printf("criando o no e colocando no inicio da prateleira\n");
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
    if((verificar_vazia(prateleira)) == 1) 
    {
        //P4
        prateleira->inicio= prateleira->fim = novo_no;
    }
    else
    {
        //p5  
        prateleira->inicio->anterior = novo_no;
        prateleira->inicio = novo_no;
    }
    return;
}

// Função para criar um novo nó e inserir no fim da lista
void criar_no_e_insere_fim(Livro livro, ListaDuplamenteEncadeada *lista) 
{
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    //passo1
    novo_no->livro = livro;
    //p2
    novo_no->proximo = NULL;
    if (verificar_vazia(lista)){
        lista->inicio = lista->fim = novo_no;
    }
    else{
        //P3  
        lista->fim->proximo = novo_no;
        //P4
        novo_no->anterior = lista->fim;
        //p5  
        lista->fim = novo_no;
    }
    printf("coloquei no fim da lista\n");
    return;
}

//remover inicio da lista sem backup
Livro RemoveInicio(ListaDuplamenteEncadeada *lista)
{ 
    printf("removendo o topo da lista\n");
    printf("antes de remover: voli:%d volf: %d\n", lista->inicio->livro.volume, lista->fim->livro.volume);
    No *atual;  
    Livro backup = { .titulo = "", .volume = -1 };
    if (verificar_vazia(lista) == 1) return backup; 
    // backup do elemento do inicio da lista pra dar free
    atual = lista->inicio; 
    backup = atual->livro;
    if (lista->inicio == lista->fim) // se só tiver um elemento na lista
        lista->inicio = lista->fim = NULL; 
    else
    { 
        // inicio da lista receba o item 2 metaforicamente   
        lista->inicio = atual->proximo; 
        // setando o item 2 como inicio da lista   
        lista->inicio->anterior = NULL;  
        printf("depois de remover: voli:%d volf: %d\n", lista->inicio->livro.volume, lista->fim->livro.volume);

    }  
    // libera a memoria do nó removido  
    free(atual); 
    return backup; 
} 

Livro RemoveFim(ListaDuplamenteEncadeada *lista){ 
    No *atual;  
    Livro backup;
    // pega o livro que sera removido
    atual = lista->fim; 
    backup = atual->livro;
    // ve se é o unico item da lista
    if (lista->inicio == lista->fim)  
        lista->inicio = lista->fim = NULL; 
    else
    {  
        // Atualiza o ponteiro fim para o penúltimo nó
        lista->fim = atual->anterior;
        lista->fim->proximo = NULL; // O novo fim da lista deve apontar para NULL
    }       
    return backup; 
} 

Livro RemoveMeio(No *livro_inicio, No *livro_achado)
{
    Livro backup;
    if (livro_inicio == livro_achado)
    {
        No *atual = livro_inicio;
        backup = atual->livro;
        if (livro_inicio->anterior) {
            livro_inicio->anterior->proximo = livro_inicio->proximo;
        }
        if (livro_inicio->proximo) {
        livro_inicio->proximo->anterior = livro_inicio->anterior;
        }
        free(atual);
    } 
    else
    {
        // recursa ate achar o no q foi adicionado
        return RemoveMeio(livro_inicio->proximo, livro_achado);
    }
    return backup; 
} 

//função para inicializar lista
void inicializar_lista (ListaDuplamenteEncadeada *lista_livros)
{
    //inicializar lista de livros com null
    lista_livros->inicio = NULL;
    lista_livros->fim = NULL;
}

//função para inicializar pratileira
void inicializar_prateleira(Prateleira *prateleira, int volume_maximo)
{
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
    estante->num_prateleiras = MAX_PRATELEIRAS; //número de prateleiras da estante recebe o máximo = 6
    for (int i = 0; i < MAX_PRATELEIRAS; i++) {
        inicializar_prateleira(&estante->prateleiras[i], VOLUME_MAXIMO); //receber volume máximo de prateleiras em cada estante
    }
}


//função para criar lista
No* achar_maior_possivel_e_adicionar_prateleira(Prateleira *prateleira, No *livros, int volume_restante)
{
    // se couber na estante ele adiciona
    if (volume_restante >= livros->livro.volume)
    {
        return livros;
    }
    return achar_maior_possivel_e_adicionar_prateleira(prateleira, livros->anterior, volume_restante);
}

//função para adicionar livro
int adicionar_livro(Prateleira *prateleira, ListaDuplamenteEncadeada *livros)
{
    printf("colocando o livro de volume %d\n", livros->inicio->livro.volume);
    printf("livros na prateleira = %d\n", prateleira->num_livros);
    if (prateleira->num_livros == 0) //caso seja primeiro livro na prateleira
    {
        Livro backup = RemoveInicio(livros); // remove livro da lista de livros
        if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
        criar_no_e_insere_inicio(backup, prateleira->lista_livros);
        prateleira->volume_usado += prateleira->lista_livros->inicio->livro.volume; //volume usado é acrescentado com volume de livro
        prateleira->num_livros++; //numero de livros da prateleira é aumentado
        printf("primeiro livro colocado\n");
        return 1;
    }
    //se caso volume usado seja menor que volume máximo, inserir livro
    if (
        ((prateleira->volume_usado + livros->inicio->livro.volume) <= prateleira->volume_maximo) && // condicao 1: se o volume cabe na estante
        // condicao 2: se a metade do livro mais recente eh maior do que o livro que quero colocar
        (((prateleira->lista_livros->fim->livro.altura / 2) < livros->inicio->livro.altura) || 
        // se metade da altura do livro que quero colocar eh menor do que o livro atual
        ((livros->inicio->livro.altura / 2) < prateleira->lista_livros->fim->livro.altura))
    )
    {
        printf("colocando livros normais\n");
        // inserir no fim da lista da prateleira
        Livro backup;
        if ((prateleira->num_livros % 2) == 0) //verificar se numero de livros é par ou impar para criar nó
        {
            printf("livros par\n");
            backup = RemoveInicio(livros); // remove livro da lista de livros
        }
        else
        {
            printf("livros impar\n");
            backup = RemoveFim(livros);
        }
        if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
        criar_no_e_insere_fim(backup, prateleira->lista_livros);
        prateleira->volume_usado += backup.volume;
        prateleira->num_livros++; //aumentar numero de livros na prateleira
        return 1;
    }
    else 
    {
        int volume_restante = prateleira->volume_maximo - prateleira->volume_usado;
        if ((prateleira->num_livros % 2) == 0)
        {
            // se o numero de livros for par a lista esta no livro menor
            // verifica o volume do livro menor da lista 
            if (volume_restante >= livros->inicio->livro.volume)
            {
                //encontrar livro de maior volume possível para inserir na prateleira e retorna o indice do livro
                No* livro_achado = achar_maior_possivel_e_adicionar_prateleira(prateleira, livros->fim, volume_restante); 
                if (livro_achado == livros->inicio) 
                {
                    Livro backup = RemoveInicio(livros);
                    if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                else if (livro_achado == livros->fim)
                {
                    Livro backup = RemoveFim(livros);
                    if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                else 
                {
                    Livro backup = RemoveMeio(livros->inicio, livro_achado);
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                prateleira->volume_usado += livro_achado->livro.volume;
                prateleira->num_livros++;
                return 1;
            }
        }
        else
        {
            // se o numero de livros for impar a lista esta no livro maior
            // verifica o volume do livro menor da lista 
            if (livros->inicio->proximo && volume_restante >= livros->inicio->proximo->livro.volume)
            {
                //encontrar livro de maior volume possível para inserir na prateleira e retorna o indice do livro
                No* livro_achado = achar_maior_possivel_e_adicionar_prateleira(prateleira, livros->inicio, volume_restante); 
                if (livro_achado == livros->inicio) 
                {
                    Livro backup = RemoveInicio(livros);
                    if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                else if (livro_achado == livros->fim)
                {
                    Livro backup = RemoveFim(livros);
                    if (backup.volume == -1) return 0; // Verifica se a remoção foi bem-sucedida
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                else 
                {
                    Livro backup = RemoveMeio(livros->inicio, livro_achado);
                    criar_no_e_insere_fim(backup, prateleira->lista_livros);
                }
                prateleira->volume_usado += livro_achado->livro.volume;
                prateleira->num_livros++;
                return 1;
            }
        }
    }
    printf("foi return 0 no add livro\n");
    return 0;
}

//função para adicionar livro na estante
int adicionar_livro_estante(Estante *estante, ListaDuplamenteEncadeada *livros) {
    for (int i = 0; i < estante->num_prateleiras; i++) 
    {
        printf("adicionando livros na prateleira [%d]\n", i);
        for (int j = 0; (adicionar_livro(&estante->prateleiras[i], livros) == 1); j++)
        {
            printf("livro adicionado\n");
        }
    }   
    return 0;
}

//função para adicionar livro na biblioteca
int adicionar_livro_biblioteca(Biblioteca *biblioteca, ListaDuplamenteEncadeada *livros) 
{
    printf("adicionar_livro_biblioteca\n");
    printf("quantidade de estantes: %d\n", biblioteca->num_estantes);
    if (biblioteca->num_estantes == 1 || !adicionar_livro_estante(&biblioteca->estantes[biblioteca->num_estantes - 1], livros)) {
        printf("criando nova estante\n");
        Estante nova_estante;
        inicializar_estante(&nova_estante); //chamar iniciar estante
        if (adicionar_livro_estante(&nova_estante, livros)) { //chamar para adicionar o livro na estante
            biblioteca->estantes[biblioteca->num_estantes] = nova_estante;
            biblioteca->num_estantes++;
            printf("dei return 1 porra\n");
            return 1;
        }
    }
    printf("dei return 0 porra\n");
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
        // poe o novo no como depois do no atual
        atual->proximo = novo_no;
        // liga o nó atual ao novo
        novo_no->anterior = atual;
        printf("livro[%d] aponta para %d\n", i, novo_no->anterior->livro.volume);
        // atual receba o novo nó
        atual = novo_no;
        //free (novo_no);
    }
    // faz o atual ser o fim da lista
    atual->proximo = NULL;
    // o inicio da lista-anterior aponte pro ultimo item 
    head->anterior = atual;
    return head;
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

void printar_biblioteca(Biblioteca *biblioteca)
{
    for (int i = 0; i < biblioteca->num_estantes; i++)
    {
        printf("Estante %d\n", i);
        for (int j = 0; j < biblioteca->estantes[i].num_prateleiras; j++)
        {
            printf("Prateleira %d\n", j);
            No* atual = biblioteca->estantes[i].prateleiras[j].lista_livros->inicio;
            do {
                printf("Titulo: %s, Volume: %d\n", atual->livro.titulo, atual->livro.volume);
                atual = atual->proximo;
            } while (atual != biblioteca->estantes[i].prateleiras[j].lista_livros->inicio);
        }
    }
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
    // o fim da lista recebe o endereço do ultimo item  
    livrosEncadeados.fim = livrosEncadeados.inicio->anterior;
    // faz a lista deixar de ser circular
    livrosEncadeados.inicio->anterior = NULL;
    adicionar_livro_biblioteca(&biblioteca, &livrosEncadeados);
    printf("acabei tudo\n");
    printar_biblioteca(&biblioteca);
    return 0;
}
