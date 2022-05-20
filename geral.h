#ifndef GERAL.H
#define GERAL.H

typedef struct reg no;
no* inicializa();
no* insere_dados(no* lista,double *bolaX,double *bolaY,double roboX,double roboY, int i,double raioTotal,double a,double *tempo,double velocidade_anteriorTotal,double primeiro_raioX,double primeiro_raioY);
double verifica_interceptacao_emX(double raioX,double *bolaX,double deslocaX,int i,double raioX_inicial);
double verifica_interceptacao_emY(double raioY,double *bolaY,double deslocaY,int i, double raioY_inicial);
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
  struct reg *prox;
};

#endif