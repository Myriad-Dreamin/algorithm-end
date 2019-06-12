

from cyaron import *

if __name__ == "__main__":
    io = IO(file_prefix="test")
    n = 300
    m = 60000
    graph = Graph.graph(n, m, directed=True, weight_limit=20)
    graph
    io.input_writeln([n, m])
    io.input_writeln(graph)

