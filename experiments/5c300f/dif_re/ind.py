import numpy as np
rtim=[]
for i in range(10,91,10):
	with open(str(i)+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()

	time=[]
	for j in range(0,10):
		for k in range(len(lineas)):
			if(lineas[k][-10:]==str(j)+"_ent.txt\n"):
				time.append(float(lineas[k+1].split()[-2]))


	rtim.append(time)

print(rtim)

np.savetxt("time_dif.txt",rtim,delimiter=" ",fmt="%i")
