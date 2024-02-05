import pytest

# Test 1: Using **kwargs to capture additional keyword arguments
def test_kwargs_capture():
    def print_info(name, age, **kwargs):
        print(f"Name: {name}, Age: {age}")
        print("Additional Info:", kwargs)

    print_info("Alice", 25, city="Wonderland", occupation="Explorer")

# Test 2: Passing **kwargs through to another function
def test_kwargs_passing():
    def process_data(**kwargs):
        # Perform data processing here
        return kwargs

    def wrapper(**kwargs):
        result = process_data(**kwargs)
        assert result == kwargs  # Ensure that processed data matches original kwargs

    wrapper(name="Bob", age=30, occupation="Developer")

# Test 3: Using **kwargs to set default values
def test_kwargs_defaults():
    def create_person(name, age, **kwargs):
        person = {"name": name, "age": age}
        person.update(kwargs)  # Update with additional information from kwargs
        return person

    john = create_person("John", 28, city="New York", occupation="Designer")

    assert john == {"name": "John", "age": 28, "city": "New York", "occupation": "Designer"}

# Test 4: Using **kwargs for dynamic function behavior
def test_dynamic_behavior():
    def perform_operation(operator, **kwargs):
        if operator == "add":
            result = sum(kwargs.values())
        elif operator == "multiply":
            result = 1
            for value in kwargs.values():
                result *= value
        else:
            raise ValueError(f"Unsupported operator: {operator}")

        return result

    add_result = perform_operation("add", a=2, b=3, c=5)
    multiply_result = perform_operation("multiply", x=2, y=3, z=4)

    assert add_result == 10
    assert multiply_result == 24

# Test 5: Using **kwargs with named arguments
def test_named_arguments():
    def display_info(name, age, **extra_info):
        print(f"Name: {name}, Age: {age}")
        print("Extra Info:", extra_info)

    display_info("Charlie", 35, city="Paris", occupation="Chef")

# Test 6: Handling unknown keyword arguments
def test_unknown_kwargs():
    def process_data(**kwargs):
        # Assume we only want to process known keys
        allowed_keys = {"name", "age", "city"}
        valid_kwargs = {key: value for key, value in kwargs.items() if key in allowed_keys}

        return valid_kwargs

    result = process_data(name="Eva", age=27, city="Berlin", hobby="Painting")

    assert result == {"name": "Eva", "age": 27, "city": "Berlin"}

