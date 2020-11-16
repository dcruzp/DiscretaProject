#include <bits/stdc++.h> 

using namespace std ; 

#define MAX 5001 /* aqui defino la mayor cantidad de nodos que puede tener mi grafo */ 
#define Node pair <int, int> /* esto es para usarlo en la cola de prioridad para el algoritmo de dijksta*/ 
#define INF 1 << 30 /* aqui defino el infinito para obtener una cota superior de las distancias que pueden tener las aristas del grafo */ 


struct cmp /* esto es para comparar por el peso de las aristas del grafo */ 
{
    bool operator () (const Node &a, const Node &b){
        return a.second > b.second; 
    }
};

int J,B,C,N,S ; /*para leer los datos de la entrada estandar */
vector <Node> ady [MAX] ;/* este es el grafo como una lista de adyacencia */
int distanciaC [MAX]; /*la distancia de la casa de CHARLY a las demas nodos del grafo */
int distanciaN [MAX]; /*la distancia de la casa de NITO a las demas nodos del grafo */
int distanciaB [MAX]; /*la distancia de del BAR a las demas nodos del grafo */
bool visitado [MAX]; /* esto es para en le dijstra saber si se ha visitado el nodo o no */ 
priority_queue<Node , vector<Node> , cmp > Q ; /*una cola de prioridad que usa el comarador de arriba para procesar los nodos en el algoritmo de dijkstra */
set< Node > Q1 ;  

void init (int distancia []) /* esto es para inicializar los arrays que uso en el algoritmo de dijkstra */
{
    for (int i = 0; i < J; i++)
    {
        distancia[i] = INF;  /* pongo todas las distancias a infinito (un valor mayor del que toma la arista de mayor peso)*/
        visitado[i] = false; /*pongo todo los nodos como que no han sido visitados*/
    }
}

void relajacion (int actual , int adyacente , int peso , int distancia []) /*esto es para actualizar un nodo en el algoritmo de dijkstra (si llege a el por un nodo tal que la distancia  hasta ese nodo mas el peso de la arista es menor que el peso del nodo actual (el que estoy analizando))*/
{
    if (distancia[actual]+ peso < distancia[adyacente]) /* si la distancia hasta el actual mas el peso de la arista es menor que el peso del adyacente entonces actualizo el peso del adyacente*/ 
    {
        distancia[adyacente] = distancia[actual]+peso; /*la distancia en el adyacente es ahora la del actual mas la del peso de la arista*/
        Q.push(Node(adyacente, distancia[adyacente]));  /* pongo el adyacente en la cola para despues analizar los adyacentes de estos */
    }
}

void dijkstra(int inicial, int distancia []) /* algorimo de dijkstra modificado (tiene como parametros el vertice inicial y el array dendo va a modificar las ditancias en el grafo desde el vertice inicial )*/
{
    init(distancia); /* se inicializa con la funcion init el array distancia que se pasa como parametro */ 
    Q.push(Node(inicial,0)); /*se pone el vertice inicial en la cola con peso 0 */ 
    distancia[inicial]= 0 ; /* se pone la distancia del vertice inicial a cero (pq la distancia de el hacia el mismo es cero) */ 
    int actual ,adyacente , peso ; 

    while (!Q.empty()) /*mientras la cola de prioridad no este vacia */
    {
        actual = Q.top().first; /* saco el vertice que esta en el tope de la pila */
        Q.pop();        
        if (visitado[actual]) continue;  /* si el vertice ya esta visitado entonces lo saco y continuo con el proximo en la cola para ser analizado */      
        visitado[actual] = true; /* pongo el actual que estoy analizando como visitado */

        for (int i = 0; i < ady[actual].size(); ++i) 
        {
            adyacente= ady[actual][i].first;
            peso = ady [actual][i].second; 
            if (!visitado[adyacente]) /* si el adyacente que estoy analizando no ha sido visitado llamo al metodo de relajacion para actualizar su distancia */
            {
                relajacion(actual,adyacente,peso , distancia); /* metodo de relajacion para el vertice actual */ 
            }
        }        
    }  
}

void dijkstra2 (int start , int distance []) 
{
    init(distance);
    //Q1.clear();
    Q1.insert(make_pair(0,start));
    distance[start] = 0; 

    while (! Q1.empty())
    {
        Node tmp = * (Q1.begin());
        Q1.erase(Q1.begin());

        int curr = tmp.second ;
        vector <Node> :: iterator i ;
        for(i = ady[curr].begin() ; i != ady[curr].end() ; ++i)
        {
            int v = (*i).first ; 
            int weight = (*i).second;

            if (distance[curr] + weight < distance[v])
            {
                if (distance[v] < INF)
                {
                    Q1.erase(Q1.find(make_pair(distance[v] , v))); 
                } 
                distance[v] = distance[curr] + weight ; 
                Q1.insert(make_pair(distance[v],v));
                
            } 

        }
    }
}

void solucion ()
{   unsigned t0 , t1; 
    t0 = clock();  
    dijkstra(B-1,distanciaB); /* aplicar dijkstra desde el BAR */ 
    dijkstra(C-1,distanciaC); /* aplicar dijkstra desde la casa de CHARLY*/
    dijkstra(N-1,distanciaN); /* aplicar dijkstra desde la casa de NITO */ 

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
    t1 = clock () ;
    double time = (double (t1-t0)/CLOCKS_PER_SEC);
    cout << j << " " << c << " " << n << " Execution Time: " << time <<  endl ; 
}

void solucion2 ()
{   
    auto start = chrono::system_clock::now(); 
    unsigned t0 , t1; 
    t0 = clock();  
    dijkstra2(B-1,distanciaB); /* aplicar dijkstra desde el BAR */ 
    dijkstra2(C-1,distanciaC); /* aplicar dijkstra desde la casa de CHARLY*/
    dijkstra2(N-1,distanciaN); /* aplicar dijkstra desde la casa de NITO */ 

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
    t1 = clock () ;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "s" <<endl;
    double time = (double (t1-t0)/CLOCKS_PER_SEC); 
    cout << j << " " << c << " " << n << " Execution Time: " << time /1000 <<  endl ; 
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
        solucion2();

        // int i ; 
        // dijkstra2( 0 , distanciaB);
        // for (i=0 ; i < J ; i++)
        // {
        //     cout << distanciaB [i] <<  " "  ;  
        // }
        // cout <<endl ;
        // dijkstra (0,distanciaB); 
        // for (i=0 ; i < J ; i++)
        // {
        //     cout << distanciaB [i] <<  " "  ;  
        // }
        // cout << endl ;
    }    


    return 0 ;     
}