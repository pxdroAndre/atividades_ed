import requests
from bs4 import BeautifulSoup

def extract_titles_and_descriptions(file_path):
    # Carregar o conteúdo HTML do arquivo
    with open(file_path, 'r', encoding='utf-8') as file:
        soup = BeautifulSoup(file, 'html.parser')
    
    # Abrir arquivos para escrita
    with open('titulos.txt', 'w', encoding='utf-8') as title_file, open('descricoes.txt', 'w', encoding='utf-8') as description_file:
        # Encontrar todos os divs com a classe 'obj_article_summary'
        article_divs = soup.find_all('div', class_='obj_article_summary')
        print(f'Divs encontradas: {len(article_divs)}')
        
        for div in article_divs:
            # Encontrar o link dentro do div
            link = div.find('a')
            if link:
                href = link.get('href')
                if href:
                    response = requests.get(href)
                    print(f'Requisição para {href} retornou status {response.status_code}')
                    if response.status_code == 200:
                        article_soup = BeautifulSoup(response.content, 'html.parser')
                        
                        # # Extrair o título
                        # title = article_soup.find('title').get_text(strip=True)
                        # print(f'Título extraído: {title}')
                        
                        # Tentar extrair a descrição de diferentes formas
                        description = None
                        
                        # Tentar encontrar a meta tag 'DC.description'
                        description_meta = article_soup.find('meta', {'name': 'DC.description'})
                        if description_meta:
                            description = description_meta.get('content')
                        
                        # Se não encontrar, tentar outras meta tags comuns
                        if not description:
                            description_meta = article_soup.find('meta', {'name': 'description'})
                            if description_meta:
                                description = description_meta.get('content')
                        
                        # Se ainda não encontrar, tentar extrair o primeiro parágrafo
                        if not description:
                            paragraph = article_soup.find('p')
                            if paragraph:
                                description = paragraph.get_text(strip=True)
                        
                        # Se ainda não encontrar, usar um texto padrão
                        if not description:
                            description = 'Descrição não encontrada'
                        
                        print(f'Descrição extraída: {description}')
                        
                        # Escrever o título no arquivo de títulos
                        # title_file.write(f'Título: {title}\n')
                        
                        # Escrever a descrição no arquivo de descrições
                        description_file.write(f'{description}\n\n')

# Exemplo de uso
extract_titles_and_descriptions('D:/OneDrive - 340tpx/André/Estudo/Faculdade/2_Periodo_UFAL/ED/Atividades/atividades_ab2/2_google/site1.html')
