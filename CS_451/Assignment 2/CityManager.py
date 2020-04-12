class CityManager:
    def __init__(self):
        self.city_lst = list()

    def add(self, city):
        self.city_lst.append(city)

    def __getitem__(self, index):
        return self.city_lst[index]

    def __len__(self):
        return len(self.city_lst)
