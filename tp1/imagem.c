#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagem.h"
#define TAM 20

//-----------------------Funções do Programa-----------------------
void criaLista(Lista *lista){//cria uma lista em que o primeiro e ultimo apontam para a cabeça
	matriz *cabeca = (matriz *)calloc(1,sizeof(matriz));
	lista->primeiro = cabeca;
	lista->ultimo = cabeca;
	cabeca->prox = NULL;
}

void insere(Lista *lista, matriz *resolucao){//insere a posição da matriz no final da lista para ser comparada posteirormente
	if(lista->primeiro==lista->ultimo){//quando a lista esta vazia
		lista->ultimo = resolucao;
		lista->primeiro->prox = resolucao;
		resolucao->prox = NULL;
	}else{
		lista->ultimo->prox = resolucao;
		lista->ultimo = resolucao;
		resolucao->prox = NULL;
	}
}

void retira(Lista *lista){//Retira da lista os elementos já comparados
	if (lista->primeiro->prox != NULL){//so acontece se tiver elementos na lista
		if(lista->primeiro->prox == lista->ultimo){//so tem a cabeça e mais um
			lista->ultimo = lista->primeiro;
			lista->primeiro->prox = NULL;
		}else{//Existe mais de uma elemento na lista
			matriz aux;
			aux.prox = lista->primeiro->prox;
			lista->primeiro->prox = lista->primeiro->prox->prox;
			aux.prox->prox = NULL;
		}
	}
}

void compara(Lista *lista, matriz **resolucao, local semente, int T, int l, int c, int coluna, int linha){//compara os pixeis ao redor da posição passada
	int a, b;
	a = resolucao[l][c].pixel;//valor de referencia para a compraração
	if((l-1) >= 0){//cima
		b = resolucao[l-1][c].pixel;
		if((l-1>=0)&&((abs(a-b))<=T)&&(resolucao[l-1][c].percorrido==0)){
			resolucao[l-1][c].pixel = a;
			resolucao[l-1][c].final.R = semente.RGB.R;
			resolucao[l-1][c].final.G = semente.RGB.G;
			resolucao[l-1][c].final.B = semente.RGB.B;
			resolucao[l-1][c].percorrido = 1;
			insere(lista, &resolucao[l-1][c]);
		}
	}
	if((c+1) < coluna){//direita
		b = resolucao[l][c+1].pixel;
		if(((c+1) < (coluna)) && ((abs(a-b)) <= T) && (resolucao[l][c+1].percorrido == 0)){
			resolucao[l][c+1].pixel = a;
			resolucao[l][c+1].final.R = semente.RGB.R;
			resolucao[l][c+1].final.G = semente.RGB.G;
			resolucao[l][c+1].final.B = semente.RGB.B;
			resolucao[l][c+1].percorrido = 1;
			insere(lista, &resolucao[l][c+1]);
		}
	}
	if((l+1) < linha){//baixo
		b = resolucao[l+1][c].pixel;
		if(((l+1) < (linha)) && ((abs(a-b)) <= T) && (resolucao[l+1][c].percorrido == 0)){
			resolucao[l+1][c].pixel = a;
			resolucao[l+1][c].final.R = semente.RGB.R;
			resolucao[l+1][c].final.G = semente.RGB.G;
			resolucao[l+1][c].final.B = semente.RGB.B;
			resolucao[l+1][c].percorrido = 1;
			insere(lista, &resolucao[l+1][c]);
		}
	}
	if((c-1) >= 0){//esquerda
		b = resolucao[l][c-1].pixel;
		if(((c-1) >= 0) && ((abs(a-b)) <= T) && (resolucao[l][c-1].percorrido == 0)){
			resolucao[l][c-1].pixel = a;
			resolucao[l][c-1].final.R = semente.RGB.R;
			resolucao[l][c-1].final.G = semente.RGB.G;
			resolucao[l][c-1].final.B = semente.RGB.B;
			resolucao[l][c-1].percorrido = 1;
			insere(lista, &resolucao[l][c-1]);
		}
	}
}
