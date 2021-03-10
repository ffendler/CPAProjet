import matplotlib.pyplot as plt
import os


file = 'a'
while file != 'q' :
	X,Y = [],[]
	print('Nom du fichier? ')
	file = input()
	if file != 'q' :
		for line in open(file , 'r'):
			values = [float(s) for s in line.split()]
			X.append(1000*values[0])
			Y.append(1000*values[1])
		if file[1].isnumeric() :
			alpha = '0.' + file[1]
		else : 
			alpha = os.path.splitext(file)[0]
		ax = plt.axes();
		ax.set_xlabel('alpha = 0.15')
		ax.set_ylabel('alpha = '+alpha)
		plt.plot(X,Y)

		plt.savefig(alpha + '.png')
		plt.show()
