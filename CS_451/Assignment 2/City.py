import numpy as np


class City:
    def __init__(self, x, y):
        self.UID = 0
        self.x = x
        self.y = y

    def calc_distance(self, other_city):
        return np.sqrt(np.square(np.abs(self.x - other_city.x)) + np.square(np.abs(self.y - other_city.y)))

    def set_uid(self, uid):
        self.UID = uid

    def __str__(self):
        return "City_{}({}, {})".format(self.UID, self.x, self.y)
