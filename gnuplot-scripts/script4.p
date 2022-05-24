
#seta o terminal como unknown para poder replotar depois
set terminal unknown

#plota as colunas 2 a 5 no eixo X, utilizando a posicao da coluna 1 do tempo como y
plot "./graficos-arquivos-txt/aceleracao_RoboBola_tempo.txt" using 2:1 title 'Bola-Ay' with lines,\
'' using 3:1  title 'Bola-Ay' with lines,\
'' using 4:1 title 'Robo-Ax' with lines,\
'' using 5:1 title 'Robo-Ay' with lines


#seta o tamanho da imagem
set terminal png size 1000,700

#legenda fora e superior direito
set key outside
set key right top


# nome do arquivo saida
set output './graficos/aceleracao_RoboBola_tempo.png'
# titulo do grafico
set title 'Grafico de aceleracao da bola e robo em funcao do tempo'

#nome do eixo x
set xlabel "Aceleracao (m/s²)"
#nome do eixo y
set ylabel "Tempo (s)"

#seta os novos limites do grafico 
set xrange [GPVAL_DATA_X_MIN-0.01:GPVAL_DATA_X_MAX+0.01]
set yrange [GPVAL_DATA_Y_MIN:GPVAL_DATA_Y_MAX+0.01]
#replota
replot 