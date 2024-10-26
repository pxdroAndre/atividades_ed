from classes import Livro, Biblioteca

#funcao para ler os livros do arquivo
def ler_livros_arquivo(arquivo_path):
    # lista para armazenar os livros
    livros = []
    with open(arquivo_path, 'r') as arquivo: #abre o arquivo para ser lido
        linhas = arquivo.readlines() #lê e armazena as linhas do arquivo
        for i, linha in enumerate(linhas): #for para percorrer as linhas 
            linha = linha.strip()#funcao para remover os espaços em branco
            if linha:
                #vai verificar se a linha não está vazia e separar os elementos da linha usando , como separador e = para separar o atributo do valor
                partes = linha.split(',')
                titulo = partes[0].split('=')[1].strip()
                autor = partes[1].split('=')[1].strip()
                largura = int(partes[2].split('=')[1].strip())
                altura = int(partes[3].split('=')[1].strip())
                profundidade = int(partes[4].split('=')[1].strip())
                volume = altura * largura * profundidade
                #depois de separar, cria um objeto livro com os valores 
                livro = Livro(titulo, autor, largura, altura, profundidade, volume, i+1)
                livros.append(livro) #adiciona o livro na lista de livros
    return livros #retorna a lista de livros

#funcao que vai organizar a biblioteca
def organizar_biblioteca(arquivo_path):  
    livros = ler_livros_arquivo(arquivo_path)
    
    # ordenar os livros por altura e largura em ordem decrescente
    livros.sort(key=lambda x: (x.volume))
    
    biblioteca = Biblioteca()
    
    for livro in livros:
        biblioteca.adicionar_livro(livro)
    return biblioteca
    
def menu(acao):
    match acao:
        case 1:
            print(biblioteca)
            return
        case 2:
            #funcao de consultar o livro
            return
        case 3:
            #funcao de pegar emprestado
            return
        case 4:
            #funcao de inserir livro
            return
        case 5:
            #funcao de remover livro
            return
        case _:
            print("acao invalida!\n")
            return
            
arquivo_path = 'entrada.txt'
biblioteca = organizar_biblioteca(arquivo_path)
print("Seus livros foram armazenados!\nEscolha uma das opcoes a seguir\n")
print("Digite um numero correspondente\n")
print("[1] Imprimir a Biblioteca \n[2] Consultar um livro \n[3] Pegar emprestado \n[4] Inserir livro \n[5] Remover livro")
acao=int(input())
menu(acao)
