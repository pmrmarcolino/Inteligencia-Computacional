#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

//Linhas é a quantidade de individuos a serem gerado
int popInicial = 100;
int linhas=180;
int linhasElite = 180;
//Colunas é a quantidade de genes
int colunas=10;
// controla o coss, nesse caso é de 60%
// controla o coss, nesse caso é de 80%
int excesso = 80;
int excessoElite = 80;
// Tava de mutação
int taxa = 5;
//elite como metodo de seleção natural se 0 elite se 1 Rein
int elite20 = 0;
//SelecionaPais, se 0 torneiro se 1 roleta
int SelecionaPais = 1;
// Tecnica de cross over, se 1 Ciclico se 0 PMX
int cross = 0;

//----------------------------------------------------------------------------------------------
//Struct individuo
typedef struct p
{
    int torneio;
    int roleta;
    int ind[10];
} Pop;
//----------------------------------------------------------------------------------------------
//Chamadas de função para o AG

//Gera a populacao inicial
Pop* criaPop(char *st1, char *st2, char *st3, char *resp);

//Zera matriz
void zeraM(Pop *Ind);

// Verificação de entradas genéricas
int verificaletraspassadas(char* resp,int tamanhoatual,char caracter);
char* verificaRep(char *st1, char *st2, char *st3);
int Repeticao(Pop Ind[], int k);

//Calculo do fitness
void soma(Pop Ind[], char *st1, char *st2, char *st3, char *resp, int num);

//Impressoes
void imprimeInd(Pop Ind[]);
void imprimeInd2(Pop Ind[]);
void imprimeFitTorneio(Pop Ind[]);
void imprimeFitTorneio2(Pop Ind[]);
void imprimeFitRoleta(Pop Ind[]);
void imprimeUmInd(Pop Ind[], int k);

//Seleciona Pais
int torneio(Pop Ind[]);
int roleta(Pop Ind[]);

//CrossOvers
void crossCiclico(Pop Ind[],int ticket1, int ticket2, char* st1,char *st2, char*st3,char* resp,int k);
void PMX(int ticket1, int ticket2, Pop Ind[], int k,char* st1,char *st2, char*st3,char* resp);
int getPosition(int* vet, int vetsize, int valor);
int itContains(int* vet, int vetsize, int valor);

//Mutação
void mutacao(Pop Ind[], char *st1, char *st2, char *st3, char *resp);

//Metodo de selecao Natural
void reinOrd(Pop Ind[]);
void ordenaPop(Pop Ind[]);
int comparador (const void* A, const void* B);
void ajusteElite20(Pop Ind[]);

//----------------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    Pop *Ind;
    int nFilhos = excesso;
    int nFilhosElite = excessoElite;
    int ticket1;
    int ticket2;
    int converg = 0;
    int geracao = 50, execucao = 1000,k;
    char st1[10], st2[10], st3[10], *resp;

    strcpy(st1, "donald");
    strcpy(st2, "gerald");
    strcpy(st3, "robert");

    resp = verificaRep(st1,st2,st3);

    //srand(0); //fixa semente
    srand(time(NULL));
int i , j;

k = popInicial;

 while(execucao != 0)
 {
    Ind = criaPop(st1,st2,st3,resp);
    while(geracao != 0)
    {
        if(elite20 == 0)
        {
                while(nFilhos!=0)
                {
                    if(SelecionaPais == 0)
                    {
                        ticket1 = torneio(Ind);
                        ticket2 = torneio(Ind);
                    }else{
                        ticket1 = roleta(Ind);
                        ticket2 = roleta(Ind);
                    }
                    if(cross == 1) crossCiclico(Ind,ticket1,ticket2, st1,st2,st3,resp, k);
                    else PMX (ticket1,ticket2, Ind, k, st1,st2, st3,resp);
                    nFilhos-=2;
                    k+=2;
                }

                mutacao(Ind,st1,st2,st3,resp);
                reinOrd(Ind);

                nFilhos = excesso;
            }
           else
           {
                reinOrd(Ind);
                while(nFilhosElite!=0)
                {
                        if(SelecionaPais == 0)
                        {
                            ticket1 = torneio(Ind);
                            ticket2 = torneio(Ind);
                        }else{
                            ticket1 = roleta(Ind);
                            ticket2 = roleta(Ind);
                        }

                        if(cross == 1) crossCiclico(Ind,ticket1,ticket2, st1,st2,st3,resp, k);
                        else PMX(ticket1,ticket2, Ind, k,st1,st2, st3,resp);
                        nFilhosElite-=2;
                        k+=2;
                }

                mutacao(Ind,st1,st2,st3,resp);
                ajusteElite20(Ind);

                nFilhosElite = excessoElite;
           }
                geracao--;
                k=popInicial;
    }


     if(!strcmp(st1,"donald") || !strcmp(st1,"cross"))
     {
            if(Ind[0].torneio == 1000000) converg++;
     }
     else
     {
            if(Ind[0].torneio == 100000) converg++;
     }

    execucao --;
    geracao = 50;
}
    printf("Convergencia = %d\n",converg);

    return 0;
}
//----------------------------------------------------------------------------------------------
void ajusteElite20(Pop Ind[]){

    int i = popInicial*0.2;
    int j, k = popInicial;
    int reserva[10];
    while(k != linhasElite)
    {
        for (j = 0; j < colunas;j++) reserva [j] = Ind[k].ind[j];

        for ( j = 0; j < colunas; j++)  Ind[i].ind[j] = reserva[j];

        k++;
        i++;
    }
}
//----------------------------------------------------------------------------------------------
void PMX(int ticket1, int ticket2, Pop Ind[], int k,char* st1,char *st2, char*st3,char* resp)
{
    int i, j;
    int comeco = colunas-1;
    int fim = 0;
    int posicao;
    int valorAtual;
    int trocaIndice;
    int trocaValor;
    int achou;

    int* trocaVetor1;
    int* trocaVetor2;
    int pai1[colunas];
    int pai2[colunas];
    int aux;


    for(i=0; i<colunas; i++)
    {
        pai1[i] = Ind[ticket1].ind[i] ;
        pai2[i] = Ind[ticket2].ind[i] ;
    }

    //Gera aleatório, começo tem que ser menor que fim
    while(comeco>=fim)
    {
      comeco = rand()%colunas;
      fim = rand()%colunas;
    }


    trocaVetor1 = (int*) malloc(sizeof(int)* colunas);
    trocaVetor2 = (int*) malloc(sizeof(int)* colunas);
    //Aloca para os dois filhos que serão gerados


    ///Crossover apenas a seção que foi sorteada
    for(i=comeco; i<fim; i++)
    {
        aux = pai1[i];
        pai1[i] = pai2[i];
        pai2[i] = aux;
    }

    for(i=comeco; i<fim; i++)
    {
        trocaVetor1[i] = -1;
        trocaVetor2[i] = -1;
    }
    ///Atribui as posições que foram trocadas
    for(i=0; i<(fim-comeco); i++)
    {
        trocaVetor1[i] = pai1[i+comeco];
        trocaVetor2[i] = pai2[i+comeco];
    }


    for(i= fim%colunas; i>=fim || i<comeco ; i = ((i+1)%colunas))
    {
        valorAtual = pai1[i];
        achou = itContains(trocaVetor1, (fim-comeco), valorAtual);
        //printf("valor Atual %d Posicao pai1 antes while: %d\n", valorAtual, posicao);
        //Se posicao for diferente de -1 quer dizer que achei
        if(achou)
        {
            //Pega a posicao que deve ser substituida com o valor repetido
            trocaIndice = getPosition(trocaVetor1, (fim-comeco), valorAtual);
            trocaValor = trocaVetor2[trocaIndice];
            while(itContains(trocaVetor1, (fim-comeco), trocaValor))
            {
                trocaIndice = getPosition(trocaVetor1, (fim-comeco), trocaValor);
                if(trocaIndice!=-1)
                    trocaValor = trocaVetor2[trocaIndice];
            }
            pai1[i] = trocaValor;
        }

        valorAtual = pai2[i];

        achou = itContains(trocaVetor2, (fim-comeco), valorAtual);
        //Se posicao for diferente de -1 quer dizer que achei
        if(achou)
        {
            //Pega a posicao que deve ser substituida com o valor repetido
            trocaIndice = getPosition(trocaVetor2, (fim-comeco), valorAtual);

            trocaValor = trocaVetor1[trocaIndice];

            while(itContains(trocaVetor2, (fim-comeco), trocaValor))
            {
                trocaIndice = getPosition(trocaVetor2, (fim-comeco), trocaValor);
                if(trocaIndice != -1)
                    trocaValor = trocaVetor1[trocaIndice];
            }
            pai2[i] = trocaValor;
        }
    }

    for(i=0; i<colunas; i++)
    {
        Ind[k].ind[i] = pai1[i];
        Ind[k+1].ind[i]= pai2[i];
    }

    //Pop Ind[], char *st1, char *st2, char *st3, char *resp, int num
    soma(Ind,st1,st2,st3,resp, k);
    soma(Ind,st1,st2,st3,resp, k+1);

}
//----------------------------------------------------------------------------------------------
int getPosition(int* vet, int vetsize, int valor)
{
    int i;
    int pos=-1;

    for(i=0; i<vetsize; i++)
    {
       if(vet[i] == valor)
       {
          pos=i;
          break;
       }
    }

    return pos;

}
//----------------------------------------------------------------------------------------------
int itContains(int* vet, int vetsize, int valor)
{
    int i;
    int achou=0;


    for(i=0; i<vetsize; i++)
    {
       if(vet[i] == valor)
       {
          achou=1;
          break;
       }
    }

    return achou;

}
//----------------------------------------------------------------------------------------------
char* verificaRep(char *st1, char *st2, char *st3)
{
    char *resp = (char*)malloc(sizeof(char)*11);

    resp[0] = st1[0];
    int i = 1, k;

    for(k=1; k<strlen(st1); k++)
    {
        if(verificaletraspassadas(resp,i,st1[k])==0)
        {
            resp[i]=st1[k];
            i++;
        }

    }
    for(k=0; k<strlen(st2); k++)
    {
        if(verificaletraspassadas(resp,i,st2[k])==0)
        {
            resp[i]=st2[k];
            i++;
        }

    }
    for(k=0; k<strlen(st3); k++)
    {
        if(verificaletraspassadas(resp,i,st3[k])==0)
        {
            resp[i]=st3[k];
            i++;
        }

    }
    resp[i]='\0';
    return resp;
}
//----------------------------------------------------------------------------------------------
int verificaletraspassadas(char* resp,int tamanhoatual,char caracter)
{
    int i;
    for(i=0; i<tamanhoatual; i++)
        if(caracter==resp[i])return 1;
    return 0;
}
//----------------------------------------------------------------------------------------------
void reinOrd(Pop Ind[])
{
    ordenaPop(Ind);
}
//----------------------------------------------------------------------------------------------
void mutacao(Pop Ind[], char *st1, char *st2, char *st3, char *resp)
{
    int pos1, pos2, troca;
    int taxAux = taxa;
    int aux ;
    while(taxAux != 0)
    {
        if(elite20 == 0) aux = rand()%excesso +popInicial ;
        else aux = rand()%excessoElite +popInicial ;
        //imprimeUmInd(Ind, aux);
        pos1 = rand()%colunas;
        pos2 = rand()%colunas;
        // tres sorteis, 1 : filho a ser mutado, e 2 posições a sererm trocadas
        troca = Ind[aux].ind[pos1];
        Ind[aux].ind[pos1] =Ind[aux].ind[pos2];
        Ind[aux].ind[pos2] =  troca;
        soma(Ind,st1,st2,st3,resp,aux);
        taxAux--;
    }

    //imprimeUmInd(Ind, aux);
}
//----------------------------------------------------------------------------------------------
void imprimeUmInd(Pop Ind[], int k)
{
    int i;
    for(i = 0; i <colunas; i++)
    {
        printf("Ind[%3d] = %d\n",k, Ind[k].ind[i]);
    }
    printf("\n");
}
//----------------------------------------------------------------------------------------------
void zeraM(Pop *Ind)
{
    int i,j;

    for(i = 0; i< linhas ; i++)
    {
        for(j = 0; j < colunas +2; j++)
        {
            Ind[i].ind[j] = 0;
        }
    }
}
//----------------------------------------------------------------------------------------------
Pop *criaPop(char *st1, char *st2, char *st3, char *resp)
{
    if(elite20 == 0)
    {
                int i,j=0, limite=0, aux;
                int num[10];

                Pop* Ind = (Pop*)malloc(linhas * sizeof(Pop));

                zeraM(Ind);

                for(i = 0; i< colunas; i++) num[i] = -1;

                while(limite <linhas-excesso)
                {
                    for(i = 0; i < colunas; i++)
                    {
                        aux = rand()%colunas;

                        while(aux != num[j] &&  i!= j )  j++;

                        if(i == j) num[i] = aux;
                        else i--;
                        j = 0;

                    }

                    for(i = 0; i< colunas; i++)
                    {
                        Ind[limite].ind[i] = num[i];
                        //printf("ind[%d][%d] = %d\n",limite,i, Ind[limite].ind[i] );
                    }
                     soma(Ind,st1,st2,st3,resp,limite);
                    //printf("indFit[%3d] = %d\n",limite,Ind[limite].torneio);
                    //getchar();
                    limite++;
                }
        return Ind;
    }
    else
    {
            int i,j=0, limite=0, aux;
            int num[10];

            Pop* Ind = (Pop*)malloc(linhasElite * sizeof(Pop));

            zeraM(Ind);

            for(i = 0; i< colunas; i++) num[i] = -1;

            while(limite <linhas-excesso)
            {
                for(i = 0; i < colunas; i++)
                {
                    aux = rand()%colunas;

                    while(aux != num[j] &&  i!= j )  j++;

                    if(i == j) num[i] = aux;
                    else i--;
                    j = 0;

                }

                for(i = 0; i< colunas; i++)
                {
                    Ind[limite].ind[i] = num[i];
                    //printf("ind[%d][%d] = %d\n",limite,i, Ind[limite].ind[i] );
                }
                 soma(Ind,st1,st2,st3,resp,limite);
                //printf("indFit[%3d] = %d\n",limite,Ind[limite].torneio);
                //getchar();
                limite++;
            }
        return Ind;
    }
}
//----------------------------------------------------------------------------------------------
void imprimeInd(Pop Ind[])
{
    int i,j;
    for(i = 0; i< linhas - excesso; i++)
    {
        printf("ind[%d] = ", i);
        for(j = 0; j < colunas; j++)
        {
            printf("%d",Ind[i].ind[j] );
        }
        printf("\n");
    }

}
//----------------------------------------------------------------------------------------------
void imprimeFitTorneio(Pop Ind[])
{
    int i;

    for(i = 0; i< linhas - excesso; i++)
    {
        printf("fitness[%2d] = %d", i, Ind[i].torneio);
        printf("\n");
    }
}
//----------------------------------------------------------------------------------------------
void imprimeFitTorneio2(Pop Ind[])
{
    int i;
    if(!elite20){
            for(i = 0; i< linhas ; i++)
            {
                printf("fitness[%3d] = %d", i, Ind[i].torneio);
                printf("\n");
            }
    }
    else{
            for(i = 0; i< linhasElite ; i++)
            {
                printf("fitness[%3d] = %d", i, Ind[i].torneio);
                printf("\n");
            }
    }
}
//----------------------------------------------------------------------------------------------
void imprimeFitRoleta(Pop Ind[])
{
    int i;

    for(i = 0; i< linhas -excesso ; i++)
    {
        printf("fitness[%3d] = %d", i, Ind[i].roleta);
        printf("\n");
    }
}
//----------------------------------------------------------------------------------------------
void imprimeInd2(Pop Ind[])
{
    int i,j;
    if(!elite20)
    {
            for(i = 0; i< linhas ; i++)
            {
                printf("ind[%3d] = ", i);
                for(j = 0; j < colunas; j++)
                {
                    printf("%d",Ind[i].ind[j]);
                }
                printf("\n");
            }
        }
        else{
            for(i = 0; i< linhasElite ; i++)
            {
                printf("ind[%3d] = ", i);
                for(j = 0; j < colunas; j++)
                {
                    printf("%d",Ind[i].ind[j]);
                }
                printf("\n");
            }
        }
}
//----------------------------------------------------------------------------------------------
void soma(Pop Ind[], char *st1, char *st2, char *st3, char *resp, int num)
{

    int ValorP1=0, ValorP2=0,i,mul=1,fitness=0,k;
    int tamPalavra = strlen(st1);

    for(i=0; i<tamPalavra; i++)
    {
        for(k=0; k<colunas; k++)if(st1[tamPalavra-i-1]==resp[k])break;
        ValorP1+=mul*(Ind[num].ind[k]);
        mul = mul*10;
    }

    mul = 1;
    tamPalavra = strlen(st2);
    for(i=0; i<tamPalavra; i++)
    {
        for(k=0; k<colunas; k++)if(st2[tamPalavra-i-1]==resp[k])break;
        ValorP2+=mul*(Ind[num].ind[k]);
        mul = mul*10;
    }

    mul = 1;
    tamPalavra = strlen(st3);
    for(i=0; i<tamPalavra; i++)
    {
        for(k=0; k<colunas; k++)if(st3[tamPalavra-i-1]==resp[k])break;
        fitness+=mul*(Ind[num].ind[k]);
        mul = mul*10;
    }

    fitness = fitness - (ValorP1 + ValorP2);
    if(!strcmp(st1,"cross") || !strcmp(st1,"donald")) fitness = 1000000 - abs(fitness);
    else fitness = 100000 - abs(fitness);

    Ind[num].torneio = fitness;
}
//----------------------------------------------------------------------------------------------
int torneio(Pop Ind[])
{
    int aux[3] ;
    int tour = 3;
    int escolhido;
    int i;

    for(i = 0; i < tour ; i++) aux[i] = rand()%(linhas-excesso);

    if(Ind[aux[0]].torneio > Ind[aux[1]].torneio)
    {
        escolhido =  aux[0];
        if (escolhido < Ind[aux[2]].torneio)
        {
            escolhido = aux[2];
        }
    }
    else
    {
        escolhido =  aux[1];
    }
    //printf("\n escolhido = %d\n", escolhido );
    //getchar();
    return escolhido;
}
//----------------------------------------------------------------------------------------------
void crossCiclico(Pop Ind[],int ticket1, int ticket2, char* st1,char *st2, char*st3,char* resp,int k)
{
    int aux = rand()%colunas;
    int i, j,troca;
    //imprimeInd(Ind);

    for(i = 0; i<colunas; i++)
    {
        Ind[k].ind[i]  = Ind[ticket1].ind[i];
        Ind[k+1].ind[i]  = Ind[ticket2].ind[i];
    }


    do{
            troca = Ind[k].ind[aux];
            Ind[k].ind[aux] = Ind[k+1].ind[aux];
            Ind[k+1].ind[aux] =  troca;
            //printf("%d\n",aux );
            for (i = 0; i < colunas; i++)
                if( i != aux && Ind[k].ind[i] == Ind[k].ind[aux] ){
                    aux = i;
                    break;
                }

        }while(Repeticao(Ind,k)==1);


     soma(Ind,st1,st2,st3,resp,k);
     soma(Ind,st1,st2,st3,resp,k+1);
    //printf("ind[%d] = %d \t ind[%d] = %d\n",k, Ind[k].torneio, k+1, Ind[k+1].torneio );

}
//----------------------------------------------------------------------------------------------
int Repeticao(Pop Ind[], int k)
{
    int vet[colunas];
    int i;

    for (i = 0 ; i< colunas; i++) vet[i] = 0;

    for (i = 0 ; i< colunas; i++)  vet[Ind[k].ind[i]]++;

     for (i = 0 ; i< colunas; i++) if (vet[i] >1 ) return 1;

    return 0;
}


int roleta(Pop Ind[])
{
    int i, aux = 0;

    for(i = 0; i< linhas - excesso; i++)
    {
        aux += Ind[i].torneio;
        Ind[i].roleta = aux;
        //printf("%d\n",Ind[i].roleta);
        //getchar();
    }
    //imprimeFitRoleta(Ind);
    aux = rand() % Ind[linhas-excesso-1].roleta;
    //printf("ale = %d", aux);
    for(i = 0; i<linhas - excesso; i++)
    {
        if(aux < Ind[i].roleta) break;
    }

    //printf("\n%d\n",i);
    return i;
}
//----------------------------------------------------------------------------------------------
int comparador (const void* A, const void* B)
{
    Pop *a = (Pop *)A;
    Pop *b = (Pop *)B;
    if ( a->torneio >  b->torneio ) return -1;
    if ( a->torneio == b->torneio ) return 0;
    if ( a->torneio <  b->torneio ) return 1;
}
//----------------------------------------------------------------------------------------------
void ordenaPop(Pop Ind[])
{
    qsort(Ind, linhas,sizeof(Pop),comparador);
}

