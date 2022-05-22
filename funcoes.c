#include "bola.h"
#include "robo.h"
#include "geral.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




double distancia(double *bolaX, double *bolaY, double roboX,
               double roboY, int i) {
  
  double auxiliarX, auxiliarY,dist;  auxiliarX = (bolaX[i] - roboX);
  auxiliarY = (bolaY[i] - roboY);  dist = sqrt((pow(auxiliarX,2) + pow(auxiliarY,2)));
  return dist;
}


double angulo(double *bolaX, double *bolaY, double roboX,double roboY, int i) {
  double oposto, adjacente, auxiliar,ang;
  auxiliar = 0;
  ang = 0;
  oposto = (bolaY[i] - roboY);
  adjacente = (bolaX[i] - roboX);
  if (adjacente != 0){
    auxiliar = (atan(oposto / adjacente)) * 180 / PI_;

  }else{
    if (bolaY[i] < roboY) {
    auxiliar = 270;
  }else{
     auxiliar = 90;
  }
  }
  ang = auxiliar;
  
  if (bolaX[i]-roboX==0){
    if (bolaY[i]>roboY){
      ang=90;
    }else{
      ang = 270;
    }
  }
  if (oposto == 0){
    if(bolaX[i]>roboX){
      ang = 360;
    }else{
      ang = 180;
    }
    
  }
   if (bolaX[i] <roboX){
    if (bolaY[i] <roboY || bolaY[i] >roboY){
      ang += 180;
    }
  }
  else if(bolaX[i] >roboX && bolaY[i] <roboY){
    ang+=360;
  }
  return ang;
}

//--------------------------------------------

//Funções referentes ao arquivo robo.h
//--------------------------------------------

double raioDecompX(double angulo,int i,double raioTotal){
  double raioX;
  angulo = angulo * PI_ / 180;
  //printf("%lf",angulo);
  raioX = raioTotal * cos(angulo);
  return raioX;
}
double raioDecompY(double angulo,int i,double raioTotal){
  double raioY;
  angulo = angulo * PI_ / 180;
  //printf("%lf",angulo);
  raioY = raioTotal * sin(angulo);
  return raioY;
}


double velRoboX(double aX, double tempo,double vel_total,double angulo) {
  double velX;
  angulo = angulo * PI_ / 180;
  velX = (vel_total*cos(angulo)) + aX * tempo;
  return velX;
}  
double velRoboY(double aY, double tempo,double vel_total,double angulo) {
  double velY;
  angulo = angulo * PI_ / 180;
  velY = (vel_total*sin(angulo)) + aY * tempo;
  return velY;  
}  
double velTotal(double velX,double velY){
  double velocidade_total =0;
  velocidade_total = sqrt(pow(velX,2)+pow(velY,2));
  return velocidade_total;
}


double deslocamentoRoboX(double deslX, double acelX,double velocidadeX, double tempo) {
  double auxiliarX;
  auxiliarX = deslX + velocidadeX * tempo + 0.5 * acelX * tempo;

  return auxiliarX;
  

}
double deslocamentoRoboY(double deslY, double acelY,double velocidadeY,double tempo) {
  double auxiliarY;
  
  auxiliarY = deslY + velocidadeY * tempo + 0.5 * acelY * tempo;
  return auxiliarY;
}
void replaceVirgula(char *string, char virgula, char ponto) {
  int tamanho = strlen(string), i = 0;
  for (i = 0; i < tamanho; i++) {
    if (string[i] == virgula) {
      string[i] = ponto;
    }
  }
}


//--------------------------------------------


//Funções referentes ao arquivo geral.h
//--------------------------------------------

double verifica_interceptacao_emX(double raioX,double *bolaX,double deslocaX,int i,double raioX_inicial){
 
 
    if (raioX_inicial > 0 && deslocaX >= bolaX[i] - raioX) {
      
      deslocaX= bolaX[i] - raioX;
    } else if (raioX_inicial < 0 &&
               deslocaX <= bolaX[i] + fabs(raioX)) {
      deslocaX = bolaX[i] + fabs(raioX);
    } 

return deslocaX;
}
double verifica_interceptacao_emY(double raioY,double *bolaY,double deslocaY,int i, double raioY_inicial){
 
 if (raioY_inicial > 0 && deslocaY >= bolaY[i] - raioY) {
      deslocaY = bolaY[i] - raioY;
    } else if (raioY_inicial < 0 &&
               deslocaY <= bolaY[i] + fabs(raioY)) {
      deslocaY = bolaY[i] + fabs(raioY);
    }
  

return deslocaY;
}



no *insere_dados(no*l,double *bolaX,double *bolaY,double roboX,double roboY,int i,double raioTotal,double a,double *tempo,double velocidade_anteriorTotal,double primeiro_raioX,double primeiro_raioY){
  no* novo_conjunto_dados = (no*)malloc(sizeof(no));
  double posicao_atualX = roboX;
  double posicao_atualY = roboY;
  //angulo auxiliar para o calculo da aceleração
  double auxiliar_angulo = 0;
  
  
  novo_conjunto_dados->angulo = angulo(bolaX,bolaY,roboX,roboY,i);
  novo_conjunto_dados->raio_decompostoX = raioDecompX(novo_conjunto_dados->angulo,i, raioTotal );
  novo_conjunto_dados->raio_decompostoY = raioDecompY(novo_conjunto_dados->angulo,i, raioTotal );
  if(i==0){
    primeiro_raioX = novo_conjunto_dados->raio_decompostoX;
    primeiro_raioY = novo_conjunto_dados->raio_decompostoY;
  }
  auxiliar_angulo = novo_conjunto_dados->angulo;
  auxiliar_angulo = auxiliar_angulo * PI_ / 180; 
  
  novo_conjunto_dados->aceleracao_roboX = a * cos(auxiliar_angulo);
  novo_conjunto_dados->aceleracao_roboY = a * sin(auxiliar_angulo);
  
  novo_conjunto_dados->velocidade_roboX = velRoboX(novo_conjunto_dados->aceleracao_roboX,tempo[i],velocidade_anteriorTotal,novo_conjunto_dados->angulo);
  novo_conjunto_dados->velocidade_roboY = velRoboY(novo_conjunto_dados->aceleracao_roboY,tempo[i],velocidade_anteriorTotal,novo_conjunto_dados->angulo);
  novo_conjunto_dados->velocidade_total = velTotal(novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY);
  
  novo_conjunto_dados->deslocamento_roboX = deslocamentoRoboX(posicao_atualX,novo_conjunto_dados->aceleracao_roboX,novo_conjunto_dados->velocidade_roboX,tempo[i]);
novo_conjunto_dados->deslocamento_roboY = deslocamentoRoboY(posicao_atualY,novo_conjunto_dados->aceleracao_roboY,novo_conjunto_dados->velocidade_roboY,tempo[i]);

novo_conjunto_dados->deslocamento_roboX = verifica_interceptacao_emX(novo_conjunto_dados->raio_decompostoX,bolaX,novo_conjunto_dados->deslocamento_roboX,i,primeiro_raioX);

novo_conjunto_dados->deslocamento_roboY = verifica_interceptacao_emY(novo_conjunto_dados->raio_decompostoY,bolaY,novo_conjunto_dados->deslocamento_roboY,i,primeiro_raioY);
    
novo_conjunto_dados->dist = distancia(bolaX,bolaY,novo_conjunto_dados->deslocamento_roboX,novo_conjunto_dados->deslocamento_roboY,i);
novo_conjunto_dados->roboX =   novo_conjunto_dados->deslocamento_roboX;
novo_conjunto_dados->roboY =   novo_conjunto_dados->deslocamento_roboY;  
novo_conjunto_dados->bolaX =   bolaX[i];
novo_conjunto_dados->bolaY =   bolaY[i];  
novo_conjunto_dados->tempo =   tempo[i];   
   
    puts("------------------------------------------");
    printf("A bola está em (%.2lf,%.2lf)\n", bolaX[i], bolaY[i]);
    printf("O robo está em (%.2lf,%.2lf)\n", posicao_atualX,
           posicao_atualY);
    printf("O robo deve ir para (%.2lf,%.2lf)\n", novo_conjunto_dados->deslocamento_roboX, novo_conjunto_dados->deslocamento_roboY);
    printf("O angulo do vetor posição atual é %.2lf\n", novo_conjunto_dados->angulo);
    printf("Instante atual de tempo: %.2lf\n", tempo[i]);
    printf("Quando o robo se mover, a distancia entre eles será: %lf\n", novo_conjunto_dados->dist);
    printf("raioX: %lf,raioY %lf\n", novo_conjunto_dados->raio_decompostoX, novo_conjunto_dados->raio_decompostoY);
    printf("velX: %lf,velY %lf\n", novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY);
    printf("Velocidade total: %lf\n",novo_conjunto_dados->velocidade_total);
    puts("------------------------------------------");

    if (novo_conjunto_dados->dist <= raioTotal + (raioTotal * 0.1)){
    printf("Enconstou na bola na posição: X: %.2lf, Y: %.2lf\n",novo_conjunto_dados->deslocamento_roboX, novo_conjunto_dados->deslocamento_roboY);
    printf("Posição da bola: X: %.2lf, Y: %.2lf\n", bolaX[i],bolaY[i]);
    printf("Instante atual de tempo: %.2lf\n", tempo[i]);
    printf("velX: %lf,velY %lf\n", novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY); 
    novo_conjunto_dados->prox = NULL;
  }else{
novo_conjunto_dados->prox = insere_dados(l,bolaX ,bolaY,novo_conjunto_dados->deslocamento_roboX,novo_conjunto_dados->deslocamento_roboY,i+1,raioTotal,a,tempo,novo_conjunto_dados->velocidade_total,primeiro_raioX,primeiro_raioY);
  }

  
 return novo_conjunto_dados;
  
}

no* inicializa(){
  return NULL;
}
//Função que destroi a lista
void limpa_lista(no* lista){
    no* atual = (no*)malloc(sizeof(no));
    if (lista == NULL){
      printf("Limpeza concluída!!");
      return;
    }
    if (lista->prox == NULL){
      printf("Ultimo tempo = %.2lf\n",lista->tempo);
    }
  
    atual = lista->prox;
    free(lista);
    limpa_lista(atual);
    
}
//Função que cria o arquivo de logs (não está funcionando)
/*
void cria_logs(char *nome_arquivo,no* lista,double inicioX,double inicioY,double bolaX,double bolaY){
  FILE *logs;
  int i;
  logs = fopen(nome_arquivo, "a");
  // cria o arquivo que mostra informações referentes ao ponto de encontro
  while(lista != NULL){
   if(i==0){
  fputs("Informações referentes ao encontro do robo com a bola\n", logs);
  fputs("--------------------------------------------------------------------\n",
      logs);
  fprintf(logs, "Posição inicial do robo: %.2lf,%.2lf\n", inicioX, inicioY);
  fprintf(logs, "Posição inicial da bola: %.2lf,%.2lf\n", bolaX,
          bolaY);
     i=1;
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
    
}
*/