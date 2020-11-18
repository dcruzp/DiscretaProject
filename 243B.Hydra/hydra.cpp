#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std ; 
#define MAX 100000
#define TUPLE pair <int,int> 

vector<int> graph [MAX];
bool visited [MAX] ;  
vector <TUPLE> aristas;
vector <int> tail , head ; 
int n,m,h,t ; 

int vertexcomun (int u , int v )
{
    int commun = 0 ; 
    int i , a ; 
    for (i=0 ; i< graph[u].size() ; i++)
    {
        a = graph [u][i];
        if (a == v)continue; 
        visited[a] = true ;  
    }
    for (i=0 ;i<graph[v].size() ; i++)
    {
        a = graph[v][i];
        if (visited[a])
        {
            commun = commun + 1; 
        }
    }
    return commun;
} 

void restorevisitedarray (int u )
{
    int i , a ;
    for (i =0 ; i< graph[u].size() ; i++)
    {
        a = graph[u][i] ; 
        visited[a] = false;
    }
} 


void buildSets1 (int u , int v)
{
    int deg_u = graph[u].size();  /* esto es el degree del vertice u*/
    int deg_v = graph[v].size();  /* esto es el degree del vertice v*/
    int i , a ;  /*varaibles necesarias */ 
    for (i=0 ; i < deg_v ; i++)
    {
        if (tail.size() == t ) break;  /* si el conjunto tail ya tiene todos los 
                                        elementos entonces dejo de anadirle elementos /*/
        a = graph[v][i]; 
        if (a == u ) continue ;     /*si el vertice actual es u entonces no me interesa marcarlo */ 
        visited[a] = true ;  /*marco el vertice como visitado */
        tail.push_back (a) ;   /*lo anado a la cola */ 
    }
    for (i=0 ; i < deg_u ; i++)
    {
        if (head.size() == h )break; /* si el conjunto tail ya tiene todos los 
                                        elementos entonces dejo de anadirle elementos /*/
        a = graph[u][i] ; 
        if (visited[a] || a == v ) /*si el vertice actual es uno visitado (que ya se escogio para el tail )
                                    o es el vertice v entonces no me interesa para formar parte del head 
                                    por lo que continuo buscando a otros vertices */ 
        {
            continue ; 
        }
        head.push_back(a);  /* si llege aqu\'i entonces anado el vertice al conjunto head */ 
    }
}

void buildSets2 (int u , int v)
{
    int deg_u = graph[u].size();  /* esto es el degree del vertice u*/
    int deg_v = graph[v].size();  /* esto es el degree del vertice v*/
    int i , a ; 
    for (i=0 ; i < deg_u ; i++)
    {
        if (head.size() ==h)break; 
        a = graph[u][i]; 
        if (a == v ) continue ; 
        visited[a] = true ; 
        head.push_back (a) ; 
    }
    for (i=0 ; i < deg_v ; i++)
    {
        if (tail.size() == t) break ;
        a = graph[v][i] ; 
        if (visited[a] || a == u ) continue ; 
        tail.push_back(a); 
    }
}


void buildSets3 (int u , int v ,int commun ) 
{
    int deg_u = graph[u].size();    /* esto es el degree del vertice u*/
    int deg_v = graph[v].size();    /* esto es el degree del vertice v*/
    int i , a ; 
    int count = 0 ; 
    for (i=0 ; i<deg_v ; i++)
    {
        if (tail.size() == t ) break; 
        a = graph[v][i]; 
        if (visited[a] && count < t - (deg_v-1 -commun) ) /*aqui si esta visitado el vertice entonces compruebo de que 
                                                            si lo voy a escoger no sea un vertice escogido de forma inecesaria 
                                                            porque si esta visitado es que es commun y solo quiero escoger la cantidad
                                                            de vertices en comun necesarias (y no mas) de los vertice que son comunes*/
        {
            count = count + 1 ; 
            visited[a] = false ; 
            tail.push_back(a);
        }
        else if (!visited[a] && a != u ) /*si no esta visitado y el vertice es distunto de u entonces lo anado al conjunto tail */
        {
            tail.push_back(a);
        }
    }
    for (i=0 ; i<deg_u ; i++)
    {
        if (head.size() == h) break; 
        a = graph[u][i];
        if (!visited[a]) continue;  /*minetras no este visitado , no me interesa */
        head.push_back(a);
    }
}

int checkEdge (int u , int v ) 
{
    int deg_u = graph[u].size();    /*cantidad de adyacentes que tiene el vertice u */
    int deg_v = graph[v].size();    /*cantidad de adyacentes que tiene el vertice V */
    int count , i , a , ind_u , ind_v , commun;  /*variables auxiliares */ 


    /*CASO 1 -> No puede existir un Hydra con estas 
    condicioes entonces el m\'etodo retorna false*/
    if (deg_u < h+1 || deg_v < t+1)
    {
        return 0 ; 
    }

    /*CASO2 -> Es posible armar un Hydra*/
    if (deg_u >= h+t+1)
    {
        buildSets1(u,v);    /*este metodo primero escoge los vertices del 
                            conjunto tail y despues los del head*/

        return 1 ;          /*el metodo termina y retorna verdadero */
    }
    if (deg_v >= h+t+1)
    {
        buildSets2(u,v);   /*este metodo primero escoge los vertices del 
                            conjunto head y despues los del tail*/

        return 1 ;         /*el metodo termina y retorna verdadero */
    }
   

    /*CASO 3 -> Hay que ver si es posible armar un Hydra */

    commun = vertexcomun(u,v);  /*cantidad de vertices que hay en comun 
                                      (que son adyacentes a u y adyacentes a v )*/
    ind_u = deg_u -1 -commun ;  /*cantidad de vertices adyacentes a u que no 
                                      son adyacentes a v */
    ind_v = deg_v -1 -commun ;  /*cantidad de vertices adyacentes a v que no 
                                      son adyacentes a u */
 
    if ( (h- ind_u + t - ind_v ) > commun) /*si la cantidad de vertices en comun no 
                                            son suficientes para poder armar los conjuntos 
                                            head y tail de forma tal que estos sean independientes*/
    {
        restorevisitedarray(u);   /*vuelvo a poner todos los adyacentes de u como no visitados */
        return 0 ;       /* el metodo retorna falso porque no es posible formar los conjuntos que 
                        estamos buscando */
    }

    buildSets3(u,v,commun); /*este metodo escoge los conjuntos head y tail */
    return 1 ;  /*retorna verdadero */ 
}

void printHydra (int u , int v) /* aqui imprimo la salida en caso de que exista un Hydra */ 
{
    cout << "YES" << endl; 
    cout << u + 1 << " " << v + 1  <<endl;
    int ih , it; 
    for (ih = 0 ; ih < head.size() ; ih ++)
    {
        cout << head[ih] + 1 << " ";
    } 
    cout << endl;
    for (it = 0; it < tail.size() ; it ++)
    {
        cout <<tail[it] + 1 << " "; 
    }
    cout << endl ;
} 

void solution ()
{
    int i , u , v ; 
   
    for (i=0 ; i < aristas.size(); i++) /*recorro todas las aristas del grafo */
    {
        u = aristas[i].first ;
        v = aristas[i].second;

        if (checkEdge(u,v)) /* si en la arista u-v se pude armar el hydra entonces imprimo la solucion */
        {
            printHydra(u,v);
            return ; 
        }
        else if (checkEdge(v,u)) /* si en la arista v-u se pude armar el hydra entonces imprimo la solucion */
        {
            printHydra(v,u);
            return ;
        }
    }
    cout << "NO" <<endl ; 
}

int main () {
    cin >> n >> m >> h >> t ;
    int a , b , i ;  

    i=0 ;
    while (i++ < m  )
    {
        cin >> a >> b ; 
        aristas.push_back(TUPLE(a-1,b-1));
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }
    solution () ;
    return 0 ; 
}