# CargasPesadas
TRABALHO AEDS
Grupo:​ Chrystian Paulo Ferreira de Melo
Gabriel Siroco Martins
Samuel Henrique Miranda Alves
1. Explicação do problema
Nossa questão consistia em resolver um problema de transporte de cargas pesadas
entre duas cidades. Porém, os viadutos por onde o transporte deve passar possuem uma
altura determinada, que não pode ser menor do que a altura da carga que está sendo
levada. Com isso, precisamos definir se existe algum caminho possível entre duas cidades,
em que a altura da carga transportada não pode ser maior do que a dos viadutos por onde
passar, e, caso exista mais do que um caminho, definir qual o menor caminho, referente a
uma menor quantidade de viadutos
2. Resolução do problema
De acordo com nossa análise, não faria diferença optar por usar uma matriz ou uma
lista para representar o grafo. Por isso, escolhemos a lista pelo fato de considerarmos essa
representação mais fácil de manipular, visto que sua utilização é dinâmica e de mais fácil
compreensão para o usuário, quando printada.
Para resolvermos o problema, consideramos que cada viaduto/cidade é um nó,
armazenando, assim, cada informação do viaduto/cidade em uma struct que seria usada
como modelo para a implementação dos nós da lista.
Nosso trabalho dispõe de, basicamente, cinco funções principais: inserir nós,
conectar nós, remover nós, buscar caminho entre cidades e imprimir grafo. Dentre estas
funções, seria interessante destacar duas delas, por serem mais complexas e interessantes.
A primeira delas é a função de conectar nós. Tal função busca no grafo os nós que
foram inseridos e pergunta ao usuário se ele quer conectar o primeiro com o segundo, o
primeiro com o terceiro e assim por diante. Por se tratar de um grafo não-orientado, quando
o usuário conecta um nó i com outro j, a função também conecta o nó j com o i,
economizando tempo do usuário e descartando a possibilidade do usuário direcionar um
único caminho entre viadutos/cidades.
A segunda função é a de busca entre duas cidades. Para realizar esta função,
utilizamos o famoso algoritmo de dijkstra, porém com uma modificação. O algoritmo de
dijkstra, para encontrar o menor caminho, soma o peso das arestas entre os nós que está
percorrendo. Porém, o menor caminho para o nosso problema significa percorrer menos
nós. Assim, quando o algoritmo percorre, através de uma estrutura de repetição, os nós
adjacentes de um determinado nó, os pesos das arestas são determinados por uma variável
count, que conta quantas vezes o loop está sendo executado.
3. Complexidade do problema
O(n^5);
4. Dificuldades e soluções encontradas
Uma das maiores dificuldades para resolver este problema foi durante a função de
busca no grafo, concernente à adaptação do algoritmo de dijkstra, visto que a maioria dos
algoritmos encontrados fazia a utilização de matrizes ao invés de lista. O único algoritmo
encontrado favorável às nossas necessidades foi o proposto pela professora Liliane Gade,
que fazia a implementação do grafo com lista. Tivemos, ainda, que consertar o problema
relacionado ao peso das arestas, como discutido anteriormente. No mais, os outros
problemas mais simples foram solucionados com a adoção de alguns métodos menos
complexos que não necessitam de ser citados.
