#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linhas = 6;
int colunas = 5;
int pesoAleatorio = 0;
int bias = 1;
int ft0 = 0;
int ft1 = 1;

//----------------------------------------------------------------------------------------------

int *criaNeuronio();
void imprime(int*P);
void geraPeso(int*P);
int *treinamento(int *P0,int *P1, int *peso);
void preenche(int *P, int i);
int *trocaPesoSoma(int *Perc, int *peso);
int *trocaPesoSubtrai(int *Perc, int *peso);
int * verificaFuncaoP0(int somatorio, int *P,int *peso);
int * verificaFuncaoP1(int somatorio, int *P,int *peso);
int somatorio(int * P, int * peso);

//----------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
    int *P0;
    int *P1;
    int **peso;

    P0 = criaNeuronio();
    P1 = criaNeuronio();
    peso = criaNeuronio();

    geraPeso(peso);
    preenche(P0,0);
    preenche(P1,1);

    imprime(P0);
    printf("\n\n");

    imprime(P1);
    printf("\n\n");

    imprime(peso);
    printf("\n\n");

    printf("O numero de iteracoes : %d", treinamento(P0,P1,peso));

    //imprimePeso(P0);

    return 0;
}
//----------------------------------------------------------------------------------------------
int *criaNeuronio()
{
    int* P;

    srand(time(NULL));

    P = malloc (linhas*colunas * sizeof(int));

    return P;
}

//----------------------------------------------------------------------------------------------
void imprime(int *P)
{
    int j;
    for(j = 0; j < linhas*colunas; j++)
    {
        if(j%5 == 0) printf("\n");
        printf("%d \t",P[j]);
    }
}

//----------------------------------------------------------------------------------------------
void geraPeso(int *peso)
{
    int i;

    if(pesoAleatorio == 1)
    {
        for(i = 0; i< linhas*colunas ; i++) peso[i] = rand()%2;
    }
    else
    {
        for(i = 0; i< linhas*colunas ; i++) peso[i] = 0;
    }
}

//----------------------------------------------------------------------------------------------
int *treinamento(int*P0, int*P1, int *peso)
{
    int iterator = 1;
    int somat = 0;
    int altera = 1;
    int i, j;

    while(altera)
    {
        somat = somatorio(P0, peso);

        peso = verificaFuncaoP0(somat, P0,peso);

        somat = somatorio(P1,peso);

        peso = verificaFuncaoP1(somat, P1,peso);

        iterator++;
    }
    printf("Iteracoes %d", iterator);
    return peso;
}

int * verificaFuncaoP0(int somatorio, int *P ,int *peso)
{

    if(somatorio > ft0)
    {
        peso = trocaPesoSubtrai(P, peso);
    }

    return peso;
}

int * verificaFuncaoP1(int somatorio, int *P ,int *peso)
{

    if(somatorio > ft1)
    {
        peso = trocaPesoSubtrai(P, peso);
    }
    else
        peso = trocaPesoSoma(P,peso);

    return peso;
}

int somatorio(int * P, int * peso)
{
    int i;
    int somat = 0;

    for (i = 0; i < linhas*colunas; ++i)
    {
        somat += P[i] * peso[i];
    }

    if(pesoAleatorio)
        somat += bias* rand()%2;
    else
        somat = bias*0;

    return somat;
}

int * trocaPesoSoma(int *Perc, int *peso)
{
    int i;
    for (i = 0; i < linhas*colunas; ++i)
    {
        peso[i] += Perc[i];
    }
    return peso;
}

int * trocaPesoSubtrai(int *Perc, int *peso)
{
    int i;
    for (i = 0; i < linhas*colunas; ++i)
    {
        peso[i] -= Perc[i];
    }

    return peso;
}

void preenche(int * p, int numero )
{
    int E[linhas][colunas];
    switch(numero)
    {
    case 0:
        E[0][0] = 0;
        E[0][1] = 1;
        E[0][2] = 1;
        E[0][3] = 1;
        E[0][4] = 0;
        E[1][0] = 1;
        E[1][1] = 0;
        E[1][2] = 0;
        E[1][3] = 0;
        E[1][4] = 1;
        E[2][0] = 1;
        E[2][1] = 0;
        E[2][2] = 0;
        E[2][3] = 0;
        E[2][4] = 1;
        E[3][0] = 1;
        E[3][1] = 0;
        E[3][2] = 0;
        E[3][3] = 0;
        E[3][4] = 1;
        E[4][0] = 1;
        E[4][1] = 0;
        E[4][2] = 0;
        E[4][3] = 0;
        E[4][4] = 1;
        E[5][0] = 0;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 0;
        break;
    case 1:
        E[0][0] = 0;
        E[0][1] = 0;
        E[0][2] = 1;
        E[0][3] = 0;
        E[0][4] = 0;
        E[1][0] = 0;
        E[1][1] = 1;
        E[1][2] = 1;
        E[1][3] = 0;
        E[1][4] = 0;
        E[2][0] = 0;
        E[2][1] = 0;
        E[2][2] = 1;
        E[2][3] = 0;
        E[2][4] = 0;
        E[3][0] = 0;
        E[3][1] = 0;
        E[3][2] = 1;
        E[3][3] = 0;
        E[3][4] = 0;
        E[4][0] = 0;
        E[4][1] = 0;
        E[4][2] = 1;
        E[4][3] = 0;
        E[4][4] = 0;
        E[5][0] = 1;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 1;
        break;
    case 2:
        E[0][0] = 0;
        E[0][1] = 1;
        E[0][2] = 1;
        E[0][3] = 1;
        E[0][4] = 0;
        E[1][0] = 0;
        E[1][1] = 1;
        E[1][2] = 0;
        E[1][3] = 1;
        E[1][4] = 0;
        E[2][0] = 0;
        E[2][1] = 0;
        E[2][2] = 0;
        E[2][3] = 1;
        E[2][4] = 0;
        E[3][0] = 0;
        E[3][1] = 0;
        E[3][2] = 1;
        E[3][3] = 0;
        E[3][4] = 0;
        E[4][0] = 0;
        E[4][1] = 1;
        E[4][2] = 0;
        E[4][3] = 0;
        E[4][4] = 0;
        E[5][0] = 1;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 1;
        break;
    case 3:
        E[0][0] = 0;
        E[0][1] = 1;
        E[0][2] = 1;
        E[0][3] = 1;
        E[0][4] = 1;
        E[1][0] = 0;
        E[1][1] = 0;
        E[1][2] = 0;
        E[1][3] = 0;
        E[1][4] = 1;
        E[2][0] = 0;
        E[2][1] = 1;
        E[2][2] = 1;
        E[2][3] = 1;
        E[2][4] = 1;
        E[3][0] = 0;
        E[3][1] = 0;
        E[3][2] = 0;
        E[3][3] = 0;
        E[3][4] = 1;
        E[4][0] = 0;
        E[4][1] = 0;
        E[4][2] = 0;
        E[4][3] = 0;
        E[4][4] = 1;
        E[5][0] = 0;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 1;
        break;
    case 4:
        E[0][0] = 1;
        E[0][1] = 0;
        E[0][2] = 0;
        E[0][3] = 1;
        E[0][4] = 0;
        E[1][0] = 1;
        E[1][1] = 0;
        E[1][2] = 0;
        E[1][3] = 1;
        E[1][4] = 0;
        E[2][0] = 1;
        E[2][1] = 0;
        E[2][2] = 0;
        E[2][3] = 1;
        E[2][4] = 0;
        E[3][0] = 1;
        E[3][1] = 1;
        E[3][2] = 1;
        E[3][3] = 1;
        E[3][4] = 0;
        E[4][0] = 0;
        E[4][1] = 0;
        E[4][2] = 0;
        E[4][3] = 1;
        E[4][4] = 0;
        E[5][0] = 0;
        E[5][1] = 0;
        E[5][2] = 0;
        E[5][3] = 1;
        E[5][4] = 0;
        break;
    case 5:
        E[0][0] = 0;
        E[0][1] = 1;
        E[0][2] = 1;
        E[0][3] = 1;
        E[0][4] = 1;
        E[1][0] = 0;
        E[1][1] = 1;
        E[1][2] = 0;
        E[1][3] = 0;
        E[1][4] = 0;
        E[2][0] = 0;
        E[2][1] = 1;
        E[2][2] = 1;
        E[2][3] = 1;
        E[2][4] = 1;
        E[3][0] = 0;
        E[3][1] = 0;
        E[3][2] = 0;
        E[3][3] = 0;
        E[3][4] = 1;
        E[4][0] = 0;
        E[4][1] = 0;
        E[4][2] = 0;
        E[4][3] = 0;
        E[4][4] = 1;
        E[5][0] = 0;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 1;
        break;
    case 6:
        E[0][0] = 1;
        E[0][1] = 1;
        E[0][2] = 1;
        E[0][3] = 1;
        E[0][4] = 0;
        E[1][0] = 1;
        E[1][1] = 0;
        E[1][2] = 0;
        E[1][3] = 0;
        E[1][4] = 0;
        E[2][0] = 1;
        E[2][1] = 1;
        E[2][2] = 1;
        E[2][3] = 1;
        E[2][4] = 0;
        E[3][0] = 1;
        E[3][1] = 0;
        E[3][2] = 0;
        E[3][3] = 1;
        E[3][4] = 0;
        E[4][0] = 1;
        E[4][1] = 0;
        E[4][2] = 0;
        E[4][3] = 1;
        E[4][4] = 0;
        E[5][0] = 1;
        E[5][1] = 1;
        E[5][2] = 1;
        E[5][3] = 1;
        E[5][4] = 0;
        break;
    }
    int i, j, k = 0;
    for(i = 0 ; i< linhas; i ++)
    {
        for(j = 0 ; j< colunas; j ++)
        {
            p[k++] = E[i][j];
        }
    }
}
