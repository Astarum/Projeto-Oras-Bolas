#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bola.h"
#include "robo.h"
#include "geral.h"


//funcao para criar os vetores de velocidade e aceleracao da bola
void velocidade_aceleracao(double *tempo,double *velocidadeX,double *velocidadeY,double *aceleracaoX,double *aceleracaoY){
 

  for(int i=0;i<MAX;i++){
    aceleracaoX[i]= -0.015;
    aceleracaoY[i] = -0.016;
    velocidadeX[i] = aceleracaoX[i]*tempo[i] +0.5;
    velocidadeY[i] = aceleracaoY[i]*tempo[i] +0.4;
  }

}


//funcao que calcula a distancia entre o robo e a bola, retorna a distancia
double distancia(double *bolaX, double *bolaY, double roboX,
               double roboY, int i) {
  
  double auxiliarX, auxiliarY,dist;  
  auxiliarX = (bolaX[i] - roboX);
  auxiliarY = (bolaY[i] - roboY);  
  dist = sqrt((pow(auxiliarX,2) + pow(auxiliarY,2)));
  return dist;
}

//calculo do angulo do vetor robo bola
double angulo(double *bolaX, double *bolaY, double roboX,double roboY, int i) {
  double oposto, adjacente, auxiliar,ang;
  auxiliar = 0;
  ang = 0;
  oposto = (bolaY[i] - roboY);
  adjacente = (bolaX[i] - roboX);
  //divisao por 0, funcao arcotangente nao continua logo nao é possivel com denominador 0
  if (adjacente != 0){
    auxiliar = (atan(oposto / adjacente)) * 180 / PI_;

  //caso seja 0 o denominador, o angulo só pode ser 90 ou 270
  }else{
    //verifica se a bola abaixo do robo
    if (bolaY[i] < roboY) {
    auxiliar = 270;
    // ou acima
  }else{
     auxiliar = 90;
  }
  }
  ang = auxiliar;
  
  //verifica caso a posicao em X dos dois seja igual
  if (oposto == 0){
    //se sim, a bola ou está a 360 graus do robo ou 180, ou a direita
    if(bolaX[i]>roboX){
      ang = 360;
      //ou a esquerda
    }else{
      ang = 180;
    }
    
  }
  //bloco para corrigir o angulo em alguns casos
  //primeiro é o caso do vetor estar no 2 ou 3 quadrante
   if (bolaX[i] <roboX){
    if (bolaY[i] <roboY || bolaY[i] >roboY){
      ang += 180;
    }
  }
  //esse é o caso dele estar no  quarto quadrante
  else if(bolaX[i] >roboX && bolaY[i] <roboY){
    ang+=360;
  }
  return ang;
}

//--------------------------------------------

//Funções referentes ao arquivo robo.h
//--------------------------------------------
//funcao que decompoe o raio de interceptacao em X
double raioDecompX(double angulo,int i,double raioTotal){
  double raioX;
  angulo = angulo * PI_ / 180;
  //printf("%lf",angulo);
  raioX = raioTotal * cos(angulo);
  return raioX;
}
//decompoe o raio em Y
double raioDecompY(double angulo,int i,double raioTotal){
  double raioY;
  angulo = angulo * PI_ / 180;
  //printf("%lf",angulo);
  raioY = raioTotal * sin(angulo);
  return raioY;
}

//decompoe a velocidade total do robo em X
double velRoboX(double aX, double tempo,double vel_total,double angulo) {
  double velX;
  angulo = angulo * PI_ / 180;
  velX = (vel_total*cos(angulo)) + aX * tempo;
  return velX;
}  
//decompoe a velocidade total em Y
double velRoboY(double aY, double tempo,double vel_total,double angulo) {
  double velY;
  angulo = angulo * PI_ / 180;
  velY = (vel_total*sin(angulo)) + aY * tempo;
  return velY;  
}  
//calcula a velocidade total
double velTotal(double velX,double velY){
  double velocidade_total =0;
  velocidade_total = sqrt(pow(velX,2)+pow(velY,2));
  return velocidade_total;
}

//calcula o deslocamento do robo em X
double deslocamentoRoboX(double deslX, double acelX,double velocidadeX, double tempo) {
  double auxiliarX;
  auxiliarX = deslX + velocidadeX * tempo + 0.5 * acelX * tempo;

  return auxiliarX;
  

}
//calcula o deslocamento do robo em y
double deslocamentoRoboY(double deslY, double acelY,double velocidadeY,double tempo) {
  double auxiliarY;
  
  auxiliarY = deslY + velocidadeY * tempo + 0.5 * acelY * tempo;
  return auxiliarY;
}
//troca virgula por ponto
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
//verifica interceptacao em X
double verifica_interceptacao_emX(double raioX,double *bolaX,double deslocaX,int i,double raioX_inicial){
 
    //olha a direcao inicial do robo, se ele está vindo da direita ou esquerda
    //se for da esquerda, a posicao do robo nao pode ser maior que a posicao da bola - o raio de interceptacao em X
    if (raioX_inicial > 0 && deslocaX >= bolaX[i] - raioX) {
      //se sim, a posicao do robo é limitada por bolaX - raioX
      deslocaX= bolaX[i] - raioX;
      // se o robo está vindo da direita, a posicao dele nao pode ser menor que a da bolaX + raioX
    } else if (raioX_inicial < 0 &&
               deslocaX <= bolaX[i] + fabs(raioX)) {
      deslocaX = bolaX[i] + fabs(raioX);
    } 
//retorna a posicao que o robo deve ir em X
return deslocaX;
}
//verifica interceptacao em Y
double verifica_interceptacao_emY(double raioY,double *bolaY,double deslocaY,int i, double raioY_inicial){
 
 //verifica se o robo está vindo de baixo, se sim, sua posicao não pode ser maior que a posicao bolaY - raioY
 if (raioY_inicial > 0 && deslocaY >= bolaY[i] - raioY) {
      deslocaY = bolaY[i] - raioY;
 //se estiver vindo de cima, a posicao dele não pode ser menor que a da bolaY - raioY     
    } else if (raioY_inicial < 0 &&
               deslocaY <= bolaY[i] + fabs(raioY)) {
      deslocaY = bolaY[i] + fabs(raioY);
    }
  
//retorna para onde o robo deve ir em Y
return deslocaY;
}


//funçao que cria a lista ligada - FILA
//cada elemento da lista corresponde a um instante de tempo da lista de tempo
//ou seja, carrega varias informacoes da bola e do robo em cada instante de tempo ate a interceptacao
no *insere_dados(no*l,double *bolaX,double *bolaY,double roboX,double roboY,int i,double raioTotal,double a,double *tempo,double velocidade_anteriorTotal,double primeiro_raioX,double primeiro_raioY){
  no* novo_conjunto_dados = (no*)malloc(sizeof(no));
  //variaveis auxiliares
  double posicao_atualX = roboX;
  double posicao_atualY = roboY;
  //angulo auxiliar para o calculo da aceleração
  double auxiliar_angulo = 0;
 //velocidades iniciais em X e Y
  double velocidade_anteriorX = 0;
  double velocidade_anteriorY = 0;
  double aceleracao_robo;
  //caso a velocidade seja = a max
  if (velocidade_anteriorTotal == velMax){
    //aceleracao vira 0
    aceleracao_robo = 0;
  }else{
    //se nao, aceleracao = aMax
    aceleracao_robo = a;
  }
   
  //define o angulo
  novo_conjunto_dados->angulo = angulo(bolaX,bolaY,roboX,roboY,i);
  //decompoe o raio de interceptacao
  novo_conjunto_dados->raio_decompostoX = raioDecompX(novo_conjunto_dados->angulo,i, raioTotal );
  novo_conjunto_dados->raio_decompostoY = raioDecompY(novo_conjunto_dados->angulo,i, raioTotal );
  if(i==0){
    //guardar as informações de onde o robo está vindo inicialmente
    primeiro_raioX = novo_conjunto_dados->raio_decompostoX;
    primeiro_raioY = novo_conjunto_dados->raio_decompostoY;
  }
  //auxiliar de angulo para calculos auxiliares
  auxiliar_angulo = novo_conjunto_dados->angulo;
  auxiliar_angulo = auxiliar_angulo * PI_ / 180; 
  //decompoe aceleracao
  novo_conjunto_dados->aceleracao_roboX = aceleracao_robo * cos(auxiliar_angulo);
  novo_conjunto_dados->aceleracao_roboY = aceleracao_robo * sin(auxiliar_angulo);
  //decompoe as velocidades iniciais para serem utilizadas na formula de deslocamento
  velocidade_anteriorX = velocidade_anteriorTotal * cos(auxiliar_angulo);
  velocidade_anteriorY = velocidade_anteriorTotal * sin(auxiliar_angulo);
  
  //calculo da velocidade ao fim do movimento do robo
  //calcula X e Y dessa velocidade e faz o calculo do modulo para descobrir a total
  novo_conjunto_dados->velocidade_roboX = velRoboX(novo_conjunto_dados->aceleracao_roboX,tempo_entre_dados,velocidade_anteriorTotal,novo_conjunto_dados->angulo);
  novo_conjunto_dados->velocidade_roboY = velRoboY(novo_conjunto_dados->aceleracao_roboY,tempo_entre_dados,velocidade_anteriorTotal,novo_conjunto_dados->angulo);
  novo_conjunto_dados->velocidade_total = velTotal(novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY);
  //se a total for maior ou igual a velMax, logo, essa velocidade é limitada por velMax
  //assim como suas componentes
  if (novo_conjunto_dados->velocidade_total>= velMax ){
    novo_conjunto_dados->velocidade_total = velMax;
    novo_conjunto_dados->velocidade_roboX = velMax* cos(auxiliar_angulo);
    novo_conjunto_dados->velocidade_roboY = velMax*sin(auxiliar_angulo);
    aceleracao_robo = 0;

  }
  //calcula o movimento do robo em X e Y
  novo_conjunto_dados->deslocamento_roboX = deslocamentoRoboX(posicao_atualX,novo_conjunto_dados->aceleracao_roboX,velocidade_anteriorX,tempo_entre_dados);
  novo_conjunto_dados->deslocamento_roboY = deslocamentoRoboY(posicao_atualY,novo_conjunto_dados->aceleracao_roboY,velocidade_anteriorY,tempo_entre_dados);
  //corrige o valor se necessario
  novo_conjunto_dados->deslocamento_roboX = verifica_interceptacao_emX(novo_conjunto_dados->raio_decompostoX,bolaX,novo_conjunto_dados->deslocamento_roboX,i,primeiro_raioX);
  novo_conjunto_dados->deslocamento_roboY = verifica_interceptacao_emY(novo_conjunto_dados->raio_decompostoY,bolaY,novo_conjunto_dados->deslocamento_roboY,i,primeiro_raioY);

  //calcula a distancia pós movimento entre o robo e a bola      
  novo_conjunto_dados->dist = distancia(bolaX,bolaY,novo_conjunto_dados->deslocamento_roboX,novo_conjunto_dados->deslocamento_roboY,i);
  //atribui o movimento as posicoes do robo
  novo_conjunto_dados->roboX =   novo_conjunto_dados->deslocamento_roboX;
  novo_conjunto_dados->roboY =   novo_conjunto_dados->deslocamento_roboY;  
  //coloca na lista as informacoes do tempo e das posicoes da bola
  novo_conjunto_dados->bolaX =   bolaX[i];
  novo_conjunto_dados->bolaY =   bolaY[i];  
  novo_conjunto_dados->tempo =   tempo[i];   
  
  //printa no terminal algumas informacoes
  puts("------------------------------------------");
  printf("A bola esta em (%.2lf,%.2lf)\n", bolaX[i], bolaY[i]);
  printf("O robo esta em (%.2lf,%.2lf)\n", posicao_atualX,posicao_atualY);
  printf("O robo deve ir para (%.2lf,%.2lf)\n", novo_conjunto_dados->deslocamento_roboX, novo_conjunto_dados->deslocamento_roboY);
  printf("O angulo do vetor posicao atual eh %.2lf\n", novo_conjunto_dados->angulo);
  printf("Instante atual de tempo: %.2lf\n", tempo[i]);
  printf("Quando o robo se mover, a distancia entre eles sera: %lf\n", novo_conjunto_dados->dist);
  printf("raioX: %lf,raioY %lf\n", novo_conjunto_dados->raio_decompostoX, novo_conjunto_dados->raio_decompostoY);
  printf("velX: %lf,velY %lf\n", novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY);
  printf("Velocidade total: %lf\n",novo_conjunto_dados->velocidade_total);
  puts("------------------------------------------");
  printf("O robo se moveu para: (%.2lf,%.2lf)!\n", novo_conjunto_dados->deslocamento_roboX, novo_conjunto_dados->deslocamento_roboY);
  //verifica a interceptacao - se a distancia for menor que o raio de interceptacao = interceptou
  if (novo_conjunto_dados->dist <= raioTotal + (raioTotal * 0.1)){
    printf("Enconstou na bola na posicao: X: %.2lf, Y: %.2lf\n",novo_conjunto_dados->deslocamento_roboX, novo_conjunto_dados->deslocamento_roboY);
    printf("Posicao da bola: X: %.2lf, Y: %.2lf\n", bolaX[i],bolaY[i]);
    printf("Instante atual de tempo: %.2lf\n", tempo[i]);
    printf("velX: %lf,velY %lf\n", novo_conjunto_dados->velocidade_roboX,novo_conjunto_dados->velocidade_roboY); 
    //finaliza a lista
    novo_conjunto_dados->prox = NULL;
  }else{
    //se ainda nao interceptou, de maneira recursiva, segue construindo o proximo elemento da lista, utilizando algumas informacoes desse elemento
    novo_conjunto_dados->prox = insere_dados(l,bolaX ,bolaY,novo_conjunto_dados->deslocamento_roboX,novo_conjunto_dados->deslocamento_roboY,i+1,raioTotal,aceleracao_robo,tempo,novo_conjunto_dados->velocidade_total,primeiro_raioX,primeiro_raioY);
  }

  //retorna a lista
  return novo_conjunto_dados;

}
//inicializa a lista
no* inicializa(){
  return NULL;
}
//Função que destroi a lista
void limpa_lista(no* lista){
    no* atual = (no*)malloc(sizeof(no));
    if (lista == NULL){
      printf("Limpeza concluida!!");
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

void cria_logs(char *nome_arquivo,no* lista,double inicioX,double inicioY,double *bolaX,double *bolaY,FILE *deslocamento_tempo,
FILE *distancia_relativa,FILE *deslocamento_RoboBola,FILE *velocidade_RoboBola_tempo,FILE *aceleracao_RoboBola_tempo,double *velocidadeX,
double *velocidadeY,double *aceleracaoX,double *aceleracaoY){
  FILE *logs;
  logs = fopen(nome_arquivo, "a");
   //variável para a primeira interação da lista
  int primeira=0;
  //cria todos arquivos para os graficos
  deslocamento_tempo = fopen("./graficos-arquivos-txt/grafico_deslocamento_tempo.txt","w");
  distancia_relativa = fopen("./graficos-arquivos-txt/grafico_distancia_relativa.txt","w");
  deslocamento_RoboBola = fopen("./graficos-arquivos-txt/grafico_deslocamento_RoboBola.txt","w");
  velocidade_RoboBola_tempo = fopen("./graficos-arquivos-txt/grafico_velocidade_RoboBola_tempo.txt","w");
  aceleracao_RoboBola_tempo = fopen("./graficos-arquivos-txt/aceleracao_RoboBola_tempo.txt","w");
  int j=0;

  //iterage pela lista
  while(lista != NULL){ 
    //primeiro item
   if(primeira==0){
     //escreve no arquivo de logs
  fputs("Informacoes referentes ao encontro do robo com a bola\n", logs);
  fputs("--------------------------------------------------------------------\n",
      logs);
  fprintf(logs, "Posicao inicial do robo: %.2lf,%.2lf\n", lista->roboX, lista->roboY);
  fprintf(logs, "Posicao inicial da bola: %.2lf,%.2lf\n", lista->bolaX ,
          lista->bolaY );
  //monta as colunas e as 2 primeiras linhas de todos arquivos de graficos       
  //grafico deslocamento/tempo
  fprintf(deslocamento_tempo, "Tempo BolaX BolaY RoboX RoboY\n"); 
  fprintf(deslocamento_tempo, "%.2f %f %f %f %f\n",lista->tempo, lista->bolaX ,
          lista->bolaY,lista->roboX,lista->roboY);
  //grafico deslocamento em X e Y        
  fprintf(deslocamento_RoboBola, ". Bola  Robo\n"); 
  fprintf(deslocamento_RoboBola, "%f %f %f %f\n", lista->bolaX ,
          lista->bolaY,lista->roboX,lista->roboY); 
  //distancia/tempo               
  fprintf(distancia_relativa, "Tempo Distancia\n");   
  fprintf(distancia_relativa, "%.2f %f\n", lista->tempo, lista->dist);  
  //velocidade/tempo
  fprintf(velocidade_RoboBola_tempo, "Tempo Bola_vx Bola_vy Robo_vx Robo_vy\n"); 
  fprintf(velocidade_RoboBola_tempo, "%.2f %f %f %f %f\n",lista->tempo, velocidadeX[j] ,
          velocidadeY[j],lista->velocidade_roboX,lista->velocidade_roboY);
  //aceleracao/tempo        
  fprintf(aceleracao_RoboBola_tempo, "Tempo Bola_ax Bola_ay Robo_ax Robo_ay\n"); 
  fprintf(aceleracao_RoboBola_tempo, "%.2f %f %f %f %f\n",lista->tempo, aceleracaoX[j] ,
          aceleracaoY[j],lista->aceleracao_roboX,lista->aceleracao_roboY);        

    //bloqueia esse bloco
     primeira=1;

   }else{
     //escreve as outras linhas dos txts
     fprintf(deslocamento_tempo, "%.2f %f %f %f %f\n",lista->tempo, lista->bolaX ,
          lista->bolaY,lista->roboX,lista->roboY);
      fprintf(distancia_relativa, "%.2f %f\n", lista->tempo, lista->dist);  
      fprintf(deslocamento_RoboBola, "%f %f %f %f\n", lista->bolaX ,
          lista->bolaY,lista->roboX,lista->roboY);  
      fprintf(velocidade_RoboBola_tempo, "%.2f %f %f %f %f\n",lista->tempo, velocidadeX[j] ,
          velocidadeY[j],lista->velocidade_roboX,lista->velocidade_roboY); 
      fprintf(aceleracao_RoboBola_tempo, "%.2f %f %f %f %f\n",lista->tempo, aceleracaoX[j] ,
          aceleracaoY[j],lista->aceleracao_roboX,lista->aceleracao_roboY);  
   }  
  //quando estiver no fim da lista, escreve no logs as informacoes da interceptacao 
  if (lista->prox == NULL){
      fprintf(logs, "Enconstou na bola na posicao: X: %.2lf, Y: %.2lf\n",
          lista->roboX, lista->roboY);
  fprintf(logs, "Posição da bola: X: %.2lf, Y: %.2lf\n", lista->bolaX,
          lista->bolaY);
  fprintf(logs, "Instante de tempo: %.2lf s\n", lista->tempo);
  fprintf(logs, "Velocidade total do robo no momento do encontro: %.5lf m/s\n",
          lista->velocidade_total);
  fprintf(logs, "Distancia entre os dois no momento da interceptacao: %.2lf\n",
          lista->dist);

  fputs("----------------------------------------------------------------\n",
        logs);
  }  
 //iterage pelos itens da lista 
 lista = lista->prox; 
 //para os vetores de velocidade e aceleracao da bola
 j+=1;
 }  
  //fecha todos arquivos
  fclose(logs);
  fclose(distancia_relativa);
  fclose(deslocamento_tempo);
  fclose(deslocamento_RoboBola);
  fclose(aceleracao_RoboBola_tempo);
  fclose(velocidade_RoboBola_tempo);
    
}
