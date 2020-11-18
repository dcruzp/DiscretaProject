a = []  # degree maximo para cada vertice 
n = 0  # la cantidad de vertices
Ones = []  # array de index con veritces con degree 1 


def solution ():
    s = 0 
    for item in a :  # esto es para contar la suma de todos los degree  
        s = s + item 
    
    if s < 2*(n-1) :# si no hay la cantidad minima requerida para armar un grafo conexo 
                    # entonces imprimo NO
        print("NO")
        return
    
    for i in range(n): # guardo los indices de los vertices cuyo degree es 1 
        if a[i] == 1 :
            a[i] = 0 
            Ones.append(i)

    t = len(Ones)
    d = (n-t) - 1 + min(2,t)# el diametro va a ser el tamano del arbol que se pueda 
                            #formar con los conjunto de vertices con degree mayor que 1 
    print("YES " + str(d) + "\n" + str(n-1) )

    l = -1 
    if len(Ones) != 0 :  # l lo pongo como el ultimo vertice en la secuencia con degee 1
        l = Ones[len(Ones)-1]
        Ones.remove(l)

    for i in range (n):  # armo el arbol que estoy buscando 
        if a[i] > 1 :
            if l !=-1:
                a[l] = a[l] -1 
                a[i] = a[i] -1 
                print (str (l+1) + " " + str(i+1))
            l=i
    
    i = n-1   # anado aristas sin armar ciclos para que el diemetro no disminuya 
    while i >=0 :
        while len(Ones) > 0 and a[i] > 0 :
            a[i] = a[i] -1 
            u = Ones[len(Ones)-1]
            print(str(i+1) + " " + str (u +1) )
            Ones.remove(u)
        i = i -1 



if __name__ == "__main__":
    line = int(input())
    n = int(line)

    line = str(input()).split()
    for i in range (n):
        a.append(int(line[i])) 

    solution()  # esto imprime la solucion del problema 
    
        