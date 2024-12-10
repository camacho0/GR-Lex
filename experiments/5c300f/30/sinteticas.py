import numpy as np

def Genera(n,m,p):
	fila=np.random.randint(0,101,size=m)
	#print(fila.shape)
	matriz =fila
	matriz=np.reshape(matriz,(1,m))
	#medios=np.array([50 for i in range(m)])
	medios=(np.max(matriz,axis=0)+np.min(matriz,axis=0))/2
	unos=0
	f=0

	while(matriz.shape[0]<n):
		i=0
		cont=0
	#	print(medios)
		#fila=np.random.randint(1,101,size=m)
		fila=np.zeros((m))
		#print(fila.shape)
		if(Densidad(matriz)<=(p/100)):
			for j in range(m):
				rd=np.random.rand()
				if(rd<=0.7):
					unos+=1
					g=np.random.randint(51,101)
					#g=np.random.randint(50,101)
					fila[j]=g
				else:
					g=np.random.randint(0,51)
					#g=np.random.randint(0,50)
					fila[j]=g
		else:
			for j in range(m):
				rd=np.random.rand()
				if(rd<0.70):
					fila[j]=np.random.randint(0,51)
				else:
					fila[j]=np.random.randint(51,101)

		while(i<matriz.shape[0]):
			aux=fila-matriz[i]
			if((aux>=np.zeros((1,m))).all()):
				break
			else:
				cont+=1
			i+=1
		if(cont==matriz.shape[0]):
				matriz=np.append(matriz,[fila],axis=0)
				medios=(np.max(matriz,axis=0)+np.min(matriz,axis=0))/2
	print(matriz)
	return matriz

def Densidad(data):
	unos=0
	medios=(np.max(data,axis=0)+np.min(data,axis=0))/2
	for i in range(data.shape[0]):
		for j in range(data.shape[1]):
			if(data[i][j]>medios[j]):
				unos+=1
	return (unos/(data.shape[0]*data.shape[1]))
	


if __name__=="__main__":
	#n=int(input("Dame el numero de filas de la matriz: "))
	'''
	m=int(input("Dame el numero de columnas de la matriz: "))
	name=input("Dame el nombre del archivo: ")
	p=int(input("Dame la densidad deseada: "))
	'''
	m=5
	p=30
	name=str(10)
	n=300
	matriz=Genera(n,m,p)
	print(Densidad(matriz))
	print((np.max(matriz,axis=0)+np.min(matriz,axis=0))/2)
	decimales=matriz/100
	np.savetxt(name+".txt",decimales,delimiter=" ",fmt="%0.2f")
	np.savetxt(name+"_ent.txt",matriz,delimiter=" ",fmt="%i")
