import matplotlib.pyplot as plt
import numpy as np
import math 
import sys

def main(argv):

    # Read outfile
    fr = open("outfile", "r")
    fr = fr.read()
    lines = fr.split("\n") 

    # Write to file
    fileName = str(argv[0])
    fw = open("figs/"+fileName+"_data.txt", "w")

    ''' PERFORMANCE GRAPHS '''
    graph_avg_fitness = {}
    graph_max_fitness = {}

    # Get average and maximum fitness per generations
    for line in lines:
        line = line.replace(" ", "")
        data = line.split("\t")
        if len(data) >= 4:
            graph_avg_fitness[data[0]] = graph_avg_fitness.get(data[0], 0) + float(data[2])
            graph_max_fitness[data[0]] = graph_max_fitness.get(data[0], 0) + float(data[3])

    # Get average average fitness for each generation
    # Divide total average fitness by 30 iterations
    for key, value in graph_avg_fitness.items():
        graph_avg_fitness[key] = value/30.0
	    
    # Get average maximum fitness for each generation
    # Divide total average fitness by 30 iterations
    for key, value in graph_max_fitness.items():
        graph_max_fitness[key] = value/30.0

    # Sort dictionaries into lists
    generations = list(graph_avg_fitness.keys())
    average_fitnesses = list(graph_avg_fitness.values())
    maximum_fitnesses = list(graph_max_fitness.values())


    # Plot average avg and max fitness for each generation
    plt.plot(generations, average_fitnesses, "-b", label="Avg Fitness")
    plt.plot(generations, maximum_fitnesses, "-r", label="Max Fitness")
    plt.legend(loc="upper left")

    plt.xticks(np.arange(0, 800, 50))
    plt.yticks(np.arange(min(average_fitnesses), max(maximum_fitnesses), max(maximum_fitnesses)-max(average_fitnesses)))
    #plt.yticks(np.arange(0, 50000, 1000))

    plt.xlabel("Generation")
    plt.ylabel("Average Fitness")
    plt.title('Genetic Algorithm\nAverage Fitness per Generation')
    plt.legend(loc="lower right")

    plt.savefig("figs/"+fileName+"_fitness.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()


    
    ''' QUATLITY - percentage distance from optimum (Average of best over all runs) '''
    fw.write("QUATLITY:\n")
    print("QUATLITY:")
    optimum = sum(maximum_fitnesses) / len(maximum_fitnesses)
    print("Optimum (Avg of Best): " + str(optimum))
    fw.write("Optimum (Avg of Best): " + str(optimum) + "\n")
    
    average_avg_fitness = sum(average_fitnesses) / len(average_fitnesses)
    print("Average (Avg of Average): " + str(average_avg_fitness))
    fw.write("Average (Avg of Average): " + str(average_avg_fitness) + "\n")
    
    # Percent difference
    percent_diff_optimum = abs(optimum - average_avg_fitness) / ((optimum + average_avg_fitness) / 2) * 100
    print("Percent Difference from Optimum:", percent_diff_optimum, "= "+str(round(percent_diff_optimum))+"%")
    fw.write("Percent Difference from Optimum: " + str(percent_diff_optimum) + " = " + str(round(percent_diff_optimum)) + "%\n")
    print()
    

    ''' RELIABILITY = Percentage of runs you get within Quality -- out of total number of runs '''
    fw.write("\nRELIABILITY:\n")
    print("RELIABILITY:")
    pop_size = int(argv[1])
    max_gens = round(pop_size * 1.5)
    num_quality_runs = 0
    avg_fits = []
    best_fits = []
    optimum_achieved = False
    for line in lines:
        line = line.replace(" ", "")
        data = line.split("\t")
        
        # Append current avg and best fitness
        if len(data) >= 4:
            avg_fits.append(float(data[2]))
            best_fits.append(float(data[3]))
        
        # If at end of run, calculate percent difference
        if len(data) >= 4:
            if int(data[0]) == max_gens-1:
                
                # Check if optimum percent diff was achieved during run
                for i in range(len(best_fits)):
                
                    percent_diff = abs(best_fits[i] - avg_fits[i]) / ((best_fits[i] + avg_fits[i]) / 2) * 100
                    #print(int(data[0]), (max_gens-1), int(data[0]) == (max_gens-1), (percent_diff < percent_diff_optimum))
                
                    if (percent_diff < percent_diff_optimum and not optimum_achieved):
                        num_quality_runs += 1
                        optimum_achieved = True
                
                avg_fits = []
                best_fits = []
    
    quality_run_percentage = (num_quality_runs / 30.0) * 100.0
    print("Percentage of runs within quality: ", quality_run_percentage, "= "+str(round(quality_run_percentage))+"%")
    fw.write("Percentage of runs within quality: " + str(quality_run_percentage) + " = " + str(round(quality_run_percentage)) + "%\n")
    

    '''	
    #SPEED
    found_generation = 0
    found_num = 0
    for line in lines:
        line = line.replace(" ", "")
        data = line.split("\t")  
        if '' not in data:  
            if float(data[2]) == best_avg_fitness:
                found_generation += int(data[0])
                found_num += 1
	      
    if found_num > 0:
        speed = found_generation/found_num
    else:
        speed = 0
    print("Speed:",speed)
    fw.write("Speed: " + str(speed) + "\n")
    '''
    fw.close()

if __name__ == "__main__":
   main(sys.argv[1:])

