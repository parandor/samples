# test_advanced_inheritance.py

class Vehicle:
    def __init__(self, brand, model):
        self.brand = brand
        self.model = model

    def get_info(self):
        return f"{self.brand} {self.model}"

class Engine:
    def __init__(self, fuel_type):
        self.fuel_type = fuel_type

    def start(self):
        return "Engine started"

    def stop(self):
        return "Engine stopped"

class Car(Vehicle, Engine):
    def __init__(self, brand, model, num_doors, fuel_type):
        Vehicle.__init__(self, brand, model)
        Engine.__init__(self, fuel_type)
        self.num_doors = num_doors

    def open_door(self):
        return "Door opened"

    def close_door(self):
        return "Door closed"

def test_car_info():
    car = Car("Toyota", "Camry", 4, "Gasoline")
    assert car.get_info() == "Toyota Camry"

def test_car_start_engine():
    car = Car("Toyota", "Camry", 4, "Gasoline")
    assert car.start() == "Engine started"

def test_car_stop_engine():
    car = Car("Toyota", "Camry", 4, "Gasoline")
    assert car.stop() == "Engine stopped"

def test_car_open_door():
    car = Car("Toyota", "Camry", 4, "Gasoline")
    assert car.open_door() == "Door opened"

def test_car_close_door():
    car = Car("Toyota", "Camry", 4, "Gasoline")
    assert car.close_door() == "Door closed"

class ElectricCar(Vehicle, Engine):
    def __init__(self, brand, model, num_doors):
        Vehicle.__init__(self, brand, model)
        Engine.__init__(self, "Electric")
        self.num_doors = num_doors
        self.battery_level = 100

    def charge(self):
        return "Charging battery"

    def get_battery_level(self):
        return self.battery_level

def test_electric_car_charge():
    electric_car = ElectricCar("Tesla", "Model S", 4)
    assert electric_car.charge() == "Charging battery"

def test_electric_car_start_engine():
    electric_car = ElectricCar("Tesla", "Model S", 4)
    assert electric_car.start() == "Engine started"

def test_electric_car_get_battery_level():
    electric_car = ElectricCar("Tesla", "Model S", 4)
    assert electric_car.get_battery_level() == 100

class HybridCar(Car, ElectricCar):
    def __init__(self, brand, model, num_doors):
        Car.__init__(self, brand, model, num_doors, "Hybrid")
        ElectricCar.__init__(self, brand, model, num_doors)
        self.petrol_tank_capacity = 50

    def refill_petrol(self):
        return "Petrol tank refilled"

    def get_petrol_tank_capacity(self):
        return self.petrol_tank_capacity

def test_hybrid_car_refill_petrol():
    hybrid_car = HybridCar("Toyota", "Prius", 4)
    assert hybrid_car.refill_petrol() == "Petrol tank refilled"

def test_hybrid_car_get_petrol_tank_capacity():
    hybrid_car = HybridCar("Toyota", "Prius", 4)
    assert hybrid_car.get_petrol_tank_capacity() == 50

def test_hybrid_car_start_engine():
    hybrid_car = HybridCar("Toyota", "Prius", 4)
    assert hybrid_car.start() == "Engine started"

def test_hybrid_car_get_battery_level():
    hybrid_car = HybridCar("Toyota", "Prius", 4)
    assert hybrid_car.get_battery_level() == 100
