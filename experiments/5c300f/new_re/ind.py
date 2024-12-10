import numpy as np
rcom=[]
rtim=[]


for i in range(10,91,10):
	with open(str(i)+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()
	combi=[]
	time=[]
	for j in range(0,10):
		for k in range(len(lineas)):
			if(lineas[k][-6:]==str(j)+".txt\n"):
				combi.append(float(lineas[k+1].split()[-1]))
				time.append(float(lineas[k+2].split()[-2]))


	rcom.append(combi)
	rtim.append(time)

print(rcom)
print(rtim)

np.savetxt("time_gr.txt",rtim,delimiter=" ",fmt="%i")
np.savetxt("com_gr.txt",rcom,delimiter=" ",fmt="%i")
