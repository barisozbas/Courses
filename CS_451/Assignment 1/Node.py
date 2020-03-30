class Node:
    def __init__(self, node, step, g_node, link):
        self.UID = ""
        self.step = step
        self.node = node
        self.distance_top = 0
        self.distance = 0
        self.g_node = g_node
        self.link = link
        self.init_node(node, g_node)

    def init_node(self, node, g_node):
        for i in range(len(node)):
            g_node.append([])
            for j in range(len(node[i])):
                g_node[i].append(node[i][j])
                self.UID += str(node[i][j])

    def is_equal(self, other):
        return self.UID == other.UID

    def deep_copy(self):
        node = []
        for i in range(len(self.g_node)):
            node.append([])
            for j in range(len(self.g_node[i])):
                node[i].append(self.g_node[i][j])
        return node

    def __str__(self):
        s = ""
        for i in range(len(self.g_node)):
            s += self.g_node[i] + "\n"
        return s

    def __gt__(self, other):
        return self.distance_top > other.distance_top

    def __lt__(self, other):
        return self.distance_top < other.distance_top

    def __eq__(self, other):
        return self.distance_top == other.distance_top
