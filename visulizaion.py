import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors


chessboard = [-1, 1, 1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1, -1, 1, -1]

def load_file(filename):
	with open(filename) as f:
		data = f.read().splitlines()
	data = [x.split(" ") for x in data]
	# print(data)
	data = np.array(data[0][:-1], dtype='float')
	return data

def resize_lattice(lattice_array, length, width):
	# resize and rescale lattice value
	N = len(lattice_array)
	if N != length * width:
		raise("Dimension not compatible!!!")

	# lattice = [(i+1)/2 for i in lattice_array]
	lattice = (np.array(lattice_array, dtype='float32') + 1) / 2
	lattice = np.resize(lattice, (length, width))
	print(lattice)
	return lattice

def plot_lattice(lattice):
	cmap = colors.ListedColormap(['white', 'black'])
	bounds = [0, 0.5, 1]
	norm = colors.BoundaryNorm(bounds, cmap.N)

	fig, ax = plt.subplots()
	ax.imshow(lattice, cmap=cmap, norm=norm)

	# ax.grid(which='major', axis='both', linestyle='-', color='k', linewidth=2)
	ax.grid(True)
	ax.set_xticks(np.array([]))
	ax.set_yticks(np.array([]))

	plt.show()



# lattice = resize_lattice(chessboard, 4, 4)
# plot_lattice(lattice)
data = load_file("./TEMPDATA.dat")
print(data)
lattice = resize_lattice(data, 256, 256)
plot_lattice(lattice)