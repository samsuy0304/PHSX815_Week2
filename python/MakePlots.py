#! /usr/bin/env python

from Random import Random
import sys
import numpy as np
import matplotlib.pyplot as plt


class Create_Histogram:
    
    def __init__(self, file_name):
        self.file_name= file_name

    def Plot(self):
        with open(self.file_name, 'r') as file:
            n = [float(x) for x in file.read().split()]

        plt.hist(n,  10, density=True, facecolor='r', alpha=0.75, label='Random Numbers')

        # plot formating options
        plt.xlabel('x')
        plt.ylabel('Probability')
        plt.title('Uniform random number')
        plt.grid(True)
        plt.legend()
        #ax = plt.gca()
        #ax.set_ylim([0.8, 1.2])
        # show figure (program only ends once closed
        plt.show()
        plt.savefig("Binomial.png")




if __name__ == "__main__":
    # if the user includes the flag -h or --help print the options
    if '-h' in sys.argv or '--help' in sys.argv:
        print ("Usage: %s [-seed number]" % sys.argv[0])
        print
        sys.exit(1)

    # default seed
    seed = 5555

    # read the user-provided seed from the command line (if there)
    if '-seed' in sys.argv:
        p = sys.argv.index('-seed')
        seed = sys.argv[p+1]

    # set random seed for numpy
    np.random.seed(seed)

    # class instance of our Random class using seed
    

    Binomial = Random()

    # create some random data
    N = 300

    # an array of random numbers from numpy
    x = np.random.rand(N)

    # an array of random numbers using our Random class
    myx = []
    # Write the numbers to a file
    file_read = "Number_list.txt"
    f = open(file_read,'w')
    for i in range(0,N):
        numb = Binomial.Binomial(N,0.35)
        myx.append(numb)
        f.write(str(numb)+" ")
    
    f.close()
    

    hist = Create_Histogram(file_read)
    hist.Plot()


