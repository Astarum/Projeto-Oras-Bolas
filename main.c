#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "bola.h"
#include "robo.h"
#include "geral.h"
#include "funcoes.c"
int main() {

  // ponteiro para ler o arquivo da bola
  FILE *arquivo;
  //txt's para os graficos
  FILE *deslocamento_tempo;
  FILE *deslocamento_RoboBola;
  FILE *distancia_relativa;
  FILE *velocidade_RoboBola_tempo;
  FILE *aceleracao_RoboBola_tempo;
  

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
  bola.velocidadeX = (double *)malloc(MAX * sizeof(double));
  bola.velocidadeY = (double *)malloc(MAX * sizeof(double));
  bola.aceleracaoX = (double *)malloc(MAX * sizeof(double));
  bola.aceleracaoY = (double *)malloc(MAX * sizeof(double));
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
  //funcao que calcula a velocidade e a aceleracao da bola
  velocidade_aceleracao(tempo,bola.velocidadeX,bola.velocidadeY,bola.aceleracaoX,bola.aceleracaoY);

  //variavel para bloquear caso os valores de entrada nao estejam dentro dos valores corretos
  int liberar=0;
  while (liberar == 0){
    puts("Digite os valores de X e Y do robo:");
    // receber os valores iniciais do robo
    scanf("%lf %lf", &inicioX, &inicioY);
    if (inicioX >=0 && inicioX <=9 && inicioY >=0 && inicioY <=6){
      liberar = 1;
    }else{
      printf("Os valores de X e Y devem estar entre 0 e 9 e 0 e 6, respectivamente.\n");
    }
  }
  // posição inicial do robo
  robo.roboX = inicioX;
  robo.roboY = inicioY;
  // robo está parado
  robo.velTotal = 0;
  
  //nome do arquivo de logs
  char* nome_arquivo = "logs.txt";
 //inicializa a lista
  no* lista = inicializa();
  //insere os dados nela
  lista = insere_dados(lista,bola.bolaX,bola.bolaY,robo.roboX,robo.roboY,0,raioTotal,acel,tempo,robo.velTotal,0,0);
  //cria todos arquivos: logs e graficos
  cria_logs(nome_arquivo,lista,inicioX,inicioY,bola.bolaX,bola.bolaY,deslocamento_tempo,distancia_relativa,deslocamento_RoboBola,
  velocidade_RoboBola_tempo,aceleracao_RoboBola_tempo,bola.velocidadeX,bola.velocidadeY,bola.aceleracaoX,bola.aceleracaoY);
  
  //executa os scripts do gnuplot
  system("gnuplot ./gnuplot-scripts/script1.p");
  system("gnuplot ./gnuplot-scripts/script2.p");
  system("gnuplot ./gnuplot-scripts/script3.p");
  system("gnuplot ./gnuplot-scripts/script4.p");
  system("gnuplot ./gnuplot-scripts/script5.p");
  //destroi a lista
  limpa_lista(lista);
  
  
  
  
  // libera a memória referente a todos vetores de alocação dinâmica
  free(bola.bolaX);
  free(bola.bolaY);
  free(tempo);
  free(bola.velocidadeX);
  free(bola.velocidadeY);
  free(bola.aceleracaoX);
  free(bola.aceleracaoY);
  //libera a matriz que guardou as linhas do arquivo inicial
  for (i = 0; i < MAX; i++) {
    free(valores[i]);
  }
  free(valores);

  return 0;
}


