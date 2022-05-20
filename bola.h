#ifndef BOLA.H
#define BOLA.H
#define raioBola 0.02
#define MAX 1002
#define PI_ 3.14159265358979323

typedef struct{
  double *bolaX,*bolaY;
}bola;

//void distancia (double *,double *,double *,double *,double *,int );
double distancia (double *bolaX ,double *bolaY,double ,double ,int );
//void angulo(double *,double *,double *,double *,double *,int);
double angulo(double *bolaX,double *bolaY,double  ,double ,int);


#endif