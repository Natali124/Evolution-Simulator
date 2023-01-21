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
    """RK: For now , the weight of the edges are not divided by 10 as the 
    drawing function did not seem to be able to display anything smaller than 1"""

    n = layers_num(matrix)
    
    net_graph = nx.DiGraph()
    
    layers = [[f'({k}, {i}): {matrix[n+k+1][i]}' for i in range(matrix[k][0])] for k in range(n)]
    for i in range(n):
         net_graph.add_nodes_from(layers[i], layer = i)
    
    for k in range(n-1):
        crnt_layer = matrix[k]
        num_neurons = crnt_layer[0]
        next_num_neurons = matrix[k+1][0]
        
        for i in range(num_neurons):     
            for j in range(next_num_neurons):
                net_graph.add_edge(layers[k][i],layers[k+1][j], weight = crnt_layer[2*(next_num_neurons*i+j)+1], activation = crnt_layer[2*(next_num_neurons*i+j)+2] )
        bias_name = f'B({k}): {matrix[n+k+1][num_neurons]}'
        net_graph.add_node(bias_name, layer = k)
        for node in layers[k+1]:
            net_graph.add_edge(bias_name, node, weight = crnt_layer[num_neurons*next_num_neurons+1+2*j], activation = crnt_layer[num_neurons*next_num_neurons+1+2*j+1])
    return net_graph


subset_color = [
    "gold",
    "violet",
    "limegreen",
    "darkorange",
]

def print_graph(G, filename = None):
 
    pos = nx.multipartite_layout(G, subset_key="layer")
    plt.figure(figsize=(10, 10))
    nodes_color = [subset_color[data["layer"]] for v, data in G.nodes(data=True)]
    edges_color = ['black' if not G[u][v]['activation'] else 'red' for u,v in G.edges]
    labels = nx.get_edge_attributes(G,'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels = labels)
    nx.draw(G, pos, node_color = nodes_color, edge_color=edges_color, with_labels = True, node_size = 500)
    plt.axis("equal")
    if filename is not None:
        plt.savefig(filename)
    plt.show()
    

    
def inpt_to_graph(filename, output = None):
    matrix = file_to_matrix(filename)
    G = matrix_to_graph(matrix)
    print_graph(G, output)

            
                
                
                
    
    
    
    