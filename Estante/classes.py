from functions import get_field

class Livro:
    #Construtor da classe Livro
    def __init__(self, titulo, largura, altura, profundidade, genero=None, autor=None, ano=None):
        self.titulo = titulo
        self.genero = genero
        self.autor = autor
        self.ano = ano
        self.largura = largura
        self.altura = altura
        self.profundidade = profundidade
    
    #Método que retorna uma string com as informações do livro
    def __str__(self):
        string = f'Título: {self.titulo}\nLargura: {self.largura}\nAltura: {self.altura}\nProfundidade: {self.profundidade}\n'
        if self.genero:
            string += f'Gênero: {self.genero}\n'
        if self.autor:
            string += f'Autor: {self.autor}\n'
        if self.ano:
            string += f'Ano: {self.ano}\n'
        return string


class Prateleira:
    #Construtor da classe Prateleira
    def __init__(self, largura):
        self.largura = largura
        self.largura_sobrando = largura
        self.generos = []
        self.livros = []

    #Método que printa os livros da prateleira
    def printa_prateleira(self):
        if len(self.livros) > 0:
            for livro in self.livros:
                print(livro.titulo)

    #Método que insere um livro na prateleira
    def inserir_livro(self, titulo, largura, altura, profundidade, genero='', autor='', ano=''):
        livro = Livro(titulo, largura, altura, profundidade, genero, autor, ano)

        #Verifica se o livro cabe na prateleira
        if largura > self.largura_sobrando:
            print(
                f'Esse livro ({livro.largura}cm) não cabe nessa prateleira, que só tem {self.largura_sobrando}cm livres')
            return False
        #Verifica se o gênero do livro já está na prateleira
        if genero not in self.generos:
            self.generos.append(genero)
        #Adiciona o livro na prateleira
        self.livros.append(livro)
        self.largura_sobrando -= largura
        return True
    
    #Método que insere um livro existente na prateleira
    def inserir_livro_existente(self, livro):
        #Verifica se o livro cabe na prateleira
        if livro.largura > self.largura_sobrando:
            return False
        #Verifica se o gênero do livro já está na prateleira*
        if livro.genero not in self.generos:
            self.generos.append(livro.genero)

        self.livros.append(livro)
        self.largura_sobrando -= livro.largura
        return True
    #Método que retorna o tamanho da prateleira
    def __len__(self):
        return len(self.livros)
    #Método que retorna uma string com as informações da prateleira
    def __str__(self):
        string = ''
        for i in range(len(self.livros)):
            string += f'Livro {i+1}:\n{self.livros[i]}\n\n'
        return string
    #Método que limpa a prateleira*
    def limpar_prateleira(self):
        if len(self.livros) > 0:
            lvs = self.livros
            self.livros = []
            self.largura_sobrando = self.largura
            return lvs


class Estante:
    #Construtor da classe Estante
    def __init__(self, largura=90):
        self.largura = largura
        self.prateleiras = []
    #Método que adiciona uma prateleira na estante
    def adicionar_prateleira(self, livros):
        if len(self.prateleiras) >= 6:
            return False
        #Cria uma nova prateleira
        prateleira = Prateleira(self.largura)
        for livro in livros:
            titulo = get_field(livro, 0)
            largura = int(get_field(livro, 1))
            altura = int(get_field(livro, 3))
            profundidade = int(get_field(livro, 4))
            genero = get_field(livro, 2)
            autor = get_field(livro, 5)
            ano = get_field(livro, 6)
            prateleira.inserir_livro(titulo, largura, altura, profundidade, genero, autor, ano)

        self.prateleiras.append(prateleira)
        return True
    #Método que retorna o tamanho da estante
    def __len__(self):
        return len(self.prateleiras)
    #Método que retorna uma string com as infos da estante
    def __str__(self):
        string = ''
        for i in range(len(self.prateleiras)):
            string += f'PRATELEIRA {i+1} - {self.prateleiras[i].largura_sobrando}cm disponíveis\n\n{self.prateleiras[i]}\n'
        return string


class Biblioteca:
    #Construtor da classe Biblioteca
    def __init__(self, array):
        self.estantes = []
        contador = 0
        for i in range(len(array)):
            if contador == 0:
                estante = Estante()
                estante.adicionar_prateleira(array[i])
            else:
                estante.adicionar_prateleira(array[i])
            contador = contador + 1

            if contador == 6:
                self.estantes.append(estante)
                contador = 0
            elif i == len(array)-1:
                self.estantes.append(estante)

    def __len__(self):
        prateleiras = 0
        for estante in self.estantes:
            prateleiras += len(estante)
        return prateleiras

    def __str__(self):
        string = ''
        for i in range(len(self.estantes)):
            string += f'---- ESTANTE {i+1} -----\n\n{self.estantes[i]}\n\n'
        return string