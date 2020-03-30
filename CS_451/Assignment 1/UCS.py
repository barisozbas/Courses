import queue as Q


class UCS:
    def __init__(self, graph, root):
        self.graph = graph
        self.visited = dict()
        self.queue = Q.PriorityQueue()
        self.counter = 0
        self.visited[root.UID] = root
        self.queue.put((0, root, root.UID)) 

    def run(self, target):
        while True :
            if(self.queue.empty()):
                break
            self.counter += 1
            depth, n, uid = self.queue.get()
            self.visited[n.UID] = n
            if n.is_equal(target):
                return True, self.counter, depth
            for nb in self.graph.reveal_neighbors(n):
                if nb.UID not in self.visited.keys():
                    nb.link = n
                    self.queue.put((depth + 1, nb, nb.UID))
        return False, 0, 0
