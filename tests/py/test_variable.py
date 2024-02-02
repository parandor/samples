# test_variable_usage.py

def test_simple_variable_assignment():
    my_variable = 42
    assert my_variable == 42

def test_variable_reassignment_and_arithmetic():
    x = 5
    y = 10
    x = x + y
    assert x == 15

def test_string_concatenation():
    first_name = "John"
    last_name = "Doe"
    full_name = first_name + " " + last_name
    assert full_name == "John Doe"

def test_variables_in_list():
    a = 1
    b = 2
    my_list = [a, b, a + b]
    assert my_list == [1, 2, 3]

def test_advanced_variable_usage():
    student_info = {
        'name': 'Alice',
        'age': 25,
        'grades': {'math': 90, 'english': 85, 'history': 88}
    }

    formatted_info = "{} is {} years old and scored {} in Math.".format(
        student_info['name'], student_info['age'], student_info['grades']['math']
    )

    assert formatted_info == "Alice is 25 years old and scored 90 in Math."

# test_variable_usage.py

def test_advanced_variable_usage():
    # Complex data structure
    student_info = {
        'name': 'Alice',
        'age': 25,
        'grades': {'math': 90, 'english': 85, 'history': 88}
    }

    # Accessing nested data
    math_score = student_info['grades']['math']
    assert math_score == 90

    # Using an f-string for formatting
    formatted_info = f"{student_info['name']} is {student_info['age']} years old and scored {math_score} in Math."
    assert formatted_info == "Alice is 25 years old and scored 90 in Math."

    # List comprehension
    numbers = [1, 2, 3, 4, 5]
    squared_numbers = [num ** 2 for num in numbers]
    assert squared_numbers == [1, 4, 9, 16, 25]

    # Lambda function
    square = lambda x: x ** 2
    squared_number = square(4)
    assert squared_number == 16

    # Tuple unpacking
    coordinates = (3, 7)
    x, y = coordinates
    assert x == 3
    assert y == 7

    # Set operations
    set1 = {1, 2, 3, 4}
    set2 = {3, 4, 5, 6}
    intersection = set1.intersection(set2)
    assert intersection == {3, 4}