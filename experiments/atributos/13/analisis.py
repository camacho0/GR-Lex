import numpy as np


for k in range(1,11):
	data=np.loadtxt(str(k)+".txt")
	#print(data.shape)
	unos=0;
	espacio=1;
	suma=np.sum(data)/(data.shape[0]*data.shape[1])
	medios= (np.max(data,axis=0)+np.min(data,axis=0))/2
	for i in range(data.shape[0]):
		for j in range(data.shape[1]):
			if(data[i][j]>medios[j]):
				unos+=1

	Denm=unos/(data.shape[0]*data.shape[1])
	for j in range(data.shape[1]):
		m=np.unique(data[:,j])
		espacio*=len(m);

	print("nombre: ",k)
	print("espacio de busqueda: %10.3E"% espacio);
	print("densidad suma: ",suma)
	print("densidad medio: ",Denm)
