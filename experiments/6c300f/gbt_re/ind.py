import numpy as np
rcom=[]
rtim=[]

for i in range(10,91,10):
	#print(i)
	with open(str(i)+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()
#	print(lineas[3][-13:])
	lc=[lineas[j] for j in range(len(lineas)) if (lineas[j][-13:]=="verificadas \n" and lineas[j][:5]!=" Cada")]
	lt=[lineas[k] for k in range(len(lineas)) if lineas[k][:4]==" tie"]
#	print(lc)
	#print(lt)
	combi=[]
	time=[]
	for l in range(len(lc)):
		#print(lc[l].split())
		combi.append(int(lc[l].split()[0]))
		time.append(float(lt[l].split()[-2]))


	rcom.append(combi)
	rtim.append(time)

print(rtim)
print(rcom)
