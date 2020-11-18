#include <bits/stdc++.h>

using namespace std ; 

int n , a[1000] ;  /*el numero de vertices de grafo y el array que me dice el 
                    mayor degree que puede tener cada vertices*/
vector <int> Ones ; /* para saber cuales vertices tienen degree 1 */

void solution () 
{
    int i,  t  , d , l ,s =0  ; 
    for ( i =0 ; i < n ; i++) /*sumo todos los degree del array a */ 
    {
        s = s + a[i]; 
    }

    if (s < 2*(n-1)) /* si no se puede armar un grafo conexo entonces imprimo NO*/ 
    {
        cout << "NO" << endl ; 
        return; 
    }

    for (i =0 ; i< n ; i++)
    {
        if (a[i] == 1 )
        {
            a[i] = 0; 
            Ones.push_back(i);
        }
    }


    t = Ones.size(); 
    d = (n-t) -1 + min(2,t) ; /* el diametro que va a tener el grafo para armar */ 

    cout << "YES" << " " << d << endl << n-1 << endl ; 

    l = -1 ; 
    if (!Ones.empty())
    {
        l = Ones.back(); 
        Ones.pop_back(); 
    }

    for (i = 0 ; i< n ; i++)
    {
        if (a[i] > 1 ) 
        {
            if (l !=-1)
            {
                a[l] = a[l] - 1;
                a[i] = a[i] - 1;
                cout << l +1 << " " << i+1 << endl ;   
            }
            l = i ; 
        }
    }

    for (i = n-1 ; i >=0 ; --i )
    {
        while (!Ones.empty() && a[i] > 0 ) 
        {
            a[i] = a[i] - 1 ; 
            cout << i+1 << " " << Ones.back() + 1 << endl ; 
            Ones.pop_back();   
        }
        
    }    
}

int main () 
{
    cin >> n ;
    int i; 
    for (i=0 ; i < n ; i++)
    {
        cin >> a[i] ;  
    } 
    solution() ;
}