import queue as Q


class AStar:
    def __init__(self, graph, root):
        self.graph = graph
        self.root = root
        self.visited = dict()
        self.queue = Q.PriorityQueue()
        self.counter = 0

    def run(self, target):
        self.queue.put((self.manhattan_distance(self.root, target), 0, self.root, self.root.UID))
        while True:
            if(self.queue.empty()):
                break
            self.counter += 1
            cost, depth, n, uid = self.queue.get()
            if n.is_equal(target):
                return True, self.counter, depth
            for nb in self.graph.reveal_neighbors(n):
                if nb.UID not in self.visited.keys():
                    nb.link = n
                    self.queue.put( ( cost + self.manhattan_distance(nb, target) + 1  , depth + 1, nb , nb.UID))        
        return False, 0, 0

    def manhattan_distance(self, n, end):
        arr = [0] * (self.graph.size + 1)
        brr = [0] * (self.graph.size + 1)
        for i in range(len(n.g_node)):
            for j in range(len(n.g_node[i])):
                arr[n.g_node[i][j]] = [i, j]

        for i in range(len(end.g_node)):
            for j in range(len(end.g_node[i])):
                brr[end.g_node[i][j]] = [i, j]
        dist = 0
        for i in range(1, len(arr)):
            dist += abs(arr[i][0] - brr[i][0]) + abs(arr[i][1] - brr[i][1])
        return dist
