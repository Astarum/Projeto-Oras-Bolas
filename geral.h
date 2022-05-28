#ifndef GERAL_H
#define GERAL_H 


typedef struct reg no;
no* inicializa();
//lista recursiva
no* insere_dados(no* lista,double *bolaX,double *bolaY,double roboX,double roboY, int i,double raioTotal,double a,double *tempo,double velocidade_anteriorTotal,double primeiro_raioX,double primeiro_raioY);
//destroi a lista
void limpa_lista(no* lista);
//verifica interceptacao em x
double verifica_interceptacao_emX(double raioX,double *bolaX,double deslocaX,int i,double raioX_inicial);
//verifica interceptacao em y
double verifica_interceptacao_emY(double raioY,double *bolaY,double deslocaY,int i, double raioY_inicial);
//troca '.' por ','
void replaceVirgula(char*,char,char);
void criar_logs(char*logs,no*lista,double inicioX,double inicioY,double *bolaX,double *bolaY,FILE *deslocamento_tempo,
FILE *distancia_relativa,FILE *deslocamento_RoboBola,FILE *velocidade_RoboBola_tempo,FILE *aceleracao_RoboBola_tempo,double *velocidadeX,
double *velocidadeY,double *aceleracaoX,double *aceleracaoY, FILE *instrucoes_javascript);

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