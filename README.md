## Algoritmo Genético desenvolvido na disciplina de Inteligência Artificial, com o objetivo de otimizar os parâmetros de uma caixa preta, assim reduzindo o ruido do sinal.

> ### Exercício 6.1 Otimização de parâmetros de uma caixa preta [Computação Evolutiva: Uma Abordagem Pragmática - Fernando J. Von Zuben]

[Computação Evolutiva: Uma Abordagem Pragmática - Fernando J. Von Zuben]: https://preview.c9users.io/mateusvilione/algoritmo-genetico/computacao-evolutiva-uma-abordagem-pragmatica.pdf?_c9_id=livepreview1&_c9_host=https://ide.c9.io


#### Parâmetros do algoritmo
+ Tamanho da população = 20
+ Comprimento 9 botoes x 4 bits = 36
+ Probabilidade de mutacao = 3%
+ Probabilidade de crossover = 60%
+ Numero de gerações = 90

    
#### População inicial
    011000101001111000001100100011000101
    111011110110110010001100000110001101
    000011101100000110100011011001101100
    010110111100110111000100110001100101
    010110100001101001010110001001000011
    100100000000101011011101001100011001
    011111100101011101111001101011110101
    000010011100011101011110100110100101
    100111110000111000111110100011101011
    100101010100010101111010110010100011
    110110111101011110101010000000111000
    001011101010111010110111110111111110
    010110001110101110011100010101110000
    000111101001000010011000001001000111
    000000100100111010010100100111001001
    011100111010000010000010100000111101
    110011001001011111111111110000111111
    011001100010101010001001110001111011
    001001001101001110101100101000100010
    110111011100110111101001010011010101

#### População final
    011110011001001111111011110100101111
    011110111001001111101011110100101111
    011110111001001111111011110000101111
    010110111011001111111011110110101111
    011110111001000111111011110100101111
    011110111001001111111011110100101111
    001110111001001111111011110100111111
    011110111001001111111011110100101111
    011110111001001111111011110100101110
    011111111001011111111111110100101111
    011110111001011111111011110100101110
    011110111001001111111011010100101101
    011110111001001111111011110100101111
    011110111001001111111011110100101111
    011110011001001111111011110100100111
    011111111001001111111010110100101111
    101010111001001101111010110100101111
    011110111000001111111011110100101111
    011110111001001111111011110100101111
    011110111001001111111001110110101111
    
    Fitness da geracao:90
    23,23,23,21,22,24,22,24,23,21,22,23,24,24,22,22,21,22,24,22.

#### Inicializar a população
``` cpp
void inicializaPop()
{
    srand(time(NULL)); //randomizar um valor
    for(int i=0; i<TAM; i++) //percorrer o tamanho da população = 20
    {
        for(int j=0; j<COMP; j++) //percorrer o comprimento de um individuo da população = 36
        {
            pop[i][j]=rand()%2; //preenche uma célula da matriz com 0 ou 1
        }
    }
}
```

#### Fitness/Avaliação
``` cpp
void avaliaPop()
{
    for (int i=0; i <TAM; i++) //Avalia os individuos da população
    {
        fitInd[i] = 9 + pop[i][1]*pop[i][4] - pop[i][22]*pop[i][13] + pop[i][23]*pop[i][3] - pop[i][20]*pop[i][9] + pop[i][35]*pop[i][14] - pop[i][10]*pop[i][25] + pop[i][15]*pop[i][16] + pop[i][2]*pop[i][32]
                    + pop[i][27]*pop[i][18] + pop[i][11]*pop[i][33] - pop[i][30]*pop[i][31] - pop[i][21]*pop[i][24] + pop[i][34]*pop[i][26] - pop[i][28]*pop[i][6] + pop[i][7]*pop[i][12] - pop[i][5]*pop[i][8] + pop[i][17]*pop[i][19] - pop[i][0]*pop[i][29]
                    + pop[i][22]*pop[i][3] + pop[i][20]*pop[i][14] + pop[i][25]*pop[i][15] + pop[i][30]*pop[i][11] + pop[i][24]*pop[i][18] + pop[i][6]*pop[i][7] + pop[i][8]*pop[i][17] + pop[i][0]*pop[i][32];
    }
}
```
#### Torneio
``` cpp
void torneio()
{
    int k=10;
    int maior=0;
    srand(time(NULL));
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
```
#### Crossover
``` cpp
void crossover()
{
    int corte,prob;
    srand(time(NULL));
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
                pop[i][x]= pop_temp[i][x];
                pop[i+1][x]= pop_temp[i+1][x];
            }
            for (int y=corte; y < COMP; y++)
            {
                pop[i][y]= pop_temp[i+1][y];
                pop[i+1][y]= pop_temp[i][y];
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
```
#### Mutação
``` cpp
void mutacao()
{
    int prob;
    srand(time(NULL));
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
```
### Imprime População
``` cpp
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
```
#### Imprime Fitness
``` cpp
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
```
