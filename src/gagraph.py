import matplotlib.pyplot as plt
import numpy as np
import math 

# Read outfile
f = open("outfile", "r")
f = f.read()
lines = f.split("\n") 


''' PERFORMANCE GRAPHS '''
graph_avg_fitness = {}
graph_max_fitness = {}

# Get average fitness per generation
for line in lines:
  line = line.replace(" ", "")
  data = line.split("\t")
  if '' not in data:
    graph_avg_fitness[data[0]] = graph_avg_fitness.get(data[0], 0) + float(data[2])

# Get maximum fitness per generation   
for line in lines:
  line = line.replace(" ", "")
  data = line.split("\t")
  if '' not in data:
    graph_max_fitness[data[0]] = graph_max_fitness.get(data[0], 0) + float(data[3])

# Get average average fitness for each generation
# Divide total average fitness by 30 iterations
for key, value in graph_avg_fitness.items():
    graph_avg_fitness[key] = value/30
    
# Get average maximum fitness for each generation
# Divide total average fitness by 30 iterations
for key, value in graph_max_fitness.items():
    graph_max_fitness[key] = value/30

# Sort dictionaries into lists
generations = list(graph_avg_fitness.keys())
average_fitness = list(graph_avg_fitness.values())
maximum_fitness = list(graph_max_fitness.values())


# Plot average avg and max fitness for each generation
plt.plot(generations, average_fitness, "-b", label="Avg Fitness")
plt.plot(generations, maximum_fitness, "-r", label="Max Fitness")
plt.legend(loc="upper left")

plt.xticks(np.arange(0, 850, 50))
plt.yticks(np.arange(0, 50000, 10000))
#plt.yticks(np.arange(min(average_fitness), max(maximum_fitness), max(maximum_fitness)-max(average_fitness)))

plt.xlabel("Generation")
plt.ylabel("Average Fitness")
plt.title('Traveling Saleperson Problem\nAverage Fitness per Generation')
plt.legend(loc="lower right")

plt.savefig('figs/Performance.png')
plt.draw()
plt.waitforbuttonpress(0)
plt.close()

