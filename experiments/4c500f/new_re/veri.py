import numpy as np
rcom=[]
rtim=[]
stdcom=[]
stdtim=[]
for i in ["40","40_nord"]:
	#print(i)
	with open(i+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()
	#print("primera: ",lineas[i][:3])
	lc=[lineas[j] for j in range(len(lineas)) if lineas[j][:13]=="numero de com"]
	lt=[lineas[k] for k in range(len(lineas)) if lineas[k][:3]=="Tie"]
	#print(lc)
	#print(lt)
	combi=[]
	time=[]
	for l in range(len(lc)):
		combi.append(float(lc[l].split()[-1]))
		time.append(float(lt[l].split()[-2]))


	rcom.append(sum(combi)/len(combi))
	rtim.append(sum(time)/len(time))
	stdcom.append(np.std(combi))
	stdtim.append(np.std(time))

print(rcom)
print(rtim)
#print(stdcom)
#print(stdtim)
