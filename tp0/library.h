#ifndef LIBRARY_H
#define LIBRARY_H

//-----------------------------Struct para as moedas----------------------------------
typedef struct retornos{
	char nome[12];
	int quant;
	int tamanho;
	int *dia;
	int *mes;
	int *ano;
	float *ret_dia;
	int maior;//indice maior
	int menor;
	float media;
	float desvio;
	float ret_total;
	float sharpe_ratio;
	float *valor;
} moeda;

//----------------------------Funções para o programa-----------------------------------
void retornoDiario(float *, int, float *);
float retornoMedio(float *, int);
float desvioPadrao(float *, int, float);
void maiorMenor(float *, int, int *, int *);
float retornoTotal(float *, int);
float sharpeRatio (float, float);

#endif
