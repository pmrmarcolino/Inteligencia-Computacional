#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linhas = 6;
int colunas = 5;
int pesoAleatorio = 0;
int bias = 1;
int aprendizado = 1;

typedef struct e
{
    int *E;
    int esperado[2];

}Entrada;

//----------------------------------------------------------------------------------------------

Entrada *criaNeuronio(int numero);
int *criaPeso();
void imprime(Entrada *P);
void imprimePeso(int*P);
void imprimeCalcula(int *P);
void geraPeso(int*P);
int treinamento(Entrada **P, int *peso, int nentradas, int indice);
void preenche(Entrada *P, int i);
int *trocaPesoSoma(Entrada *Perc, int *peso);
int *trocaPesoSubtrai(Entrada *Perc, int *peso);
int * verificaFuncaoP0(int somatorio, Entrada *P,int *peso, int *altera);
int * verificaFuncaoP1(int somatorio, Entrada *P,int *peso, int *altera);
int somatorio(Entrada * P, int * peso);
void distorcao(Entrada *P, int **peso, int esperado);
int calculaSaida(int* P, int * peso);
void printavet(int*  vet);
void treinaOutros(Entrada *P, int **peso);

//----------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    //srand(0); // semente

    Entrada *P[6];
    Entrada *Letras[4];
    int *peso[6];
    int esperado;
    int soma = 0;
    int i;

    for ( i = 0; i < 6; ++i)
    {
        P[i] = criaNeuronio(i);
        peso[i] = criaPeso();
        geraPeso(peso[i]);
        preenche(P[i],i);  
    }

    printf("\nPeso:\n\n");
    imprimePeso(peso[0]);
    imprimePeso(peso[1]);

    printf("\nZero:\n\n");
    imprime(P[0]);

    printf("\nUm:\n\n");
    imprime(P[1]);

    soma = treinamento(P,peso[0],2,0);
    soma += treinamento(P,peso[1],2,1);

    printf("\nPeso Final:\n\n");
    printf("\nPeso zero:\n");
    printavet(peso[0]);
    printf("\nPeso um:\n");
    printavet(peso[1]);
    printf("Iteracoes = %d\n", soma);

    distorcao(P[0],peso,0);
    distorcao(P[1],peso,1);


    for (i = 2; i < 6; ++i)
    {
        treinaOutros(P[i],peso);
    }

    return 0;
}
//----------------------------------------------------------------------------------------------
void treinaOutros(Entrada *P, int **peso){

    int i,j, aleatorio, Y[6];

    imprime(P);

    for (j = 0; j < 6; ++j)
        Y[j] = calculaSaida(P->E,peso[j]);

    for (i = 0; i < 6; ++i)
    {
        printf("\nO resultado do neuronio %d eh %d\n",i,Y[i]);
    }
    printf("\n");
}
//----------------------------------------------------------------------------------------------
void printavet(int*  vet)
{
    int i,j,k;
    printf("\n\n");
    printf("\n+");
    for(k=0; k<5; k++)
        printf("---+");
    printf("\n");
    for(i=0; i<6; i++)
    {
        for(j=0; j<5; j++)
            if(vet[i*5+j]!=0)
                printf("|%2.0d ",vet[i*5+j]);
            else
                printf("|   ");
        printf("|\n+");
        for(k=0; k<5; k++)
            printf("---+");
        printf("\n");
            //printf("%2.0f ",vet[i*5+j]);
    }
}
//----------------------------------------------------------------------------------------------
void distorcao(Entrada *P, int **peso, int esperado){

    int i, aleatorio, Y[2];

    for(i = 0; i < 10; i++)
    {
        aleatorio = rand()%((colunas*linhas)+1);

        if(P->E[aleatorio] == 0)
            P->E[aleatorio] = 1;
        else
            P->E[aleatorio] = 0;

        imprime(P);

        Y[0] = calculaSaida(P->E,peso[0]);
        Y[1] = calculaSaida(P->E,peso[1]);

        printf("Y[0] = %d\n",Y[0] );
        printf("Y[1] = %d\n",Y[1] );

    }
}
//----------------------------------------------------------------------------------------------
Entrada *criaNeuronio(int numero)
{
    Entrada* P;
    int i;

    P = (Entrada *)malloc (sizeof(Entrada));
    P->E = (int *)malloc (31*sizeof(int));

    for (i = 0; i < 2; ++i)
        P->esperado[i] = 0;

    P->esperado[numero] = 1;

    return P;
}
//----------------------------------------------------------------------------------------------
int *criaPeso()
{
    int* P;

    P = malloc ((linhas*colunas+1) * sizeof(int));

    return P;
}
//----------------------------------------------------------------------------------------------
void imprimeCalcula(int *P)
{
    int j;

    printf("%d \n",P[0]);

    for(j = 1; j < linhas*colunas+1; j++)
    {
        if(j == 6) printf("\n");
        if(j == 11) printf("\n");
        if(j == 16) printf("\n");
        if(j == 21) printf("\n");
        if(j == 26) printf("\n");

        if (P[j] == 1)
            printf("#  ");
        else
            printf(".  ");
    }

    printf("\n\n");
}

//----------------------------------------------------------------------------------------------
void imprime(Entrada *P)
{
    int j;

    printf("%d \n",P->E[0]);

    for(j = 1; j < linhas*colunas+1; j++)
    {
        if(j == 6) printf("\n");
        if(j == 11) printf("\n");
        if(j == 16) printf("\n");
        if(j == 21) printf("\n");
        if(j == 26) printf("\n");

        if (P->E[j] == 1)
            printf("#  ");
        else
            printf(".  ");
    }

    printf("\n\n");
}

//----------------------------------------------------------------------------------------------
void imprimePeso(int *P)
{
    int j;

    printf("%d \n",P[0]);

    for(j = 1; j < linhas*colunas+1; j++)
    {
        if(j == 6) printf("\n");
        if(j == 11) printf("\n");
        if(j == 16) printf("\n");
        if(j == 21) printf("\n");
        if(j == 26) printf("\n");

       printf("%d \t",P[j]);
    }

    printf("\n\n");
}

//----------------------------------------------------------------------------------------------
void geraPeso(int *peso)
{
    int i;

    if(pesoAleatorio == 1)
    {
        for(i = 0; i< (linhas*colunas+1) ; i++) peso[i] = rand()%2;
    }
    else
    {
        for(i = 0; i< (linhas*colunas+1) ; i++) peso[i] = 0;
    }
}

//----------------------------------------------------------------------------------------------
int treinamento(Entrada **P, int *peso, int nentradas, int indice)
{
    int somat = 0;
    int iteracoes = 0;
    int i, j;
    int altera = 0;


    do {

        altera = 0;
        for ( i = 0; i < nentradas; ++i)
        {
            somat = calculaSaida(P[i]->E,peso);
                //printf("Desenho %d: esperado: %d, somat = %d\n",i,P[i]->esperado[indice],somat); system("pause");
            if(somat != P[i]->esperado[indice]){
                altera = 1;
                if(somat == 0)
                    trocaPesoSoma(P[i],peso);
                else
                    trocaPesoSubtrai(P[i],peso);
            }
        }
        iteracoes++;
    }while(altera != 0);

    return iteracoes;
}

//----------------------------------------------------------------------------------------------
int * verificaFuncaoP0(int somatorio, Entrada *P ,int *peso, int *altera)
{

    if(somatorio > 0){
        peso = trocaPesoSubtrai(P, peso);
        *altera = 1;
    }
    else
        *altera = 0;


    return peso;
}

//----------------------------------------------------------------------------------------------
int * verificaFuncaoP1(int somatorio, Entrada *P ,int *peso, int *altera)
{

    if(somatorio <= 0){
        peso = trocaPesoSoma(P,peso);
        *altera = 1;
    }
    else
        *altera = 0;

    return peso;
}
//----------------------------------------------------------------------------------------------
int calculaSaida(int *E, int * peso)
{
    int i;
    int somat = 0;

    for (i = 0; i < (linhas*colunas+1); ++i)
    {
        somat += E[i] * peso[i];
    }

    if(somat <= 0)
        return 0;
    else
        return 1;
}
//----------------------------------------------------------------------------------------------
int somatorio(Entrada * P, int * peso)
{
    int i;
    int somat = 0;

    for (i = 0; i < (linhas*colunas+1); ++i)
    {
        somat += P->E[i] * peso[i];
    }

    return somat;
}

//----------------------------------------------------------------------------------------------
int * trocaPesoSoma(Entrada *Perc, int *peso)
{
    int i;
    for (i = 0; i < (linhas*colunas+1); ++i)
    {
        peso[i] += Perc->E[i]*aprendizado;
    }
    return peso;
}

//----------------------------------------------------------------------------------------------
int * trocaPesoSubtrai(Entrada *Perc, int *peso)
{
    int i;
    for (i = 0; i < (linhas*colunas+1); ++i)
    {
        peso[i] -= Perc->E[i]*aprendizado;
    }

    return peso;
}

//----------------------------------------------------------------------------------------------
void preenche(Entrada * p, int numero )
{
    int E[linhas][colunas];
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

    int i, j, k = 1;
    p->E[0] = bias;
    for(i = 0 ; i< linhas; i ++)
    {
        for(j = 0 ; j< colunas; j ++)
        {
            p->E[k++] = E[i][j];
        }
    }
}