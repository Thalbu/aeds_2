#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagem.h"

int main(int argc,char *argv[]){
	if(argc <= 1){
		printf("NÃO FOI PASSADA UM IMAGEM");
	}else{
		int i=1, j, nSemente, limiar, linha, coluna, nCinza;
		int TAM = strlen(argv[i]) + 5;
		char solucao[TAM];
		char nome[TAM];
		char aux[TAM];
		char p2[TAM];
		
		strcpy(solucao,argv[i]);
		strcat(solucao,".ppm");
		strcpy(nome,argv[i]);
		strcat(nome,".pgm");
		strcpy(aux,argv[i]);
		strcat(aux,".txt");

		FILE *auxiliar;
		FILE *arquivo;
		FILE *saida;
		
		matriz **resolucao;
		local *semente;

		arquivo = fopen(nome,"r");
		auxiliar = fopen(aux,"r");
		
		Lista lista;
		criaLista(&lista);

		fscanf(auxiliar,"%d %d",&nSemente, &limiar);
		semente = (local *)calloc(nSemente, sizeof(local));//Separa o espaço para as sementes
		for(i=0 ; i<nSemente ; i++){//Le as sementes
			fscanf(auxiliar,"%d, %d <%d, %d, %d>", &semente[i].y, &semente[i].x, &semente[i].RGB.R, &semente[i].RGB.G, &semente[i].RGB.B);
			semente[i].x -= 1;
			semente[i].y -= 1;
		}
		
		fscanf(arquivo,"%s %d %d %d", p2, &coluna, &linha, &nCinza);
		resolucao = (matriz **)calloc(linha,sizeof(matriz *));//Separa o espaço para a matriz
		for(i=0 ; i<linha ; i++){
			resolucao[i] = (matriz *)calloc(coluna,sizeof(matriz));
		}
		for(i=0 ;i<linha;i++){//Le a imagem
			for(j=0 ; j<coluna ; j++){
				fscanf(arquivo,"%d", &resolucao[i][j].pixel);
				resolucao[i][j].final.R = resolucao[i][j].pixel;
				resolucao[i][j].final.G = resolucao[i][j].pixel;
				resolucao[i][j].final.B = resolucao[i][j].pixel;
				resolucao[i][j].percorrido = 0;
				resolucao[i][j].coluna = j;
				resolucao[i][j].linha = i;
			}
		}

		for(i=0 ; i<nSemente ; i++){//Faz a chamada da função para comparar os valores
			int px = semente[i].x;
			int py = semente[i].y;
			compara(&lista, resolucao, semente[i], limiar, resolucao[px][py].linha, resolucao[px][py].coluna, coluna, linha);
			resolucao[px][py].percorrido = 1;
			retira(&lista);
			while((lista.primeiro != lista.ultimo) && (lista.primeiro->prox != NULL)){//Faz com que a comparção comtinue até que não existam elementos na lista
				compara(&lista, resolucao, semente[i], limiar, lista.primeiro->prox->linha, lista.primeiro->prox->coluna, coluna, linha);
				retira(&lista);
			}
		}

		saida = fopen(solucao,"w");
		fprintf(saida,"P3\n");//Imprime o tipo da imagem
		fprintf(saida,"%d %d\n", coluna, linha);//Imprime a quantidade de colunas e de linhas
		fprintf(saida,"255\n");//Imprime a quantidade de niveis de cores
		for(i=0 ; i<linha ; i++){//Imprime as cores dos pixeis
			for(j=0; j<coluna ; j++){
				fprintf(saida,"%d %d %d ",resolucao[i][j].final.R, resolucao[i][j].final.G, resolucao[i][j].final.B);
			}
			fprintf(saida,"\n");
		}
		
		//Libera a memoria usada
		for(i=0; i<linha ; i++){
			free(resolucao[i]);
		}
		free(lista.primeiro);
		free(resolucao);
		free(semente);
		//Fecha os arquivos abertos
		fclose(auxiliar);
		fclose(arquivo);
		fclose(saida);
	}
	return 0;
}
