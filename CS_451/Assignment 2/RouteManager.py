from Route import Route


class RouteManager:
    def __init__(self, cities, population_size):
        self.routes = list()
        self.cities = cities
        self.population_size = population_size

        for _ in range(population_size):
            route = Route(self.cities)
            route.generate_route()
            self.routes.append(route)

    def set_route(self, idx, new_route):
        self.routes[idx] = new_route

    def get_route(self, idx):
        return self.routes[idx]

    def find_best_route(self):
        best_route = None
        for i, _route in enumerate(self.routes):
            if i == 0:
                best_route = _route
            else:
                if _route.calc_fitness() >= best_route.calc_fitness(): #IT IS FIXED --> now it is trying to find better solution
                    best_route = _route

        return best_route

    def __len__(self):
        return len(self.routes)

    def __str__(self):
        _str = "\nRoute list:\n"
        for r in self.routes:
            _str += str(r) + "\n"
        best_route = self.find_best_route()
        _str += "Best route:\n{}\nBest Fitness:\n{}".format(best_route, best_route.calc_fitness())
        return _str
