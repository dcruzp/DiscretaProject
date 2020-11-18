#include <bits/stdc++.h>

using namespace std ;

#define Tuple pair<int,int> 
#define MAX 300043
#define llong long long 
#define INF (llong)(1e18)

vector <pair<int , Tuple > > graph [MAX] ;
vector <llong> distances (MAX);  
vector <int> last (MAX);
vector <int> answer ;   
set<pair<llong , int> >Q ; 
int n , m , k ; 

void init ()
{
    int i ; 
    for (i=0 ; i < n ; i++)
    {
        distances[i] = INF;
        last[i] = -1 ;
    }
}

void dijkstra (int str , int k ) 
{
    init(); 
    distances[str] = 0 ; 
    Q.insert(make_pair(0,str)); 

    int count = 0; 
    while (!Q.empty()&& count < k ) 
    {
        auto tmp = *Q.begin(); 
        Q.erase(Q.begin());
        int curr = tmp.second;
        if (last[curr]!=-1)
        {
            
            count = count + 1;
            answer.push_back(last[curr]); 
        }
        for (auto ady : graph[curr])
        {
            int to = ady.first ; 
            int w = ady.second.first;
            int idx = ady.second.second; 

            
            if (distances[to] > distances[curr] + w)
            {
                Q.erase(make_pair(distances[to], to));
                distances[to] = distances[curr] + w ; 
                last[to] = idx; 
                Q.insert(make_pair(distances[to],to));
            } 
        }
    }
}

int main (int argc ,char ** argv ) 
{
    cin >> n >> m >> k ; 
    int i ; 
    for (i=0 ; i < m ; i++)
    {
        int x , y , w ; 
        cin >> x >> y >> w ; 
        graph[x-1].push_back(make_pair(y-1,make_pair(w,i)));
        graph[y-1].push_back(make_pair(x-1,make_pair(w,i))); 
    }
    dijkstra(0,k);
    cout << answer.size() << endl ; 
    
    for (i =0 ; i < answer.size() ; i++)
    {
        cout << answer[i] +1 <<  " " ;  
    } 
    cout << endl; 
}
