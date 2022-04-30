#include <stdio.h>
#include <malloc.h>


#define V 5


#define true 1
#define false 0


typedef int bool;

void inicializaMatriz(int** m)
{

    int i, j;

    for(i = 0; i < V; i++)
    {
        m[i] = malloc( V * sizeof (int));
        for (j = 0; j < V; j++)
        {
            m[i][j] = 0;
        }
    }
}





bool inserirAresta(int** m, int i, int j)
{
    if(m[i-1][j-1] == 0)
    {
        m[i-1][j-1] = 1;
        return true;
    }

    return false;
}


bool removerAresta(int** m, int i, int j)
{
    if(m[i-1][j-1] == 1)
    {
        m[i-1][j-1] = 0;
        return true;
    }

    return false;
}




int contarLacos(int** m)
{

    int i, count = 0;

    for(i = 0;i<V;i++){
        if(m[i][i] == 1) count++;
    }   

    return count;
}




void exibirMatrizAdjacencia(int** m)
{
    int i, j;

    for(i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            printf("%i  ", m[i][j]);
        }
        printf("\n");
    }
}






int main()
{

    int **m = malloc( V * sizeof (int *));
    inicializaMatriz(m);
    // exibirMatrizAdjacencia(m);

    inserirAresta(m,1,2);
    inserirAresta(m,1,1);
    inserirAresta(m,2,3);
    inserirAresta(m,2,2);
    inserirAresta(m,2,4);
    inserirAresta(m,3,1);
    inserirAresta(m,4,1);

    exibirMatrizAdjacencia(m);

    int countLacos = contarLacos(m);

    printf("Numero de lacos: %i", countLacos);


    return 0;
}