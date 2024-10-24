#funcao que retorna o campo de um array, mas caso o campo nao exista, retorna None
def get_field(fields, index):
    if len(fields) > index:
        return fields[index]
    else:
        return None