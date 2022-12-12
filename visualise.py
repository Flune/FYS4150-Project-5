import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import pyarma as pa
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("filename")
filename = parser.parse_args().filename
fileroot = filename[:-4]

U = pa.cx_mat()
U.load(f"{fileroot}/{fileroot}.bin", pa.arma_binary)
U = np.array(U).T
shape = U.shape
length = (int)(shape[1]**0.5+0.5)
shape = (shape[0],length, length)
U = U.reshape(shape)
print(f"U has shape {U.shape}")

metadata = np.genfromtxt(f"{fileroot}/{fileroot}_meta.dat", skip_header=1)
# print(metadata)
print(f"metadata has shape {metadata.shape}")
f, a = plt.subplots(1,1)
a.plot(metadata[:,0],metadata[:,1])
a.set_xlabel("Time [s]")
a.set_ylabel("Probability")
a.set_title("Probability deviation from 1.0")
f.savefig(f"{fileroot}/{fileroot}_prob_deviation.pdf")

dt = (metadata[-1,0] - metadata[0,0])/(metadata.shape[0]-1)

data = zip([abs(U)**2, U.real, U.imag], ["Amplitude", "Real", "Imaginary"])


#
# Now the list z_data_list contains a series of "frames" of z(x,y,t), 
# where each frame can be plotted as a 2D image using imshow. Let's
# animate it!
#

# Some settings
fontsize = 12
t_min = metadata[0,0]
# print(t_min)
x_min, x_max = 0,1
y_min, y_max = 0,1

# Create figure
fig = plt.figure()
ax = plt.gca()

# Axis labels
plt.xlabel("x", fontsize=fontsize)
plt.ylabel("y", fontsize=fontsize)
plt.xticks(fontsize=fontsize)
plt.yticks(fontsize=fontsize)

# Add a text element showing the time
text = f"t = {t_min:.3}"
# print(text)
time_txt = plt.text(0.95, 0.95, text, color="white", 
                    horizontalalignment="right", verticalalignment="top", fontsize=fontsize)

# Function that takes care of updating the z data and other things for each frame
def make_func(dataset):
    def animation(i):
        # Normalize the colour scale to the current frame?
        norm = matplotlib.cm.colors.Normalize(vmin=np.min(dataset[i]), vmax=np.max(dataset[i]))
        img.set_norm(norm)

        # Update z data
        img.set_data(dataset[i].T)

        # Update the time label
        current_time = metadata[i,0]
        text = f"t = {current_time:.3e}"
        # print(text)
        time_txt.set_text(text)

        return img
    return animation

for i, (z_data_list, name) in enumerate(data):

    # Create a colour scale normalization according to the max z value in the first frame
    norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[0]))

    # Plot the first frame
    img = ax.imshow(z_data_list[0], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("viridis"), norm=norm)

    if(i==0):
        # Add a colourbar
        cbar = fig.colorbar(img, ax=ax)
        cbar.set_label("z(x,y,t)", fontsize=fontsize)
        cbar.ax.tick_params(labelsize=fontsize)
        
        # Calculate the response on the screen
        time_index = np.searchsorted(metadata[:,0],2e-3)
        x_index = (int)((length+1)*0.8+0.5)
        amp_ = z_data_list[time_index,x_index]
        amp = amp_ / np.sum(amp_)
        x_min = 1./(length+1)
        x_max = 1-x_min
        
        # Plot the response on the screen
        fig2, ax2 = plt.subplots(1,1)
        ax2.plot(np.linspace(x_min, x_max, length, True),amp)
        ax2.set_xlabel("y")
        ax2.set_ylabel("Probability")
        ax2.set_title("Detection Probability, p(y|x=0.8; t=0.002)")
        fig2.savefig(f"{fileroot}/{fileroot}_screen.pdf")

    # Use matplotlib.animation.FuncAnimation to put it all together
    animation = make_func(z_data_list)
    anim = FuncAnimation(fig, animation, interval=1, frames=np.arange(0, len(z_data_list), 2), repeat=False, blit=0)

    # Run the animation!
    plt.show()

    # Save the animation
    anim.save(f'{fileroot}/animation_{name}.mp4', writer="ffmpeg", bitrate=-1, fps=30)
    
    # Sava some frames
    for i in [0, 1e-3, 2e-3]:
        animation(np.searchsorted(metadata[:,0],i))
        fig.savefig(f"{fileroot}/{fileroot}_{i:.3e}_{name}.pdf")
        
    
    
    
