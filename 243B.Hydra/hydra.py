graph = []
visited = [] 
head = []
tail = [] 
n,m,h,t,i = 0,0,0,0,0

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

def restorevisitedarray (u):
    i=0
    while i < len(graph[u]):
        a = graph[u][i]
        i = i + 1 
        visited [a] = False

def solution (u,v):
    deg_u = len (graph[u])
    deg_v = len (graph[v])
    
    if deg_u < h+1 or deg_v < t+1:
        return False 

    if deg_u >= h+t+1:
        i=0
        while i < deg_v:
            if len(tail) == t : break 
            a = graph[v][i]
            i = i + 1 
            if a == u : continue 
            visited[a] = True 
            tail.append(a)
        i=0
        while i < deg_u:
            if len(head) == h : break
            a = graph[u][i]
            i = i +1 
            if a == v  or visited[a]: continue 
            head.append(a)
        return True

    if deg_v > h+t+1:
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
        return True 
        
    communvertex = vertexcommun(u,v)
    ind_u = deg_u -1 - communvertex
    ind_v = deg_v -1 - communvertex

    if h - ind_u + t - ind_v > communvertex:
        restorevisitedarray(u)
        return False 

    countcommun = 0 
    i=0
    while i < deg_v:
        if len(tail) == t : break 
        a = graph[v][i]
        i = i + 1
        if visited[a] and countcommun < t - ind_v:
            countcommun = countcommun + 1
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
    return True 


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
    
    flag = False
    for item in edges :
        u , v = item[0] , item [1]

        if solution(u,v):
            printsolution(u,v)
            flag = True
            break 
        elif solution(v,u):
            printsolution(v,u)
            flag = True
            break 

    if not flag : 
        print("NO")

        

    
