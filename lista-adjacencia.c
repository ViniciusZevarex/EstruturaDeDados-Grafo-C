#include <stdio.h>
#include <malloc.h>


#define V 5

#define true 1
#define false 0


#define NAO_VISITADO 0
#define DESCOBERTO 1
#define CONCLUIDO 2



typedef int bool;




typedef struct s{
	struct s* prox;
	int v;
    int peso;
} NO;




typedef struct{
	int info;
    int flag;
    int via;
	NO* inicio;
} VERTICE;


typedef struct aux {
  int i;
  struct aux* prox;
} ELEMENTO, *PONT;


typedef struct {
  PONT inicio;
  PONT fim;
} FILA;






void inicializarFila(FILA* f)
{
  f->inicio = NULL;
  f->fim = NULL;
}



bool entrarNaFila(FILA* f, int i)
{
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->i = i;
  novo->prox = NULL;
  if(f->inicio==NULL) f->inicio = novo;
  else f->fim->prox = novo;
  f->fim = novo;
  return true;
}



int sairFila(FILA* f)
{
  if(f->inicio == NULL) return false;
  
  int i  = f->inicio->i;

  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  
  free(apagar);
  
  if(f->inicio == NULL) f->fim = NULL;

  return i;
}





void zerarFlags(VERTICE* g)
{
    int i;
    
    for(i = 0; i < V; i++){
        g[i].flag = 0;
    }
}







NO* buscaAresta(VERTICE* g, int i, int j, NO* ant)
{
    ant = NULL;

    NO* p = g[i - 1].inicio;

    while(p){
        if(p->v == j) return p;

        ant = p;
        p = p->prox;
    }

    return NULL;
}





bool inserirAresta(VERTICE* g, int i, int j){
    NO* ant;
    NO* atual = buscaAresta(g, i, j, ant);

    if(atual) return false;

    atual = (NO*)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i - 1].inicio;
    g[i - 1].inicio = atual;

    return true;
}





bool excluirAresta(VERTICE* g, int i, int j){
    NO* ant;
    NO* atual = buscaAresta(g,i,j,ant);

    if(!atual) return false;
    if(ant) ant->prox = atual->prox;
    else g[i - 1].inicio = atual->prox;

    free(atual);

    return true;
}





int grauDeSaida(VERTICE* g, int i){
    int count = 0;

    NO* p = g[i - 1].inicio;

    while(p){
        count++;
        p = p->prox;
    }

    return count;
}




int grauDeEntrada(VERTICE* g, int i){

    int count = 0;

    int x;
    NO* ant;

    for(x = 0; x <= V;x++){
        
        NO* p = g[x - 1].inicio;

        while(p){
            if(p->v == i){
                count++;
                p->prox;
                break; //TODO: testar esse break aqui;
            }
        }

    }

    return count;
}




bool subgrafo(VERTICE* g1, VERTICE* g2)
{
	int n1;
    int i;
    int j;

	for(n1 = 1; n1 <= V; n1++){
		NO* p1 = g1[n1 - 1].inicio;
		while(p1){
			i = n1;
			j = p1->v;


			NO* ant;
			NO* aux = buscaAresta(g2, i, j, ant);
			
            if(!aux || aux->peso != p1->peso) return false;
			
            p1 = p1->prox;
		}
	}
	return true;
}




void prof(VERTICE* g, int i)
{
    g[i - 1].flag = DESCOBERTO;

    NO* p = g[i - 1].inicio;

    while(p)
    {
        if(g[p->v - 1].flag == 0)
        {
            prof(g,p->v);
        }
        p = p->prox;
    }
    g[i - 1].flag = CONCLUIDO;
}




void existeCaminho(VERTICE* g, int v1, int v2, bool* achou)
{

    g[v1 - 1].flag = DESCOBERTO;

    if(v1 == v2)
    {
        *achou = true;
        return;
    }


    NO* p = g[v1 - 1].inicio;

    while(p)
    {
        if(g[p->v - 1].flag == NAO_VISITADO && *achou == false)
        {
            existeCaminho(g,p->v,v2, achou);
        }
        p = p->prox;
    }
    g[v1 - 1].flag = CONCLUIDO;

}





void largura(VERTICE* g,int  i)
{
    FILA* f;
    inicializarFila(f);
    zerarFlags(g);

    entrarNaFila(f, i);

    while(f->inicio)
    {
        i = sairFila(f);

        NO* p = g[i - 1].inicio;

        while(p)
        {
            if(g[p->v - 1].flag == NAO_VISITADO)
            {
                entrarNaFila(f,p->v);
                g[p->v - 1].flag = DESCOBERTO;
                g[p->v - 1].via = i;
            }
            p = p->prox;
        }
        g[i - 1].flag = CONCLUIDO;
    }



}




void exibeMatrizEsparca(VERTICE* g)
{
    int i;
    for(i = 0; i < V; i++)
    {
        NO* p = g[i].inicio;

        printf("[%i]", i + 1);

        while(p)
        {
            printf("->%i",p->v);
            p = p->prox;
        }

        printf("\n");
    }
}




int contarLacos(VERTICE* g)
{
    int i, count = 0;

    NO* p;

    for(i = 0; i < V ; i++){
        p = g[i].inicio;

        while(p)
        {   
            if( (p->v - 1) == i){
                count++;
                break;
            }
            p = p->prox;
        }
    }

    return count;
}




void removerLacos(VERTICE* g)
{
    int i;
    NO* p;  


    for(i = 0; i < V; i++)
    {
        NO* ant = NULL;
        p = g[i].inicio;

        while(p)
        {
            if((p->v - 1) == i)
            {
                if(ant == NULL) {
                    g[i].inicio = p->prox;
                }else{
                    ant->prox = p->prox;
                }
            }

            ant = p;
            p = p->prox;
        }
    }
}




void main(){

    VERTICE* g = (VERTICE*)malloc(sizeof(VERTICE)*V);

    int i;

    for(i = 0; i < V;i++)
        g[i].inicio = NULL;

    zerarFlags(g);


    if(inserirAresta(g,1,2)) printf("inserido!\n"); 
    else printf("não inserido!\n");
    // exibeMatrizEsparca(g);

    if(inserirAresta(g,1,1)) printf("inserido!\n"); 
    else printf("não inserido!\n");
    // exibeMatrizEsparca(g);

    if(inserirAresta(g,2,3)) printf("inserido!\n");
    else printf("Não inserido!\n");

    if(inserirAresta(g,2,2)) printf("inserido!\n");
    else printf("Não inserido!\n");
    // exibeMatrizEsparca(g);


    if(inserirAresta(g,1,3)) printf("inserido!\n");
    else printf("Não inserido!\n");
    // exibeMatrizEsparca(g);


    if(inserirAresta(g,1,4)) printf("inserido!\n");
    else printf("Não inserido!\n");
    // exibeMatrizEsparca(g);


    if(inserirAresta(g,4,5)) printf("inserido!\n");
    else printf("Não inserido!\n");
    // exibeMatrizEsparca(g);


    if(inserirAresta(g,5,3)) printf("inserido!\n");
    else printf("Não inserido!\n");
    // exibeMatrizEsparca(g);


    bool achou = false;


    // existeCaminho(g, 1,5,&achou);

    // printf("\n");

    exibeMatrizEsparca(g);


    printf("\n");

    // if(achou) printf("Exite!");
    // else printf("Nao exite!");

    int count = contarLacos(g);
    printf("Quantidade de lacos: %i\n", count);

    removerLacos(g);
    exibeMatrizEsparca(g);
    
    
    count = contarLacos(g);
    printf("Quantidade de lacos: %i\n", count);
}