from City import City
from CityManager import CityManager
from RouteManager import RouteManager
from GeneticAlgorithmSolver import GeneticAlgorithmSolver


if __name__ == '__main__':
    cm = CityManager()
    c1 = City(60, 200)
    cm.add(c1)
    c2 = City(180, 200)
    cm.add(c2)
    c3 = City(80, 180)
    cm.add(c3)
    c4 = City(140, 180)
    cm.add(c4)
    c5 = City(20, 160)
    cm.add(c5)
    c6 = City(100, 160)
    cm.add(c6)
    c7 = City(200, 160)
    cm.add(c7)
    c8 = City(140, 140)
    cm.add(c8)
    c9 = City(40, 120)
    cm.add(c9)
    c10 = City(100, 120)
    cm.add(c10)
    c11 = City(180, 100)
    cm.add(c11)
    c12 = City(60, 80)
    cm.add(c12)
    c13 = City(120, 80)
    cm.add(c13)
    c14 = City(180, 60)
    cm.add(c14)
    c15 = City(20, 40)
    cm.add(c15)
    c16 = City(100, 40)
    cm.add(c16)
    c17 = City(200, 40)
    cm.add(c17)
    c18 = City(20, 20)
    cm.add(c18)
    c19 = City(60, 20)
    cm.add(c19)
    c20 = City(160, 20)
    cm.add(c20)

    rm = RouteManager(cm, 50)

    print(rm.find_best_route().calc_route_distance())

    gas = GeneticAlgorithmSolver(cm, 50)

    rm = gas.evolve(rm)
    for i in range(100):
        rm = gas.evolve(rm)

    print(rm.find_best_route().calc_route_distance())

    print(rm.find_best_route())
