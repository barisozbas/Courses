import numpy as np


class Route:
    def __init__(self, cities):
        self.fitness = 0.0
        self.total_distance = 0.0
        self.cities = cities
        self.route = list()

        for i in range(len(self.cities)):
            self.route.append(None)

    def generate_route(self):
        for i in range(len(self.route)):
            self.cities[i].UID = i
            self.assign_city(i, self.cities[i])
        np.random.shuffle(self.route)

    def calc_route_distance(self):
        if self.total_distance == 0:
            for i in range(len(self.route)):
                arrival = self.route[i]
                if i+1 < len(self.route):
                    destination = self.route[i+1]
                else:
                    destination = self.route[0]
                self.total_distance += arrival.calc_distance(destination)
        return self.total_distance

    def calc_fitness(self):
        if self.fitness == 0:
            self.fitness = 1.0 / self.calc_route_distance()
        return self.fitness

    def get_city(self, idx):
        return self.route[idx]

    def assign_city(self, idx, city):
        self.route[idx] = city
        self.fitness = 0
        self.total_distance = 0

    def __len__(self):
        return len(self.route)

    def __contains__(self, city):
        return city in self.route

    def __str__(self):
        _str = "\nRoute:\n"
        for i, v in enumerate(self.route):
            if i == len(self.route) - 1:
                _str += str(v)
            else:
                _str += str(v) + " --> "
        return _str
