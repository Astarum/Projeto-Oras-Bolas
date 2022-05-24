#ifndef BOLA_H
#define BOLA_H
#define raioBola 0.02
#define MAX 1001
#define PI_ 3.14159265358979323

typedef struct{
  double *bolaX,*bolaY,*velocidadeY,*velocidadeX,*aceleracaoX,*aceleracaoY;
}bola;

//void distancia (double *,double *,double *,double *,double *,int );
double distancia (double *bolaX ,double *bolaY,double ,double ,int );
//void angulo(double *,double *,double *,double *,double *,int);
double angulo(double *bolaX,double *bolaY,double  ,double ,int);
//funcao que calcula velocidade e aceleracao da bola
void velocidade_aceleracao(double *tempo,double *velocidadeX,double *velocidadeY,double *aceleracaoX,double *aceleracaoY);

#endif