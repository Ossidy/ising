import numpy as np 
import matplotlib.pyplot as plt 
from matplotlib import colors
import json 
# import pickle

def load_blob(filename, is_json=False):
	print("Loading data")
	with open(filename) as f:
		data = f.read().splitlines()
	data = [x.split(" ") for x in data]
	# print(data)
	print("Creating data blobs")
	blobs = []
	for item in data:
		blob = {}
		blob["T"] = float(item[0])
		blob["mag"] = float(item[1])
		blob["mag_abs"] = float(item[2])
		blob["mag_sqr"] = float(item[3])
		blob["eng"] = float(item[4])
		blob["lattice"] = [(float(i) + 1.0) / 2.0 for i in item[4:]]

		blob["lattice"] = resize_lattice(blob["lattice"])
		# print(blob["lattice"])

		blobs.append(blob)

	if is_json == True:
		print("Dumping to json file...")
		with open(filename[:-3]+"txt", 'w') as outfile:
			json.dump(blobs, outfile)
			# np.save(outf)

	print("Finished!!!")
	
	return blobs


def resize_lattice(lattice_array):
	# resize and rescale lattice value
	N = len(lattice_array)
	# if N != length * width:
	# 	raise("Dimension not compatible!!!")
	L = int(np.sqrt(N))
	# lattice = [(i+1)/2 for i in lattice_array]
	lattice = np.array(lattice_array)
	lattice = np.resize(lattice, (L, L))
	# print(lattice)
	return lattice.tolist()

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


if __name__ == "__main__":

	# blobs = load_blob("./Temp2.dat", is_json=False)
	with open('./Temp2.txt') as data_file:
		blobs = json.load(data_file)
		
	for i in range(len(blobs)):
		plot_lattice(blobs[i]["lattice"])
