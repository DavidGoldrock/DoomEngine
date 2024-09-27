import os
for i in range(14):
    for j in range(32):
        p = f"./results/PLAYPAL{i}/COLORMAP{j}/"
        os.makedirs(p + "Sprites/")
        os.makedirs(p + "Flats/")
        os.makedirs(p + "Patches/")
        os.makedirs(p + "Textures/")