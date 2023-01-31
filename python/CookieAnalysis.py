#! /usr/bin/env python

# imports of external packages to use in our code
import sys
import math
import numpy as np
import matplotlib.pyplot as plt
import time
import statistics


# import our Random class from python/Random.py file
sys.path.append(".")
from MySort import MySort

def Average(lst):
    return sum(lst) / len(lst)

# main function for our CookieAnalysis Python code
if __name__ == "__main__":
   
    haveInput = False

    for i in range(1,len(sys.argv)):
        if sys.argv[i] == '-h' or sys.argv[i] == '--help':
            continue

        InputFile = sys.argv[i]
        haveInput = True
    
    if '-h' in sys.argv or '--help' in sys.argv or not haveInput:
        print ("Usage: %s [options] [input file]" % sys.argv[0])
        print ("  options:")
        print ("   --help(-h)          print options")
        print
        sys.exit(1)
    
    Nmeas = 1
    times = []
    times_avg = []

    need_rate = True
    
    with open(InputFile) as ifile:
        for line in ifile:
            if need_rate:
                need_rate = False
                rate = float(line)
                continue
            
            lineVals = line.split()
            Nmeas = len(lineVals)
            t_avg = 0
            for v in lineVals:
                t_avg += float(v)
                times.append(float(v))

            t_avg /= Nmeas
            times_avg.append(t_avg)

    Sorter = MySort()

    times = Sorter.DefaultSort(times)
    times_avg = Sorter.DefaultSort(times_avg)
    # try some other methods! see how long they take
    # times_avg = Sorter.BubbleSort(times_avg)
    # times_avg = Sorter.InsertionSort(times_avg)
    # times_avg = Sorter.QuickSort(times_avg)

    # ADD YOUR CODE TO PLOT times AND times_avg HERE
    print(times)
    print(times_avg)
    variance = statistics.variance(times)
    q25 = np.quantile(times, 0.25)
    q50 = np.quantile(times, 0.5)
    q75 = np.quantile(times, 0.75)
    
    
    plt.hist(times, 40, density=True, facecolor='r', alpha=0.75, label='Times')
    plt.hist(times_avg,  40, density=True, facecolor='g', alpha=0.75, label='Average')
    plt.axvline(q25, color='k', linestyle='dashed', linewidth=1, label ='Q25')
    plt.axvline(q50, color='k', linestyle='dashed', linewidth=1, label ='Q50')
    plt.axvline(q75, color='k', linestyle='dashed', linewidth=1, label ='Q75')
    plt.axvline(Average(times), color='b', linestyle='dashed', linewidth=1, label ='Times Average')
    
    plt.title('Cookie Time Probability')
    plt.xlabel('Time')
    plt.ylabel('Probability')
    plt.legend()
    plt.show()
    plt.savefig("TimesHistogramPlot.png")
    