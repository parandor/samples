# test_list_comprehensions.py

def test_basic_list_comprehension():
    # Beginner Level: Basic List Comprehension
    squares = [x**2 for x in range(5)]
    # For each x in the range from 0 to 4 (inclusive), calculate x squared and create a list.
    assert squares == [0, 1, 4, 9, 16]

def test_list_comprehension_with_condition():
    # Intermediate Level: List Comprehension with Condition
    even_squares = [x**2 for x in range(10) if x % 2 == 0]
    # For each x in the range from 0 to 9, include x squared in the list only if x is even.
    assert even_squares == [0, 4, 16, 36, 64]

def test_nested_list_comprehension():
    # Intermediate Level: Nested List Comprehension
    matrix = [[i+j for j in range(3)] for i in range(3)]
    # Create a nested list where each element is the sum of i and j, for i and j in the specified ranges.
    assert matrix == [[0, 1, 2], [1, 2, 3], [2, 3, 4]]

def test_list_comprehension_with_expression():
    # Intermediate Level: List Comprehension with Expression
    powers_of_two = [2**x for x in range(5)]
    # For each x in the range from 0 to 4, calculate 2 to the power of x and create a list.
    assert powers_of_two == [1, 2, 4, 8, 16]

def test_advanced_list_comprehension():
    # Advanced Level: List Comprehension with Multiple Conditions and Expression
    filtered_numbers = [x**2 for x in range(10) if x % 2 == 0 if x > 4]
    # For each x in the range from 0 to 9, include x squared in the list only if x is even and greater than 4.
    assert filtered_numbers == [36, 64]

    # Additional test for advanced usage
    nested_conditions = [(x, y) for x in range(5) if x > 2 for y in range(3) if y < 2]
    # Create a list of tuples where each tuple contains x and y, satisfying specified conditions for x and y.
    assert nested_conditions == [(3, 0), (3, 1), (4, 0), (4, 1)]
