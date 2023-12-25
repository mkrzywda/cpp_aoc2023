from collections import defaultdict
import sys
from networkx import minimum_edge_cut, connected_components, Graph

# Check if the correct number of command-line arguments is provided
if len(sys.argv) != 2:
    print("Usage: python script.py [path_to_file]")
    sys.exit(1)

path_to_file = sys.argv[1]

# Read the input file
with open(path_to_file, "r") as text_file:
    lines = [list(map(str.strip, line.split(': '))) for line in text_file.readlines()]
    lines = {line[0]: line[1].split(' ') for line in lines}

connections = defaultdict(list)
for k, v in lines.items():
    for m in v:
        connections[k].append(m)
        connections[m].append(k)

# Part 1
graph = Graph()
for n, cs in connections.items():
    for c in cs:
        graph.add_edge(n, c, capacity=1)
        graph.add_edge(c, n, capacity=1)

edges_to_remove = minimum_edge_cut(graph)
graph.remove_edges_from(edges_to_remove)
comp1, comp2 = list(connected_components(graph))
resp1 = len(comp1) * len(comp2)
print("Part 1: {}".format(resp1))

# Part 2
resp2 = "Got 50 stars!!!! See you next year!"
print("Part 2: {}".format(resp2))
