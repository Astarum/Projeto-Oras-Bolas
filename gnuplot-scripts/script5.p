#seta como unknown para editar os limites depois
set terminal unknown


#plota as colunas 2 a 5 no eixo X, utilizando a posicao da coluna 1 do tempo como Y
plot "./graficos-arquivos-txt/grafico_velocidade_RoboBola_tempo.txt" using 1:2 title 'Bola-Vx' with lines,\
'' using 1:3  title 'Bola-Vy' with lines,\
'' using 1:4 title 'Robo-Vx' with lines,\
'' using 1:5 title 'Robo-Vy' with lines

#seta o tamanho da imagem
set terminal png size 1000,700

#legenda fora e superior direito
set key outside
set key right top

# nome do arquivo saida
set output './graficos/velocidade_RoboBola_tempo.png'
# titulo do grafico
set title 'Grafico da velocidade do robo e da bola em função do tempo'

#nome do eixo x
set xlabel "Tempo (s)"
#nome do eixo y
set ylabel "Velocidade (m/s)"


#seta os limites do grafico ao replotar
set xrange [GPVAL_DATA_X_MIN-0.01:GPVAL_DATA_X_MAX+0.01]
set yrange [GPVAL_DATA_Y_MIN:GPVAL_DATA_Y_MAX+0.1]
replot 