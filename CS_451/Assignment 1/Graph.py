from Node import Node


class Graph:
    def __init__(self, size):
        self.size = size

    @staticmethod
    def find_zero(node):
        for i in range(len(node.g_node)):
            for j in range(len(node.g_node[i])):
                if node.g_node[i][j] == 0:
                    return [i, j]
        return [-1, -1]

    def reveal_neighbors(self, node):
        children_lst = []
        x, y = self.find_zero(node)
        tmp_node = node.deep_copy()

        if x == 0 and y == 0:
            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif x == 0 and y == (len(node.g_node[x]) - 1):
            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif x == (len(node.g_node[y]) - 1) and y == 0:
            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif x == (len(node.g_node[y]) - 1) and y == (len(node.g_node[x]) - 1):
            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif 0 < x < len(node.g_node[y]) and y == 0:
            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            n1 = Node(tmp_node, node.step + 1, list(), None)
            children_lst.append(n1)
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif x == 0 and 0 < y < len(node.g_node[x]):
            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif 0 < x < len(node.g_node[y]) and y == (len(node.g_node[x]) - 1):
            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        elif x == (len(node.g_node[y]) - 1) and 0 < y < len(node.g_node[x]):
            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0
        else:
            tmp_node[x][y] = tmp_node[x - 1][y]
            tmp_node[x - 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x - 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y - 1]
            tmp_node[x][y - 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y - 1] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x][y + 1]
            tmp_node[x][y + 1] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x][y + 1] = tmp_node[x][y]
            tmp_node[x][y] = 0

            tmp_node[x][y] = tmp_node[x + 1][y]
            tmp_node[x + 1][y] = 0
            children_lst.append(Node(tmp_node, node.step + 1, list(), None))
            tmp_node[x + 1][y] = tmp_node[x][y]
            tmp_node[x][y] = 0

        return children_lst
