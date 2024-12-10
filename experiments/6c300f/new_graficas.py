import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import seaborn as sns

sns.set_context("poster")
plt.rcParams.update({'font.size': 22})
densi=np.array(range(10,91,10))
densi2=np.array(range(20,91,10))

print(densi)
'''
tlexI=[22291.1, 47017.0, 51692.0, 43233.5, 34955.4, 23073.1, 14096.0, 9174.9, 6283.3]
comlexI=[402469183.3, 771682054.1428572, 833638297.7142857, 660581582.125, 510375905.0, 351112483.5, 230901840.1, 142516378.6, 102489410.3]
stdcI=[44970504.351143524, 69237259.58361736, 99301427.29847102, 59337108.959936306, 51879138.249032885, 25478522.678489856, 12009224.661686594, 10867215.605155889, 8606804.703675121]
stdtI=[4560.829320419697, 6527.140918612726, 12177.42997750933, 10687.295904483977, 9335.414443933381, 4594.093761559509, 1439.7690092511368, 832.1651819200321, 617.0525180241954]


tlexD=[22361.3, 47577.857142857145, 50262.42857142857, 49141.71428571428, 34424.0, 24235.0, 13310.1, 8789.4, 6313.5]
comlexD=[402859894.2, 786138990.4285715, 794748346.5714285, 748738205.8571428, 501063888.6, 362240377.3, 224043163.4, 134415833.5, 101179104.3]
stdcD=[41903903.3770965, 54423805.054590374, 51023703.66595775, 71565472.15788706, 34959023.549722806, 37884525.52749271, 14173492.336355336, 9047770.204060372, 12058604.796362339]
stdtD=[4618.355660838606, 7117.1184463652025, 7814.213402642701, 7007.751457478777, 6533.384023612878, 4421.556490648966, 1486.9065505269657, 741.3073856370244, 760.8758440113604]
'''


'''
resultados anteriores
tgbt=[0.11,0.44,5,32,183,1150,5495,27585,0,0,0,0,0,0,0]
comgbt=[326799,1737206,17253119,99924080,515202696,2856531098,13021705874,61251071910,0,0,0,0,0,0,0]
'''
comNew=[11768758571.428572, 26895733333.333332, 28815050000.0, 22388666666.666668, 15494775000.0, 8428042500.0, 6030780000.0, 3518696000.0, 2125011000.0]
tNew=[408599.71428571426, 946922.3333333334, 1099567.5, 880793.6666666666, 627766.25, 359678.25, 262708.8, 154206.8, 92205.2]
stdcN=[2128769037.2904549, 3545331960.323164, 1015450000.0, 1477166046.4852583, 1561611624.8526711, 789272329.9145548, 641075526.2369637, 238154439.73186812, 142721332.5645469]
stdtN=[73697.71804514184, 159427.3745928081, 24032.5, 18758.007753727175, 29282.496139972427, 34865.12727550984, 33386.615925547165, 11236.787163597965, 7306.13169604819]


tgbt=[118802.6, 376439.0, 734793.5, 1051583.3333333333, 796508.75, 1435827.5, 981668.3333333334, 570381.1666666666, 259979.2]
comgbt=[5854568244.5, 21454407069.444443, 39861142115.5, 61788317537.333336, 48932454262.75, 81362944992.5, 57719271569.333336, 32756696416.333332, 13336469130.0]
stdcG=[1626145962.9040034, 3419632195.9417157, 7727451484.569095, 20036936030.599316, 4408775268.776076, 12088761129.5, 9873603346.991898, 8180604267.930851, 3825672785.682359]
stdtG=[32249.458715457535, 58483.336506127016, 181563.0812933896, 322581.3584925342, 84866.99404767144, 171394.5, 255564.25957781257, 174729.46161558508, 86379.80210303796]



tdif=[660300.0, 911065.0, 749965.75, 684531.2, 644999.6, 924986.0, 948158.6666666666, 853604.25, 821930.0]
stdtDif=[163223.3062231004, 123003.29423501903, 73581.0764951662, 177475.42096684827, 91994.16276829742, 63625.513472715225, 105206.01999991361, 83784.26881096176, 108034.42362969315]


fig=plt.figure()
#plt.title("time")
plt.xlabel("Density")
plt.ylabel("Time(s)")
#plt.errorbar(densi,tlexI,stdtI,capsize=5,label="izq",linestyle="--")
plt.errorbar(densi,tNew,stdtN,capsize=5,label="GR-Lex",linestyle="--")
plt.errorbar(densi,tgbt,stdtG,capsize=5,label="GFR")
plt.errorbar(densi,tdif,stdtDif,capsize=5,label="CC-DIF")
plt.legend()
plt.show()
fig2=plt.figure()
#plt.title("Evaluated candidates")
plt.xlabel("Density")
plt.ylabel("Candidates evaluated")
#plt.errorbar(densi,comlexI,stdcI,capsize=5,label="izq",linestyle="--")
plt.errorbar(densi,comNew,stdcN,capsize=5,label="GR-Lex",linestyle="--")
plt.errorbar(densi,comgbt,stdcG,capsize=5,label="GFR")

plt.legend()
plt.show()