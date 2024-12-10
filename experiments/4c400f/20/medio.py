import numpy as np 

for i in range(1,11):
	data=np.loadtxt(str(i)+".txt")
	print(str(i)+".txt")
	#calculamos densidad
	medios=(np.max(data,axis=0)+np.min(data,axis=0))/2
	unos=0
	for i in range(data.shape[0]):
		for j in range(data.shape[1]):
			if(data[i][j]>medios[j]):
				unos+=1
	den=unos/(data.shape[0]*data.shape[1])
	print("densidad",den)
	#estadisticas
	print("minimos",np.min(data,axis=0))
	print("maximos",np.max(data,axis=0))
	print("mean",np.mean(data,axis=0))
	print("std",np.std(data,axis=0))

	#calculamos valores distintos
	unicos=[]
	for i in range(data.shape[1]):
		uni=np.unique(data[:,i]) 
		unicos.append(len(uni))

	print("unicos",unicos)
