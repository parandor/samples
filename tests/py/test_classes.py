# test_classes.py

class Calculator:
    def add(self, a, b):
        return a + b

    def subtract(self, a, b):
        return a - b

def test_addition():
    calc = Calculator()
    result = calc.add(3, 4)
    assert result == 7

def test_subtraction():
    calc = Calculator()
    result = calc.subtract(8, 3)
    assert result == 5

class ShoppingCart:
    def __init__(self):
        self.items = []

    def add_item(self, item):
        self.items.append(item)

    def calculate_total(self):
        return sum(item['price'] for item in self.items)

def test_shopping_cart_add_item():
    cart = ShoppingCart()
    cart.add_item({'name': 'Product 1', 'price': 10})
    assert len(cart.items) == 1

def test_shopping_cart_total():
    cart = ShoppingCart()
    cart.add_item({'name': 'Product 1', 'price': 10})
    cart.add_item({'name': 'Product 2', 'price': 20})
    assert cart.calculate_total() == 30

class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author

    def get_info(self):
        return f"{self.title} by {self.author}"

def test_book_info():
    book = Book("Python Basics", "John Doe")
    assert book.get_info() == "Python Basics by John Doe"

class Student:
    def __init__(self, name, age, courses=None):
        self.name = name
        self.age = age
        self.courses = courses or []

    def enroll(self, course):
        self.courses.append(course)

    def get_course_list(self):
        return self.courses

def test_student_enroll():
    student = Student("Alice", 20)
    student.enroll("Mathematics")
    assert "Mathematics" in student.get_course_list()

def test_student_course_list():
    student = Student("Bob", 22, ["Physics", "Chemistry"])
    assert len(student.get_course_list()) == 2

class BankAccount:
    def __init__(self, balance=0):
        self.balance = balance

    def deposit(self, amount):
        self.balance += amount

    def withdraw(self, amount):
        if amount <= self.balance:
            self.balance -= amount
        else:
            print("Insufficient funds.")

def test_bank_account_deposit():
    account = BankAccount()
    account.deposit(100)
    assert account.balance == 100

def test_bank_account_withdraw():
    account = BankAccount(200)
    account.withdraw(50)
    assert account.balance == 150

def test_insufficient_funds():
    account = BankAccount(30)
    account.withdraw(40)
    assert account.balance == 30
