#ifndef IMAGEM_H
#define IMAGEM_H

//------------------Struct para Modularização------------------------
typedef struct c{//cores para a imagem
	int R;
	int G;
	int B;
}cor;

typedef struct S{//posição da semente
	int x;
	int y;
	cor RGB;
}local;

typedef struct matriz{//valoves e informações referentes a matriz
	cor final;
	int pixel;
	int linha;
	int coluna;
	int percorrido;
	struct matriz *prox;
}matriz;

typedef struct Lista{//Lista para realizar a ordenação
	matriz *primeiro;
	matriz *ultimo;
}Lista;

//------------------Enunciado das Funções-----------------------------
void criaLista(Lista *lista);
void insere(Lista *lista, matriz *resolucao);
void retira(Lista *lista);
void compara(Lista *lista, matriz **resolucao, local semente, int T, int l, int c, int coluna, int linha);


#endif