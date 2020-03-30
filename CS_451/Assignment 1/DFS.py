class DFS:
    def __init__(self, graph, root):
        self.graph = graph
        self.visited = dict()
        self.stack = list()
        self.stack.append(root)
        self.counter = 0

    def run(self, target):
        while len(self.stack) != 0:
            self.counter += 1
            init_node = self.stack.pop(len(self.stack) - 1)
            if init_node.UID not in self.visited.keys():
                self.visited[init_node.UID] = init_node
                if init_node.is_equal(target):
                    return True, self.counter, init_node.step
                for nb in self.graph.reveal_neighbors(init_node):
                    nb.link = init_node
                    self.stack.append(nb)
        return False, 0, 0
