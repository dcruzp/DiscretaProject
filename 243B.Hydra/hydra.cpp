#include <stdio.h>
#include <iostream>
#include <vector> 

using namespace std ; 
#define MAX 10^5
#define TUPLE pair <int,int> 

vector<int> graph [MAX];
bool visited [MAX] ;  
vector <TUPLE> aristas;
vector <int> tail , head ; 


int n,m,h,t ; 


void solution ()
{   
    int i , j , u , v , a , deg_u , deg_v , count , comun ,ind_u , ind_v ; 
    for(i=0 ; i<m ; i++)
    {
        TUPLE e = aristas[i];
        u = e.first ;
        v = e.second ; 
        deg_u = graph[u].size() ;
        deg_v = graph[v].size();


        if ( (deg_u < h+1 | deg_v < t + 1) && (deg_u < t+1 | deg_v < h+1))
            continue ; 

        if (deg_u >= h+t+1) 
        {
            count = 0; 
            for (j =0 ; j <= deg_v ; j++)
            {
                a = graph[v][j]; 
                if (a == u)
                {
                    continue;
                }
                visited[a] = true ;
                tail.push_back(a);
                count = count + 1 ; 
                if (count >= t )
                {
                    break ; 
                }
            }
            count = 0 ; 
            for (j=0 ; j<= deg_u ; j++)
            {
                a = graph[u][j]; 
                if (a == v)
                {
                    continue ; 
                }
                visited[a] = true ; 
                head.push_back(a);
                count = count + 1 ; 
                if (count >= h)
                {
                    break; 
                }
            }
        }
        if (deg_v >= h+t+1)
        {
            count = 0 ; 
            for (j=0 ; j<deg_u ; j++)
            {
                a = graph[u][j];
                if (a == v)
                {
                    continue ; 
                }
                visited[a] = true ; 
                tail.push_back(a);
                count = count + 1 ; 
                if (count >= t )
                {
                    break; 
                }
            }
            count = 0 ; 
            for (j=0 ; j < deg_v ; j++)
            {
                a = graph[v][j]; 
                if (a== u)
                {
                    continue;
                }
                visited[a] = true ; 
                head.push_back(a);
                count = count + 1 ;
                if (count >= h )
                {
                    break; 
                }
            }
        }

        for (j=0 ; j<deg_u ; j++)
        {
            a = graph[u][j];
            if (a == v)
            {
                continue ;
            }
            visited[a] = true ; 
        }
        for (j=0 ; j<deg_v ; j++)
        {
            a = graph[v][j];
            if (a == u)
            {
                continue;
            }
            if (visited[a])
            {
                comun = comun +1 ;
            }
              
        }

        ind_u = deg_u - comun -1; 
        ind_v = deg_v - comun -1; 

        if (deg_u >= h+1 && deg_v >=t+1)
        {
            if (h - ind_u + t -ind_v > comun)
                continue ;


            int select_commun = 0 ; 
            for (j=0 ; j < deg_v ; j++)
            {
                if (tail.size() >= t )
                {
                    break; 
                }
                a = graph[v][j];
                if (visited[a])
                {
                    if (select_commun < t - ind_v )
                    {
                        tail.push_back(a);
                        visited[a] = false; 
                        select_commun = select_commun + 1 ;
                    }
                }
                else
                {
                    tail.push_back(a);
                }
            } 
            for (j=0 ; j < deg_u ; j++)
            {
                if (head.size() >= t)
                {
                    break; 
                }
                a = graph[u][j];
                if (visited[a])
                {
                    head.push_back(a);
                }
            }          

        }



          
    } 
} 


int shortsolution (int u , int v ) 
{
    int deg_u = graph[u].size(); 
    int deg_v = graph[v].size();
    int count , i , a ; 

    if (deg_u < h+1 || deg_v < t+1)
    {
        return 0 ; 
    }
    if (deg_u >= h+t+1)
    {
        count = 0; 
        for (i=0 ; i < deg_v ; i++)
        {
            a = graph[v][i]; 
            if (a == u ) 
            {
                continue ; 
            }
            visited[a] = true ; 
            count = count + 1 ; 
            tail.push_back (a) ; 
            if (count >= t )
            {
                break ; 
            }
        }
        count =0 ; 
        for (i=0 ; i < deg_u ; i++)
        {
            a = graph[u][i] ; 
            if (visited[a] || a == v ) 
            {
                continue ; 
            }
            count = count + 1 ; 
            head.push_back(a); 
            if (count >= h )
            {
                break ; 
            }
        }
        return 1 ; 
    }
    if (deg_v >= h+t+1)
    {
        count = 0; 
        for (i=0 ; i < deg_u ; i++)
        {
            a = graph[u][i]; 
            if (a == v ) 
            {
                continue ; 
            }
            visited[a] = true ; 
            count = count + 1 ; 
            head.push_back (a) ; 
            if (count >= h )
            {
                break ; 
            }
        }
        count =0 ; 
        for (i=0 ; i < deg_v ; i++)
        {
            a = graph[v][i] ; 
            if (visited[a] || a == u ) 
            {
                continue ; 
            }
            count = count + 1 ; 
            tail.push_back(a); 
            if (count >= t )
            {
                break ; 
            }
        }
        return 1 ; 
    }
    int communvertex = 0 ; 

    for (i=0 ; i< deg_u ; i++)
    {
        a = graph [u][i];
        if (a == v)
        {
            continue ; 
        }
        visited[a] = true ;  
    }
    for (i=0 ;i<deg_v ; i++)
    {
        a = graph[v][i];
        if (visited[a])
        {
            communvertex = communvertex + 1; 
        }
    }

    if ( (h-(deg_u -1 -communvertex) + t - (deg_v-1 - communvertex)) > communvertex)
    {
        for (i =0 ; i< deg_u ; i++)
        {
            a = graph[u][i] ; 
            visited[a] = false;
        }
        return 0 ; 

    }

    int countcommun = 0 ; 

    for (i=0 ; i<deg_v ; i++)
    {
        
        if (tail.size() == t )
        {
            break; 
        }
        a = graph[v][i]; 
        if (visited[a] && countcommun < t - (deg_v -communvertex) )
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
        if (head.size() == h)
        {
            break; 
        }
        a = graph[u][i];
        if (!visited[a])
        {
            continue; 
        }
        else 
        {
            head.push_back(a);
        }
    }
    return 1 ; 
}

int main () {
    cin >> n >> m >> h >> t ;
    int a , b , i , j ;  

    i=0 ;
    while (i++ < m  )
    {
        cin >> a >> b ; 
        aristas.push_back(TUPLE(a,b));
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }
    
    int u , v ; 
    for (u=0 ; u< n ; u++)
    {
        for ( j = 0 ; j < graph[u].size() ; j++ )
        {
            v = graph[u][j];
            if (shortsolution(u,v))
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
                return 0 ; 
            }
        }
    }
    cout << "YES" <<endl ; 
    return 0 ; 
}