import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

#sns.set_context("poster")
#plt.rcParams.update({'font.size': 12,'font.weight' : 'bold'})
plt.rcParams.update({'font.size': 14})

tim_gr=np.loadtxt("time_gr.txt")
tim_gfr=np.loadtxt("time_gfr.txt")
tim_dif=np.loadtxt("time_dif.txt")

com_gr=np.loadtxt("com_gr.txt")
com_gfr=np.loadtxt("com_gfr.txt")

den=[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9]

fig,axs= plt.subplots(5,2,layout='constrained')

for i in range (5):
	for j in range(2):
		axs[i,j].plot(den,tim_gr[:,(i*2)+j],label="GR-Lex")
		axs[i,j].plot(den,tim_gfr[:,(i*2)+j],label="GFR")
		axs[i,j].plot(den,tim_dif[:,(i*2)+j],label="CC-DIF")

for ax in axs.flat:
    ax.set(xlabel='Density', ylabel='Time(s)')
    #ax.set(xlabel='Density', ylabel='Time(s)')

#for ax in fig.get_axes():
#    ax.label_outer()
plt.show()
