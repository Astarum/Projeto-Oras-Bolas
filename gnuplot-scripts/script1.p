#setar terminal como unknown para depois corrigir os valores máximos e minimos
set terminal unknown
#plota o grafico com o titulo da coluna do arquivo txt
plot "./graficos-arquivos-txt/grafico_distancia_relativa.txt" using 1:2 title 'Distancia' with lines

#tamanho da imagem
set terminal png size 1000,700
#legenda fora e superior direito
set key outside
set key right top
# nome do arquivo saida
set output './graficos/distancia_relativa.png'
# titulo do grafico
set title 'Grafico de distancia relativa entre o robo e a bola'

#nome do eixo x
set xlabel "Tempo (s)"
#nome do eixo y
set ylabel "Distancia (m)"
#seta o x maximo para +0.01 além do tamanho que ele tiver (eixo = tempo)
set xrange [GPVAL_DATA_X_MIN:GPVAL_DATA_X_MAX+0.5]
#seta o eixo y para 0.1 a mais
set yrange [GPVAL_DATA_Y_MIN:GPVAL_DATA_Y_MAX+0.1]
#replota o grafico, dessa vez criando a imagem
replot 