
try:
    import Queue as queue
except ImportError:
    import queue 


class Vertice: 
    def __init__(self ,clave):
        self.id = clave 
        self.conectadoA = {}

    def agregarVecino (self, vecino , ponderacion = 0 , index =-1 ):
        self.conectadoA [vecino] = (ponderacion , index )

    def __str__(self):
        return str(self.id) + ' conectadoA: ' + str([x.id for x in self.conectadoA])

    def obtenerConexiones (self):
        return self.conectadoA.keys()

    def obtenerId (self):
        return self.id 

    def obtenerPonderacion (self , vecino ):
        return self.conectadoA[vecino][0]

    def obtenerIndex (self , vecino) :
        return self.conectadoA[vecino][1] 


class  Grafo:
    def __init__(self):
        self.listadeVertices = {} 
        self.numVertices = 0 

    def agregarVertice (self, clave):
        self.numVertices = self.numVertices + 1 
        nuevoVertice = Vertice (clave) 
        self.listadeVertices[clave] = nuevoVertice
        return nuevoVertice

    def obtenerVertice (self,n):
        if n in self.listadeVertices:
            return self.listadeVertices[n]
        else:
            return None

    def __contains__ (self , n):
        return n in self.listadeVertices

    def agregarArista (self , de , a , costo = 0 , index=-1):
        if de not  in self.listadeVertices:
            nv = self.agregarVertice (de) 
        if a not in self.listadeVertices:
            nv = self.agregarVertice (a) 
        self.listadeVertices[de].agregarVecino(self.listadeVertices[a] , costo , index ) 

    def obtenerVertices (self):
        return self.listadeVertices.keys() 

    def __iter__(self):
        return iter (self.listadeVertices.values())  


g = Grafo() 
distances  = []
visited = [] 
last = [] 
answer = [] 
n,m,k = 0 , 0 ,0  

priority_queue = queue.PriorityQueue()

def init ():
    for i in range(n):
        distances.append(1e18)
        last.append(-1)
        visited.append(False) 


def dijkstra (str , k):
    init()
    distances[str] = 0; 
    priority_queue.put((0,str))

    count =0 

    while not priority_queue.empty() and count < k :
        top = priority_queue.get()
        actual = top[1]
        vertice_actual = g.obtenerVertice(actual)
        if visited[actual]: continue 
        visited[actual] = True

        if last[actual] != -1 :
            count = count + 1
            answer.append(last[actual]) 
        for adyacente in vertice_actual.obtenerConexiones():
            peso = vertice_actual.obtenerPonderacion(adyacente)
            index = vertice_actual.obtenerIndex(adyacente) 

            id_adyacent = adyacente.obtenerId()
            if not visited[id_adyacent]:
                if distances[actual] + peso < distances[id_adyacent]:
                    distances[id_adyacent] = distances[actual] + peso 
                    priority_queue.put((distances[id_adyacent],id_adyacent))
                    last[id_adyacent] = index;  


if __name__ == '__main__':
    line  = str(input()).split()
        
    n= int(line[0])
    m= int(line[1])
    k= int(line[2])
  
    for v in range (n):
        g.agregarVertice(v)

    for i in range (m):
        line  = str(input()).split()
        x , y , w = int(line[0]) , int(line[1]) , int(line[2])
        g.agregarArista(x-1,y-1,w,i)
        g.agregarArista(y-1,x-1,w,i) 

    dijkstra(0,k)
    
    print(len(answer))

    for item in answer :
        print (item +1 , end = " ")
    print() 


