import networkx as nx
import matplotlib.pyplot as plt


def file_to_matrix(filename):
    """Returns a matrix of the network file"""
   
    with open(filename) as infile:
       otpt = []
       for line in infile:
           prev_i = 0
           crnt_line = []
           for i in range(len(line)):
               if line[i] == ' ':
                   crnt_line.append(int(line[prev_i:i]))
                   prev_i = i+1
           otpt.append(crnt_line)              
       return otpt
   


def layers_num(matrix):
    """Returns the number of layers in the network given its matrix"""
    n = 0
    while(len(matrix[n]) != 0):
        n+=1
    return n
        
         
def matrix_to_graph(matrix):

    n = layers_num(matrix)
    
    net_graph = nx.DiGraph()
    
    layers = [[f'N({k}, {i}): {matrix[n+k+1][i]}' for i in range(matrix[k][0])] for k in range(n)]
    print(layers)
    for i in range(n):
         net_graph.add_nodes_from(layers[i], layer = i)
    
    for k in range(n-1):
        crnt_layer = matrix[k]
        num_neurons = crnt_layer[0]
        next_num_neurons = matrix[k+1][0]
        
        for i in range(num_neurons):     
            for j in range(next_num_neurons):
                net_graph.add_edge(layers[k][i],layers[k+1][j], weight = crnt_layer[2*(next_num_neurons*i+j)+1] )
        bias_name = f'NB({k}): {matrix[n+k+1][num_neurons]}'
        net_graph.add_node(bias_name, layer = k)
        for node in layers[k+1]:
            net_graph.add_edge(bias_name, node, weight = crnt_layer[num_neurons*next_num_neurons+1+2*j])
    return net_graph


def print_graph(G):
 
    pos = nx.multipartite_layout(G, subset_key="layer")
    plt.figure(figsize=(8, 8))
    labels = nx.get_edge_attributes(G,'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels = labels)
    nx.draw(G, pos, with_labels = True)
    plt.axis("equal")
    plt.show()
    

            
                
                
                
    
    
    
    