
try:
    import Queue as queue
except ImportError:
    import queue 


class Vertice: 
    def __init__(self ,clave):
        self.id = clave 
        self.conectadoA = {}

    def agregarVecino (self, vecino , ponderacion = 0):
        self.conectadoA [vecino] = ponderacion 

    def __str__(self):
        return str(self.id) + ' conectadoA: ' + str([x.id for x in self.conectadoA])

    def obtenerConexiones (self):
        return self.conectadoA.keys()

    def obtenerId (self):
        return self.id 

    def obtenerPonderacion (self , vecino ):
        return self.conectadoA[vecino]


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

    def agregarArista (self , de , a , costo = 0):
        if de not  in self.listadeVertices:
            nv = self.agregarVertice (de) 
        if a not in self.listadeVertices:
            nv = self.agregarVertice (a) 
        self.listadeVertices[de].agregarVecino(self.listadeVertices[a] , costo) 

    def obtenerVertices (self):
        return self.listadeVertices.keys() 

    def __iter__(self):
        return iter (self.listadeVertices.values())  


priority_queue = queue.PriorityQueue()


MAX = 5001
INF = 1<<30 


g = Grafo() 
distanciaC = [] 
distanciaN = [] 
distanciaB = [] 
visitado = [] 
J,B,C,N,S = 0,0,0,0,0

def init  (distancia ):
    visitado.clear()
    i = 0 
    while i < MAX : 
        distancia.append (INF) 
        visitado.append (False) 
        i = i + 1 

def relajacion (actual , adyacente , peso , distancia):
    if distancia[actual] + peso < distancia[adyacente]:
        distancia[adyacente] = distancia[actual] + peso 
        priority_queue.put((distancia[adyacente],adyacente))


def dijkstra (inicial ,distancia):
    init(distancia)
    distancia[inicial] = 0
    priority_queue.put((0,inicial))
    
    while not priority_queue.empty():
        top = priority_queue.get()
        actual = top[1]
        vertice_actual = g.obtenerVertice(actual)
        if visitado[actual]: continue 
        visitado[actual] = True

        for adyacente in vertice_actual.obtenerConexiones():
            peso = vertice_actual.obtenerPonderacion(adyacente)

            if not visitado[adyacente.obtenerId()]:
                relajacion (actual , adyacente.obtenerId() , peso , distancia)       


def solucion ():
    distC = distanciaB[C-1] 
    distN = distanciaB[N-1]
    j = 0 
    c = distC
    n = distN

    for i in range (J) :
        if distC == distanciaB[i] + distanciaC[i] and distN == distanciaB[i] + distanciaN[i] and distanciaB[i] > j :
            j = distanciaB[i]
            c = distanciaC[i]
            n = distanciaN[i] 

    print (str (j) + ' ' + str (c) + ' ' +str(n))


if __name__ == '__main__':
    
    while True :
        line  = str(input()).split()
        
        J= int(line[0])
        B= int(line[1])
        C= int(line[2])
        N= int(line[3])
        S= int(line[4])

        if J == -1 and B == -1 and C ==-1 and N ==-1 and S ==-1:
            break 


        for v in range (J):
            g.agregarVertice(v)

        i=0
        while(i< S):
            line = str(input()).split()
            E1 ,E2 ,L = int(line[0]) , int (line [1]) , int (line[2])
            g.agregarArista(E1-1,E2-1,L)
            g.agregarArista(E2-1,E1-1,L)
            i = i + 1
        
        #for v in g : 
        #    for w in v.obtenerConexiones():
        #        print ( "( %s , %s , %s )" % (v.obtenerId()+1 , w.obtenerId()+1 , v.obtenerPonderacion(w)))
        
        dijkstra(B-1,distanciaB)
        dijkstra(C-1,distanciaC)
        dijkstra(N-1,distanciaN)

        solucion() 