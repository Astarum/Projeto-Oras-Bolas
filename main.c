#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bola.h"
#include "robo.h"
#include "geral.h"
int main() {

  // ponteiro para o arquivo
  FILE *arquivo;
  FILE *logs;
  FILE *deslocamento_tempo;
  FILE *distancia_relativa;
  

  // instanciando a struct robo
  robo robo;
  // instanciando a struct bola
  bola bola;

  // alocação dinamica - matriz de vetores de strings
  char **valores;


  // alocação da matriz de vetores do tipo string
  valores = (char **)malloc(MAX * sizeof(char *));
  for (int i = 0; i < MAX; i++) {
    valores[i] = (char *)malloc(25 * sizeof(char));
  }

  // vetor referente ao tempo dentro do arquivo
  double *tempo;

  double inicioX, inicioY;
  
  

  // aceleração Total e velocidade Total
  double aceTot = 0;
  double velTot = 0;
  // variaveis para os for's
  int i, j = 0;

  // raio total somando as duas constantes
  double raioTotal = raioBola + raioRobo;

 
  bola.bolaX = (double *)malloc(MAX * sizeof(double));
  bola.bolaY = (double *)malloc(MAX * sizeof(double));
  tempo = (double *)malloc(MAX * sizeof(double));

  // tratamento do arquivo
  arquivo = fopen("./infobola.txt", "r");
  if (arquivo == NULL) {
    printf("Não foi possível abrir o arquivo");
    return 1;
  }
  
  for (j = 0;j<MAX ; j++) {
     // fgets transfere cada linha do arquivo para de um vetor com tamanho max 25
    // chars, dentro da matriz de strings
    fgets(valores[j], 25, arquivo);
    
    
    // se os valores forem diferente de 'NULL' (ou linha vazia)
    if (feof(arquivo)==0) {
      // função para substituir a virgula dos números por '.'
      replaceVirgula(valores[j], ',', '.');
      // sscanf coloca cada valor dentro da sua respectiva variavel, já fazendo
      // a troca do valor de string para double
      sscanf(valores[j], "%lf %lf %lf\n", tempo + j, bola.bolaX + j,
             bola.bolaY + j);
      //printf("%lf %lf %lf\n",tempo[j],bola.bolaX[j],bola.bolaY[j]);
    }
  }

  // fecha o arquivo
  fclose(arquivo);
  int liberar=0;
  
  while (liberar == 0){
    puts("Digite os valores de X e Y do robo:");
    // receber os valores iniciais do robo
    scanf("%lf %lf", &inicioX, &inicioY);
    if (inicioX >=0 && inicioX <=9 && inicioY >=0 && inicioY <=6){
      liberar = 1;
    }else{
      printf("Os valores de X e Y devem estar entre 0 e 9, e 0 e 6, respectivamente.\n");
    }
  }
  // posição inicial do robo
  robo.roboX = inicioX;
  robo.roboY = inicioY;
  // robo está parado
  robo.velTotal = 0;
  

  char* nome_arquivo = "logs.txt";
 
  no* lista = inicializa();
  lista = insere_dados(lista,bola.bolaX,bola.bolaY,robo.roboX,robo.roboY,0,raioTotal,acel,tempo,robo.velTotal,0,0);
  //criar_logs("logs.txt",lista,inicioX,inicioY,bola.bolaX[0],bola.bolaY[0]);

  //variável para a primeira interação da lista
  int primeira=0;
  // cria o arquivo que mostra informações referentes ao ponto de encontro
  logs = fopen(nome_arquivo, "a");
  deslocamento_tempo = fopen("grafico_deslocamento_tempo.txt","w");
  distancia_relativa = fopen("grafico_distancia_relativa.txt","w");
  while(lista != NULL){
  fprintf(deslocamento_tempo, "%lf %lf %lf %lf %lf\n", lista->bolaX ,
          lista->bolaY,lista->roboX,lista->roboY,lista->tempo);
  fprintf(distancia_relativa, "%lf %lf\n", lista->dist, lista->tempo);





    
   if(primeira==0){
  fputs("Informações referentes ao encontro do robo com a bola\n", logs);
  fputs("--------------------------------------------------------------------\n",
      logs);
  fprintf(logs, "Posição inicial do robo: %.2lf,%.2lf\n", lista->roboX, lista->roboY);
  fprintf(logs, "Posição inicial da bola: %.2lf,%.2lf\n", lista->bolaX ,
          lista->bolaY );
     primeira=1;
   }  
  if (lista->prox == NULL){
      fprintf(logs, "Enconstou na bola na posição: X: %.2lf, Y: %.2lf\n",
          lista->roboX, lista->roboY);
  fprintf(logs, "Posição da bola: X: %.2lf, Y: %.2lf\n", lista->bolaX,
          lista->bolaY);
  fprintf(logs, "Instante de tempo: %.2lf s\n", lista->tempo);
  fprintf(logs, "Velocidade total do robo no momento do encontro: %.5lf m/s\n",
          lista->velocidade_total);
  fprintf(logs, "Distância entre os dois no momento da interceptação: %.2lf\n",
          lista->dist);

  fputs("----------------------------------------------------------------\n",
        logs);
  }  
 lista = lista->prox; 
 }    
  fclose(logs);
    char * commandsForGnuplot[] = {"set title \"TITLEEEEE\"", "plot 'grafico_distancia_relativa.txt'"};
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[0]);
  
  limpa_lista(lista);
  
  
  
  
  // libera a memória referente a todos vetores de alocação dinâmica
  free(bola.bolaX);
  free(bola.bolaY);
  free(tempo);
 
  for (i = 0; i < j; i++) {
    free(valores[i]);
  }
  free(valores);

  return 0;
}


