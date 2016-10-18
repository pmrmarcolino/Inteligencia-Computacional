#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linhas = 6;
int colunas = 5;
int pesoAleatorio = 1;
int bias = 1; 
int ft0 = 0;
int numero = 5;

typedef struct p{
	int perc;
	int peso;
} Perceptron;

//----------------------------------------------------------------------------------------------

Perceptron **criaNeuronio();
void imprimePeso(Perceptron **P);
void imprimePerc(Perceptron **P);
void geraPeso(Perceptron **P);
void zeraM(Perceptron **P);
void treinamento(Perceptron **P, int **valor);
void imprimeNum(int **P);
int **preenche();

//----------------------------------------------------------------------------------------------

int main(int argc, char const *argv[]){

	Perceptron **P;
	int *peso;
	int **valor;

	P = criaNeuronio();

	valor = preenche();

	imprimeNum(valor);

	//peso = treinamento(P, valor);

	return 0;
}
//----------------------------------------------------------------------------------------------
Perceptron **criaNeuronio(){
	Perceptron ** P;
	int i;

	srand(time(NULL));

	P = malloc (linhas * sizeof(Perceptron));


	for(i =0; i< linhas; i++)
	{
		P[i] =  malloc(colunas * sizeof(Perceptron));
	}

	geraPeso(P);

	return P;
}

//----------------------------------------------------------------------------------------------
void zeraM(Perceptron **P)
{
    int i,j;

    for(i = 0; i< linhas ; i++)
    {
        for(j = 0; j < colunas
        	; j++)
        {
            P[i][j].perc = 0;
        }
    }
}

//----------------------------------------------------------------------------------------------
void imprimePerc(Perceptron **P)
{
	int i,j;

    for(i = 0; i< linhas ; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            printf("%d \t",P[i][j].perc);
        }
        printf("\n");
    }   
}

//----------------------------------------------------------------------------------------------
void imprimePeso(Perceptron **P)
{
	int i,j;

    for(i = 0; i< linhas ; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            printf("%d \t",P[i][j].peso);
        }
        printf("\n");
    }   
}
//----------------------------------------------------------------------------------------------
void imprimeNum(int **P)
{
	int i,j;

    for(i = 0; i< linhas ; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            printf(" %d ",P[i][j]);
        }
        printf("\n");
    }   
}

//----------------------------------------------------------------------------------------------
void geraPeso(Perceptron **P)
{
	int i, j;

	if(pesoAleatorio == 1)
	{
		for(i = 0; i< linhas ; i++)
	    {
	        for(j = 0; j < colunas; j++)
	        {
	            P[i][j].peso = rand()%2;
	        }
	    }

	}
	else
	{
		for(i = 0; i< linhas ; i++)
	    {
	        for(j = 0; j < colunas; j++)
	        {
	            P[i][j].peso = 0;
	        }
	    }
	}
}

//----------------------------------------------------------------------------------------------
/*void treinamento(Perceptron **P, int **valor);
{
	int invalido = 1;
	int *peso;
	int somatorio = 1;
	int funcao;

	peso = malloc(colunas+1*sizeof(int));

	for (int i = 0; i < ; ++i) peso = P[i][j].peso;
	if(pesoAleatorio) peso[colunas+1] = rand()%2;
	else peso[colunas+1] = 0;	

	while(invalido){

		for (int i = 0; i < linhas; ++i){	

			for (int i = 1; i < colunas; ++i)
			{
				somatorio = peso[i]* P[i][j].perc;
			}

			if(pesoAleatorio)
				somatorio += bias* rand()%2;
			else
				somatorio = bias*peso[colunas+1]; 
		}
		
		somatorio <= ft0 ? funcao = 0 : funcao = 1;

		if(funcao != valor[])


		funcao  	
	}

	return peso;
}
*/
int **preenche()
{
	int **E;
    int i,j;

	E = malloc (linhas * sizeof(int*));

	for(i =0; i< linhas; i++) E[i] =  malloc(colunas * sizeof(int));		

    switch(numero)
    {
	    case 0:
	        E[0][0] = 0;E[0][1] = 1;E[0][2] = 1;E[0][3] = 1;E[0][4] = 0;
	        E[1][0] = 1;E[1][1] = 0;E[1][2] = 0;E[1][3] = 0;E[1][4] = 1;
	        E[2][0] = 1;E[2][1] = 0;E[2][2] = 0;E[2][3] = 0;E[2][4] = 1;
	        E[3][0] = 1;E[3][1] = 0;E[3][2] = 0;E[3][3] = 0;E[3][4] = 1;
	        E[4][0] = 1;E[4][1] = 0;E[4][2] = 0;E[4][3] = 0;E[4][4] = 1;
	        E[5][0] = 0;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 0;
	        break;
	    case 1:
	        E[0][0] = 0;E[0][1] = 0;E[0][2] = 1;E[0][3] = 0;E[0][4] = 0;
	        E[1][0] = 0;E[1][1] = 1;E[1][2] = 1;E[1][3] = 0;E[1][4] = 0;
	        E[2][0] = 0;E[2][1] = 0;E[2][2] = 1;E[2][3] = 0;E[2][4] = 0;
	        E[3][0] = 0;E[3][1] = 0;E[3][2] = 1;E[3][3] = 0;E[3][4] = 0;
	        E[4][0] = 0;E[4][1] = 0;E[4][2] = 1;E[4][3] = 0;E[4][4] = 0;
	        E[5][0] = 1;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 1;
	        break;
	    case 2:
	        E[0][0] = 0;E[0][1] = 1;E[0][2] = 1;E[0][3] = 1;E[0][4] = 0;
	        E[1][0] = 0;E[1][1] = 1;E[1][2] = 0;E[1][3] = 1;E[1][4] = 0;
	        E[2][0] = 0;E[2][1] = 0;E[2][2] = 0;E[2][3] = 1;E[2][4] = 0;
	        E[3][0] = 0;E[3][1] = 0;E[3][2] = 1;E[3][3] = 0;E[3][4] = 0;
	        E[4][0] = 0;E[4][1] = 1;E[4][2] = 0;E[4][3] = 0;E[4][4] = 0;
	        E[5][0] = 1;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 1;
	        break;
	    case 3:
	        E[0][0] = 0;E[0][1] = 1;E[0][2] = 1;E[0][3] = 1;E[0][4] = 1;
	        E[1][0] = 0;E[1][1] = 0;E[1][2] = 0;E[1][3] = 0;E[1][4] = 1;
	        E[2][0] = 0;E[2][1] = 1;E[2][2] = 1;E[2][3] = 1;E[2][4] = 1;
	        E[3][0] = 0;E[3][1] = 0;E[3][2] = 0;E[3][3] = 0;E[3][4] = 1;
	        E[4][0] = 0;E[4][1] = 0;E[4][2] = 0;E[4][3] = 0;E[4][4] = 1;
	        E[5][0] = 0;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 1;
	        break;
	    case 4:
	        E[0][0] = 1;E[0][1] = 0;E[0][2] = 0;E[0][3] = 1;E[0][4] = 0;
	        E[1][0] = 1;E[1][1] = 0;E[1][2] = 0;E[1][3] = 1;E[1][4] = 0;
	        E[2][0] = 1;E[2][1] = 0;E[2][2] = 0;E[2][3] = 1;E[2][4] = 0;
	        E[3][0] = 1;E[3][1] = 1;E[3][2] = 1;E[3][3] = 1;E[3][4] = 0;
	        E[4][0] = 0;E[4][1] = 0;E[4][2] = 0;E[4][3] = 1;E[4][4] = 0;
	        E[5][0] = 0;E[5][1] = 0;E[5][2] = 0;E[5][3] = 1;E[5][4] = 0;
	        break;
	    case 5:
	        E[0][0] = 0;E[0][1] = 1;E[0][2] = 1;E[0][3] = 1;E[0][4] = 1;
	        E[1][0] = 0;E[1][1] = 1;E[1][2] = 0;E[1][3] = 0;E[1][4] = 0;
	        E[2][0] = 0;E[2][1] = 1;E[2][2] = 1;E[2][3] = 1;E[2][4] = 1;
	        E[3][0] = 0;E[3][1] = 0;E[3][2] = 0;E[3][3] = 0;E[3][4] = 1;
	        E[4][0] = 0;E[4][1] = 0;E[4][2] = 0;E[4][3] = 0;E[4][4] = 1;
	        E[5][0] = 0;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 1;
	        break;
	    case 6:
	        E[0][0] = 1;E[0][1] = 1;E[0][2] = 1;E[0][3] = 1;E[0][4] = 0;
	        E[1][0] = 1;E[1][1] = 0;E[1][2] = 0;E[1][3] = 0;E[1][4] = 0;
	        E[2][0] = 1;E[2][1] = 1;E[2][2] = 1;E[2][3] = 1;E[2][4] = 0;
	        E[3][0] = 1;E[3][1] = 0;E[3][2] = 0;E[3][3] = 1;E[3][4] = 0;
	        E[4][0] = 1;E[4][1] = 0;E[4][2] = 0;E[4][3] = 1;E[4][4] = 0;
	        E[5][0] = 1;E[5][1] = 1;E[5][2] = 1;E[5][3] = 1;E[5][4] = 0;
	        break;
    }

    return E;
}




