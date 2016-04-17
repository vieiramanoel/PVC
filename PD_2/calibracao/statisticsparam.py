import math
import statistics

with open("first.txt") as f:
    first_param = f.read().splitlines()

first_param = list(map(float, first_param))

mean = statistics.mean(first_param)
variance = statistics.variance(first_param)
sigma = math.sqrt(variance)

print (mean, sigma)
