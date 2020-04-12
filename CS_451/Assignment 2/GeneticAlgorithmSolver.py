from RouteManager import RouteManager
from Route import Route
import numpy 


class GeneticAlgorithmSolver:
    def __init__(self, cities, population_size=50, mutation_rate=0.2, tournament_size=10, elitism=False):
        self.cities = cities
        self.population_size = population_size
        self.mutation_rate = mutation_rate
        self.tournament_size = tournament_size
        self.elitism = elitism

    def evolve(self, routes:RouteManager):
        route = RouteManager(self.cities , routes.population_size)
        i_elitism = 0
        if(self.elitism):
            route.set_route(0 , routes.find_best_route())
            i_elitism = 1
        for i in range(i_elitism, route.population_size):
            p1 = self.tournament(routes)
            p2 = self.tournament(routes)
            child = self.crossover(p1,p2)
            route.set_route(i,child)
        for j in range(i_elitism, route.population_size):
            self.mutate(route.get_route(j))
        return route

    def crossover(self, r_1, r_2):
        child = Route(self.cities)
        s = int(len(r_1) * numpy.random.random())
        e = int(len(r_2) * numpy.random.random())
        for i in range(len(child)):
            if i < e and i > s and s < e:
                child.assign_city(i, r_1.get_city(i))
            elif s > e:
                if not (i > e and i < s):
                    child.assign_city(i, r_1.get_city(i))
        for j in range(len(r_2)):
            if not r_2.get_city(j) in child:
                for y in range(len(child)):
                    if child.get_city(y) == None:
                        child.assign_city(y, r_2.get_city(j))
                        break
        return child

    def mutate(self, route):
        for i_1 in range(len(route)):
            if numpy.random.random() < self.mutation_rate:
                i_2 = int(len(route) * numpy.random.random())
                c_1 = route.get_city(i_1)
                c_2 = route.get_city(i_2)
                route.assign_city(i_1, c_2)
                route.assign_city(i_2, c_1)
                
    def tournament(self, routes):
        tournament = RouteManager(self.cities, self.tournament_size)
        for i in range(self.tournament_size):
            randid = int(routes.population_size * numpy.random.random())
            tournament.set_route(i, routes.get_route(randid))
        best_fit = tournament.find_best_route()
        return best_fit
