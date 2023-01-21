import matplotlib.pyplot as plt


def readresults(filename):
    info = []
    generation = []
    loss = []
    with open(filename) as file:
        for line in file:
            if line.strip() == '':
                continue
            lst = line.split()
            if lst[0] != 'Generation:':
                info.append(lst[0])
            else:
                generation.append(int(lst[1]))
                loss.append(float(lst[3]))
    return info, generation, loss
            
def plot(filename):
    """
    Info:
        int n = 100; // number of networks
        double r = 10; // number of children per network
        double tests = 10; // number of test vectors per generation
        int n_in = 5; // size of input vectors
        int n_out = n_in; // size of output vectors (has to coincide with output of want_func!)
        int n_gen = 1000; // number of generations
        int print_every = 10; // prints average loss of generation every print_every-th generation
    """
    info, generation, loss = readresults(filename)
    
    plt.plot(generation, loss)
    plt.title(f'Number of networks: {info[0]}, number of inputs: {info[3]}')
    plt.xlabel('Generation')
    plt.ylabel('Average loss')
