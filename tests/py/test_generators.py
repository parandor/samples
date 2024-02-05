# test_generators.py

# What is yield?
# yield is a special keyword used in Python within functions that allows them to become generators.
# Generators:
# Generators are a type of iterable, similar to lists or tuples, but they allow lazy, on-the-fly 
# generation of values.

# The primary benefit of generators is that they are memory-efficient, especially when dealing with 
# large datasets or infinite sequences.

# How yield Works:
# When a function contains the yield keyword, it is no longer an ordinary function. Instead, it 
# becomes a generator function.

# When the generator function is called, it returns a generator object. However, the code inside 
# the function is not executed immediately.

# The generator object is an iterator and can be iterated over using loops or functions like next().

# The first time the generator is iterated over, the function runs until it encounters the yield
# statement. At this point, the function's state is saved, and the yielded value is returned to the 
# caller.

# The function is then paused, and the next time the generator is iterated (using next()), it resumes 
# execution immediately after the yield statement.

# This process repeats each time the generator is iterated, allowing for the lazy evaluation of values.
    
def generate_numbers_up_to_n(n):
    # Intermediate Level: Basic Generator
    i = 0
    while i < n:
        yield i  # Yielding the current value of i
        i += 1

def test_generator_basic():
    # Usage: Generating a sequence of numbers up to a certain limit
    numbers_generator = generate_numbers_up_to_n(5)
    assert list(numbers_generator) == [0, 1, 2, 3, 4]

def test_generator_with_condition():
    # Usage: Generating even numbers within a range with a condition
    even_numbers_generator = (num for num in range(10) if num % 2 == 0)
    assert list(even_numbers_generator) == [0, 2, 4, 6, 8]

def fibonacci_generator():
    # Usage: Generating Fibonacci sequence indefinitely
    a, b = 0, 1
    while True:
        yield a  # Yielding the current value of a
        a, b = b, a + b

def test_infinite_generator():
    # Usage: Generating Fibonacci numbers one at a time
    fib_gen = fibonacci_generator()
    assert next(fib_gen) == 0
    assert next(fib_gen) == 1
    assert next(fib_gen) == 1
    assert next(fib_gen) == 2

def squares_generator(nums):
    # Usage: Generating squares of numbers from an external iterable
    for num in nums:
        yield num ** 2  # Yielding the square of the current number

def test_generator_with_external_data():
    # Usage: Generating squares of numbers from a list
    input_numbers = [1, 2, 3, 4, 5]
    squares_gen = squares_generator(input_numbers)
    assert list(squares_gen) == [1, 4, 9, 16, 25]

def filter_generator(nums, condition):
    # Usage: Generating numbers from an iterable based on a filtering condition
    for num in nums:
        if condition(num):
            yield num  # Yielding the current number if it meets the condition

def test_generator_with_function():
    # Usage: Generating numbers greater than 20 from a list using a condition function
    input_numbers = [10, 15, 20, 25, 30]
    condition_func = lambda x: x > 20
    filtered_gen = filter_generator(input_numbers, condition_func)
    assert list(filtered_gen) == [25, 30]
