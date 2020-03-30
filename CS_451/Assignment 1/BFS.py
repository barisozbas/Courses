class BFS:
    def __init__(self, graph, root):
        self.graph = graph
        self.visited = dict()
        self.queue = list()
        self.counter = 0
        self.visited[root.UID] = root
        self.queue.append(root)

    def run(self, target):
        while len(self.queue) != 0:
            self.counter += 1
            n = self.queue.pop(0)
            if n.is_equal(target):
                return True, self.counter, n.step
            neighbors = self.graph.reveal_neighbors(n)
            for nb in neighbors:
                if nb.UID not in self.visited.keys():
                    nb.link = n
                    self.visited[nb.UID] = nb
                    self.queue.append(nb)
        return False, 0, 0
