from Graph import Graph
from Node import Node

from BFS import BFS
from DFS import DFS
from AStar import AStar
from UCS import UCS

from time import time
from math import sqrt

if __name__ == "__main__":
    print("Enter the grid size: ")
    N = int(input())
    G = Graph(N)

    print("Enter initial state: ")
    init_state = list()
    for _ in range(int(sqrt(N + 1))):
        init_state.append(list(map(int, input().split())))

    print("Enter goal state: ")
    goal_state = list()
    for _ in range(int(sqrt(N + 1))):
        goal_state.append(list(map(int, input().split())))

    root = Node(init_state, 0, list(), None)
    target = Node(goal_state, 0, list(), None)

    while True:
        print("\n-------Menu-------\n"
              "1. BFS\n"
              "2. DFS\n"
              "3. UCS\n"
              "4. A*\n"
              "5. Exit\n")

        opt = int(input())
        algorithm = None

        if opt == 1:
            algorithm = BFS(G, root)
        elif opt == 2:
            algorithm = DFS(G, root)
        elif opt == 3:
            algorithm = UCS(G, root)
        elif opt == 4:
            algorithm = AStar(G, root)
        elif opt == 5:
            break
        else:
            raise AssertionError("Invalid input for algorithm selection!")

        init_time = time()
        found, counter, step = algorithm.run(target)
        elapsed_time = time() - init_time

        if found:
            print("Match found!\n"
                  "Num. of visited nodes: {}\n"
                  "Depth of graph: {}".format(counter, step))
        else:
            print("Match not found!\n")
        print("Elapsed time: {} secs.".format(elapsed_time))
