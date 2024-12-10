
rcom=[]
rtim=[]
for i in range(10,71,10):
	#print(i)
	with open(str(i)+".txt") as archivo:
		lineas= archivo.readlines()
	archivo.close()
	#print("primera: ",lineas[i][:3])
	lc=[lineas[j] for j in range(len(lineas)) if lineas[j][:3]=="Num"]
	lt=[lineas[k] for k in range(len(lineas)) if lineas[k][:3]=="Tie"]
	#print(lc)
	#print(lt)
	combi=[]
	time=[]
	for l in range(len(lc)):
		combi.append(int(lc[l].split()[-1]))
		time.append(float(lt[l].split()[-2]))


	rcom.append(sum(combi)/len(combi))
	rtim.append(sum(time)/len(time))

print(rcom)
print(rtim)
