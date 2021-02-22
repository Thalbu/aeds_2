#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "library.h"

int main(int argc, char *argv[]) {
	if(argc<=1){//testa se foi passada alguma moeda
		printf("Nao foi passado nenhuma criptomoeda.\n\n");
		return 0;
	}else{
		int i,n;
		moeda tudo[argc-1];
		FILE *arquivo;
		FILE *resultado;
		resultado = fopen("saida.txt","w");
		for(i=1;i<argc;i++){//Concatena a extensão do arquivo para poder abrir
			strcpy(tudo[i-1].nome,argv[i]);//Copia o nome da moeda
			strcat(argv[i],".csv");
		}
		for(i=0; i<(argc-1) ; i++){
			arquivo = fopen(argv[i+1],"r");
			fscanf(arquivo,"%d",&(tudo[i].quant));
			tudo[i].tamanho = (tudo[i].quant - 1);
			//------------------aloca as variaveis necessarias--------------------------
			tudo[i].ret_dia = (float *) calloc (tudo[i].tamanho, sizeof(float));
			tudo[i].valor = (float *) calloc (tudo[i].quant, sizeof(float));
			tudo[i].dia = (int *) calloc (tudo[i].quant, sizeof(int));
			tudo[i].mes = (int *) calloc (tudo[i].quant, sizeof(int));
			tudo[i].ano = (int *) calloc (tudo[i].quant, sizeof(int));
			for ( n=tudo[i].quant-1 ; n>=0; n--){//le o arquivo
				fscanf(arquivo,"%d/%d/%d,%f", &(tudo[i].mes[n]), &(tudo[i].dia[n]), &(tudo[i].ano[n]), &(tudo[i].valor[n]) );
			}
			//-------------------Faz a chamada das funções------------------------------
			retornoDiario(tudo[i].valor, tudo[i].quant, tudo[i].ret_dia);
			maiorMenor(tudo[i].ret_dia, tudo[i].tamanho, &(tudo[i].maior), &(tudo[i].menor));
			tudo[i].media = retornoMedio(tudo[i].ret_dia, tudo[i].tamanho);
			tudo[i].desvio = desvioPadrao(tudo[i].ret_dia, tudo[i].tamanho, tudo[i].media);
			tudo[i].ret_total = retornoTotal(tudo[i].valor, tudo[i].quant);
			tudo[i].sharpe_ratio = sharpeRatio(tudo[i].media, tudo[i].desvio);
		}
		
		fclose(arquivo);
		fprintf(resultado,"               DataMenor     DataMaior        Menor       Maior       Media       Desvio      RTotal      Sharpe\n");
		for(i=0;i<(argc-1);i++){//Escreve os resultados no arquivo de saida
			fprintf(resultado,"%10s",tudo[i].nome);
			fprintf(resultado,"%8d/%2d/%2d",tudo[i].dia[tudo[i].menor+1],tudo[i].mes[tudo[i].menor+1],tudo[i].ano[tudo[i].menor+1]);
			fprintf(resultado,"%8d/%2d/%2d",tudo[i].dia[tudo[i].maior+1],tudo[i].mes[tudo[i].maior+1],tudo[i].ano[tudo[i].maior+1]);
			fprintf(resultado,"%12.2f%%",tudo[i].ret_dia[tudo[i].menor]*100);
			fprintf(resultado,"%11.2f%%",tudo[i].ret_dia[tudo[i].maior]*100);
			fprintf(resultado,"%11.2f%%",tudo[i].media*100);
			fprintf(resultado,"%13.2f",tudo[i].desvio*100);
			fprintf(resultado,"%12.2f",tudo[i].ret_total);
			fprintf(resultado,"%12.2f\n",tudo[i].sharpe_ratio);
		}
		if(argc>2){//Compara de foram passadas mais de uma moeda, pois não existe sentido em fazer um portfolio para apenas uma moeda
			moeda port1;
			port1.quant=tudo[0].quant;
			port1.tamanho = port1.quant - 1;
			//-------------------Aloca memoria para o portfolio----------------------
			port1.valor = (float *) calloc (port1.quant,sizeof(float));
			port1.ret_dia = (float *) calloc (port1.tamanho,sizeof(float));
			port1.valor[0] = 1.00;
			for(n=1;n<(port1.quant);n++){
				for(i=0;i<(argc-1);i++){
					port1.valor[n]+= (port1.valor[n-1]/(argc-1))*(1.00+tudo[i].ret_dia[n-1]);
				}
			}
			//---------------Faz a chamada da funções o para o portfolio----------------
			retornoDiario(port1.valor, port1.quant, port1.ret_dia);
			maiorMenor(port1.ret_dia, port1.tamanho, &(port1.maior), &(port1.menor));
			port1.media = retornoMedio(port1.ret_dia, port1.tamanho);
			port1.desvio = desvioPadrao(port1.ret_dia, port1.tamanho, port1.media);
			port1.ret_total = retornoTotal(port1.valor, port1.quant);
			port1.sharpe_ratio = sharpeRatio(port1.media, port1.desvio);
			i=0;
			//---------------Escreve o portfolio no arquivo de saida--------------------
			fprintf(resultado,"Portfolio1");
			fprintf(resultado,"%8d/%2d/%2d",tudo[i].mes[port1.menor+1],tudo[i].dia[port1.menor+1],tudo[i].ano[port1.menor+1]);
			fprintf(resultado,"%8d/%2d/%2d",tudo[i].mes[port1.maior+1],tudo[i].dia[port1.maior+1],tudo[i].ano[port1.maior+1]);
			fprintf(resultado,"%12.2f%%",port1.ret_dia[port1.menor]*100);
			fprintf(resultado,"%11.2f%%",port1.ret_dia[port1.maior]*100);
			fprintf(resultado,"%11.2f%%",port1.media*100);
			fprintf(resultado,"%13.2f",port1.desvio*100);
			fprintf(resultado,"%12.2f",port1.ret_total);
			fprintf(resultado,"%12.2f\n",port1.sharpe_ratio);
			fprintf(resultado,"\n\nPROPORCOES:\n\nPORTFOLIO1");
			float p = 1.00/(argc-1);
			for(i=0;i<argc-2;i++){
				fprintf(resultado,"%7.4f", p);
				fprintf(resultado,",");
			}
			fprintf(resultado,"%7.4f", p);
			fprintf(resultado,"\n");
			free(port1.valor);
			free(port1.ret_dia);
		}
		fclose(resultado);
		//---------------Libera memoria----------------
		for(i=0;i<argc-1;i++){
			free(tudo[i].dia);
			free(tudo[i].mes);
			free(tudo[i].ano);
			free(tudo[i].ret_dia);
			free(tudo[i].valor);
		}
	}
	return 0;
}
