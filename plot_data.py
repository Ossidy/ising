import numpy as np
import matplotlib.pyplot as plt 


def load_data(filename):
	with open(filename) as f:
		data = f.read().splitlines()
	data = [x.split(" ") for x in data]
	data = np.array(data, dtype='float')
	return data

def plot_data(data_dict):
	fig, ax = plt.subplots()
	for item in data_dict.keys():
		data = data_dict[item]
		ax.plot(data[:,0], data[:,2], marker='*',label=str(item))
	ax.legend()	
	ax.grid(True)
	# plt.show()
	return fig, ax

def collect_data(file_list, label_list):
	data_dict = {} 
	for ind, file in enumerate(file_list):
		# print(ind, file, load_data(file))
		data_dict[label_list[ind]] = load_data(file)
	return data_dict

def analytic_solution(Tmin, Tmax, Tint=1): 
	# print((Tmax - Tmin) / Tint)
	T = [i * Tint + Tmin for i in range(int((Tmax - Tmin) / Tint))]
	m = np.power(1 - np.power(np.sinh(2 * np.power(T, -1)), -4), 0.125)
	return T, m 

if __name__ == "__main__":
	file1 = "./DATA16_10M_Metropolis.dat"
	file2 = "./DATA16_1W_clustering.dat"
	labels = ["1", "2"]
	# file3 = "./DATA4_5M_Metropolis.dat"
	# file4 = "./DATA2_5M_Metropolis.dat"
	# labels = ["L=16", "L=8", "L=4", "L=2"]
	# data_dict = collect_data([file1, file2], labels)
	data_dict = collect_data([file2], ["2"])

	fig, ax = plot_data(data_dict)
	T, m = analytic_solution(0.5, 5, 0.0001)
	print(T, m)
	ax.plot(T,m)
	plt.show()