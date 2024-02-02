# Test 1: Integer arithmetic
def test_integer_arithmetic():
    result = 5 + 3 * 2 - 1
    assert result == 10

# Test 2: Floating-point arithmetic
def test_float_arithmetic():
    result = 10.5 / 2 + 3.2
    assert result == 8.45

# Test 3: String manipulation
def test_string_manipulation():
    greeting = "Hello, World!"
    uppercased = greeting.upper()
    lowercased = greeting.lower()
    assert uppercased == "HELLO, WORLD!"
    assert lowercased == "hello, world!"

# Test 4: Boolean operations
def test_boolean_operations():
    is_true = True
    is_false = False
    result_and = is_true and is_false
    result_or = is_true or is_false
    result_not = not is_false
    assert result_and is False
    assert result_or is True
    assert result_not is True

# Test 5: List manipulation and slicing
def test_list_manipulation_and_slicing():
    numbers = [1, 2, 3, 4, 5]
    numbers.append(6)
    numbers.extend([7, 8])
    numbers.pop(2)
    sliced_numbers = numbers[1:4]
    assert numbers == [1, 2, 4, 5, 6, 7, 8]
    assert sliced_numbers == [2, 4, 5]

# Test 6: Dictionary operations
def test_dictionary_operations():
    person = {"name": "Alice", "age": 25, "city": "Wonderland"}
    person["gender"] = "Female"
    age = person.pop("age")
    keys = list(person.keys())
    values = list(person.values())
    assert person == {"name": "Alice", "city": "Wonderland", "gender": "Female"}
    assert age == 25
    assert keys == ["name", "city", "gender"]
    assert values == ["Alice", "Wonderland", "Female"]

# Test 7: Bitwise operators
def test_bitwise_operators():
    num1 = 0b1010  # Binary representation of 10
    num2 = 0b1100  # Binary representation of 12

    bitwise_and = num1 & num2
    bitwise_or = num1 | num2
    bitwise_xor = num1 ^ num2
    bitwise_not_num1 = ~num1
    left_shift = num1 << 2
    right_shift = num2 >> 1

    assert bitwise_and == 8  # Binary: 0b1000
    assert bitwise_or == 14   # Binary: 0b1110
    assert bitwise_xor == 6   # Binary: 0b0110
    assert bitwise_not_num1 == -11  # Binary: 0b...11110101 (negative due to two's complement)
    assert left_shift == 40   # Binary: 0b1010000
    assert right_shift == 6   # Binary: 0b0000110
