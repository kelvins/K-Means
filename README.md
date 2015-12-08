# K-Means

Implementação do algoritmo de agrupamento K-Means em C++ com interface gráfica. Este projeto tem como objetivo ser utilizado como trabalho na disciplina de Mineração de Dados e ser utilizado futuramente para fins didáticos.

## Descrição

"Em mineração de dados, agrupamento k-means é um método de Clustering que objetiva particionar n observações dentre k grupos onde cada observação pertence ao grupo mais próximo da média. Isso resulta em uma divisão do espaço de dados em um Diagrama de Voronoi."

Informações mais detalhadas e o passo-a-passo podem ser encontrados neste [link](http://imasters.com.br/artigo/4709/sql-server/data-mining-na-pratica-algoritmo-k-means/).

### Parâmetros

O único parâmetro para o K-Means é o número de Ks, que na verdade é o número de grupos esperado.

## Instruções de Utilização

- Botão Arquivo: é possível selecionar e carregar um arquivo no formato CSV.
- Campos Coluna 1 e Coluna 2: são utilizados para selecionar as colunas desejadas do arquivo carregado.
- Possui Cabeçalho: este campo deve ser selecionado se o arquivo possui cabeçalho, pois ele é utilizado para ignorar ou não a primeira linha do arquivo CSV.
- K: é o parâmetro do K-Means que é o número esperado de grupos encontrados.
- Botão START: utilizado para rodar o K-Means nos dados carregados (arquivo CSV) e configurados.
- Campo Resultado: mostra as informações utilizadas no K-Means e a quantidade de grupos com seus respectivos pontos.
- Gráfico: apenas plota os dados para facilitar a visualização.
- Botão Salvar o Gráfico como Imagem: permite salvar o gráfico como uma imagem.
- Botão Salvar Resultado em CSV: permite salvar o resultado do K-Means em CSV, sendo que cada linha irá apresentar o grupo referente ao ponto em que ele pertence.

## Gráficos gerados

![alt text](https://github.com/kelvins/K-Means/blob/master/Graficos.png "Graficos")

> Obs.: Esta aplicação foi desenvolvida como estudo e trabalho para a disciplina de Mineração de Dados e tem como objetivo ser utilizada para o desenvolvimento do trabalho e posteriormente para fins didáticos do algoritmo K-Means.

Qualquer dúvida ou sugestão sobre a aplicação entre em contato pelo e-mail: kelvinpfw@hotmail.com