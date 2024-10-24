from functions import get_field
from classes import Biblioteca

def criar_biblioteca():
    # receber o input
    with open('./entrada.txt', 'r') as arquivo:
        linhas = arquivo.readlines()

    livros = []
    for linha in linhas:
        linha = linha.strip()
        # se a linha não for vazia
        if linha:
            # separar os dados
            partes = linha.split(',')
            # pegar os dados
            titulo = partes[0].split('=')[1].strip()
            autor = partes[1].split('=')[1].strip()
            largura = int(partes[2].split('=')[1].strip())
            altura = int(partes[3].split('=')[1].strip())
            profundidade = int(partes[4].split('=')[1].strip())
            # adicionar os dados na lista de livros
            livros.append([titulo, largura, autor, altura, profundidade])

    # Ordenar os livros por altura e depois por largura (decrescente)
    livros.sort(key=lambda livro: (livro[3], livro[1]), reverse=True)

    # Criar as prateleiras
    prateleiras = []
    prateleira_atual = []
    largura_atual = 0
    largura_maxima_prateleira = 96

    
    for livro in livros:
        largura_livro = livro[1]
        # se a largura do livro for menor ou igual a largura máxima da prateleira add um livro na prateleira
        if largura_atual + largura_livro <= largura_maxima_prateleira:
            prateleira_atual.append(livro)
            largura_atual += largura_livro
        else:
            prateleiras.append(prateleira_atual)
            prateleira_atual = [livro]
            largura_atual = largura_livro

    if prateleira_atual:
        prateleiras.append(prateleira_atual)

    return Biblioteca(prateleiras)


def sortar_biblioteca(biblioteca):
    livros = []
    for estante in biblioteca.estantes:
        for prateleira in estante.prateleiras:
            l = prateleira.limpar_prateleira()
            for livro in l:
                livros.append(livro)

    livros = sorted(livros, key=lambda livro: (livro.genero, livro.autor, livro.ano, livro.titulo))

    estante = 0
    prateleira = 0
    while len(livros) > 0:
        livro = livros.pop(0)
        adicionar = biblioteca.estantes[estante].prateleiras[prateleira].inserir_livro_existente(livro)
        if adicionar == False:
            prateleira += 1
            if prateleira == 6:
                estante += 1
                prateleira = 0
            adicionar = biblioteca.estantes[estante].prateleiras[prateleira].inserir_livro_existente(livro)


# Criando e organizando a biblioteca
my_library = criar_biblioteca()
sortar_biblioteca(my_library)
print(my_library)