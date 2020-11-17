#include <bits/stdc++.h> 

using namespace std ; 

#define MAX 5001 /* aqui defino la mayor cantidad de nodos que puede tener mi grafo */ 
#define Node pair <int, int> /* esto es para usarlo en la cola de prioridad para el algoritmo de dijksta*/ 
#define INF 1 << 30 /* aqui defino el infinito para obtener una cota superior de las distancias que pueden tener las aristas del grafo */ 

int J,B,C,N,S ; /*para leer los datos de la entrada estandar */
vector <Node> ady [MAX] ;/* este es el grafo como una lista de adyacencia */
int distanciaC [MAX]; /*la distancia de la casa de CHARLY a las demas nodos del grafo */
int distanciaN [MAX]; /*la distancia de la casa de NITO a las demas nodos del grafo */
int distanciaB [MAX]; /*la distancia de del BAR a las demas nodos del grafo */
set< Node > Q ;   /*una cola de prioridad que usa el comarador de arriba para procesar los nodos en el algoritmo de dijkstra */

void init (int distancia []) /* esto es para inicializar los arrays que uso en el algoritmo de dijkstra */
{
    for (int i = 0; i < J; i++)
    {
        distancia[i] = INF;  /* pongo todas las distancias a infinito (un valor mayor del que toma la arista de mayor peso)*/
    }
}

void shortedPath (int start , int distance []) 
{
    init(distance);  /*aqui inicializo el array donde voy a poner las distancias */
    Q.insert(make_pair(0,start));  /*inseto el primer elemanto en la cola de prioridad con distancia 0 */
    distance[start] = 0;   /*pongo la distancia en el nodo inicial en 0 */

    while (! Q.empty())
    {
        Node tmp = * (Q.begin());  /*en tmp pongo el primer elemento del 
                                    principio de la cola (el que menor peso tiene )*/
        Q.erase(Q.begin());  /*borro el primer elemnto del conjunto*/

        int curr = tmp.second ;   /*en curr pongo el numero del nodo que voy a procesar*/
        vector <Node> :: iterator i ; /*declaro un iterador para recorrer los adyacentes */
        for(i = ady[curr].begin() ; i != ady[curr].end() ; ++i)
        {
            int v = (*i).first ;    /*en v pongo el id del vecino que voy a procesar*/
            int weight = (*i).second;  /* pongo en weight el peso del vecino*/

            if (distance[curr] + weight < distance[v])  /* si la distancia hasta  el adyacente es 
                                                        mayor que la distancia del actual mas es peso
                                                        de la arista que estoy procesando entonces actualizo  */
            {
                if (distance[v] < INF) /*si  el adyacente ya estaba en la cola entonces lo saco de la cola  */
                {
                    Q.erase(Q.find(make_pair(distance[v] , v))); 
                } 
                distance[v] = distance[curr] + weight ; /*actualizo la distancia */  
                Q.insert(make_pair(distance[v],v)); /* pongo en vertice con su nuevo peso en la cola
                                                     para ser procesado */
            } 
        }
    }
}


void solucion()
{   
    //auto start = chrono::system_clock::now(); 
    //unsigned t0 , t1; 
    //t0 = clock();


    shortedPath(B-1,distanciaB); /* aplicar dijkstra desde el BAR */ 
    shortedPath(C-1,distanciaC); /* aplicar dijkstra desde la casa de CHARLY*/
    shortedPath(N-1,distanciaN); /* aplicar dijkstra desde la casa de NITO */ 

    int distC = distanciaB[C-1]; /* esta es la menor distancia desde el BAR hasta la casa de CHARLY*/
    int distN = distanciaB[N-1]; /* esta es la menor distancia desde el BAR hasta la casa de NITO*/
    int j = 0 , c =distC , n =distN; /* j es la mayor distancia que ellos caminan juntos , c es la distancia que camina CHARLY solo y n es la distancia que camina  NITO solo */

    for (int i = 0; i < J; i++)
    {
        /* aqui por cada vertice pregunto si este es un vertice comun a algun par de caminos minimos que van del BAR a casa de NITO y a casa de CHARLY 
           respectivamente y que la distancia desde ese nodo al BAR es mayor que una anterior analizada que cumpla las mismas condiciones de estar 
           en un camino de distancia minima*/
        if (distC == distanciaB[i]+distanciaC[i] && distN == distanciaB[i] + distanciaN[i] && distanciaB[i] > j)
        {
            j = distanciaB[i];  /* actualizo la mayor distancia que caminan juntos */
            c = distanciaC[i];  /* actualizo la distancia que camina CHARLY solo */
            n = distanciaN[i];  /* actualiza la distancia que camina NITO solo */ 
        }
    }
    //t1 = clock () ;
    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed = end - start;
    //std::cout << "Elapsed time: " << elapsed.count() << "s" <<endl;
    //double time = (double (t1-t0)/CLOCKS_PER_SEC); 
    cout << j << " " << c << " " << n << endl ; 
}

int main ()
{
     
    while (true)
    {
        cin >> J >> B >> C >> N >> S ; 
        if ( J == -1 && B ==-1 && C ==-1 && N ==-1 && S==-1)break; /* si todas la entradas fueron -1 entonces salgo del ciclo */

        int E1 , E2 , L; /* variables temporales par obtener las aristas y sus respectivos pesos */

        while (S-->0) /*leo todas las entradas  que me da la informacion de las aristas */
        {
            cin >> E1 >> E2 >> L; 
            ady[E1-1].push_back(Node(E2-1,L));
            ady[E2-1].push_back(Node(E1-1,L));
        }       

        solucion(); /* calcular la solucion al problema e imprimir la respuesta */ 
    }    


    return 0 ;     
}