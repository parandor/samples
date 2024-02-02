# Test Function 1: Simple function call
def add_numbers(a, b):
    return a + b

def test_simple_function_call():
    result = add_numbers(2, 3)
    assert result == 5

# Test Function 2: Parameter handling
def greet(name="Guest"):
    return f"Hello, {name}!"

def test_function_with_default_parameter():
    result = greet()
    assert result == "Hello, Guest!"

    result_with_name = greet("Alice")
    assert result_with_name == "Hello, Alice!"

# Test Function 3: Return values and assertions
def calculate_square_and_cube(x):
    return x ** 2, x ** 3

def test_function_return_values():
    square, cube = calculate_square_and_cube(3)
    assert square == 9
    assert cube == 27

# Test Function 4: Exception handling
def divide_numbers(a, b):
    try:
        result = a / b
        return result
    except ZeroDivisionError:
        return "Cannot divide by zero!"

def test_function_exception_handling():
    result = divide_numbers(10, 2)
    assert result == 5

    result_divide_by_zero = divide_numbers(5, 0)
    assert result_divide_by_zero == "Cannot divide by zero!"

# Test Function 5: Higher-order functions
def multiply_by(factor):
    def multiply(x):
        return x * factor
    return multiply

def test_higher_order_function():
    double = multiply_by(2)
    triple = multiply_by(3)

    result_double = double(5)
    result_triple = triple(4)

    assert result_double == 10
    assert result_triple == 12
