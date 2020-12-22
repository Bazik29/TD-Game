import matplotlib.pyplot as plt
import numpy as np

def spiral(a):
    df = np.linspace(0, 6*np.pi, 25)

    x = a/(2*np.pi) * df * np.cos(df)
    y = a/(2*np.pi) * df * np.sin(df)
    return x, y

x, y = spiral(5/np.pi)
# plt.plot(data[0], data[1])
# plt.show()

with open("spiral.txt", "w") as file:
    for x, y in zip(x, y):
        file.write("{" + str(x) + ", " + str(y) + "},\n")
