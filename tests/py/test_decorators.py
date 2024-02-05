import pytest

# Test 1: Basic decorator
# Use Case: Logging, code instrumentation, or pre/post-processing around function calls.
# Decorators provide a clean way to extend or modify the behavior of functions.
def test_basic_decorator():
    def simple_decorator(func):
        def wrapper():
            print("Before function call")
            func()
            print("After function call")

        return wrapper

    @simple_decorator
    def say_hello():
        print("Hello!")

    say_hello()

# Test 2: Decorator with arguments
# Use Case: Configurable behavior around function calls, such as repetition or customization.
def test_decorator_with_arguments():
    def repeat_decorator(n):
        def decorator(func):
            def wrapper(*args, **kwargs):
                for _ in range(n):
                    func(*args, **kwargs)

            return wrapper

        return decorator

    @repeat_decorator(n=3)
    def print_message(message):
        print(message)

    print_message("Decorators are fun!")

# Test 3: Class-based decorator
# Use Case: More advanced behavior or state management. Class-based decorators allow for
# initialization and maintaining state across multiple function calls.
def test_class_based_decorator():
    class LogDecorator:
        def __init__(self, func):
            self.func = func

        def __call__(self, *args, **kwargs):
            print(f"Calling function: {self.func.__name__}")
            result = self.func(*args, **kwargs)
            print(f"Function result: {result}")
            return result

    @LogDecorator
    def multiply(a, b):
        return a * b

    assert multiply(4, 5) == 20

# Test 4: Decorator stacking
# Use Case: Composing multiple behaviors. Decorator stacking allows for combining
# different decorators to achieve complex functionality.
def test_decorator_stacking():
    def uppercase_decorator(func):
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            return result.upper()

        return wrapper

    def exclamation_decorator(func):
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            return f"{result}!"

        return wrapper

    @exclamation_decorator
    @uppercase_decorator
    def greet(name):
        return f"Hello, {name}"

    assert greet("John") == "HELLO, JOHN!"

# Test 5: Decorator with state
# Use Case: Tracking information across multiple calls. Decorators with state allow for
# maintaining information or counters related to the decorated function.
def test_decorator_with_state():
    def counter_decorator(func):
        def wrapper(*args, **kwargs):
            wrapper.calls += 1
            result = func(*args, **kwargs)
            return result

        wrapper.calls = 0
        return wrapper

    @counter_decorator
    def some_function():
        pass

    some_function()
    some_function()
    some_function()

    assert some_function.calls == 3
