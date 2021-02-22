#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "library.h"

//------------------------Funções do programa---------------------------------
//Os retornos acontecem a partir do segundo dia
void retornoDiario(float *valor, int quant, float *ret_dia){
	int k;
	for(k=1;k<quant;k++){
		ret_dia[k-1] = (valor[k] - valor[k-1]) / valor[k-1]; 
	}
}

//A media dos retornos é o somatorio deles sobre a quantidades de retornos
float retornoMedio(float *ret_dia, int tamanho){
	float media = 0;
	int k;
	for(k=0; k<tamanho; k++){
	media+= ret_dia[k];
	}
	media = media / tamanho;
	return media;
}

//O desvio padrão é a raiz quadrada da variancia
//A variancia é o retorno menos a media ao quadrado sobre o numero de retornos menos um
float desvioPadrao(float *ret_dia,int tamanho, float media){
	float variancia = 0;
	float desvio;
	int k;
	for(k=0; k<tamanho; k++){
	variancia += pow((ret_dia[k] - media),2);
	}
	variancia = variancia / (tamanho - 1);
	desvio = sqrt(variancia);
	return desvio;
}

//Recolhe o indice do maior e do menor retorno
void maiorMenor(float *retorno_dia, int tamanho, int *indice_maior, int *indice_menor){
	int i;
	float max, min;//
	*indice_maior=0;
	*indice_menor=0;
	max=retorno_dia[0];
	min=retorno_dia[0];
	for(i=1;i<tamanho;i++){
		if(max<retorno_dia[i]){
			max=retorno_dia[i];
			*indice_maior=i;//altera o indice
		}else{
			if(min>retorno_dia[i]){
				min=retorno_dia[i];
				*indice_menor=i;//altera o indice
			}
		}
	}
}

//Retorno total é comprar a moeda no primeiro dia e vender no ultimo
float retornoTotal(float *valor, int quant){
	return (valor[quant-1] / valor[0]);
}

//Sharpe ratio é a insegurança do investimento, quanto maior mais inseguro se torna o investimento
float sharpeRatio (float media, float desvio){
	return ((media - 0.00038) / desvio);
}
