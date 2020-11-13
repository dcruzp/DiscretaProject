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
    int communvertex = 0 ; 
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
            communvertex = communvertex + 1; 
        }
    }
    return communvertex;
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

int shortsolution (int u , int v ) 
{
    int deg_u = graph[u].size(); 
    int deg_v = graph[v].size();
    int count , i , a , communvertex; 

    if (deg_u < h+1 || deg_v < t+1)
    {
        return 0 ; 
    }



    if (deg_u >= h+t+1)
    {
        for (i=0 ; i < deg_v ; i++)
        {
            if (tail.size() == t ) break; 
            a = graph[v][i]; 
            if (a == u ) continue ;
            visited[a] = true ; 
            tail.push_back (a) ; 
        }
        for (i=0 ; i < deg_u ; i++)
        {
            if (head.size() == h )break;
            a = graph[u][i] ; 
            if (visited[a] || a == v ) 
            {
                continue ; 
            }
            head.push_back(a); 
        }
        return 1 ; 
    }
    if (deg_v >= h+t+1)
    {
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
        return 1 ; 
    }
   
    communvertex = vertexcomun(u,v);

    if ( (h-(deg_u -1 -communvertex) + t - (deg_v-1 - communvertex)) > communvertex)
    {
        restorevisitedarray(u);
        return 0 ; 
    }

    int countcommun = 0 ; 

    for (i=0 ; i<deg_v ; i++)
    {
        if (tail.size() == t ) break; 
        a = graph[v][i]; 
        if (visited[a] && countcommun < t - (deg_v-1 -communvertex) )
        {
            countcommun = countcommun + 1 ; 
            visited[a] = false ; 
            tail.push_back(a);
        }
        else if (!visited[a] && a != u )
        {
            tail.push_back(a);
        }
    }
    for (i=0 ; i<deg_u ; i++)
    {
        if (head.size() == h) break; 
        a = graph[u][i];
        if (!visited[a]) continue; 
        head.push_back(a);
    }
    return 1 ; 
}

void printsolution (int u , int v)
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
    
    int u , v ; 
   
    for (i=0 ; i < aristas.size(); i++)
    {
        u = aristas[i].first ;
        v = aristas[i].second;

        if (shortsolution(u,v))
        {
            printsolution(u,v);
            return 0 ; 
        }
        else if (shortsolution(v,u))
        {
            printsolution(v,u);
            return 0 ;
        }
    }

    

    cout << "NO" <<endl ; 
    return 0 ; 
}