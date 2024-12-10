import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import seaborn as sns

sns.set_context("poster")
plt.rcParams.update({'font.size': 22})

densi=np.array(range(5,17))
densi2=np.array(range(5,13))

print(densi)
tnew=[0.0, 0.7, 3.7, 12.8, 44.2, 158.3, 486.1, 1271.5, 2472.2, 9101.2, 22397.8, 68779.8]
comnew=[42090.8, 171712.8, 637372.4, 1989167.0, 5731973.0, 18209420.0, 53145230.0, 127741810.0, 68703767.0, 831998000.0, 1834058000.0, 4743082000.0]



tdif=[0,0,0,0,0,0,0,0,0,0,0,0]

'''
resultados anteriores
tgbt=[0.11,0.44,5,32,183,1150,5495,27585,0,0,0,0,0,0,0]
comgbt=[326799,1737206,17253119,99924080,515202696,2856531098,13021705874,61251071910,0,0,0,0,0,0,0]
'''


tgbt=[0.1111111111111111, 0.4444444444444444, 5.0, 32.111111111111114, 180.33333333333334, 1150.6666666666667, 5496.888888888889, 27585.88888888889]
comgbt=[326799.3333333333, 1737206.111111111, 17253119.444444444, 99924080.22222222, 515202696.1111111, 2856531098.6666665, 13021705874.555555, 61251071910.888885]

fig=plt.figure()
#plt.title("time")
plt.xlabel("Caracteristicas")
plt.ylabel("Tiempo(s)")
plt.plot(densi,tnew,label="Algoritmo propuesto",linestyle="--")
plt.plot(densi,tdif,label="CC-DIF")
plt.plot(densi2,tgbt,label="GFR")
plt.legend()
plt.show()

fig2=plt.figure()
#plt.title("Candidatos Evaluados")
plt.xlabel("Caracteristicas")
plt.ylabel("Candidatos evaluados")
plt.plot(densi,comnew,label="new",linestyle="--")
plt.plot(densi2,comgbt,label="GFR")

plt.legend()
plt.show()
