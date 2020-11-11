
class Vertex (object):    # this class is used tu represent a vertex an her neighbors

    def __init__(self,n):
        self.name = n   # vertex 
        self.neighbor = list() # list of vertex that are its neighbors

    def addneighbor (self , v ):  # this is to add neighbors to the list
        if v not in self.neighbor:  
            self.neighbor.append(v)
            self.neighbor.sort() 


class Graph (object): # this represent the graph 
    vertices = {}  

    def addvertex (self , vertex ):
        if isinstance(vertex,Vertex):
            self.vertices[vertex.name] = vertex
            return True 
        else:
            return False 


    def addedge (self ,u , v):  #this is 
        if u in self.vertices and v in self.vertices:
            self.vertices[u].addneighbor(v)
            self.vertices[v].addneighbor(u)
            return True
        else:
            return False 



    def printGraph (self):  # this should be printed the graph 
        for key in sorted(list(self.vertices.keys())):
            print( str(key) + ' ' + str( self.vertices[key].neighbor ) )
           


if __name__ == '__main__':
    g = Graph() 

    for i in range (1,6):
        g.addvertex(Vertex(i))

    bordes = ['53','54','31','35','41','42','45','12','13','14','21','24']

    for borde in bordes:
        g.addedge(int(borde[:1]), int (borde[1:]))
       
    g.printGraph()

    