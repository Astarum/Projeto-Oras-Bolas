
#ifndef GERAL.H
#define GERAL.H

typedef struct reg no;
no* inicializa();
//lista recursiva
no* insere_dados(no* lista,double *bolaX,double *bolaY,double roboX,double roboY, int i,double raioTotal,double a,double *tempo,double velocidade_anteriorTotal,double primeiro_raioX,double primeiro_raioY);
void limpa_lista(no* lista);
double verifica_interceptacao_emX(double raioX,double *bolaX,double deslocaX,int i,double raioX_inicial);
double verifica_interceptacao_emY(double raioY,double *bolaY,double deslocaY,int i, double raioY_inicial);

void criar_logs(char*logs,no*lista,double inicioX,double inicioY,double bolaX,double bolaY);

struct reg{
  double dist;
  double angulo;
  double raio_decompostoX;
  double raio_decompostoY;
  double aceleracao_roboX;
  double aceleracao_roboY;
  double velocidade_roboX;
  double velocidade_roboY;
  double velocidade_total;
  double deslocamento_roboX;
  double deslocamento_roboY;
  double roboX;
  double roboY;
  double bolaX;
  double bolaY;
  double tempo;
  struct reg *prox;
};

#endif