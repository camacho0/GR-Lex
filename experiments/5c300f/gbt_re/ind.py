import numpy as np
rcom=[]
rtim=[]

for i in range(10,91,10):
	#print(i)
	with open(str(i)+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()
	combi=[]
	time=[]
#	print(lineas[3][-13:])
	for j in range(0,10):
		for k in range(len(lineas)):
			if(lineas[k][-6:]==str(j)+".txt\n"):
				combi.append(int(lineas[k+11].split()[0]))
				time.append(float(lineas[k+15].split()[-2]))


	rcom.append(combi)
	rtim.append(time)

print(rtim)
print(rcom)

np.savetxt("time_gfr.txt",rtim,delimiter=" ",fmt="%i")
np.savetxt("com_gfr.txt",rcom,delimiter=" ",fmt="%i")

