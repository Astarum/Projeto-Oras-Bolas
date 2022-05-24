#seta o terminal para unknown para poder editá-lo com replot
set terminal unknown
#cria o estilo de linha 10 cor ciano
set style line 10 lc rgb '#0ce90b' lt 1 lw 1.5

#cria um estilo para a linha 3
set style line 3 lt 1 lw 1.5

#plota as 2 primeiras colunas do grafico (coordenadas X e Y da bola) utilizando a linha 10 e com o titulo da coluna no arquivo txt, linha de baixo faz a msma coisa
#soh que com a linha 3 para as colunas 3 e 4 do txt (coordenadas X e Y do robo)
plot "./graficos-arquivos-txt/grafico_deslocamento_RoboBola.txt" using 1:2 with line ls 10 title columnheader,\
"" using 3:4 with line ls 3 title columnheader


#seta o tamanho da imagem
set terminal png size 1000,700

#legenda fora e superior direito
set key outside
set key right top

# nome do arquivo saida
set output './graficos/deslocamento_RoboBola.png'
# titulo do grafico
set title 'Grafico de deslocamento entre a bola e o robo'



#nome do eixo x
set xlabel "Posicao em X (m)"
#nome do eixo y
set ylabel "Posicao em Y (m)"

#seta os limites de X e Y para o tamanho do campo (9 x 6)
set xrange [0:9]
set yrange [0:6]
replot 