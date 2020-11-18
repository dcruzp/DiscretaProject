graph = []
visited = [] 
head = []
tail = [] 
n,m,h,t,i = 0,0,0,0,0

# esto es para determina los  
# vertices en comun 
def vertexcommun (u,v):
    count = 0 
    i=0
    while i < len(graph[u]):
        a = graph[u][i]
        i=i+1
        if a == v : continue 
        visited[a] = True 
    i=0
    while i < len(graph[v]):
        a = graph[v][i]
        i= i+1
        if visited[a]:
            count = count +1 
    return count 

# esto es prara poner todos los vertices de nuevo 
# como que no ha side visitados
def restorevisitedarray (u):
    i=0
    while i < len(graph[u]):
        a = graph[u][i]
        i = i + 1 
        visited [a] = False

#esto es para determinar los subconjuntos 
#acorde con el caso 2
def buildSet1 (u,v):
    deg_u = len (graph[u]) # degree del vertuce u 
    deg_v = len (graph[v]) # degree del vertuce v

    #determinar el tail 
    i=0
    while i < deg_v:
        if len(tail) == t : break 
        a = graph[v][i]
        i = i + 1 
        if a == u : continue 
        visited[a] = True 
        tail.append(a)

    #determinar el head
    i=0
    while i < deg_u:
        if len(head) == h : break
        a = graph[u][i]
        i = i +1 
        if a == v  or visited[a]: continue 
        head.append(a)

#esto es para determinar los subconjuntos 
#acorde con el otro subcaso del caso 2
def buildSet2 (u,v):
    deg_u = len (graph[u]) # degree del vertuce u 
    deg_v = len (graph[v]) # degree del vertuce v
    i=0 
    while i  < deg_u:
        if len(head) == h :break
        a = graph[u][i]
        i = i + 1 
        if a == v : continue 
        visited[a]= True 
        head.append(a)
    i=0 
    while i < deg_v:
        if len(tail) == t : break
        a= graph[v][i]
        i = i+1
        if a == u or visited[a] : continue
        tail.append(a)

#esto es para determinar los subconjuntos 
#acorde con el caso 3
def buildSet3 (u,v , commun):
    deg_u = len (graph[u]) # degree del vertuce u 
    deg_v = len (graph[v]) # degree del vertuce v

    count = 0 
    i=0
    while i < deg_v:
        if len(tail) == t : break 
        a = graph[v][i]
        i = i + 1
        if visited[a] and count < t - (deg_v-1 -commun):    # para no escoger mas de los vertices que tiene en comun necesarios 
                                                            # o sea no escoger de mas vertices que sean comunas a la hora de 
                                                            # formar el tail  
            count = count + 1
            visited[a] = False 
            tail.append(a)
        elif visited[a] == False  and a != u :
            tail.append(a)
    i=0 
    while i < deg_u:
        if len(head)==h : break 
        a = graph[u][i]
        i=i+1
        if  visited[a] == False : continue 
        head.append(a)  

def checkEdge (u,v):
    deg_u = len (graph[u])  # degree del vertice u 
    deg_v = len (graph[v])  # degree del vertice v
    
    #Caso 1 
    if deg_u < h+1 or deg_v < t+1:
        return False 

    #Caso 2
    if deg_u >= h+t+1:
        buildSet1(u,v)
        return True
    if deg_v > h+t+1:
        buildSet2(u,v)
        return True 
    
    #Caso 3 
    commun = vertexcommun(u,v)  #verties adyacentes a u y a v a la vez 
    ind_u = deg_u -1 - commun   #vertices edyacentes a u que no son adyacentes a v
    ind_v = deg_v -1 - commun   #vertices edyacentes a v que no son adyacentes a u

    if h - ind_u + t - ind_v > commun:  #no hay vertices en comun suficientes 
                                        #para armar los dos subconjuntos  
        restorevisitedarray(u)
        return False 

    buildSet3(u,v ,commun)
    return True 

# esto es para inicializar el grafo 
def init (n):
    i =0 ; 
    while i < n:
        graph.append([])
        visited.append(False)
        i= i+1  

def printsolution (u,v):
    print("YES")
    print (str(u+1) + " " + str(v+1))
    for item in head:
        print (str (item+1) , end = ' ')
    print()
    for item in tail:
        print(str(item+1),end = ' ')
    print()

def solution ():
    for item in edges :  # recorre todas las aristas 
        u , v = item[0] , item [1]

        if checkEdge(u,v):
            printsolution(u,v)
            return 
        elif checkEdge (v,u):
            printsolution(v,u)
            return 
    print("NO")


if __name__ == '__main__':
    
    line = input().split()
    n = int(line[0])
    m = int(line[1])
    h = int(line[2])
    t = int(line[3])

    edges = [] 

    init(n)

    i=0
    while i < m:
        line = input().split()
        a , b = int (line[0]) , int (line[1])
        edges.append((a-1,b-1))   
        graph[a-1].append(b-1)
        graph[b-1].append(a-1)  
        i = i+1 
    
    solution()