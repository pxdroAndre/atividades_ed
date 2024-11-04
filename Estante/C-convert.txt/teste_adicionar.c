// Função para adicionar um livro à prateleira
int adicionar_livro_a_prateleira(Prateleira *prateleira, Livro livro) {
    if (prateleira->largura_usada + livro.largura <= prateleira->largura_maxima) {
        No *novo_no = (No *)malloc(sizeof(No));
        if (!novo_no) {
            printf("Erro ao alocar memória para novo livro\n");
            exit(1);
        }
        novo_no->livro = livro;
        novo_no->proximo = NULL;
        novo_no->anterior = prateleira->lista_livros->fim;

        if (prateleira->lista_livros->fim != NULL) {
            prateleira->lista_livros->fim->proximo = novo_no;
        } else {
            prateleira->lista_livros->inicio = novo_no;
        }
        prateleira->lista_livros->fim = novo_no;
        prateleira->largura_usada += livro.largura;
        prateleira->num_livros++;
        return 1;  // Sucesso
    }
    return 0;  // Não há espaço suficiente
}

// Função para adicionar um livro à biblioteca (Atualizado)
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
            if (adicionar_livro_a_prateleira(prateleira, livro)) {
                return;  // Livro adicionado com sucesso
            }
        }
    }

    // Se todas as prateleiras em todas as estantes estiverem cheias, adicionar nova estante
    adicionaEstante(biblioteca);
    adicionaLivro(biblioteca, livro); // Tentar adicionar o livro novamente
}
