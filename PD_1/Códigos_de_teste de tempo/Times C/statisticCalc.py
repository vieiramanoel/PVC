import matplotlib.pyplot as plt
import numpy as np
import matplotlib.mlab as mlab
import math
import statistics

with open("timevalues4320p.txt") as f:
    lines = f.read().splitlines()

numbers = list(map(float, lines))

mean = statistics.mean(numbers)
variance = statistics.variance(numbers)
sigma = math.sqrt(variance)
x = np.linspace(-0.02, 0.5, 300)
plt.plot(x, mlab.normpdf(x, mean, sigma)/22)
plt.show()
