import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def read_data(file_path):
    data = {}
    with open(file_path, 'r') as file:
        headers = file.readline().split()
        for line in file:
            values = line.split()
            body = values[0]
            time = float(values[1])
            x = float(values[2])
            y = float(values[3])
            z = float(values[4])
            if body not in data:
                data[body] = {'time': [], 'x': [], 'y': [], 'z': []}
            data[body]['time'].append(time)
            data[body]['x'].append(x)
            data[body]['y'].append(y)
            data[body]['z'].append(z)
    return data

def plot_data(data):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for body, values in data.items():
        ax.plot(values['x'], values['y'], values['z'], label=body)
    ax.set_xlabel('X Position')
    ax.set_ylabel('Y Position')
    ax.set_zlabel('Z Position')
    ax.legend()
    plt.title('3D Plot of N-Body Simulation')
    plt.show()

if __name__ == "__main__":
    file_path = 'output.txt'
    data = read_data(file_path)
    plot_data(data)