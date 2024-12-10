import numpy as np

def Genera(n,m,p,k):
	fila=np.random.randint(0,101,size=m)
	name=str(k)
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
				if(rd<=0.8):
					unos+=1
					g=np.random.randint(51,101)
					#g=np.random.randint(50,101)
					fila[j]=g
				else:
					g=np.random.randint(1,51)
					#g=np.random.randint(0,50)
					fila[j]=g
		else:
			for j in range(m):
				rd=np.random.rand()
				if(rd<0.8):
					fila[j]=np.random.randint(1,51)
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

	decimales=matriz/100
	np.savetxt(name+".txt",decimales,delimiter=" ",fmt="%0.2f")
	np.savetxt(name+"_ent.txt",matriz,delimiter=" ",fmt="%i")
	#print(matriz)
	return Densidad(matriz)

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
	m=6
	p=50
	name=str(2)
	n=230

	k=1
	print((p+2)/100)
	while k<11:
		den=Genera(n,m,p,k)
		print(den)
		if(den>=((p-2)/100) and den<=((p+2)/100)):
			print("METIDO")
			k+=1

		

	'''
	print(Densidad(matriz))
	print((np.max(matriz,axis=0)+np.min(matriz,axis=0))/2)
	decimales=matriz/100
	np.savetxt(name+".txt",decimales,delimiter=" ",fmt="%0.2f")
	np.savetxt(name+"_ent.txt",matriz,delimiter=" ",fmt="%i")
	'''
