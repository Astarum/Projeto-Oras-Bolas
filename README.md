# Projeto Ora Bolas -> Feito em C

Nosso projeto consiste no robô interceptar a bola. Para realizar isso, aplicamos fórmulas de física em todos os movimentos da bola e do robô.

Utilizamos lista ligada em C para registrar cada instante de tempo do robô e da bola como um elemento da lista. Após isso, o programa lê cada elemento, cria os arquivos .txt dos gráficos (que são utilizados como scripts para o gnuplot), cria também o arquivo de logs com informações como velocidade e instante de tempo referentes as interceptações da bola, além disso, ele também cria um arquivo .txt, utilizado para a animação feita com javascript no canvas.

![chrome_BnhU1SYs3g](https://user-images.githubusercontent.com/97410682/170841256-043640b5-0f3a-476c-8456-9ce258c090a6.gif)

Exemplo de gráficos gerados pelo algoritmo:


![distancia_relativa](https://user-images.githubusercontent.com/97410682/170841324-cca06d79-d7ee-4c0c-998a-4b795b269ef1.png)
