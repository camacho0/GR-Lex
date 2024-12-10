import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import seaborn as sns

sns.set_context("poster")

densi=np.array(range(5,15))
densi2=np.array(range(5,13))

print(densi)
tlexI=[0.2, 0.6, 3.0, 9.6, 43.8, 184.7, 665.4, 1958.2, 4264.9, 14740.2]
comlexI=[41043.1, 169274.5, 650367.0, 1812877.0, 6670564.0, 18483889.4, 51523648.3, 128408162.4, 119967637.2, 816201373.6]


tlexD=[0.2, 0.5, 2.5, 8.4, 31.6, 162.7, 550.7, 1474.3, 5151.9, 11617.6]
comlexD=[38835.5, 151694.2, 560343.9, 1589329.3, 4855506.9, 16211785.9, 41474553.5, 97019251.0, 142675441.5, 598779471.7]

'''
resultados anteriores
tgbt=[0.11,0.44,5,32,183,1150,5495,27585,0,0,0,0,0,0,0]
comgbt=[326799,1737206,17253119,99924080,515202696,2856531098,13021705874,61251071910,0,0,0,0,0,0,0]
'''


tgbt=[0.11,0.44,5,32,183,1150,5495,27585]
comgbt=[326799,1737206,17253119,99924080,515202696,2856531098,13021705874,61251071910]

fig=plt.figure()
plt.title("time")
plt.xlabel("Features")
plt.ylabel("Log(time(s))")
plt.plot(densi,np.log10(tlexI),label="izq",linestyle="--")
plt.plot(densi,np.log10(tlexD),label="der",linestyle="--")
plt.plot(densi2,np.log10(tgbt),label="GFR")
plt.legend()
plt.show()
fig2=plt.figure()
plt.title("Evaluated candidates")
plt.xlabel("Features")
plt.ylabel("Candidates")
plt.plot(densi,comlexI,label="izq",linestyle="--")
plt.plot(densi,comlexD,label="der",linestyle="--")
plt.plot(densi2,comgbt,label="GFR")

plt.legend()
plt.show()
