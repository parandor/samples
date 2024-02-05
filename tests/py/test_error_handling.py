# test_error_handling.py

class CustomError(Exception):
    pass

def divide_numbers(a, b):
    try:
        result = a / b
    except ZeroDivisionError as zde:
        # Intermediate Level: Handling ZeroDivisionError
        raise CustomError("Cannot divide by zero") from zde
    else:
        return result

def test_basic_error_handling():
    # Beginner Level: Basic Error Handling
    try:
        result = divide_numbers(10, 2)
        assert result == 5
    except Exception as e:
        assert False, f"Unexpected exception: {e}"

def test_custom_error_handling():
    # Intermediate Level: Custom Error Handling
    try:
        result = divide_numbers(10, 0)
        assert False, "Expected CustomError but no exception was raised."
    except CustomError as ce:
        assert str(ce) == "Cannot divide by zero"

def open_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
    except FileNotFoundError:
        # Intermediate Level: Handling FileNotFoundError
        raise CustomError(f"File not found: {file_path}")
    except Exception as e:
        raise CustomError(f"Error reading file: {file_path}") from e
    else:
        return content

def test_file_handling(tmpdir):
    # Intermediate Level: Test File Handling
    try:
        content = open_file(str(tmpdir / "nonexistent_file.txt"))
        assert False, "Expected CustomError but no exception was raised."
    except CustomError as ce:
        assert str(ce) == "File not found: " + str(tmpdir / "nonexistent_file.txt")

def advanced_function():
    raise RuntimeError("Advanced Error")

def test_advanced_error_handling():
    # Advanced Level: Handling Multiple Exceptions and Chaining
    try:
        advanced_function()
        assert False, "Expected RuntimeError but no exception was raised."
    except (ValueError, RuntimeError) as e:
        assert isinstance(e, RuntimeError)
        assert str(e) == "Advanced Error"
    except Exception as e:
        assert False, f"Unexpected exception: {e}"
