# Test 1: If-elif-else statement with multiple conditions
def test_if_elif_else_statement():
    x = 10
    if x > 15:
        assert "Greater than 15"
    elif 5 < x <= 15:
        assert "Between 5 and 15"
    else:
        assert "Not greater than 15 and not between 5 and 15"

# Test 2: For loop with a conditional break
def test_for_loop_with_conditional_break():
    numbers = [4, 2, 3, 4, 5, 6]
    result = 0
    for num in numbers:
        if num % 2 == 0:
            result += num
        else:
            break
    assert result == 6

# Test 3: While loop with an else block
def test_while_loop_with_else():
    count = 0
    total = 0
    while count < 10:
        total += count
        count += 1
    else:
        total *= 2
    assert total == 90

# Test 4: List comprehension with multiple conditions
def test_list_comprehension_with_multiple_conditions():
    numbers = [1, 2, 3, 4, 5]
    squared_numbers = [num ** 2 if num % 2 == 0 else num ** 3 for num in numbers if num > 2]
    assert squared_numbers == [27, 16, 125]

# Test 5: Nested exception handling with multiple exceptions
def test_nested_exception_handling():
    def divide_numbers(a, b):
        try:
            result = a / b
            return result
        except ZeroDivisionError:
            return "Cannot divide by zero!"
        except (TypeError, ValueError):
            return "Type or value error occurred!"

    assert divide_numbers(10, 2) == 5
    assert divide_numbers(5, 0) == "Cannot divide by zero!"
    assert divide_numbers("abc", 2) == "Type or value error occurred!"
