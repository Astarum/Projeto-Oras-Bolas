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
  // enquanto a condição não for falsa, ele executa o for
  // fgets transfere cada linha do arquivo para de um vetor com tamanho max 25
  // chars, dentro da matriz de strings
  for (j = 0; fgets(valores[j], 25, arquivo); j++) {
    // função para substituir a virgula dos números por '.'
    replaceVirgula(valores[j], ',', '.');
    // se os valores forem diferente de 'NULL' (ou linha vazia)
    if (valores[j] != NULL) {
      // sscanf coloca cada valor dentro da sua respectiva variavel, já fazendo
      // a troca do valor de string para double
      sscanf(valores[j], "%lf %lf %lf\n", tempo + j, bola.bolaX + j,
             bola.bolaY + j);
      // printf("%lf %lf %lf\n",tempo[j],bola.bolaX[j],bola.bolaY[j]);
    }
  }

  // fecha o arquivo
  fclose(arquivo);

  puts("Digite os valores de X e Y do robo:");
  // receber os valores iniciais do robo
  scanf("%lf %lf", &inicioX, &inicioY);

 
  // posição inicial do robo
  robo.roboX = inicioX;
  robo.roboY = inicioY;
  // robo está parado
  robo.velTotal = 0;
  

 
  no* lista = inicializa();
  lista = insere_dados(lista,bola.bolaX,bola.bolaY,robo.roboX,robo.roboY,0,raioTotal,acel,tempo,robo.velTotal,0,0);
  

    
  // cria o arquivo que mostra informações referentes ao ponto de encontro
  /*
  logs = fopen("logs.txt", "a");
  fputs("Informações referentes ao encontro do robo com a bola\n", logs);
  fputs(
      "--------------------------------------------------------------------\n",
      logs);
  fprintf(logs, "Posição inicial do robo: %.2lf,%.2lf\n", inicioX, inicioY);
  fprintf(logs, "Posição inicial da bola: %.2lf,%.2lf\n", bola.bolaX[0],
          bola.bolaY[0]);
  fprintf(logs, "Enconstou na bola na posição: X: %.2lf, Y: %.2lf\n",
          robo.roboX[i], robo.roboY[i]);
  fprintf(logs, "Posição da bola: X: %.2lf, Y: %.2lf\n", bola.bolaX[i],
          bola.bolaY[i]);
  fprintf(logs, "Instante de tempo: %.2lf s\n", tempo[i]);
  fprintf(logs, "Velocidade total do robo no momento do encontro: %.5lf m/s\n",
          velTot);
  fprintf(logs, "Aceleração total do robo no momento do encontro: %.5lf m/s²\n",
          aceTot);

  fputs("----------------------------------------------------------------\n",
        logs);
  fclose(logs);
*/
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
