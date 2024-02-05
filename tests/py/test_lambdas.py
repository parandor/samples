import pytest

# Test 1: Basic lambda function
def test_basic_lambda():
    add = lambda x, y: x + y
    assert add(2, 3) == 5

# Test 2: Using lambda with built-in functions
def test_filter_lambda():
    numbers = [1, 2, 3, 4, 5, 6]
    even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
    assert even_numbers == [2, 4, 6]

# Test 3: Lambda in a list comprehension
def test_map_lambda():
    numbers = [1, 2, 3, 4, 5]
    squared_numbers = list(map(lambda x: x**2, numbers))
    assert squared_numbers == [1, 4, 9, 16, 25]

# Test 4: Using lambda for sorting
def test_sort_lambda():
    names = ["Alice", "Bob", "Charlie", "David"]
    sorted_names = sorted(names, key=lambda x: len(x))
    assert sorted_names == ["Bob", "Alice", "David", "Charlie"]

# Test 5: Advanced usage with higher-order functions
def test_higher_order_lambda():
    def multiplier(factor):
        return lambda x: x * factor

    double = multiplier(2)
    triple = multiplier(3)

    assert double(5) == 10
    assert triple(5) == 15

# Test 6: Using lambda to create closures
def test_lambda_closure():
    def outer_function(power):
        return lambda x: x ** power

    square = outer_function(2)
    cube = outer_function(3)

    assert square(4) == 16
    assert cube(3) == 27

# Test 7: Lambda with conditional expression
def test_lambda_conditional():
    absolute_value = lambda x: x if x >= 0 else -x

    assert absolute_value(5) == 5
    assert absolute_value(-3) == 3

# Test 8: Combining lambdas in a higher-order function
def test_combining_lambdas():
    def combine_functions(f, g):
        return lambda x: f(g(x))

    double = lambda x: x * 2
    square = lambda x: x ** 2

    double_then_square = combine_functions(square, double)

    assert double_then_square(3) == 36
