#programa para generar matrices sinteticas 
import numpy as np


			
#los objetos de la misma clase deben estar contiguos
def CM(n,m):
	bm=[]
	ni=[]
	sup=False

	while(len(bm)<n):
		f=np.random.randint(0,101,size=m) 
		if len(bm)==0:
		#print(f)
			bm.append(f)
		else:
			ni=[]
			sup=False
			for l in range(len(bm)):
				d=(bm[l]-f).astype(np.float32)
				if((d<=0).all()):
					#print(d)
					ni=[]
					sup=True
					break
				elif((d>=0).all()):
					ni.append(l)
			if(len(ni)>0 and (not sup)):
				res=0
				for a in ni:
					bm.pop(a-res)
					res+=1
				bm.append(f)

			if((not sup) and len(ni)==0):
				#print(f)
				bm.append(f)

	bm=np.array(bm)/100
#	print(bm.shape)
	return bm
	

if __name__=="__main__":
	#m=int(input("Dame el numero de columnas de la matriz: "))
	m=17
	n=20
	for i in range(10):
		name=str(i+1)
		cm=CM(n,m)
		#print(cm)
		#print(cm.shape)
	
		np.savetxt(name+".txt",cm,delimiter=" ",fmt="%0.2f")

