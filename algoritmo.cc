#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 20
#define COMP 36
#define PM 3
#define PC 60

using namespace std;

int pop [TAM][COMP];
int pop_temp[TAM][COMP];
int fitInd [TAM];

void inicializaPop();
void avaliaPop();
void torneio();
void crossover();
void mutacao();
void imprimePop();
void imprimeFitness();
///////////////////////////////// MAIN /////////////////////////////////////////
int main()
{
    int g=0, geracoes=90;
    inicializaPop();
    cout <<"Populacao inicial"<<endl;
//    imprimePop();

    do
    {
        avaliaPop();
        torneio();
        crossover();
        mutacao();
//        cout <<"------------------------------------------------------------"<<endl;
//        cout <<"geracoes:"<< g <<endl;
//        imprimePop();
        cout <<"Fitness da geracao:"<<g<<endl;
        imprimeFitness();
        g++;
    }
    while(g<geracoes);
    cout <<"------------------------------------------------------------"<<endl;
    cout <<"geracoes:"<< g <<endl;
    imprimePop();
    cout <<"Fitness da geracao:"<<g<<endl;
    imprimeFitness();
    getchar();
    return 0;
}
///////////////////////////////// FUNCOES //////////////////////////////////////
void inicializaPop()
{
    //srand(time(NULL));
    srand( (unsigned)time(NULL) );
    for(int i=0; i<TAM; i++)
    {
        for(int j=0; j<COMP; j++)
        {
            pop[i][j]=rand()%2;
        }
    }
}

void avaliaPop()
{
    for (int i=0; i <TAM; i++)
    {
        fitInd[i] = 9 + pop[i][1]*pop[i][4] - pop[i][22]*pop[i][13] + pop[i][23]*pop[i][3] - pop[i][20]*pop[i][9] + pop[i][35]*pop[i][14] - pop[i][10]*pop[i][25] + pop[i][15]*pop[i][16] + pop[i][2]*pop[i][32]
                    + pop[i][27]*pop[i][18] + pop[i][11]*pop[i][33] - pop[i][30]*pop[i][31] - pop[i][21]*pop[i][24] + pop[i][34]*pop[i][26] - pop[i][28]*pop[i][6] + pop[i][7]*pop[i][12] - pop[i][5]*pop[i][8] + pop[i][17]*pop[i][19] - pop[i][0]*pop[i][29]
                    + pop[i][22]*pop[i][3] + pop[i][20]*pop[i][14] + pop[i][25]*pop[i][15] + pop[i][30]*pop[i][11] + pop[i][24]*pop[i][18] + pop[i][6]*pop[i][7] + pop[i][8]*pop[i][17] + pop[i][0]*pop[i][32];
    }
}

void torneio()
{
    int k=10;
    int maior=0;
    //srand(time(NULL));
    srand( (unsigned)time(NULL) );
    for(int i=0; i<TAM; i++)
    {
        int idx;
        for(int j=0; j<k; j++)
        {
            idx=rand()%(TAM);
            if(j==0)
            {
                maior=idx;
            }
            else
            {
                if(fitInd[idx]>fitInd[maior])
                {
                    maior=idx;
                }
            }
            for(int l=0; l<COMP; l++)
            {
                pop_temp[i][l] = pop[maior][l];
            }
        }
    }
}

void crossover()
{
    int corte,prob;
    //srand(time(NULL));
    srand( (unsigned)time(NULL) );
    for(int i=0; i<TAM; i+=2)
    {
        prob=rand()%101;
        if(prob<PC)
        {
            corte=rand () % COMP;
            if (corte==0)
            {
                corte=1;
            }
            if(corte == COMP)
            {
                corte=COMP-1;
            }
            for (int x=0; x < corte; x++)
            {
                pop[i][x]   = pop_temp[i][x];
                pop[i+1][x] = pop_temp[i+1][x];
            }
            for (int y=corte; y < COMP; y++)
            {
                pop[i][y]   = pop_temp[i+1][y];
                pop[i+1][y] = pop_temp[i][y];
            }
        }
        else
        {
            for(int j=0; j<COMP; j++)
            {
                pop[i][j]= pop_temp [i][j];
                pop[i+1][j]= pop_temp [i+1][j];
            }
        }
    }
}

void mutacao()
{
    int prob;
    //srand(time(NULL));
    srand( (unsigned)time(NULL) );
    for(int i=0; i<TAM; i++)
    {
        for(int j=0; j<COMP; j++)
        {
            prob=rand()%101;
            if(prob<PM)
            {
                if(pop[i][j]== 0)
                {
                    pop[i][j]=1;
                }
                else
                {
                    pop[i][j]=0;
                }
            }
        }
    }
}

void imprimePop()
{
    for(int i=0; i<TAM; i++)
    {
        for(int j=0; j<COMP; j++)
        {
            cout << pop[i][j];
        }
        cout << "\n";
    }
}

void imprimeFitness()
{
    for(int i = 0; i< TAM; i++)
    {
        cout<<fitInd[i];
        if(i==TAM-1)
        {
            cout<<"."<<endl;
        }
        else
        {
            cout<<",";
        }

    }
}
