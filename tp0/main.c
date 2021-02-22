#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct moedas
{
    char sigla[15];
    int quantidade;
    int *dia;
    int *mes;
    int *ano;
    float *valor;
    int tamanho;
    float *RDiario;
    float RDMaior;
    int DiaMaior;
    int MesMaior;
    int AnoMaior;
    float RDMenor;
    int DiaMenor;
    int MesMenor;
    int AnoMenor;
    float RDMedio;
    float DPadrao;
    float RTotal;
    float SRadio;

}moedas;

void RetornoDiario(float *valor, int tamanho, float *RDiario)
{
    int i;
    for(i = 1; i < tamanho; i++)
    {
        RDiario[i] = (valor[i] - valor[i-1]) / valor[i-1];
    }
}

float MaiorRetorno(int quantidade, float *RDiario, int *dia, int *mes, int *ano, int *DiaMaior, int *MesMaior, int *AnoMaior)
{
    int i;
    float RDMaior = 0.00;
    for(i = 0; i < quantidade; i++)
    {
        if(RDiario[i] > RDMaior)
        {
            RDMaior = RDiario[i];
            *DiaMaior = dia[i];
            *MesMaior = mes[i];
            *AnoMaior = ano[i];
        }
    }
    return (RDMaior);
}

float MenorRetorno(int quantidade, float *RDiario, int *dia, int *mes, int *ano, int *DiaMenor, int *MesMenor, int *AnoMenor)
{
    int i;
    float RDMenor = RDiario[0];
    for(i = 0 ; i < quantidade; i++)
    {
        if(RDiario[i] < RDMenor)
        {
            RDMenor = RDiario[i];
            *DiaMenor = dia[i];
            *MesMenor = mes[i];
            *AnoMenor = ano[i];
        }
    }
    return (RDMenor);
}

float RetornoMedio(int quantidade, float *RDiario)
{
    int i;
    float RDMedio;
    float soma = 0.00;
    for(i = 0; i < quantidade; i++)
    {
        soma += RDiario[i];
    }
    RDMedio = (soma / quantidade);
    return(RDMedio);
}

float DesvioPadrao(int quantidade, float *RDiario, float RDMedio)
{
    int i;
    float soma = 0.00;
    float DPadrao;
    for(i = 0; i < quantidade; i++)
    {
        soma += pow((RDiario[i] - RDMedio),2);
    }
    soma = soma / (quantidade-1);
    DPadrao = sqrt(soma);
    return (DPadrao);
}

float RetornoTotal(int tamanho, float *valor)
{
    float RTotal;
    RTotal = (valor[tamanho-1]/valor[0]);
    return (RTotal);
}

float SharpeRadio(float RDMedio, float DPadrao)
{
    float SRadio;
    SRadio = ((RDMedio - 0.00038) / DPadrao);
    return (SRadio);
}

int main(int argc, char *argv[])
{
    //Garantir que um arquivo será passado
    if(argc == 1)
    {
        printf("Passe um arquivo!");
        return 0;
    }
    else
    {
		int i;
		int n;

        FILE *arquivo;
        moedas m[argc-1];
		FILE *saida;
        saida = fopen("saida.txt","w");

        //acrescentar ".csv" no nome do arquivo
        for(i = 1; i < argc; i++)
        {
			strcpy(m[i-1].sigla,argv[i]);// Salvando a sigla do nome da moeda(nome do arquivo)
            strcat(argv[i],".csv");
        }
        for(i = 0; i < (argc-1); i++)
        {
            arquivo = fopen(argv[i+1], "r"); 
            fscanf(arquivo,"%d", &m[i].tamanho);
			
            m[i].quantidade = m[i].tamanho-1;
            m[i].dia = (int*)malloc(m[i].tamanho*sizeof(int));
            m[i].mes = (int*)malloc(m[i].tamanho*sizeof(int));
            m[i].ano = (int*)malloc(m[i].tamanho*sizeof(int));
            m[i].valor = (float*)malloc(m[i].tamanho*sizeof(float));
            m[i].RDiario = (float*)malloc(m[i].quantidade*sizeof(float));

            //salvando as datas
            for(n = m[i].quantidade; n >(-1) ; n--)
            {
                fscanf(arquivo,"%d/%d/%d,%f", &m[i].mes[n], &m[i].dia[n], &m[i].ano[n], &m[i].valor[n]);
            }
           //chamar as funções
            RetornoDiario(m[i].valor, m[i].tamanho, m[i].RDiario);
            m[i].RDMaior = MaiorRetorno(m[i].quantidade, m[i].RDiario, m[i].dia, m[i].mes, m[i].ano, &(m[i].DiaMaior), &(m[i].MesMaior), &(m[i].AnoMaior));
            m[i].RDMenor = MenorRetorno(m[i].quantidade, m[i].RDiario, m[i].dia, m[i].mes, m[i].ano, &(m[i].DiaMenor), &(m[i].MesMenor), &(m[i].AnoMenor));
            m[i].RDMedio = RetornoMedio(m[i].quantidade, m[i].RDiario);
            m[i].DPadrao = DesvioPadrao(m[i].quantidade, m[i].RDiario, m[i].RDMedio);
            m[i].RTotal = RetornoTotal(m[i].tamanho, m[i].valor);
            m[i].SRadio = SharpeRadio(m[i].RDMedio, m[i].DPadrao);
		}
		fclose(arquivo);


        //Escrever no arquivo de saida os resultados das fuçoes
        fprintf(saida,"               DataMaior     DataMenor        Maior       Menor       Media       Desvio      RTotal      Sharpe\n");
        for(i = 0; i < (argc-1); i++)
        {
            fprintf(saida, "%10s", m[i].sigla);
            fprintf(saida, "%8d/%2d/%2d", m[i].MesMaior, m[i].DiaMaior, m[i].AnoMaior);
            fprintf(saida, "%8d/%2d/%2d", m[i].MesMenor, m[i].DiaMenor, m[i].AnoMenor);
            fprintf(saida, "%13.2f", m[i].RDMaior);
            fprintf(saida, "%12.2f", m[i].RDMenor);
            fprintf(saida, "%12.2f", m[i].RDMedio*100);
            fprintf(saida, "%12.2f", m[i].DPadrao*100);
            fprintf(saida, "%12.2f", m[i].RTotal);
            fprintf(saida, "%12.2f\n", m[i].SRadio);
        }
        fclose(saida);
		for(i = 0; i < (argc-1); i++)
		{
			free(m[i].dia);
			free(m[i].mes);
			free(m[i].ano);
			free(m[i].valor);
			free(m[i].RDiario);
		}	
    }
    return 0;
}

