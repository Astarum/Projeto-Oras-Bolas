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


