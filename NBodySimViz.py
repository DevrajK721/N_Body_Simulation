import matplotlib.pyplot as plt
import numpy as np

# Load positions from the output file
positions = []  # To store positions
names = []  # To store body names

with open('../output.txt', 'r') as file:
    # Skip the header line
    next(file)
    for line in file:
        parts = line.split()  # Split the line into components
        if len(parts) < 8:
            continue  # Skip lines that do not have enough data
        names.append(parts[0])  # Body name
        # Read positions (we only need the last positions)
        positions.append([float(parts[5]), float(parts[6]), float(parts[7])])  # Final x, y, z

# Convert positions to a numpy array for easier plotting
positions = list(zip(*positions))  # Transpose to separate x, y, z

# Create a color map with a distinct color for each body
colors = plt.cm.viridis(np.linspace(0, 1, len(names)))  # You can choose any colormap

# Create the plot with white background
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.set_facecolor('white')  # Set the background color to white

# Set grid and labels with default colors
ax.xaxis.pane.fill = True
ax.yaxis.pane.fill = True
ax.zaxis.pane.fill = True
ax.xaxis._axinfo['grid'].update(color='gray', linewidth=0.5)
ax.yaxis._axinfo['grid'].update(color='gray', linewidth=0.5)
ax.zaxis._axinfo['grid'].update(color='gray', linewidth=0.5)

ax.set_xlabel('X-axis', color='black')
ax.set_ylabel('Y-axis', color='black')
ax.set_zlabel('Z-axis', color='black')
ax.set_title('N Body Simulation', color='black')

# Plot the final positions of all bodies with different colors
for i, name in enumerate(names):
    ax.scatter(positions[0][i], positions[1][i], positions[2][i], color=colors[i], s=100, label=name)  # Plot each body

# Show the plot
plt.show()
