# mesmo esquema do outro código, classes que são como structs e possuem uma hierarquia de organização

class Livro:
    def __init__(self, titulo, autor, largura, altura, profundidade, volume, indice):
        self.titulo = titulo
        self.autor = autor
        self.largura = largura
        self.altura = altura
        self.profundidade = profundidade
        self.volume = volume
        self.indice = indice

    def __str__(self):
        return f"Livro[{self.indice}]: {self.titulo} Autor: {self.autor} ({self.largura}cm x {self.altura}cm x {self.profundidade}cm x {self.volume}cm3)\n"


class Prateleira:
    def __init__(self, largura_maxima):
        self.largura_maxima = largura_maxima
        self.largura_usada = 0
        self.livros = []

    def adicionar_livro(self, livro):
        if self.largura_usada + livro.largura <= self.largura_maxima:
            self.livros.append(livro)
            self.largura_usada += livro.largura
            return True
        return False

    def remover_livro(self, indice):
        for livro in self.livros:
            if livro.indice == indice:
                self.livros.remove(livro)
                self.largura_usada -= livro.largura
                return True
        return False

    def __str__(self):
        return "\n".join(str(livro) for livro in self.livros)


class Estante:
    def __init__(self, num_prateleiras=6, largura_maxima=96):
        self.prateleiras = [Prateleira(largura_maxima) for _ in range(num_prateleiras)]

    def adicionar_livro(self, livro):
        for prateleira in (self.prateleiras):
            if prateleira.adicionar_livro(livro):
                return True
        return False

    def remover_livro(self, indice):
        for prateleira in (self.prateleiras):
            if prateleira.remover_livro(indice):
                return True
        return False

    def __str__(self):
        return "\n".join([f"Prateleira {i + 1}:\n{prateleira}\n" for i, prateleira in enumerate(self.prateleiras)])


class Biblioteca:
    def __init__(self, largura_estante=96, altura_estante=188, profundidade_estante=32, num_prateleiras=6):
        self.estantes = []
        self.largura_estante = largura_estante
        self.altura_estante = altura_estante
        self.profundidade_estante = profundidade_estante
        self.num_prateleiras = num_prateleiras

    def adicionar_livro(self, livro):
        for estante in self.estantes:
            if estante.adicionar_livro(livro):
                return
        nova_estante = Estante(self.num_prateleiras, self.largura_estante)
        nova_estante.adicionar_livro(livro)
        self.estantes.append(nova_estante)

    def remover_livro(self, indice):
        for estante in (self.estantes):
            if estante.remover_livro(indice):
                return True
        return False

    def __str__(self):
        result = []
        for i, estante in enumerate(self.estantes):
            result.append(
                f"-------------------ESTANTE {i + 1}:-------------------\n{estante}---------------------------------------------------------------\n")
        return "\n".join(result)
